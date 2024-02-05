/* 
 * Trying to answer the question on 2 pointers to "Hello World!"
 * 
 * Copyright (c) U. Raich) Jan. 2024
 */

#include <stdio.h>

int main(int argc, char **argv) {
  char *h1 = "Hello World!";
  char *h2 = "Hello world!";

  printf("h1: %p, h2: %p\n",(void *) h1, (void *) h2);
  if (h1 == h2)
    printf("The strings are equal\n");
  else
    printf("The strings are not equal\n");
}
