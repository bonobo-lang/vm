// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_BONOBO_FFI_H
#define BONOBO_BONOBO_FFI_H

#include <stddef.h>
#include "bonobo_object.h"
#include "bonobo_vm.h"

struct _bonobo_ffi_arguments;

typedef struct _bonobo_ffi_arguments *bonobo_ffi_arguments_t;

typedef void (*BonoboFFIFunction)(bonobo_ffi_arguments_t arguments, void *state);

int bonobo_ffi_register(bonobo_vm_t *vm, char *name, BonoboFFIFunction function, void *state);

bonobo_object_t bonobo_ffi_invoke(bonobo_vm_t *vm, char *name, size_t number_of_arguments, bonobo_object_t *arguments);

bonobo_vm_t *bonobo_ffi_get_vm(bonobo_ffi_arguments_t arguments);

size_t bonobo_ffi_get_number_of_arguments(bonobo_ffi_arguments_t arguments);

bonobo_object_t bonobo_ffi_get_argument(bonobo_ffi_arguments_t arguments, size_t index);

void bonobo_ffi_return(bonobo_ffi_arguments_t arguments, bonobo_object_t object);

#endif //BONOBO_BONOBO_FFI_H
