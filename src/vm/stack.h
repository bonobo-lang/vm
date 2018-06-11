// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_STACK_H
#define BONOBO_STACK_H

#include <bonobo.h>
#include <stddef.h>

typedef struct
{
    bonobo_object_t *data;
} bonobo_stack_entry_t;

typedef struct
{
    bonobo_stack_entry_t *entries;
    size_t size, index;
} bonobo_stack_t;

bonobo_stack_entry_t *bonobo_stack_top(bonobo_vm_t *vm);

bonobo_stack_entry_t *bonobo_stack_pop(bonobo_vm_t *vm);

int bonobo_stack_push(bonobo_vm_t *vm, bonobo_object_t *data);

#endif //BONOBO_STACK_H
