#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
  /* read the result file */
  FILE *fp;
  int i,j;
  uint32_t dht11Results[32];
  uint32_t *buf;
  uint32_t tmp;
  buf = dht11Results;
  
  fp = fopen("result.txt","r");
  for (i=0;i<32;i++) {
    fscanf(fp,"%x",buf);
    buf++;
  }
  buf = dht11Results;
  for (i=0; i<32;i++) {
    printf("%08x\n",*buf);
    buf++;
  }
  fclose(fp);
  
  /* open a file to be plotted with gnuplot */
  fp = fopen("plotfile.txt","w");
  for (i=0;i<32;i++) {
    tmp = dht11Results[i];
    for (j=0;j<32;j++) {
      if (tmp & 0x80000000)
	fprintf(fp,"%d\n",1);
      else
	fprintf(fp,"%d\n",0);
      tmp <<= 1;
    }
  }
  fclose(fp);
    
}
