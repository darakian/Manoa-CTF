#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sodium.h>
#include <unistd.h>

int base64_encode(char* input_buffer, int input_length, char* output_buffer, int output_buffer_length)
{
  if (output_buffer_length<(((input_length*4)/3) + 3))
  {
    return -1;
  }
  //See https://en.wikipedia.org/wiki/Base64 for an explination on the lookup table
  char * base64_lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  int length_remainder = input_length%3;
  int i, index = 0;
  int character1, character2, character3 = 0;
  int temp_bits1, temp_bits2, temp_bits3, temp_bits4 = 0;

  for (i = 0; i<input_length; i+=3)
  {
    /* split 3 characters into 4 groups of at most 6 bits each */
    character1 = (input_buffer[i]) & 0xff;
    if (i + 1 < input_length)
    {
      character2 = (input_buffer[i+1]) & 0xff;
    }
    if (i + 2 < input_length)
    {
      character3 = (input_buffer[i+2]) & 0xff;
    }
    temp_bits1 = (character1>>2) & 0x3f;
    temp_bits2 = ((character1<<4) | (character2>>4)) & 0x3f;
    temp_bits3 = ((character2<<2) | (character3>>6)) & 0x3f;
    temp_bits4 = character3 & 0x3f;

    output_buffer[index++] = base64_lookup[temp_bits1];
    output_buffer[index++] = base64_lookup[temp_bits2];
    if (i + 1 < input_length)
    {
      output_buffer[index++] = base64_lookup[temp_bits3];
    }
    else
    {
      output_buffer[index++] = '=';
    }
    if (i + 2 < input_length)
    {
      output_buffer[index++] = base64_lookup[temp_bits4];
    }
    else
    {
      output_buffer[index++] = '=';
    }
  }
  output_buffer[index] = '\0';
  output_buffer_length = index;
  return index;
}

void main(int argc, char *argv[])
{
  if (argc<2)
  {
    printf("To who?\n");
    return;
  }
  if (argc>2)
  {
    printf("Too many.\n");
    return;
  }
  int fd = 0;
  int system_init = 0;
  int server_socket = 0;
  struct sockaddr_in server_address;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  server_address.sin_port = htons(9001);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  struct sockaddr_in remote_sockaddr;
	remote_sockaddr.sin_family = AF_INET;
  remote_sockaddr.sin_port = htons(9002);
  inet_pton(AF_INET, argv[1], &remote_sockaddr.sin_addr);

  if (bind(server_socket,(struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  	{
  		perror("Bind() on server_socket has failed\n");
      return;
  	}
    if (connect(server_socket, (const struct sockaddr *) &remote_sockaddr, sizeof(remote_sockaddr)) < 0)
  	{
  		perror("Client connection error");
      return;
  	}

    char winrar[14] = "You a winrar!";
    char meat_and_potatoes[1024];
    char hash[64];
    char base64_buffer[88];
    int write_length = 0;
    sodium_memzero(&hash, sizeof(hash));
    sodium_memzero(&meat_and_potatoes, sizeof(meat_and_potatoes));
    randombytes_buf(meat_and_potatoes, sizeof(meat_and_potatoes));
    crypto_generichash(hash, sizeof(hash), meat_and_potatoes, sizeof(meat_and_potatoes),NULL, 0);
    write_length = base64_encode(hash, sizeof(hash), base64_buffer, sizeof(base64_buffer));

    write(server_socket, winrar, sizeof(winrar));

    close(server_socket);

}
