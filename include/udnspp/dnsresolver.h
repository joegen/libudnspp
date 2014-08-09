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


#ifdef HAVE_BOOSTLIBS
#define ENABLE_ASYNC_RESOLVE
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#endif

namespace udnspp {

#ifdef ENABLE_ASYNC_RESOLVE

typedef boost::function<void(const DNSARecordV4&, void*)> DNSARecordV4CB;
typedef boost::function<void(const DNSARecordV6&, void*)> DNSARecordV6CB;
typedef boost::function<void(const DNSSRVRecord&, void*)> DNSSRVRecordCB;
typedef boost::function<void(const DNSPTRRecord&, void*)> DNSPTRRecordCB;
typedef boost::function<void(const DNSTXTRecord&, void*)> DNSTXTRecordCB;
typedef boost::function<void(const DNSNAPTRRecord&, void*)> DNSNAPTRRecordCB;
typedef boost::function<void(const DNSMXRecord&, void*)> DNSMXRecordCB;

#endif

class DNSResolver
{
public:
  DNSResolver();

  DNSResolver(DNSContext* pContext);

  ~DNSResolver();

  DNSARecord resolveA4(const std::string& name, int flags) const;

  DNSARecord resolveA6(const std::string& name, int flags) const;

  DNSSRVRecord resolveSRV(const std::string& name, int flags) const;

  DNSNAPTRRecord resolveNAPTR(const std::string& name, int flags) const;

  DNSPTRRecord resolvePTR4(const std::string& ip4address) const;

  DNSPTRRecord resolvePTR6(const std::string& ip6address) const;

  DNSMXRecord resolveMX(const std::string& name, int flags) const;

  DNSTXTRecord resolveTXT(const std::string& name, int qcls, int flags) const;

#ifdef ENABLE_ASYNC_RESOLVE

  void resolveA4(const std::string& name, int flags, DNSARecordV4CB cb, void* userData) const;

  void resolveA6(const std::string& name, int flags, DNSARecordV6CB cb, void* userData) const;

  void resolveSRV(const std::string& name, int flags, DNSSRVRecordCB cb, void* userData) const;

  void resolveNAPTR(const std::string& name, int flags, DNSNAPTRRecordCB cb, void* userData) const;

  void resolvePTR4(const std::string& ip4address, DNSPTRRecordCB cb, void* userData) const;

  void resolvePTR6(const std::string& ip6address, DNSPTRRecordCB cb, void* userData) const;

  void resolveMX(const std::string& name, int flags, DNSMXRecordCB cb, void* userData) const;

  void resolveTXT(const std::string& name, int qcls, int flags, DNSTXTRecordCB cb, void* userData) const;

  void start();

  void stop();

private:
  bool _stopProcessingEvents;

  boost::thread* _pThread;

  void startProcessingEvents();

  void processEvents();

#endif  // ENABLE_ASYNC_RESOLVE

private:
  DNSContext* _pContext;
  bool _canDeleteContext;
};

//
// Inlines
//


} // namespace udnspp


#endif