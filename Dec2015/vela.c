#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#include "base64.h"

//Vela. Named for the first pular I found of wikipedia

void make_some_noise(struct sockaddr * an_sockaddr, int socket)
{
  int noise = rand();
  write(socket, &noise, sizeof(noise));
  sendto(socket,  &noise, sizeof(noise), 0, an_sockaddr, sizeof(struct sockaddr));
  //sendto(socket,  &noise, 4, 0, an_sockaddr, sizeof(an_sockaddr));
}

void broadcast_one (struct sockaddr * an_sockaddr, int socket)
{
  int var = 40;
  var++;
  var++;
  unsigned char hash[crypto_generichash_BYTES];
  crypto_generichash(hash, sizeof(hash), (const unsigned char *)&var, 4, NULL, 0);
  //write(socket, &hash, sizeof(hash));
  sendto(socket,  &hash, sizeof(hash), 0, an_sockaddr, sizeof(struct sockaddr));
  //sendto(socket,  &hash, sizeof(hash), NULL, an_sockaddr, sizeof(an_sockaddr));
}

void broadcast_two (struct sockaddr * an_sockaddr, int socket)
{
  char welcome[] = "User:salt\nPass:sodium";
  //write(socket, &welcome, sizeof(welcome));
  sendto(socket,  &welcome, sizeof(welcome), 0, an_sockaddr, sizeof(struct sockaddr));
  //sendto(socket,  &welcome, sizeof(welcome), NULL, an_sockaddr, sizeof(an_sockaddr));
}

void broadcast_three (struct sockaddr * an_sockaddr, int socket)
{
  int var = 1022;
  var++;
  var++;
  char da_encode[90];
  unsigned char hash[crypto_generichash_BYTES];
  crypto_generichash(hash, sizeof(hash), (const unsigned char *)&var, 4, NULL, 0);
  //base64 encode hash
  base64_default_encode((char *)&hash, sizeof(hash), (char *)&da_encode, sizeof(da_encode));
  sendto(socket,  &da_encode, sizeof(da_encode), 0, an_sockaddr, sizeof(struct sockaddr));
  //sendto(socket,  &noise, 4, NULL, an_sockaddr, sizeof(an_sockaddr));
}

void test_cast (struct sockaddr * an_sockaddr, int socket)
{
  int var = 1022;
  var++;
  var++;
  int write_result = 0;
  char da_encode[90];
  unsigned char hash[crypto_generichash_BYTES];
  crypto_generichash(hash, sizeof(hash), (const unsigned char *)&var, 4, NULL, 0);
  //base64 encode hash
  base64_default_encode((char *)&hash, sizeof(hash), (char *)&da_encode, sizeof(da_encode));
  write_result = sendto(socket,  &da_encode, sizeof(da_encode), 0, an_sockaddr, sizeof(struct sockaddr));
  printf("sendto_result = %d\n", write_result);
  perror("FUCK!");
}

int main(int argc, char * argv[])
{
  //Setup sockaddr for broadcast
  struct sockaddr_in bcast_addr;
  bcast_addr.sin_family = AF_INET;
  bcast_addr.sin_port = htons(9001);
  bcast_addr.sin_addr.s_addr = INADDR_ANY;
  //inet_pton(AF_INET, "192.168.1.255", &bcast_addr.sin_addr);

  struct sockaddr_in send_addr;
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(9001);
  //send_addr.sin_addr.s_addr = "192.168.1.255";
  inet_pton(AF_INET, "192.168.1.255", &send_addr.sin_addr);
  int broadcastEnable=1;


  //Open a socket and prep to spray
  int bcast_sock = 0;
  bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);
  int ret=setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
  if (bind(bcast_sock,(struct sockaddr *)&bcast_addr, sizeof(bcast_addr)) < 0)
    {
      perror("The internet has gone wrong!");
      return 0;
    }

  while(1)
  {
    //test_cast((struct sockaddr *)&send_addr, bcast_sock);
    //test_cast((struct sockaddr *)&send_addr, bcast_sock);
    make_some_noise((struct sockaddr *)&send_addr, bcast_sock);
    broadcast_one((struct sockaddr *)&send_addr, bcast_sock);
    make_some_noise((struct sockaddr *)&send_addr, bcast_sock);
    broadcast_two((struct sockaddr *)&send_addr, bcast_sock);
    make_some_noise((struct sockaddr *)&send_addr, bcast_sock);
    broadcast_three((struct sockaddr *)&send_addr, bcast_sock);
    make_some_noise((struct sockaddr *)&send_addr, bcast_sock);
    sleep(3);
  }
}
