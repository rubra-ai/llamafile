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

#pragma once
#include <pthread.h>

class Lockable {
  public:
    Lockable() {
        if (pthread_mutex_init(&lock_, nullptr))
            __builtin_trap();
    }

    virtual ~Lockable() {
        if (pthread_mutex_destroy(&lock_))
            __builtin_trap();
    }

    void lock() {
        if (pthread_mutex_lock(&lock_))
            __builtin_trap();
    }

    void unlock() {
        if (pthread_mutex_unlock(&lock_))
            __builtin_trap();
    }

  private:
    pthread_mutex_t lock_;
};
