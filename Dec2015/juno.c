#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sodium.h>

#include "base64.h"

int main (int argc, char * argv[])
{
  char a = 'm';
  char b = 'h';
  char c = 'w';
  char d = 'i';
  char e = 'o';
  char f = 'k';
  char g = 'u';
  char h = 'x';
  char i = 'n';
  char j = 'x';
  char k = 'x';
  char l = 'x';
  char m = 'x';
  char n = 'x';
  char o = 'a';
  char p = 'x';
  char q = 'x';
  char r = 'x';
  char s = 'x';
  char t = 'x';
  char answer[5] = {0};


  if (argc==1)
  {
    answer[0] = f;
    answer[1] = o;
    answer[2] = g;
    answer[3] = o;
    answer[4] = d;
    unsigned char hash[crypto_generichash_BYTES];
    crypto_generichash(hash, sizeof(hash), (const unsigned char *)&answer, 5, NULL, 0);
    char da_encode[87] = {0};
    base64_default_encode(&hash, sizeof(hash), da_encode, sizeof(da_encode));
    printf("%s\n", da_encode);
  }

  if (argc==2)
  {
    answer[0] = a;
    answer[1] = o;
    answer[2] = i;
    answer[3] = e;
    answer[4] = o;
    if(memcmp(argv[1], answer, sizeof(answer))==0)
    {
      unsigned char hash[crypto_generichash_BYTES];
      crypto_generichash(hash, sizeof(hash), (const unsigned char *)&answer, 5, NULL, 0);
      char da_encode[87] = {0};
      base64_default_encode(&hash, sizeof(hash), da_encode, sizeof(da_encode));
      printf("%s\n", da_encode);
    }
  }

  if (argc==3)
  {
    char buffer[6] = {0};
    char arg1_buff[4] = {0};
    char arg2_buff[4] = {0};
    memcpy(&arg1_buff, argv[1], 4);
    memcpy(&arg2_buff, argv[2], 4);
    char xor_array[5] = {0};
    xor_array[0] = (arg1_buff[0]^arg2_buff[0]);
    xor_array[1] = (arg1_buff[1]^arg2_buff[1]);
    xor_array[2] = (arg1_buff[2]^arg2_buff[2]);
    xor_array[3] = (arg1_buff[3]^arg2_buff[3]);
    char da_encode[6] = {0};
    base64_default_encode(&xor_array, sizeof(xor_array), da_encode, sizeof(da_encode));
    printf("%s\n", da_encode);
    printf("%x\n", &xor_array);
  }
}
