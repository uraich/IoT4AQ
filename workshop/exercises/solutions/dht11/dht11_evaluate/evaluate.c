// evaluate.c: Reads the file used to plot the protocol. This corresponds to an
// array of 32 * 32 = 1024 zeros and ones.
// This start signal is skipped and the 5 8-bit result values extracted
// The first 4 values are summed up and compared with the fifth value (testing
// the checksum). If the checksum is ok, the first two values are assembled to
// acquire the relative humidity in % and then the third and forth value to
// get at the temperature in °C

// Copyright (c) U. Raich
// This program is part of the IoT4AQ workshop at the
// university Alioune Diop, Bambay, Sénégal, 2024
// It is released under the MIT license

// I deliberately left the debugging statements in the code, just commenting them out
// If you want to follow the code in detail, just uncomment them

#include <stdio.h>
#include <stdlib.h>

// expects a pointer to the beginning of the bit buffer
// skips the start signal advancing the pointer until the signal goes
// low again

char *skipStartSignal(char *buf) {
  char *startBuf = buf;
  while (*buf == 0)
    buf++; // now the signal is high
  while (*buf == 1)
    buf++; // now it is low again. We have skipped the start signal
  // printf("We skipped %d bits\n",(int)(buf - startBuf));
  return buf;
}

char *readByte(unsigned char *buf, unsigned char *result) {
  unsigned char *startPtr = buf;
  unsigned char tmp = 0;
  // We advance the pointer until the signal rises
  // 
  for (int i=0;i<8;i++) {
    while (*buf == 0)
      buf++; // wait until the signal rises
    
    // A one corresponds to a signal that is high for 70us while a zero
    // is high high for only 28us. We therefore look ahead by (70us - 28 us)/2 + 28
    // to get the highest chance to be right. Since we sampled the data
    // at a data rate of 4us we have to divide this number by 4:
    // ((70-28)/2 + 28)/4 = 12.25
    
    tmp <<= 1;           // shift the result by one to make space for the new bit    
    if (*(buf+12) == 1)  // if the signal is still high 12 positions later
      tmp |= 1;          // we read a one and we or a 1 into the result

    // printf("Bit %d: tmp: 0x%02x\n",i,(int)tmp);
    while (*buf == 1) 
      buf++;           // advance the pointer until the signal falls again
    // printf("Relative pointer position: %d\n",(int) (buf - startPtr));
  }
  *result = tmp;
  return buf;          // return the updated buffer pointer for the next byte
}

int main(int argc, char **argv) {
  int i;
  FILE *fp;
  unsigned char buf[1024];
  unsigned char *bufPtr;
  float temperature, humidity;
  unsigned char humi_int, humi_dec;
  unsigned char temp_int, temp_dec;
  unsigned char checksum,chs;
  
  // read the plot file

  if ((fp = fopen("plotfile.txt","r")) == NULL) {
    printf("The program expects a text file with 32*32=1024 zero or one values\n");
    printf("named \"plotfile.txt\". This file was not found!\n");
    exit(-1);
  }
  bufPtr = buf;
  for (i=0;i<1024;i++) {
    fscanf(fp,"%d",(int *)bufPtr);
    bufPtr++;
  }
  // used for debugging only
  /*
  bufPtr = buf;
  for (i=0;i<10;i++) {
    printf("%d ",(int)*bufPtr);
    bufPtr++;
  }
  printf("\n");
  */
  
  // skip the start signal
  bufPtr = skipStartSignal(buf);
  bufPtr = readByte(bufPtr,&humi_int);
  // printf("Integral part of humidity: 0x%02x, %d\n",(int)humi_int, (int)humi_int); 
  bufPtr = readByte(bufPtr,&humi_dec);
  // printf("Decimal part of humidity: 0x%02x, %d\n",(int)humi_dec, (int)humi_dec); 
  bufPtr = readByte(bufPtr,&temp_int);
  // printf("Integral part of temperature: 0x%02x, %d\n",(int)temp_int, (int)temp_int); 
  bufPtr = readByte(bufPtr,&temp_dec);
  // printf("Decimal part of humidity: 0x%02x, %d\n",(int)temp_dec, (int)temp_dec); 
  bufPtr = readByte(bufPtr,&checksum);
  // printf("Checksum: 0x%02x\n",(int)checksum);
  // calculate checksum and compare with the value read from the protocol
  chs = humi_int + humi_dec + temp_int + temp_dec;
  if (chs != checksum) 
    printf("Checksum expected: 0x%02x, checksum calculated: 0x%02x\n",(int)checksum,(int)chs);
  else {
    printf("Checksum ok\n");
    temperature = temp_int + 0.1*temp_dec;
    humidity = humi_int + 0.1*humi_dec;
    printf("Temperature: %4.1f°C, humidity: %4.1f%%\n",temperature,humidity);
  }
}
