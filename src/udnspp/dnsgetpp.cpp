#include <udnspp/dnsresolver.hpp>
#include <iostream>
#include <cstdio>


#ifdef WINDOWS
#include <windows.h>
#include <winsock2.h>
#endif

#define PROGNAME "dnsgetpp"

static void die(int errnum, const char *fmt, ...) {
  va_list ap;
  fprintf(stderr, "%s: ", PROGNAME);
  va_start(ap, fmt); vfprintf(stderr, fmt, ap); va_end(ap);
  if (errnum) fprintf(stderr, ": %s\n", strerror(errnum));
  else putc('\n', stderr);
  fflush(stderr);
  exit(1);
}

int main(int argc, char** argv)
{
  //
  // Initialize the default context
  //

#ifdef WINDOWS
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
  {
    die(0, "WSAStartup() failed miserably! With error code %ld\n", WSAGetLastError());
  }
#endif

  udnspp::DNSContext::defaultContext()->open();
  udnspp::DNSResolver resolver;

  udnspp::DNSRRA4 rr = resolver.resolveA4(argv[1], 0);

  std::cout << "QName: " << rr.getRR().begin()->_qname << std::endl;
  std::cout << "Address: " << rr.getRR().begin()->_address << std::endl;
  std::cout << "CName: " << rr.getRR().begin()->_cname << std::endl;
  std::cout << "TTL: " << rr.getRR().begin()->_ttl << std::endl;
  
}