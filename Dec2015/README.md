# December 2015 CTF event  challenges

## Simple Connector
Simple connector wants as input a single IP address. If a valid input is received simple connector will attempt to connect to it and send a flag.

## Feedme5
A simple program designed to take one argument on the command line. The correct input would lead to success.  
There are at least two ways to solve this problem.  
1. Brute force the input. Simple, but slow.
2. Inspect the binary. The correct input was written in as a variable and exists in ascii in the binary.

## Juno
Similar to Feedme5, but with a more complicated check on the input. The idea was to force the contestant to brute force the input.

## King Jeff
King Jeff is a program that takes one token as input. If the token is a valid ipv4 address King Jeff will open a socket and send a flag to the ip.

## Lupus
Lupus is the inverse of King Jeff. Lupus opens a socket on a specific port number which can be overridden by launching the program with a numeric argument. Lupus will sit on this port, accept connections and ask for a password. When the correct password is given the user is presented with the flag. A few things about Lupus:
1. It will drop a connection on the first wrong character it receives.
2. It expects the user to write a custom brute force utility.
3. It is single threaded and thus can only handle one attempt at a time. This will be fixed in the future.

## Vela
Vela is a service written to make the network a little harder to deal with. Vela generates noise and broadcasts it to the working subnet. Mixed in with this noise is a valid flag.
