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

#ifndef UDNSPP_DNSARecord_INCLUDED
#define UDNSPP_DNSARecord_INCLUDED


#include <udns.h>
#include <string>
#include <vector>
#include <cassert>

#ifdef WINDOWS
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

namespace udnspp {
  // RR -> dns_rr_a4

typedef std::vector<std::string> DNSAddressList;

class DNSARecord
{
public:
  DNSARecord()
  {
  }

  DNSARecord(const DNSARecord& rr)
  {
    _address = rr._address;
    _cname = rr._cname;
    _qname = rr._qname;
    _ttl = rr._ttl;
  }

  ~DNSARecord()
  {
  }

  void swap(DNSARecord& rr)
  {
    std::swap(_address, rr._address);
    std::swap(_cname, rr._cname);
    std::swap(_qname, rr._qname);
    std::swap(_ttl, rr._ttl);
  }

  DNSARecord& operator=(const DNSARecord& rr)
  {
    DNSARecord clonable(rr);
    swap(clonable);
    return *this;
  }

  DNSAddressList& getAddressList()
  {
    return _address;
  }

  const DNSAddressList& getAddressList() const
  {
    return _address;
  }

  const std::string& getCName() const
  {
    return _cname;
  }

  const std::string& getQName() const
  {
    return _qname;
  }

  unsigned int getTTL() const
  {
    return _ttl;
  }

protected:
  DNSAddressList _address;      // IP4/IP6 Address Array
  std::string _cname;		// canonical name
  std::string _qname;		// original query name
  unsigned int _ttl;	  // TTL value
};


class DNSARecordV4 : public DNSARecord
{
public:
  DNSARecordV4()
  {
  }

  DNSARecordV4(dns_rr_a4* pRr)
  {
    parseRR(pRr);
  }


  DNSARecordV4& operator=(dns_rr_a4* pRr)
  {
    parseRR(pRr);
    return *this;
  }

  void parseRR(dns_rr_a4* pRr)
  {
    assert(pRr);
    _cname = pRr->dnsa4_cname;
    _qname = pRr->dnsa4_qname;
    _ttl = pRr->dnsa4_ttl;

    _address.clear();
    for (int i = 0; i < pRr->dnsa4_nrr; i++)
    {
      char buf[6 * 5 + 4 * 4];
      _address.push_back(dns_ntop(AF_INET, (void*)&pRr->dnsa4_addr[i], buf, sizeof(buf)));
    }
  }
};

class DNSARecordV6 : public DNSARecord
{
public:
  DNSARecordV6()
  {
  }

  DNSARecordV6(dns_rr_a6* pRr)
  {
    parseRR(pRr);
  }


  DNSARecordV6& operator=(dns_rr_a6* pRr)
  {
    parseRR(pRr);
    return *this;
  }

  void parseRR(dns_rr_a6* pRr)
  {
    assert(pRr);
    _cname = pRr->dnsa6_cname;
    _qname = pRr->dnsa6_qname;
    _ttl = pRr->dnsa6_ttl;

    _address.clear();
    for (int i = 0; i < pRr->dnsa6_nrr; i++)
    {
      char buf[6 * 5 + 4 * 4];
      _address.push_back(dns_ntop(AF_INET6, (void*)&pRr->dnsa6_addr[i], buf, sizeof(buf)));
    }
  }
};


} // namespace udns

#endif // UDNSPP_DNSARecord_INCLUDED