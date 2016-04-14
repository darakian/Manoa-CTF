#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void main (int argc, char *argv[])
{
  char answer[7] = "po'oihe";
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(answer, sizeof(answer) - 1, hash);

  if (argc<2)
  {
    printf("Program takes one argument!\n");
    return;
  }
  if (argc>2)
  {
    printf("Program takes one argument!\n");
    return;
  }

  int comp = (memcmp(argv[1], answer, sizeof(answer)));
  if (comp > 0)
  {
    printf("Input value over target value\n");
    return;
  }
  if (comp<0)
  {
    printf("Input value under target value\n");
    return;
  }
  if (comp==0)
  {
    for(int i = 0; i<20;i++)
    {
      printf("%x", hash[i]);
    }
    return;
  }
}
