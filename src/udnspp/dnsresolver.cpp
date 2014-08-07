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
  dns_rr_a4* pRr = resolve_a4(name, flags);
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
  dns_rr_a6* pRr = resolve_a6(name, flags);
  if (pRr)
  {
    DNSARecordV6 rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSARecord();
}

dns_rr_srv* DNSResolver::resolve_srv(const std::string& qname, int flags) const
{
  std::string srv;
  std::string proto;

  char* tok = 0;
  tok = std::strtok((char*)qname.c_str(), ".");
  if (!tok)
    return 0;
  srv = tok;

  tok = std::strtok(0, ".");
  if (!tok)
    return 0;
  proto = tok;

  return dns_resolve_srv(_pContext->context(), 
    qname.c_str() + srv.length() + proto.length() + 2, // domain less the srv and proto string plus two dots
    srv.c_str() + 1, // srv less the underscore
    proto.c_str() + 1,  // proto less the underscore
    flags);
}

DNSSRVRecord DNSResolver::resolveSrv(const std::string& name, int flags) const
{
  dns_rr_srv* pRr = resolve_srv(name, flags);
  if (pRr)
  {
    DNSSRVRecord rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSSRVRecord();
}


}
