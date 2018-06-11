// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_BONOBO_PROGRAM_H
#define BONOBO_BONOBO_PROGRAM_H

#include <stddef.h>
#include <stdint.h>

typedef struct
{
    char* name;
    const uint8_t *bytes;
    uint64_t length;
} bonobo_function_t;

typedef struct
{
    const uint8_t *data;
    uint8_t *constant_data;
    uint64_t constant_data_size;
    bonobo_function_t *functions;
    uint64_t number_of_functions;
} bonobo_program_t;

void *bonobo_load_function(bonobo_vm_t *vm, bonobo_function_t *function);

bonobo_program_t *bonobo_load_program(bonobo_vm_t *vm, const uint8_t *bytes, size_t length);

#endif //BONOBO_BONOBO_PROGRAM_H
