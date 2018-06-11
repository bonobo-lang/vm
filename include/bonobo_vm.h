// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_BONOBO_VM_H
#define BONOBO_BONOBO_VM_H

#include <stddef.h>

struct _bonobo_vm;
typedef struct _bonobo_vm bonobo_vm_t;

typedef void *(*BonoboHeapAllocator)(size_t size);

typedef void (*BonoboHeapDeallocator)(void *ptr);

typedef void (*BonoboUndefinedFunctionHandler)(char *name, void *state);

bonobo_vm_t *bonobo_vm_new_with_allocator(BonoboHeapAllocator allocator);

void bonobo_vm_destroy_with_deallocator(bonobo_vm_t *vm, BonoboHeapDeallocator deallocator);

bonobo_vm_t *bonobo_vm_new();

void bonobo_vm_destroy(bonobo_vm_t *vm);

void bonobo_vm_set_allocator(bonobo_vm_t *vm, BonoboHeapAllocator allocator);

void bonobo_vm_set_deallocator(bonobo_vm_t *vm, BonoboHeapDeallocator deallocator);

void bonobo_vm_set_undefined_function_handler(bonobo_vm_t *vm, BonoboUndefinedFunctionHandler handler, void *state);

void bonobo_vm_set_stack_size(bonobo_vm_t *vm, size_t size);

void *bonobo_vm_allocate(bonobo_vm_t *vm, size_t size);

void bonobo_vm_deallocate(bonobo_vm_t *vm, void *ptr);

void bonobo_vm_boot(bonobo_vm_t *vm);

void bonobo_vm_shutdown(bonobo_vm_t *vm);

#endif //BONOBO_BONOBO_VM_H
