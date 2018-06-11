// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_MEMORY_H
#define BONOBO_MEMORY_H

#include <bonobo.h>

struct _bonobo_scope;
typedef struct _bonobo_scope bonobo_scope_t;


typedef struct _bonobo_scope_block
{
    void *ptr;
    struct _bonobo_scope_block *next;
} bonobo_scope_block_t;

struct _bonobo_scope
{
    struct _bonobo_scope *parent;
    bonobo_scope_block_t *blocks;
};

void bonobo_vm_enter_scope(bonobo_vm_t *vm);

void bonobo_vm_exit_scope(bonobo_vm_t *vm);

#endif //BONOBO_MEMORY_H
