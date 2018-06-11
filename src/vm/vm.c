// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <string.h>
#include "vm.h"
#include "stack.h"
#include "memory.h"

bonobo_vm_t *bonobo_vm_new_with_allocator(BonoboHeapAllocator allocator) {
    bonobo_vm_t *vm = (bonobo_vm_t *) allocator(sizeof(bonobo_vm_t));

    if (vm != NULL) {
        vm->allocator = allocator;
        vm->deallocator = &free;
        vm->ffi = NULL;
        vm->scope = (bonobo_scope_t *) allocator(sizeof(bonobo_scope_t));
        vm->scope->blocks = NULL;
        vm->scope->parent = NULL;
        vm->stack.index = 0;
        vm->stack.size = 255;
        vm->undefined_function_handler = NULL;
    }

    return vm;
}

void bonobo_vm_destroy_with_deallocator(bonobo_vm_t *vm, BonoboHeapDeallocator deallocator) {
    if (vm != NULL) {
        deallocator(vm);
    }
}

bonobo_vm_t *bonobo_vm_new() {
    return bonobo_vm_new_with_allocator(&malloc);
}

void bonobo_vm_destroy(bonobo_vm_t *vm) {
    bonobo_vm_destroy_with_deallocator(vm, vm->deallocator);
}

void bonobo_vm_set_allocator(bonobo_vm_t *vm, BonoboHeapAllocator allocator) {
    vm->allocator = allocator;
}

void bonobo_vm_set_deallocator(bonobo_vm_t *vm, BonoboHeapDeallocator deallocator) {
    vm->deallocator = deallocator;
}

void bonobo_vm_set_undefined_function_handler(bonobo_vm_t *vm, BonoboUndefinedFunctionHandler handler, void *state) {
    vm->undefined_function_handler = handler;
    vm->undefined_function_handler_state = state;
}

void *bonobo_vm_allocate(bonobo_vm_t *vm, size_t size) {
    void *ptr = vm->allocator(size);

    if (ptr != NULL) {
        if (vm->scope->blocks == NULL) {
            bonobo_scope_block_t *block = vm->scope->blocks = (bonobo_scope_block_t *) vm->allocator(
                    sizeof(bonobo_scope_block_t));
            block->next = NULL;
            block->ptr = ptr;
        } else {
            bonobo_scope_block_t *block = vm->scope->blocks;
            while (block->next != NULL) block = block->next;
            block = block->next = (bonobo_scope_block_t *) vm->allocator(sizeof(bonobo_scope_block_t));
            block->next = NULL;
            block->ptr = ptr;
        }
    }

    return ptr;
}

void bonobo_vm_deallocate(bonobo_vm_t *vm, void *ptr) {
    if (vm->scope->blocks != NULL) {
        bonobo_scope_block_t *block = vm->scope->blocks;

        while (block != NULL) {
            if (block->ptr == ptr) block->ptr = NULL;
            block = block->next;
        }
    }

    if (ptr != NULL)
        vm->deallocator(ptr);
}

void bonobo_vm_set_stack_size(bonobo_vm_t *vm, size_t size) {
    vm->stack.size = size;
}

void bonobo_vm_boot(bonobo_vm_t *vm) {
    vm->stack.entries = (bonobo_stack_entry_t *) vm->allocator(vm->stack.size * sizeof(bonobo_stack_entry_t));

    for (size_t i = 0; i < vm->stack.size; i++)
        vm->stack.entries[i].data = NULL;
}

void bonobo_vm_shutdown(bonobo_vm_t *vm) {
    for (size_t i = 0; i < vm->stack.size; i++)
        vm->deallocator(vm->stack.entries[i].data);

    vm->deallocator(vm->stack.entries);
}