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
  struct sockaddr_in the-dolphin_addr;
  the-dolphin_addr.sin_family = AF_INET;
  the-dolphin_addr.sin_port = htons(9002);
  the-dolphin_addr.sin_addr.s_addr = INADDR_ANY

  struct sockaddr_in send_addr;
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(9002);
  //Gonna have to re-ip things
  inet_pton(AF_INET, "192.168.1.102", &send_addr.sin_addr);
  int bcast_sock = 0;
  bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);
  int ret=setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

  //Bind on UDP
  if (bind(bcast_sock,(struct sockaddr *)&the-dolphin_addr, sizeof(the-dolphin_addr)) < 0)
    {
      perror("The internet has gone wrong!");
      return 0;
    }

  //Main loop
  while(1)
  {
    //Broadcast packet to subnet. Cycle through the
  }

}
