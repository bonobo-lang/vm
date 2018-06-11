add_library(${BONOBO_LIBRARY} STATIC
        ../include/bonobo.h
        ../include/bonobo_vm.h
        vm/vm.h vm/vm.c
        vm/stack.c vm/stack.h
        vm/object.c vm/object.h
        ../include/bonobo_object.h ../include/bonobo_ffi.h vm/internal.h vm/ffi.c vm/ffi.h vm/memory.c vm/memory.h)
target_include_directories(${BONOBO_LIBRARY} PUBLIC ${BONOBO_INCLUDE_DIRS})

add_executable(${BVM_EXECUTABLE}
        bvm/main.c)
target_include_directories(${BVM_EXECUTABLE} PUBLIC ${BONOBO_INCLUDE_DIRS})
target_link_libraries(${BVM_EXECUTABLE} ${BONOBO_LIBRARY})