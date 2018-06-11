// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "vm.h"

bonobo_stack_entry_t *bonobo_stack_top(bonobo_vm_t *vm) {
    bonobo_stack_t *stack = &vm->stack;
    return &stack->entries[stack->index];
}

bonobo_stack_entry_t *bonobo_stack_pop(bonobo_vm_t *vm) {
    bonobo_stack_t *stack = &vm->stack;
    bonobo_stack_entry_t *entry = bonobo_stack_top(vm);
    if (stack->index > 0) stack->index--;
    return entry;
}

int bonobo_stack_push(bonobo_vm_t *vm, bonobo_object_t *data) {
    bonobo_stack_t *stack = &vm->stack;
    if (stack->index >= stack->size)
        return EXIT_FAILURE;

    bonobo_object_t *object = (bonobo_object_t *) bonobo_vm_allocate(vm, sizeof(bonobo_object_t));
    memcpy(object, data, sizeof(bonobo_object_t));

    size_t index = stack->index++;
    bonobo_vm_deallocate(vm, stack->entries[index].data);
    stack->entries[index].data = object;
    return EXIT_SUCCESS;
}