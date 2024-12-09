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

#include "client.h"
#include "server.h"
#include "slot.h"
#include "slots.h"
#include "utils.h"
#include "worker.h"

namespace lf {
namespace server {

bool
Client::slotz()
{
    std::string s = std::string(or_empty(param("add_special")));
    int id = atoi(s.c_str());
    if (id < 0)
        return send_error(400);
    if (id >= worker_->server_->slots_->size())
        return send_error(404);
    Slot* slot = worker_->server_->slots_->slots_[id].get();
    std::string dump;
    slot->dump(&dump);
    char* p = append_http_response_message(obuf_.p, 200);
    p = stpcpy(p, "Content-Type: text/plain\r\n");
    return send_response(obuf_.p, p, dump);
}

} // namespace server
} // namespace lf
