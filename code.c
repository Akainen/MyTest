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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rsa.h"
#define LENGTH 15
#define MAXLEN 2

int main(void)
{
    int choice;
    long long key[LENGTH];
    srand(time(NULL));
    bool exit;

    while (1)
    {
        /* Get the user's selection. */

        choice = menu();

        /* Branch based on the input. */

        if(choice == 1)
        {
            puts("\nExecuting prime number generation...");
            printf("Choosing two primes p and q.\n\n");
            exit = primeGen(key);
            if (exit == 0)
            {
                puts("The primes q and p have been generated successfully.");
                printf("\nThe first prime p is %lld, the second prime q is %lld\n", key[0], key[1]); //Needs to be hidden later
            }
        }
        else if(choice == 2)
        {
            puts("\nExecuting key generation...");
            keyGen(key);
        }
        else if(choice == 3)
        {
            puts("\nExecuting task C.");
        }
        else if(choice == 4)
        {
            puts("\nExecuting task D.");
        }
        else if(choice == 5)		/* Exit program. */
        {
            puts("\nExiting program now...\n");
            break;
        }
        else
        {
            puts("\nInvalid choice, try again.");
        }
    }
    return 0;
}

/* Displays a menu and inputs user's selection. */
int menu(void)
{
    int reply;

    puts("\nEnter 1 for prime number generation.");
    puts("Enter 2 for RSA key generation.");
    puts("Enter 3 for task C.");
    puts("Enter 4 for task D.");
    puts("Enter 5 to exit program.");

    scanf("%d", &reply);

    return reply;
}

bool primeGen(long long key[])
{
    char buffer[MAXLEN];
    unsigned count = 0, count1 = 0, count2 = 0, count4 = 0;
    int remainder = 1;
    for(count = 0; count < 2; count++)
    {
        do
        {
            key[count] = rand()/100;
            for(count1 = 2; count1 < key[count] && remainder != 0 && key[count] >= 3; count1++)
            {
                remainder = key[count]%count1;
            }
            if(remainder != 0 && key[count] != 0)
            {
                //printf("number %ld is a prime, it gets assigned to key[%d]\n", key[count], count);
                count4 = 1;
            }
            else
            {
                //printf("number %ld from key[%d] is not a prime\n", key[count], count);
                remainder = 1;
                count4 = 0;
                count2++;
                if(count2 == 100)
                {
                    printf("\nNo prime has been found yet. Enter c to continue, enter q to quit.\n");
                    while (1)
                    {
                        fgets(buffer, MAXLEN, stdin);
                        if(buffer[0] == 'c')
                            break;
                        if(buffer[0] == 'q')
                            return 1;
                    }
                    count2 = 0;
                }
            }

        }
        while (count4 == 0);
    }
    return 0;
}

bool keyGen(long long key[])
{
    unsigned remainder1 = 0, remainder2 = 0, count1, ggt = 1;
    bool exit;
    puts("---------------------------------------------------------");
    printf("Choosing two primes p and q.\n");
    exit = primeGen(key);
    if (exit == 0)
    {
        puts("The primes q and p have been generated successfully.");
        printf("\nThe first prime p is %lld, the second prime q is %lld\n", key[0], key[1]); //Needs to be hidden later
        puts("---------------------------------------------------------");
        puts("Calculating n...");
        key[2] = key[0]*key[1];
        printf("n is %lld\n", key[2]);
        puts("---------------------------------------------------------");
        puts("Calculating gamma...");
        key[3] = (key[0] - 1)*(key[1] - 1);
        printf("gamma is %lld\n", key[3]);
        puts("---------------------------------------------------------");
        printf("choosing e");
        do
        {
            key[4] = rand()%10 + 3;
            printf(".");
            //printf("\ne is %ld\n", key[4]);
            for(count1 = 1; count1 <= key[4]; count1++)
            {
                remainder1 = key[4]%count1;
                remainder2 = key[3]%count1;
                if(remainder1 == 0 && remainder2 == 0)
                {
                    ggt = count1;
                }
            }
            //printf("\nGgT of e and gamma: %d\n", ggt);
        }
        while(ggt != 1);
        printf("\nSuccess: e is %lld\n", key[4]);
        puts("---------------------------------------------------------");
        printf("choosing d");

        key[5] = key[3];
        key[6] = key[3];
        key[7] = key[4];
        key[8] = 1;
        do
        {
            printf(".");
            key[9] = key[7];
            key[10] = key[8];
            key[11] = key[5] - ((key[5]/key[7])*key[7]);
            key[12] = key[6] - ((key[5]/key[7])*key[8]);
            if(key[12] < 0)
            {
                key[12] = modulo(key); //Muss noch verbessert werden!
            }
            key[5] = key[9];
            key[6] = key[10];
            key[7] = key[11];
            key[8] = key[12];
        }
        while(key[7] != 1);
        printf("\nSuccess: c is %lld, therefore is d %lld\n",key[7], key[8]);
        printf("Proof: %lld * %lld mod %lld = %lld\n", key[4], key[8], key[3], (key[4] * key[8])%key[3]);
        puts("---------------------------------------------------------");
    }
    return 0;
}

long long modulo(long long key[])
{
    return ((key[12]%key[3] + key[3])% key[3]); //geht solange key[3] positiv ist, was hier immer der Fall ist.
}

