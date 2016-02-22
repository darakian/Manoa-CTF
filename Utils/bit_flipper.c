#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
  char byte = 0;
#ifdef hardmode
  char xor_buffer = 0xA;
#endif /*hardmode*/
#ifdef easymode
  char xor_buffer = 0x01;
#endif /*easymode*/
  char write_byte = 0;
  if (argc!=3)
    {
      printf("arg1: file_to_flip, arg2: flipped_file\n");
      exit(1);
    }
  int file_to_flip = open(argv[1], O_RDONLY);
  int flipped_file = open(argv[2], O_RDWR|O_CREAT, S_IRWXU|S_IRGRP|S_IROTH);
  while (read(file_to_flip, &byte, 1)>0)
    {
      write_byte = xor_buffer ^ byte;
      write(flipped_file, &write_byte, 1);
    }
  if (read(file_to_flip, &byte, 1)<0)
    {
      perror("read");
    }

}
