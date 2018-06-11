// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include "memory.h"
#include "vm.h"

void bonobo_vm_enter_scope(bonobo_vm_t *vm) {
    bonobo_scope_t *scope = (bonobo_scope_t *) vm->allocator(sizeof(bonobo_scope_t));

    if (scope != NULL) {
        scope->blocks = NULL;
        scope->parent = vm->scope;
        vm->scope = scope;
    }
}

void bonobo_vm_exit_scope(bonobo_vm_t *vm) {
    if (vm->scope->parent != NULL) {
        bonobo_scope_t *scope = vm->scope;
        bonobo_scope_block_t *block = scope->blocks;

        while (block != NULL) {
            bonobo_scope_block_t *b = block;
            if (b->ptr != NULL) vm->deallocator(b->ptr);
            block = b->next;
            vm->deallocator(b);
        }

        vm->scope = scope->parent;
        vm->deallocator(scope);
    }
}