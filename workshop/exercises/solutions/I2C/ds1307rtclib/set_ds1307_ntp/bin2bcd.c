/* bin2bcd.c converts a binary int8_t to bcd representation */

#include <stdio.h>
#include <stdlib.h>

unsigned char bin2bcd(unsigned char int_bin) {
  unsigned char high_nibble = int_bin / 10;
  unsigned char low_nibble  = int_bin % 10;
  return (high_nibble << 4) | low_nibble;
}

int main(int argc, char ** argv) {
  unsigned char int_bin;
  int tmp;
  if (argc != 2) {
    printf("Usage %s hex number\n",argv[0]);
    exit(-1);
  }
  sscanf(argv[1],"%x",&tmp);
  int_bin = (unsigned char) tmp;
  printf("0x%02x corresponds to bdc: 0x%02x\n",int_bin,bin2bcd(int_bin));
}
