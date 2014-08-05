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
#include <udnspp/dnsquery.hpp>


namespace udnspp {


DNSQuery::DNSQuery() :
  _type(DNS_T_INVALID),
  _dn(0)
{
}

DNSQuery::DNSQuery(dns_type type, const std::string& name) :
  _type(DNS_T_INVALID),
  _dn(0)
{
  create(type, name);
}

DNSQuery::DNSQuery(const DNSQuery& query) :
  _type(DNS_T_INVALID),
  _dn(0)
{
  create(query._type, query._name);
}

DNSQuery::~DNSQuery()
{
  ::free(_dn);
}

void DNSQuery::create(dns_type type, const std::string& name)
{
  _type = type;
  _name = name;
  _dn = (unsigned char*)::malloc(dns_dnlen(_dn));
}

void DNSQuery::swap(DNSQuery& copy)
{
  std::swap(_type, copy._type);
  std::swap(_dn, copy._dn);
  std::swap(_name, copy._name);
}

DNSQuery& DNSQuery::operator=(const DNSQuery& query)
{
  DNSQuery clonable(query);
  swap(clonable);
  return *this;
}

}
