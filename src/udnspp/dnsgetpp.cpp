#include <udnspp/dnsresolver.h>
#include <iostream>
#include <cstdio>
#include <sstream>


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
  std::string qname = "bridge.ossapp.com";
  if (argc >= 2)
    qname = argv[1];

  udnspp::DNSContext::defaultContext()->open();
  udnspp::DNSResolver resolver;

  udnspp::DNSARecord rr = resolver.resolveA4(qname, 0);

  if (!rr.getRecords().empty())
  {
    std::cout << "======A Record=====" << std::endl;
    std::cout << "QName: " << rr.getQName() << std::endl;
    std::cout << "CName: " << rr.getCName() << std::endl;
    std::cout << "Address: " << rr.getRecords().front() << std::endl;
    std::cout << "TTL: " << rr.getTTL() << std::endl;
  }
  else
  {
    std::cout << qname << " did not yield any A Record result." << std::endl;
    exit(-1);
  }


  std::ostringstream srvudp;
  srvudp << "_sip._udp." << qname;
  udnspp::DNSSRVRecord srv_rr = resolver.resolveSRV(srvudp.str(), 0);

  if (!srv_rr.getRecords().empty())
  {
    std::cout << "======SRV Record=====" << std::endl;
    std::cout << "QName: " << srv_rr.getQName() << std::endl;
    std::cout << "CName: " << srv_rr.getCName() << std::endl;
    std::cout << "Address: " << srv_rr.getRecords().front().name << std::endl;
    std::cout << "TTL: " << srv_rr.getTTL() << std::endl;
  }
  else
  {
    std::cout << qname << " did not yield any SRV Record result." << std::endl;
    exit(-1);
  }

  exit(0);
}