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
#include <udnspp/dnsnaptrrecord.h>
#include <udnspp/dnsptrrecord.h>
#include <udnspp/dnsmxrecord.h>
#include <udnspp/dnstxtrecord.h>


namespace udnspp {


class DNSResolver
{
public:
  DNSResolver();

  DNSResolver(DNSContext* pContext);

  DNSARecord resolveA4(const std::string& name, int flags) const;

  DNSARecord resolveA6(const std::string& name, int flags) const;

  DNSSRVRecord resolveSRV(const std::string& name, int flags) const;

  DNSNAPTRRecord resolveNAPTR(const std::string& name, int flags) const;

  DNSPTRRecord resolvePTR4(const std::string& ip4address) const;

  DNSPTRRecord resolvePTR6(const std::string& ip6address) const;

  DNSMXRecord resolveMX(const std::string& name, int flags) const;

  DNSTXTRecord resolveTXT(const std::string& name, int qcls, int flags) const;

private:
  DNSContext* _pContext;
  bool _canDeleteContext;
};

//
// Inlines
//


} // namespace udnspp


#endif