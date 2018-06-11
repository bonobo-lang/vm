// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_VM_H
#define BONOBO_VM_H

#include <bonobo.h>
#include <stdlib.h>
#include "ffi.h"
#include "memory.h"
#include "stack.h"

struct _bonobo_vm
{
    BonoboHeapAllocator allocator;
    BonoboHeapDeallocator deallocator;
    bonobo_ffi_entry_t *ffi;
    bonobo_scope_t *scope;
    bonobo_stack_t stack;
    BonoboUndefinedFunctionHandler undefined_function_handler;
    void *undefined_function_handler_state;
};

#endif //BONOBO_VM_H
