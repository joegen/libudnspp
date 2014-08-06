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

#ifndef UDNSPP_DNSRRA4_INCLUDED
#define UDNSPP_DNSRRA4_INCLUDED


#include <udns.h>
#include <string>
#include <vector>

namespace udnspp {


class DNSRRA4
{
public:
  struct A4
  {
    std::string _address; // IP4 Address
    std::string _cname;		// canonical name
    std::string _qname;		// original query name
    unsigned int _ttl;	  // TTL value		
  };

  typedef std::vector<A4> RRA4;

  DNSRRA4();

  DNSRRA4(const DNSRRA4& rr);
  
  DNSRRA4(dns_rr_a4* pRr);
  
  ~DNSRRA4();

  void swap(DNSRRA4& copy);

  DNSRRA4& operator=(const DNSRRA4& rr);

  DNSRRA4& operator=(dns_rr_a4* pRr);

  RRA4& getRR();

  const RRA4& getRR() const;

protected:
  void parseRR(dns_rr_a4* pRr);
private:
  RRA4 _rr;
};

//
// Inlines
//

inline DNSRRA4::RRA4& DNSRRA4::getRR()
{
  return _rr;
}

inline const DNSRRA4::RRA4& DNSRRA4::getRR() const
{
  return _rr;
}

} // namespace udns

#endif // UDNSPP_DNSRRA4_INCLUDED