/**
www.sourceforge.net/projects/tinyxml
Original file by Yves Berquin.

THIS FILE WAS ALTERED BY Tyge Løvset, 7. April 2005.
THIS FILE WAS ALTERED BY Josue Candela, 03. November 2010.

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/


#ifndef XML_USE_STL

#include "xmlstr.h"

namespace onyx2d
{

// Error value for find primitive
const cXMLString::size_type cXMLString::npos = static_cast< cXMLString::size_type >(-1);


// Null rep.
cXMLString::Rep cXMLString::nullrep_ = { 0, 0, { '\0' } };


void cXMLString::reserve (size_type cap)
{
	if (cap > capacity())
	{
		cXMLString tmp;
		tmp.init(length(), cap);
		memcpy(tmp.start(), data(), length());
		swap(tmp);
	}
}


cXMLString& cXMLString::assign(const char* str, size_type len)
{
	size_type cap = capacity();
	if (len > cap || cap > 3*(len + 8))
	{
		cXMLString tmp;
		tmp.init(len);
		memcpy(tmp.start(), str, len);
		swap(tmp);
	}
	else
	{
		memmove(start(), str, len);
		set_size(len);
	}
	return *this;
}


cXMLString& cXMLString::append(const char* str, size_type len)
{
	size_type newsize = length() + len;
	if (newsize > capacity())
	{
		reserve (newsize + capacity());
	}
	memmove(finish(), str, len);
	set_size(newsize);
	return *this;
}


cXMLString operator + (const cXMLString & a, const cXMLString & b)
{
	cXMLString tmp;
	tmp.reserve(a.length() + b.length());
	tmp += a;
	tmp += b;
	return tmp;
}

cXMLString operator + (const cXMLString & a, const char* b)
{
	cXMLString tmp;
	cXMLString::size_type b_len = static_cast<cXMLString::size_type>( strlen(b) );
	tmp.reserve(a.length() + b_len);
	tmp += a;
	tmp.append(b, b_len);
	return tmp;
}

cXMLString operator + (const char* a, const cXMLString & b)
{
	cXMLString tmp;
	cXMLString::size_type a_len = static_cast<cXMLString::size_type>( strlen(a) );
	tmp.reserve(a_len + b.length());
	tmp.append(a, a_len);
	tmp += b;
	return tmp;
}

}


#endif	// XML_USE_STL
