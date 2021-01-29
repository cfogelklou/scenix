#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <mem.h>

#define WIN32

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#define BUF_LEN	 1024

#define DUMP_COMMAND	0x10
#define SET_COMMAND	0x20
#define GET_COMMAND	0x30
#define HELLO_COMMAND	0x40

extern int errno;

void print_help(char *prog) {
  printf("%s [-hedsg] ip - Send and receive UDP packets to an SX microcontroller.\n", prog);
  printf("   ip             IP address of the SX in x.x.x.x notation\n");
  printf("   -h             This help message.\n");
  printf("   -e             Get the SX's hello message.\n");
  printf("   -d             Dump the SX's register file.\n");
  printf("   -s addr value  Set the register at the address to a certain value.\n");
  printf("   -g addr        Get the value at the given address.\n");
  printf("   For the -s and -g commands the values must be given in decimal\n" );
}

unsigned int decodeAddress( char *a ) {
  char *dot;
  unsigned int addr = 0;

  dot = strchr(a,'.');
  if (!dot )
    return 0;
  *dot = '\0';
  addr = atoi(a)<<24;

  a = dot + 1;
  dot = strchr(a,'.');
  if (!dot )
    return 0;
  *dot = '\0';
  addr |= atoi(a)<<16;

  a = dot + 1;
  dot = strchr(a,'.');
  if (!dot )
    return 0;
  *dot = '\0';
  addr |= atoi(a)<<8;

  a = dot + 1;
  addr |= atoi(a);

  return addr;
}

int main( int argc, char *argv[] ) {
  int err, i, j;
  int clientLen, lenReceived, commandLen;
  unsigned char buffer[BUF_LEN];
  int sock;
  struct sockaddr_in addr, clientAddr;
  unsigned char commandBuf[3];
  char command;
  unsigned char address, data;
  unsigned int ipAddr;

#ifdef WIN32
  WSADATA lpWSAData;
#endif

  /* Decode the command line options. */
  if ( argc > 1 ) {
    if ( !strcmp( argv[1], "-d" ) ) {
      command = 'd';
      commandBuf[0] = DUMP_COMMAND;
      commandLen = 1;
      printf("Dumping the SX's register file\n");
    }
    else if ( !strcmp( argv[1], "-e" ) ) {
      command = 'e';
      commandBuf[0] = HELLO_COMMAND;
      commandLen = 1;
      printf("Reqesting hello message\n");
    }
    else if ( !strcmp( argv[1], "-s" ) && argc == 5 ) {
      command = 's';
      address = atoi( argv[2] );
      data = atoi( argv[3] );
      commandBuf[0] = SET_COMMAND;
      commandBuf[1] = address;
      commandBuf[2] = data;
      commandLen = 3;
     printf("Setting the register at address %2.2X to %2.2X\n", address, data);
    }
    else if ( !strcmp( argv[1], "-g" ) && argc == 4 ) {
      command = 'g';
      address = atoi( argv[2] );
      commandBuf[0] = GET_COMMAND;
      commandBuf[1] = address;
      commandLen = 2;
      printf("Getting the register at address %2.2X\n", address);
    }
    else {
      print_help(argv[0]);
      return 1;
    }
  }
  else {
    print_help(argv[0]);
  	return 1;
  }

#ifdef WIN32
  /* Windows requires that winsock be initialized. */
  err = WSAStartup (0x0101, &lpWSAData);
  if ( err != 0 ) {
  	printf("Cannot open WinSock\n");
    return 1;
  }
#endif

  /* Get the IP address of the destination. */
  ipAddr = decodeAddress( argv[argc-1] );
  if ( ipAddr == 0 ) {
   	printf("Invalid IP address\n");
    return 1;
  }
  printf("IP address of SX: %d.%d.%d.%d\n", (ipAddr&0xff000000)>>24,
         (ipAddr&0x00ff0000)>>16, (ipAddr&0x0000ff00)>>8, ipAddr&0x000000ff );

  clientLen = sizeof( clientAddr );

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if ( sock < 0 ) {
    perror("socket");
    return 1;
  }

  memset( (char*) &addr, 0, sizeof( addr ) );
  memset( (char*) &clientAddr, 0, sizeof( clientAddr ) );

  addr.sin_family = AF_INET;
  addr.sin_port = htons(1024);
  addr.sin_addr.s_addr = INADDR_ANY;

  printf("Connecting to local port %d\n", ntohs(addr.sin_port) );

  err = bind( sock, (struct sockaddr*) &addr, sizeof(addr) );
  if ( err == -1 ) {
    perror("bind");
    return 1;
  }

  clientAddr.sin_family = AF_INET;	
  clientAddr.sin_port = htons(280);
  printf("Using port %d on the SX\n", ntohs(clientAddr.sin_port) );
  clientAddr.sin_addr.s_addr = htonl( ipAddr );

  printf("Sending command\n" );
  
  if (sendto( sock, &commandBuf, commandLen, 0, (struct sockaddr*)&clientAddr,
	      sizeof( clientAddr )) == -1 ) {
    perror("sendto");
    return 1;
  }

  if ( command == 's' ) {
    printf("Set command sent\n");
    return 0;
  }

  printf("Starting receive\n");

  lenReceived = recvfrom( sock, &buffer, BUF_LEN, 0, (struct sockaddr*)&clientAddr, &clientLen);

  if ( command == 'e' ) {
  	printf("Hello message from the SX: %s\n", &buffer );
  }
  else if ( command == 'd' ) {
    if ( lenReceived != 192 ) {
      printf("No enough data received. Expected 192 bytes.\n" );
       return 1;
    }

    for ( i = 0; i < 8; i++ )
      printf("$%2X: %2X\n", i, buffer[i] );

    for ( i = 0; i < 16; i++ ) {
      printf("$%2.2X: ", i + 16 );
      for ( j = 0; j < 8; j++ )
	printf("%2.2X ", buffer[8 + i + (j * 24)] );
      printf("\n");
    }
  }
  else if ( command == 'g' ) {
    if ( lenReceived != 1 ) {
      printf("No enough data received. Expected 1 byte.\n" );
      return 1;
    }

    printf("Register value: %2.2X\n", buffer[0]);

  }
  return 0;
}
