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

#ifndef UDNSPP_DNSQUERY_INCLUDED
#define UDNSPP_DNSQUERY_INCLUDED

#include <udns.h> 
#include <string>

namespace udnspp {

class DNSQuery
{
public:
  DNSQuery();

  DNSQuery(dns_type type, const std::string& name);

  DNSQuery(const DNSQuery& query);

  ~DNSQuery();

  void create(dns_type type, const std::string& name);

  void swap(DNSQuery& copy);

  DNSQuery& operator=(const DNSQuery& query);

  dns_type getType() const;

  const unsigned char* getDn() const;

  unsigned char*& getDn();

  const std::string& getName() const;

private:
  dns_type _type;
  unsigned char* _dn;
  std::string _name;
};

//
// Inlines
//

inline dns_type DNSQuery::getType() const
{
  return _type;
}

inline const unsigned char* DNSQuery::getDn() const
{
  return _dn;
}

inline unsigned char*& DNSQuery::getDn()
{
  return _dn;
}

inline const std::string& DNSQuery::getName() const
{
  return _name;
}

} // udnspp

#endif


