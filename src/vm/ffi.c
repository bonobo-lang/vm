// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#include <string.h>
#include "internal.h"

int bonobo_ffi_register(bonobo_vm_t *vm, char *name, BonoboFFIFunction function, void *state) {
    bonobo_ffi_entry_t *entry = vm->ffi;

    if (entry == NULL) {
        entry = vm->ffi = vm->allocator(sizeof(bonobo_ffi_entry_t));
        entry->function = function;
        entry->name = strdup(name);
        entry->next = NULL;
        entry->state = state;
        return EXIT_SUCCESS;
    }

    uint8_t found = 0;

    while (entry->next != NULL && found == 0) {
        if (strcmp(entry->name, name) == 0)
            found = 1;
        entry = entry->next;
    }

    if (found == 0) {
        entry = entry->next = vm->allocator(sizeof(bonobo_ffi_entry_t));
        entry->function = function;
        entry->name = strdup(name);
        entry->next = NULL;
        entry->state = state;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

bonobo_object_t bonobo_ffi_invoke(bonobo_vm_t *vm, char *name, size_t number_of_arguments, bonobo_object_t *arguments) {
    bonobo_ffi_entry_t *entry = bonobo_ffi_lookup(vm, name);
    struct _bonobo_ffi_arguments ffi_arguments;
    ffi_arguments.arguments = arguments;
    ffi_arguments.number_of_arguments = number_of_arguments;
    ffi_arguments.return_value.type = BONOBO_OBJECT_VOID;

    if (entry == NULL) {
        // TODO: Return error instead
    } else {
        bonobo_vm_enter_scope(vm);
        entry->function(&ffi_arguments, entry->state);
        bonobo_vm_exit_scope(vm);
    }

    return ffi_arguments.return_value;
}

bonobo_ffi_entry_t *bonobo_ffi_lookup(bonobo_vm_t *vm, char *name) {
    bonobo_ffi_entry_t *entry = vm->ffi;

    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) return entry;
        entry = entry->next;
    }

    return NULL;
}

bonobo_vm_t *bonobo_ffi_get_vm(bonobo_ffi_arguments_t arguments) {
    return arguments->vm;
}

size_t bonobo_ffi_get_number_of_arguments(bonobo_ffi_arguments_t arguments) {
    return arguments->number_of_arguments;
}

bonobo_object_t bonobo_ffi_get_argument(bonobo_ffi_arguments_t arguments, size_t index) {
    return arguments->arguments[index];
}

void bonobo_ffi_return(bonobo_ffi_arguments_t arguments, bonobo_object_t object) {
    arguments->return_value = object;
}