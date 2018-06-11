// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_THREADING_H
#define BONOBO_THREADING_H

#include <bonobo.h>

typedef void (*BonoboThreadEntryPoint)(bonobo_vm_t *vm, void *state);

void *bonobo_thread_fork(bonobo_vm_t *vm, BonoboThreadEntryPoint entry_point, void *state);

void bonobo_thread_detach(void *thread);

void bonobo_thread_join(void *thread);

#endif //BONOBO_THREADING_H
