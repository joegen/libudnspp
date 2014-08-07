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
#include <cassert>
#include <udnspp/dnscontext.h>
#include <iostream>


namespace udnspp {


class DefaultContext : public DNSContext
{
public:
  DefaultContext();
  static dns_ctx* gDefCtx;
};

dns_ctx* DefaultContext::gDefCtx = 0;

DefaultContext::DefaultContext()
{
  if (!DefaultContext::gDefCtx)
  {
    _canFreeCtx = false;
    dns_init(0, 0);
    _pCtx = DefaultContext::gDefCtx = &dns_defctx;
  }
}


static DefaultContext* gDefaultContext = 0;

DNSContext::DNSContext()
{
  _pCtx = 0;
  _canFreeCtx = true;
  _socketFd = -1;
}

DNSContext::DNSContext(const DNSContext& context)
{
  _pCtx = dns_new(context._pCtx);
  _canFreeCtx = true;
  _socketFd = -1;
}

DNSContext::~DNSContext()
{
  if (_pCtx && _canFreeCtx)
    dns_free(_pCtx);
}

DNSContext* DNSContext::defaultContext()
{
  if (!gDefaultContext)
    gDefaultContext = new DefaultContext();
  return gDefaultContext;
}

dns_ctx* DNSContext::context()
{
  if (!_pCtx)
  {
    assert(DefaultContext::gDefCtx);
    _pCtx = dns_new(DefaultContext::gDefCtx);
    if (_pCtx)
      open();
  }
  return _pCtx;
}


}