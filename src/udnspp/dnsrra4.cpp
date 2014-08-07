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


#include <cassert>
#include <udnspp/dnsarecord.hpp>


#ifdef WINDOWS
#include <windows.h>
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif


namespace udnspp {


DNSRRA4::DNSRRA4()
{
}

DNSRRA4::DNSRRA4(const DNSRRA4& rr)
{
  _address = rr._address;
  _cname = rr._cname;
  _qname = rr._qname;
  _ttl = rr._ttl;
}

DNSRRA4::DNSRRA4(dns_rr_a4* pRr)
{
  parseRR(pRr);
}

DNSRRA4::~DNSRRA4()
{
}

void DNSRRA4::swap(DNSRRA4& rr)
{
  std::swap(_address, rr._address);
  std::swap(_cname, rr._cname);
  std::swap(_qname, rr._qname);
  std::swap(_ttl, rr._ttl);
}

DNSRRA4& DNSRRA4::operator=(const DNSRRA4& rr)
{
  DNSRRA4 clonable(rr);
  swap(clonable);
  return *this;
}

DNSRRA4& DNSRRA4::operator=(dns_rr_a4* pRr)
{
  parseRR(pRr);
  return *this;
}

void DNSRRA4::parseRR(dns_rr_a4* pRr)
{
  assert(pRr);
  _cname = pRr->dnsa4_cname;
  _qname = pRr->dnsa4_qname;
  _ttl = pRr->dnsa4_ttl;

  for (int i = 0; i < pRr->dnsa4_nrr; i++) 
  {    
    _address.push_back(inet_ntoa(pRr->dnsa4_addr[i]));
  }
}


} // namespace udns

