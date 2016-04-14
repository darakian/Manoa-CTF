#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <openssl/sha.h>

int main(int argc, char * argv[])
{
  struct sockaddr_in ecco_addr;
  ecco_addr.sin_family = AF_INET;
  ecco_addr.sin_port = htons(9002);
  ecco_addr.sin_addr.s_addr = INADDR_ANY

  struct sockaddr_in send_addr;
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(9001);
  //Gonna have to re-ip things
  inet_pton(AF_INET, "192.168.1.255", &send_addr.sin_addr);
  unsigned char hash[SHA_DIGEST_LENGTH];
  int bcast_sock = 0;
  bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);
  int ret=setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

  if (bind(bcast_sock,(struct sockaddr *)&ecco_addr, sizeof(ecco_addr)) < 0)
    {
      perror("The internet has gone wrong!");
      return 0;
    }

  while(1)
  {
    //Wait for 'correct' packet. Reply to whoever sent it with the flag. Broadcast that the flag as been sent.
    char temp_char = '\0';
    if (read(bcast_sock, temp_char, 1))
    {
      if (temp_char=='{')
      {
        //Broadcast notification of flag-age
      }
    }
  }
}
