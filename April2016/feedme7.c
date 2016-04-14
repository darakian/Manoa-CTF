#include <stdio.h>
#include <string.h>

void main (int argc, char *argv[])
{
  char answer[7] = "po'oihe";

  if (argc<2)
  {
    printf("MOAR!\n");
    return;
  }
  if (argc>2)
  {
    printf("LESS!\n");
    return;
  }

  int comp = (memcmp(argv[1], answer, sizeof(answer)));
  if (comp > 0)
  {
    printf("TOO SPICEY!\n");
    return;
  }
  if (comp<0)
  {
    printf("TOO SOUR!\n");
    return;
  }
  if (comp==0)
  {
    printf("Just right!\n");
    return;
  }
}
