#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

using namespace std;

bool is_number(char *str)
{
  int i;
  for(i = 0; i < strlen(str) - 1; i++) {
    if(!(str[i] >= '0' && str[i] <= '9')) {
      return false;
    }
  }
  return true;
}

int main ( int argc, char *argv[] )
{
  int port = 0;
  
  if (argc == 1) {
    port = 12345;
  } else {
    if (is_number(argv[1])) {
      port = atoi(argv[1]);
    } else {
      std::cout << "Usage : " << argv[0] << " [port]\n";
      return -1;
    }
  }

  std::cout << "running on port " << port << "\n";

  try
    {
      // Create the socket
      ServerSocket server (port);
      while ( true )
	{
	  ServerSocket new_sock;
	  server.accept ( new_sock );
	  try
	    {
	      while ( true )
		{
		  std::string data;
		  new_sock >> data;
		  std::cout << data;
		  new_sock << data;
		}
	    }
	  catch ( SocketException& ) {}	  
	}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    } 
  return 0;
}
