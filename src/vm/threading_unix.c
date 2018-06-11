// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef WIN32

#include <pthread.h>
#include "threading.h"
#include "vm.h"

typedef struct
{
    bonobo_vm_t *vm;
    void *state;
    BonoboThreadEntryPoint entry_point;
} bonobo_thread_state_t;

void *bonobo_thread_main(void *ptr) {
    bonobo_thread_state_t *state = (bonobo_thread_state_t *) ptr;
    state->entry_point(state->vm, state->state);
    return ptr;
}

void *bonobo_thread_fork(bonobo_vm_t *vm, BonoboThreadEntryPoint entry_point, void *state) {
    pthread_t *thread = (pthread_t *) vm->allocator(sizeof(pthread_t));
    bonobo_thread_state_t thread_state;
    thread_state.vm = vm;
    thread_state.state = state;
    thread_state.entry_point = entry_point;

    int result = pthread_create(thread, NULL, &bonobo_thread_main, &thread_state);
    if (result != 0) return NULL;//(void *) result;
    return thread;
}

void bonobo_thread_detach(void *thread) {
    pthread_detach(thread);
}

void bonobo_thread_join(void *thread) {
    pthread_join(thread, NULL);
}

#endif