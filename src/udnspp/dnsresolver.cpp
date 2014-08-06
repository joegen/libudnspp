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
#include <udnspp/dnsresolver.hpp>

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

dns_rr_a4* DNSResolver::resolve_a4(const std::string& name, int flags)
{
  return dns_resolve_a4(_pContext->context(), name.c_str(), flags);
}

dns_rr_a6* DNSResolver::resolve_a6(const std::string& name, int flags)
{
  return dns_resolve_a6(_pContext->context(), name.c_str(), flags);
}

DNSRRA4 DNSResolver::resolveA4(const std::string& name, int flags)
{
  dns_rr_a4* pRr = resolve_a4(name, flags);
  if (pRr)
  {
    DNSRRA4 rr(pRr);
    free(pRr);
    return rr;
  }
  return DNSRRA4();
}


}
