/**
 * @file main.c
 * @ref <lab2>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Christophe PRACHT, 2018.
 *
 * @author Christophe PRACHT -- <>
 * @date 21-11-2018
 *
 * @brief This is a short description.
 *
 * This is a longer description
 */

#ifndef RSA_H
#define RSA_H

#include <stdbool.h>

bool primeGen(long long key[]);
int menu(void);
bool keyGen(long long key[]);
long long modulo(long long key[]);
#endif // RSA_H

