// Copyright 2021 Ola Nordstrom
#ifndef UTIL_H
#define UTIL_H

void* allocate_shared_memory_or_exit(size_t size);
void free_memory(void *mem);

#endif