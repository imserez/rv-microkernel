#pragma once
#include "common.h"

__attribute__((noreturn)) void exit(void);
void putchar(char ch);
long getchar(void);

#define SCAUSE_ECALL 8