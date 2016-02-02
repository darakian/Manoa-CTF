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

int main (int argc, char * argv[])
{
  char eins = 'd';
  char fluff = 'q';
  char du = 'a';
  char gtfo = 'x';
  char three = 't';
  char O_O = 's';
  char four = 'f';
  char T_T[] = "if you're looking here, you're doing it wrong!!!!";
  char go = 'i';
  char sechs = 'l';
  char set = 'e';
  char reference_char[7] = {0};

  int var = 507;
  var++;
  var++;
  char da_encode[90];
  unsigned char hash[crypto_generichash_BYTES];
  crypto_generichash(hash, sizeof(hash), (const unsigned char *)&var, 4, NULL, 0);


  //Some downright stupid stupidity
  memcpy(&reference_char, &eins, 1);
  memcpy(&reference_char+1, &du, 1);
  memcpy(&reference_char+2, &three, 1);
  memcpy(&reference_char+3, &four, 1);
  memcpy(&reference_char+4, &go, 1);
  memcpy(&reference_char+5, &sechs, 1);
  memcpy(&reference_char+6, &set, 1);

  //Setup sockaddr for broadcast
  struct sockaddr_in reception_addr;
  reception_addr.sin_family = AF_INET;

  if (argc!=2)
  {
    reception_addr.sin_port = htons(9002);
  }
  else if(argc==2)
  {
    reception_addr.sin_port = htons((int)argv[1]);
  }
  reception_addr.sin_addr.s_addr = INADDR_ANY;

  //Open a socket and prep to operate
  int reception_sock = 0;
  reception_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(reception_sock,(struct sockaddr *)&reception_addr, sizeof(reception_addr)) < 0)
    {
      perror("The internet sucks!");
      return -1;
    }
  int connected_socket = 0;
  struct sockaddr_in remote_sockadder;
  int remote_length = 0;
  char input_buffer[7] ={0};
  char welcome[] = "Password plz\n";
  char goodbye[] = "goodbye";
  int winrar = 0;
  while(1)
  {
    if(listen(reception_sock, 1)<0)
    {
      perror("The internet is a bag of dicks!");
    }
    connected_socket = accept(reception_sock, (struct sockaddr *)&remote_sockadder, &remote_length);
    write(connected_socket, &welcome, sizeof(welcome));

    for(int i = 0; i<7;i++)
    {
      if (read(connected_socket, &input_buffer+i, 1)<0)
      {
        continue;
      }
      if(input_buffer[i]!=reference_char[i])
      {
        write(connected_socket, &goodbye, sizeof(goodbye));
        close(connected_socket);
        memset(&input_buffer, 0, 7);
        break;
      }
      winrar = 1;
    }
    if (winrar==1)
    {
      write(connected_socket, &hash, sizeof(hash));
      write(connected_socket, "\n", 1);
      winrar = 0;
      memset(&input_buffer, 0, 7);
      close(connected_socket);
    }
  }
}
