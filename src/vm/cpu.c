// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <string.h>
#include "cpu.h"
#include "vm.h"

void *bonobo_load_function(bonobo_vm_t *vm, bonobo_function_t *function) {
    // TODO: Support loading one-off functions
    return NULL;
}

bonobo_program_t *bonobo_load_program(bonobo_vm_t *vm, const uint8_t *bytes, size_t length) {
    if (length < 19 || bytes[0] != 0xb || bytes[1] != 0x0 || bytes[2] != 0xb) return NULL;
    size_t index = 3;

    // Read constant data
    uint64_t constant_data_size = *((uint64_t *) &bytes[index]);
    index += sizeof(constant_data_size);
    const uint8_t *constant_data = &bytes[index];
    index += constant_data_size;

    // Read functions
    uint64_t number_of_functions = *((uint64_t *) &bytes[index]);
    index += sizeof(number_of_functions);

    bonobo_function_t *functions = (bonobo_function_t *) vm->allocator(number_of_functions * sizeof(bonobo_function_t));

    for (uint64_t i = 0; i < number_of_functions; i++) {
        bonobo_function_t function = functions[i];
        function.name = (char *) &bytes[index];
        index += strlen(function.name) + 1;
        function.length = *((uint64_t *) &bytes[index]);
        index += function.length;
        function.bytes = &bytes[index];
    }

    bonobo_program_t *program = (bonobo_program_t *) vm->allocator(sizeof(bonobo_program_t));
    program->data = bytes;
    program->number_of_functions = number_of_functions;
    program->functions = functions;
    program->constant_data_size = constant_data_size;
    program->constant_data = (uint8_t *) constant_data;
    return program;
}