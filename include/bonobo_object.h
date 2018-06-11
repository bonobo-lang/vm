// Copyright (c) 2018, Tobechukwu Osakwe.
//
// All rights reserved.
//
// Use of this source code is governed by an
// MIT-style license that can be found in the LICENSE file.
#ifndef BONOBO_BONOBO_OBJECT_H
#define BONOBO_BONOBO_OBJECT_H

#include <stdint.h>

typedef enum
{
    BONOBO_OBJECT_VOID,
    BONOBO_OBJECT_ERROR,
    BONOBO_OBJECT_UINT8,
    BONOBO_OBJECT_UINT8ARRAY,
    BONOBO_OBJECT_INT32,
    BONOBO_OBJECT_INT64,
    BONOBO_OBJECT_DOUBLE,
    BONOBO_OBJECT_STRING,
    BONOBO_OBJECT_ARRAY
} bonobo_object_type;

typedef struct _bonobo_object
{
    bonobo_object_type type;
    union
    {
        uint8_t as_uint8;
        int32_t as_int32;
        int64_t as_int64;
        double as_double;
        char *as_string;
        struct _bonobo_object *as_error;
        struct
        {
            intptr_t length;
            struct _bonobo_object *values;
        } as_array;
        struct
        {
            intptr_t length;
            uint8_t *values;
        } as_uint8_array;
    };
} bonobo_object_t;

#endif //BONOBO_BONOBO_OBJECT_H
