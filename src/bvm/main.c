// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <bonobo.h>
#include <stdio.h>

void my_printf(bonobo_ffi_arguments_t arguments, void *state);

int main() {
    bonobo_vm_t *vm = bonobo_vm_new();
    bonobo_vm_set_stack_size(vm, 1024);
    bonobo_vm_boot(vm);

    bonobo_object_t hello;
    hello.type = BONOBO_OBJECT_STRING;
    hello.as_string = "Hello, world!";

    bonobo_ffi_register(vm, "my_printf", &my_printf, NULL);
    bonobo_ffi_invoke(vm, "my_printf", 1, &hello);

    bonobo_vm_shutdown(vm);
    bonobo_vm_destroy(vm);
    return 0;
}

void my_printf(bonobo_ffi_arguments_t arguments, void *state) {
    bonobo_object_t arg = bonobo_ffi_get_argument(arguments, 0);
    printf("%s\n", arg.as_string);
}