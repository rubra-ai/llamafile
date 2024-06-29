// -*- mode:c++;indent-tabs-mode:nil;c-basic-offset:4;coding:utf-8 -*-
// vi: set et ft=cpp ts=4 sts=4 sw=4 fenc=utf-8 :vi
//
// Copyright 2024 Mozilla Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <assert.h>
#include <third_party/dlmalloc/dlmalloc.h>
#include <tool/args/args.h>

#include "llama.cpp/llama.h"
#include "llamafile/llamafile.h"
#include "llamafile/version.h"

#include "json.h"
#include "log.h"
#include "server.h"
#include "signals.h"
#include "time.h"

Server* g_server;
llama_model* g_model;

int
main(int argc, char* argv[])
{
    llamafile_check_cpu();
    if (llamafile_has(argv, "--version")) {
        puts("llamafile-server v" LLAMAFILE_VERSION_STRING);
        exit(0);
    }

    // get config
    LoadZipArgs(&argc, &argv);
    llamafile_get_flags(argc, argv);
    time_init();

    // load model
    llama_model_params mparams = {
        .n_gpu_layers = FLAG_n_gpu_layers,
        .split_mode = (enum llama_split_mode)FLAG_split_mode,
        .main_gpu = FLAG_main_gpu,
        .tensor_split = nullptr,
        .rpc_servers = nullptr,
        .progress_callback = nullptr,
        .progress_callback_user_data = nullptr,
        .kv_overrides = nullptr,
        .vocab_only = true,
        .use_mmap = true,
        .use_mlock = false,
        .check_tensors = false,
    };
    g_model = llama_load_model_from_file(FLAG_model, mparams);

    // create server
    if (FLAG_workers <= 0)
        FLAG_workers = __get_cpu_count();
    if (FLAG_workers <= 0)
        FLAG_workers = 16;
    set_thread_name("server");
    g_server = new Server(create_listening_socket(FLAG_listen));
    for (int i = 0; i < FLAG_workers; ++i)
        unassert(!g_server->spawn());

    // run server
    setup_signals();
    g_server->run();
    restore_signals();

    // shutdown server
    LOG("shutdown");
    g_server->shutdown();
    g_server->close();
    delete g_server;
    llama_free_model(g_model);
    LOG("exit");

    // // quality assurance
    // CheckForMemoryLeaks();
}
