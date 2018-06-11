// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_FFI_H
#define BONOBO_FFI_H

#include <bonobo.h>

struct _bonobo_ffi_arguments
{
    bonobo_vm_t *vm;
    size_t number_of_arguments;
    bonobo_object_t *arguments;
    bonobo_object_t return_value;
};

typedef struct _bonobo_ffi_entry
{
    char *name;
    BonoboFFIFunction function;
    struct _bonobo_ffi_entry *next;
    void *state;
} bonobo_ffi_entry_t;

bonobo_ffi_entry_t *bonobo_ffi_lookup(bonobo_vm_t *vm, char *name);

#endif //BONOBO_FFI_H
