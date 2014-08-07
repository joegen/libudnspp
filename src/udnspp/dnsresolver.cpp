// Library: libudnspp
// Copyright (c) OSS Software Solutions
// Contributor: Joegen Baclor - mailto:joegen@ossapp.com
//
// Permission is hereby granted, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, execute, and to prepare 
// derivative works of the Software, all subject to the 
// "GNU Lesser General Public License (LGPL)".
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include <cstdlib>
#include <cstring>
#include <iostream>
#include <udnspp/dnsresolver.h>

#ifdef WINDOWS
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif


namespace udnspp {


DNSResolver::DNSResolver()
{
  _canDeleteContext = true;
  _pContext = new DNSContext();
}

DNSResolver::DNSResolver(DNSContext* pContext)
{
  _canDeleteContext = false;
  _pContext = pContext;
}

DNSARecord DNSResolver::resolveA4(const std::string& name, int flags) const
{
  dns_rr_a4* pRr = dns_resolve_a4(_pContext->context(), name.c_str(), flags);
  if (pRr)
  {
    DNSARecordV4 rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSARecord();
}

DNSARecord DNSResolver::resolveA6(const std::string& name, int flags) const
{
  dns_rr_a6* pRr = dns_resolve_a6(_pContext->context(), name.c_str(), flags);
  if (pRr)
  {
    DNSARecordV6 rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSARecord();
}

DNSPTRRecord DNSResolver::resolvePTR4(const std::string& address) const
{
  in_addr ip4;
  dns_pton(AF_INET, address.c_str(), &ip4);
  dns_rr_ptr* pRr = dns_resolve_a4ptr(_pContext->context(), &ip4);
  if (pRr)
  {
    DNSPTRRecord rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSPTRRecord();
}

DNSPTRRecord DNSResolver::resolvePTR6(const std::string& address) const
{
  in6_addr ip6;
  dns_pton(AF_INET6, address.c_str(), &ip6);
  dns_rr_ptr* pRr = dns_resolve_a6ptr(_pContext->context(), &ip6);
  if (pRr)
  {
    DNSPTRRecord rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSPTRRecord();
}

DNSMXRecord DNSResolver::resolveMX(const std::string& name, int flags) const
{
  dns_rr_mx* pRr = dns_resolve_mx(_pContext->context(), name.c_str(), flags);
  if (pRr)
  {
    DNSMXRecord rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSMXRecord();
}

DNSNAPTRRecord DNSResolver::resolveNAPTR(const std::string& name, int flags) const
{
  dns_rr_naptr* pRr = dns_resolve_naptr(_pContext->context(), name.c_str(), flags);
  if (pRr)
  {
    DNSNAPTRRecord rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSNAPTRRecord();
}

DNSTXTRecord DNSResolver::resolveTXT(const std::string& name, int qcls, int flags) const
{
  dns_rr_txt* pRr = dns_resolve_txt(_pContext->context(), name.c_str(), qcls, flags);
  if (pRr)
  {
    DNSTXTRecord rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSTXTRecord();
}


DNSSRVRecord DNSResolver::resolveSRV(const std::string& name, int flags) const
{
  std::string srv;
  std::string proto;

  char* tok = 0;
  tok = std::strtok((char*)name.c_str(), ".");
  if (!tok)
    return 0;
  srv = tok;

  tok = std::strtok(0, ".");
  if (!tok)
    return 0;
  proto = tok;

  dns_rr_srv* pRr = dns_resolve_srv(_pContext->context(),
    name.c_str() + srv.length() + proto.length() + 2, // domain less the srv and proto string plus two dots
    srv.c_str() + 1, // srv less the underscore
    proto.c_str() + 1,  // proto less the underscore
    flags);

  if (pRr)
  {
    DNSSRVRecord rr(pRr);
    free(pRr);
    return rr;
  }

  return DNSSRVRecord();
}


}
