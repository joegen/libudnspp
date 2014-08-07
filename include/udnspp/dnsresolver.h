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

#ifndef UDNSPP_DNSRESOLVER_INCLUDED
#define UDNSPP_DNSRESOLVER_INCLUDED


#include <udnspp/dnsquery.h>
#include <udnspp/dnscontext.h>
#include <udnspp/dnsarecord.h>
#include <udnspp/dnssrvrecord.h>


namespace udnspp {


class DNSResolver
{
public:
  DNSResolver();

  DNSResolver(DNSContext* pContext);

  DNSARecord resolveA4(const std::string& name, int flags) const;

  DNSARecord resolveA6(const std::string& name, int flags) const;

  DNSSRVRecord resolveSrv(const std::string& name, int flags) const;

protected:
  dns_rr_a4* resolve_a4(const std::string& name, int flags) const;

  dns_rr_a6* resolve_a6(const std::string& name, int flags) const;

  dns_rr_srv* resolve_srv(const std::string& name, int flags) const;
private:
  DNSContext* _pContext;
  bool _canDeleteContext;
};

//
// Inlines
//

inline dns_rr_a4* DNSResolver::resolve_a4(const std::string& name, int flags) const
{
  return dns_resolve_a4(_pContext->context(), name.c_str(), flags);
}

inline dns_rr_a6* DNSResolver::resolve_a6(const std::string& name, int flags) const
{
  return dns_resolve_a6(_pContext->context(), name.c_str(), flags);
}


} // namespace udnspp


#endif