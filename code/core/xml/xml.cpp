/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2006 Lee Thomason (www.grinninglizard.com)

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


#include <ctype.h>

#ifdef XML_USE_STL
#include <sstream>
#include <iostream>
#endif

#include "xml.h"

namespace onyx2d
{

FILE* cXMLFOpen( const char* filename, const char* mode );

bool cXMLBase::condenseWhiteSpace = true;

// Microsoft compiler security
FILE* XMLFOpen( const char* filename, const char* mode )
{
	#if defined(_MSC_VER) && (_MSC_VER >= 1400 )
		FILE* fp = 0;
		errno_t err = fopen_s( &fp, filename, mode );
		if ( !err && fp )
			return fp;
		return 0;
	#else
		return fopen( filename, mode );
	#endif
}

void cXMLBase::EncodeString( const XML_STRING& str, XML_STRING* outString )
{
	int i=0;

	while( i<(int)str.length() )
	{
		unsigned char c = (unsigned char) str[i];

		if (    c == '&'
		     && i < ( (int)str.length() - 2 )
			 && str[i+1] == '#'
			 && str[i+2] == 'x' )
		{
			// Hexadecimal character reference.
			// Pass through unchanged.
			// &#xA9;	-- copyright symbol, for example.
			//
			// The -1 is a bug fix from Rob Laveaux. It keeps
			// an overflow from happening if there is no ';'.
			// There are actually 2 ways to exit this loop -
			// while fails (error case) and break (semicolon found).
			// However, there is no mechanism (currently) for
			// this function to return an error.
			while ( i<(int)str.length()-1 )
			{
				outString->append( str.c_str() + i, 1 );
				++i;
				if ( str[i] == ';' )
					break;
			}
		}
		else if ( c == '&' )
		{
			outString->append( entity[0].str, entity[0].strLength );
			++i;
		}
		else if ( c == '<' )
		{
			outString->append( entity[1].str, entity[1].strLength );
			++i;
		}
		else if ( c == '>' )
		{
			outString->append( entity[2].str, entity[2].strLength );
			++i;
		}
		else if ( c == '\"' )
		{
			outString->append( entity[3].str, entity[3].strLength );
			++i;
		}
		else if ( c == '\'' )
		{
			outString->append( entity[4].str, entity[4].strLength );
			++i;
		}
		else if ( c < 32 )
		{
			// Easy pass at non-alpha/numeric/symbol
			// Below 32 is symbolic.
			char buf[ 32 ];

			#if defined(XML_SNPRINTF)
				XML_SNPRINTF( buf, sizeof(buf), "&#x%02X;", (unsigned) ( c & 0xff ) );
			#else
				sprintf( buf, "&#x%02X;", (unsigned) ( c & 0xff ) );
			#endif

			//*ME:	warning C4267: convert 'size_t' to 'int'
			//*ME:	Int-Cast to make compiler happy ...
			outString->append( buf, (int)strlen( buf ) );
			++i;
		}
		else
		{
			//char realc = (char) c;
			//outString->append( &realc, 1 );
			*outString += (char) c;	// somewhat more efficient function call.
			++i;
		}
	}
}


cXMLNode::cXMLNode( NodeType _type ) : cXMLBase()
{
	parent = 0;
	type = _type;
	firstChild = 0;
	lastChild = 0;
	prev = 0;
	next = 0;
}


cXMLNode::~cXMLNode()
{
	cXMLNode* node = firstChild;
	cXMLNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}
}


void cXMLNode::CopyTo( cXMLNode* target ) const
{
	target->SetValue (value.c_str() );
	target->userData = userData;
	target->location = location;
}


void cXMLNode::Clear()
{
	cXMLNode* node = firstChild;
	cXMLNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}

	firstChild = 0;
	lastChild = 0;
}


cXMLNode* cXMLNode::LinkEndChild( cXMLNode* node )
{
	assert( node->parent == 0 || node->parent == this );
	assert( node->GetDocument() == 0 || node->GetDocument() == this->GetDocument() );

	if ( node->Type() == cXMLNode::TINYXML_DOCUMENT )
	{
		delete node;
		if ( GetDocument() ) GetDocument()->SetError( XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, XML_ENCODING_UNKNOWN );
		return 0;
	}

	node->parent = this;

	node->prev = lastChild;
	node->next = 0;

	if ( lastChild )
		lastChild->next = node;
	else
		firstChild = node;			// it was an empty list.

	lastChild = node;
	return node;
}


cXMLNode* cXMLNode::InsertEndChild( const cXMLNode& addThis )
{
	if ( addThis.Type() == cXMLNode::TINYXML_DOCUMENT )
	{
		if ( GetDocument() ) GetDocument()->SetError( XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, XML_ENCODING_UNKNOWN );
		return 0;
	}
	cXMLNode* node = addThis.Clone();
	if ( !node )
		return 0;

	return LinkEndChild( node );
}


cXMLNode* cXMLNode::InsertBeforeChild( cXMLNode* beforeThis, const cXMLNode& addThis )
{
	if ( !beforeThis || beforeThis->parent != this ) {
		return 0;
	}
	if ( addThis.Type() == cXMLNode::TINYXML_DOCUMENT )
	{
		if ( GetDocument() ) GetDocument()->SetError( XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, XML_ENCODING_UNKNOWN );
		return 0;
	}

	cXMLNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->next = beforeThis;
	node->prev = beforeThis->prev;
	if ( beforeThis->prev )
	{
		beforeThis->prev->next = node;
	}
	else
	{
		assert( firstChild == beforeThis );
		firstChild = node;
	}
	beforeThis->prev = node;
	return node;
}


cXMLNode* cXMLNode::InsertAfterChild( cXMLNode* afterThis, const cXMLNode& addThis )
{
	if ( !afterThis || afterThis->parent != this ) {
		return 0;
	}
	if ( addThis.Type() == cXMLNode::TINYXML_DOCUMENT )
	{
		if ( GetDocument() ) GetDocument()->SetError( XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, XML_ENCODING_UNKNOWN );
		return 0;
	}

	cXMLNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->prev = afterThis;
	node->next = afterThis->next;
	if ( afterThis->next )
	{
		afterThis->next->prev = node;
	}
	else
	{
		assert( lastChild == afterThis );
		lastChild = node;
	}
	afterThis->next = node;
	return node;
}


cXMLNode* cXMLNode::ReplaceChild( cXMLNode* replaceThis, const cXMLNode& withThis )
{
	if ( !replaceThis )
		return 0;

	if ( replaceThis->parent != this )
		return 0;

	if ( withThis.ToDocument() ) {
		// A document can never be a child.	Thanks to Noam.
		cXMLDocument* document = GetDocument();
		if ( document )
			document->SetError( XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, XML_ENCODING_UNKNOWN );
		return 0;
	}

	cXMLNode* node = withThis.Clone();
	if ( !node )
		return 0;

	node->next = replaceThis->next;
	node->prev = replaceThis->prev;

	if ( replaceThis->next )
		replaceThis->next->prev = node;
	else
		lastChild = node;

	if ( replaceThis->prev )
		replaceThis->prev->next = node;
	else
		firstChild = node;

	delete replaceThis;
	node->parent = this;
	return node;
}


bool cXMLNode::RemoveChild( cXMLNode* removeThis )
{
	if ( !removeThis ) {
		return false;
	}

	if ( removeThis->parent != this )
	{
		assert( 0 );
		return false;
	}

	if ( removeThis->next )
		removeThis->next->prev = removeThis->prev;
	else
		lastChild = removeThis->prev;

	if ( removeThis->prev )
		removeThis->prev->next = removeThis->next;
	else
		firstChild = removeThis->next;

	delete removeThis;
	return true;
}

const cXMLNode* cXMLNode::FirstChild( const char * _value ) const
{
	const cXMLNode* node;
	for ( node = firstChild; node; node = node->next )
	{
		if ( strcmp( node->Value(), _value ) == 0 )
			return node;
	}
	return 0;
}


const cXMLNode* cXMLNode::LastChild( const char * _value ) const
{
	const cXMLNode* node;
	for ( node = lastChild; node; node = node->prev )
	{
		if ( strcmp( node->Value(), _value ) == 0 )
			return node;
	}
	return 0;
}


const cXMLNode* cXMLNode::IterateChildren( const cXMLNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild();
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling();
	}
}


const cXMLNode* cXMLNode::IterateChildren( const char * val, const cXMLNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild( val );
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling( val );
	}
}


const cXMLNode* cXMLNode::NextSibling( const char * _value ) const
{
	const cXMLNode* node;
	for ( node = next; node; node = node->next )
	{
		if ( strcmp( node->Value(), _value ) == 0 )
			return node;
	}
	return 0;
}


const cXMLNode* cXMLNode::PreviousSibling( const char * _value ) const
{
	const cXMLNode* node;
	for ( node = prev; node; node = node->prev )
	{
		if ( strcmp( node->Value(), _value ) == 0 )
			return node;
	}
	return 0;
}


void cXMLElement::RemoveAttribute( const char * name )
{
    #ifdef XML_USE_STL
	XML_STRING str( name );
	cXMLAttribute* node = attributeSet.Find( str );
	#else
	cXMLAttribute* node = attributeSet.Find( name );
	#endif
	if ( node )
	{
		attributeSet.Remove( node );
		delete node;
	}
}

const cXMLElement* cXMLNode::FirstChildElement() const
{
	const cXMLNode* node;

	for (	node = FirstChild();
			node;
			node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


const cXMLElement* cXMLNode::FirstChildElement( const char * _value ) const
{
	const cXMLNode* node;

	for (	node = FirstChild( _value );
			node;
			node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


const cXMLElement* cXMLNode::NextSiblingElement() const
{
	const cXMLNode* node;

	for (	node = NextSibling();
			node;
			node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


const cXMLElement* cXMLNode::NextSiblingElement( const char * _value ) const
{
	const cXMLNode* node;

	for (	node = NextSibling( _value );
			node;
			node = node->NextSibling( _value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


const cXMLDocument* cXMLNode::GetDocument() const
{
	const cXMLNode* node;

	for( node = this; node; node = node->parent )
	{
		if ( node->ToDocument() )
			return node->ToDocument();
	}
	return 0;
}


cXMLElement::cXMLElement (const char * _value)
	: cXMLNode( cXMLNode::TINYXML_ELEMENT )
{
	firstChild = lastChild = 0;
	value = _value;
}


#ifdef XML_USE_STL
cXMLElement::cXMLElement( const std::string& _value )
	: cXMLNode( cXMLNode::TINYXML_ELEMENT )
{
	firstChild = lastChild = 0;
	value = _value;
}
#endif


cXMLElement::cXMLElement( const cXMLElement& copy)
	: cXMLNode( cXMLNode::TINYXML_ELEMENT )
{
	firstChild = lastChild = 0;
	copy.CopyTo( this );
}


void cXMLElement::operator=( const cXMLElement& base )
{
	ClearThis();
	base.CopyTo( this );
}


cXMLElement::~cXMLElement()
{
	ClearThis();
}


void cXMLElement::ClearThis()
{
	Clear();
	while( attributeSet.First() )
	{
		cXMLAttribute* node = attributeSet.First();
		attributeSet.Remove( node );
		delete node;
	}
}


const char* cXMLElement::Attribute( const char* name ) const
{
	const cXMLAttribute* node = attributeSet.Find( name );
	if ( node )
		return node->Value();
	return 0;
}


#ifdef XML_USE_STL
const std::string* cXMLElement::Attribute( const std::string& name ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	if ( attrib )
		return &attrib->ValueStr();
	return 0;
}
#endif


const char* cXMLElement::Attribute( const char* name, int* i ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	const char* result = 0;

	if ( attrib ) {
		result = attrib->Value();
		if ( i ) {
			attrib->QueryIntValue( i );
		}
	}
	return result;
}


#ifdef XML_USE_STL
const std::string* cXMLElement::Attribute( const std::string& name, int* i ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	const std::string* result = 0;

	if ( attrib ) {
		result = &attrib->ValueStr();
		if ( i ) {
			attrib->QueryIntValue( i );
		}
	}
	return result;
}
#endif


const char* cXMLElement::Attribute( const char* name, double* d ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	const char* result = 0;

	if ( attrib ) {
		result = attrib->Value();
		if ( d ) {
			attrib->QueryDoubleValue( d );
		}
	}
	return result;
}


#ifdef XML_USE_STL
const std::string* cXMLElement::Attribute( const std::string& name, double* d ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	const std::string* result = 0;

	if ( attrib ) {
		result = &attrib->ValueStr();
		if ( d ) {
			attrib->QueryDoubleValue( d );
		}
	}
	return result;
}
#endif


int cXMLElement::QueryIntAttribute( const char* name, int* ival ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	if ( !attrib )
		return XML_NO_ATTRIBUTE;
	return attrib->QueryIntValue( ival );
}


#ifdef XML_USE_STL
int cXMLElement::QueryIntAttribute( const std::string& name, int* ival ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	if ( !attrib )
		return XML_NO_ATTRIBUTE;
	return attrib->QueryIntValue( ival );
}
#endif


int cXMLElement::QueryDoubleAttribute( const char* name, double* dval ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	if ( !attrib )
		return XML_NO_ATTRIBUTE;
	return attrib->QueryDoubleValue( dval );
}


#ifdef XML_USE_STL
int cXMLElement::QueryDoubleAttribute( const std::string& name, double* dval ) const
{
	const cXMLAttribute* attrib = attributeSet.Find( name );
	if ( !attrib )
		return XML_NO_ATTRIBUTE;
	return attrib->QueryDoubleValue( dval );
}
#endif


void cXMLElement::SetAttribute( const char * name, int val )
{
	cXMLAttribute* attrib = attributeSet.FindOrCreate( name );
	if ( attrib ) {
		attrib->SetIntValue( val );
	}
}


#ifdef XML_USE_STL
void cXMLElement::SetAttribute( const std::string& name, int val )
{
	cXMLAttribute* attrib = attributeSet.FindOrCreate( name );
	if ( attrib ) {
		attrib->SetIntValue( val );
	}
}
#endif


void cXMLElement::SetDoubleAttribute( const char * name, double val )
{
	cXMLAttribute* attrib = attributeSet.FindOrCreate( name );
	if ( attrib ) {
		attrib->SetDoubleValue( val );
	}
}


#ifdef XML_USE_STL
void cXMLElement::SetDoubleAttribute( const std::string& name, double val )
{
	cXMLAttribute* attrib = attributeSet.FindOrCreate( name );
	if ( attrib ) {
		attrib->SetDoubleValue( val );
	}
}
#endif


void cXMLElement::SetAttribute( const char * cname, const char * cvalue )
{
	cXMLAttribute* attrib = attributeSet.FindOrCreate( cname );
	if ( attrib ) {
		attrib->SetValue( cvalue );
	}
}


#ifdef XML_USE_STL
void cXMLElement::SetAttribute( const std::string& _name, const std::string& _value )
{
	cXMLAttribute* attrib = attributeSet.FindOrCreate( _name );
	if ( attrib ) {
		attrib->SetValue( _value );
	}
}
#endif


void cXMLElement::Print( FILE* cfile, int depth ) const
{
	int i;
	assert( cfile );
	for ( i=0; i<depth; i++ ) {
		fprintf( cfile, "    " );
	}

	fprintf( cfile, "<%s", value.c_str() );

	const cXMLAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		fprintf( cfile, " " );
		attrib->Print( cfile, depth );
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	cXMLNode* node;
	if ( !firstChild )
	{
		fprintf( cfile, " />" );
	}
	else if ( firstChild == lastChild && firstChild->ToText() )
	{
		fprintf( cfile, ">" );
		firstChild->Print( cfile, depth + 1 );
		fprintf( cfile, "</%s>", value.c_str() );
	}
	else
	{
		fprintf( cfile, ">" );

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			if ( !node->ToText() )
			{
				fprintf( cfile, "\n" );
			}
			node->Print( cfile, depth+1 );
		}
		fprintf( cfile, "\n" );
		for( i=0; i<depth; ++i ) {
			fprintf( cfile, "    " );
		}
		fprintf( cfile, "</%s>", value.c_str() );
	}
}


void cXMLElement::CopyTo( cXMLElement* target ) const
{
	// superclass:
	cXMLNode::CopyTo( target );

	// Element class:
	// Clone the attributes, then clone the children.
	const cXMLAttribute* attribute = 0;
	for(	attribute = attributeSet.First();
	attribute;
	attribute = attribute->Next() )
	{
		target->SetAttribute( attribute->Name(), attribute->Value() );
	}

	cXMLNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		target->LinkEndChild( node->Clone() );
	}
}

bool cXMLElement::Accept( cXMLVisitor* visitor ) const
{
	if ( visitor->VisitEnter( *this, attributeSet.First() ) )
	{
		for ( const cXMLNode* node=FirstChild(); node; node=node->NextSibling() )
		{
			if ( !node->Accept( visitor ) )
				break;
		}
	}
	return visitor->VisitExit( *this );
}


cXMLNode* cXMLElement::Clone() const
{
	cXMLElement* clone = new cXMLElement( Value() );
	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


const char* cXMLElement::GetText() const
{
	const cXMLNode* child = this->FirstChild();
	if ( child ) {
		const cXMLText* childText = child->ToText();
		if ( childText ) {
			return childText->Value();
		}
	}
	return 0;
}


cXMLDocument::cXMLDocument() : cXMLNode( cXMLNode::TINYXML_DOCUMENT )
{
	tabsize = 4;
	useMicrosoftBOM = false;
	ClearError();
}

cXMLDocument::cXMLDocument( const char * documentName ) : cXMLNode( cXMLNode::TINYXML_DOCUMENT )
{
	tabsize = 4;
	useMicrosoftBOM = false;
	value = documentName;
	ClearError();
}


#ifdef XML_USE_STL
cXMLDocument::cXMLDocument( const std::string& documentName ) : cXMLNode( cXMLNode::TINYXML_DOCUMENT )
{
	tabsize = 4;
	useMicrosoftBOM = false;
    value = documentName;
	ClearError();
}
#endif


cXMLDocument::cXMLDocument( const cXMLDocument& copy ) : cXMLNode( cXMLNode::TINYXML_DOCUMENT )
{
	copy.CopyTo( this );
}


void cXMLDocument::operator=( const cXMLDocument& copy )
{
	Clear();
	copy.CopyTo( this );
}


bool cXMLDocument::LoadFile( XMLEncoding encoding )
{
	return LoadFile( Value(), encoding );
}


bool cXMLDocument::SaveFile() const
{
	return SaveFile( Value() );
}

bool cXMLDocument::LoadFile( const char* _filename, XMLEncoding encoding )
{
	XML_STRING filename( _filename );
	value = filename;

	// reading in binary mode so that tinyxml can normalize the EOL
	FILE* file = XMLFOpen( value.c_str (), "rb" );

	if ( file )
	{
		bool result = LoadFile( file, encoding );
		fclose( file );
		return result;
	}
	else
	{
		SetError( XML_ERROR_OPENING_FILE, 0, 0, XML_ENCODING_UNKNOWN );
		return false;
	}
}

bool cXMLDocument::LoadFile( FILE* file, XMLEncoding encoding )
{
	if ( !file )
	{
		SetError( XML_ERROR_OPENING_FILE, 0, 0, XML_ENCODING_UNKNOWN );
		return false;
	}

	// Delete the existing data:
	Clear();
	location.Clear();

	// Get the file size, so we can pre-allocate the string. HUGE speed impact.
	long length = 0;
	fseek( file, 0, SEEK_END );
	length = ftell( file );
	fseek( file, 0, SEEK_SET );

	// Strange case, but good to handle up front.
	if ( length <= 0 )
	{
		SetError( XML_ERROR_DOCUMENT_EMPTY, 0, 0, XML_ENCODING_UNKNOWN );
		return false;
	}

	// Subtle bug here. TinyXml did use fgets. But from the XML spec:
	// 2.11 End-of-Line Handling
	// <snip>
	// <quote>
	// ...the XML processor MUST behave as if it normalized all line breaks in external
	// parsed entities (including the document entity) on input, before parsing, by translating
	// both the two-character sequence #xD #xA and any #xD that is not followed by #xA to
	// a single #xA character.
	// </quote>
	//
	// It is not clear fgets does that, and certainly isn't clear it works cross platform.
	// Generally, you expect fgets to translate from the convention of the OS to the c/unix
	// convention, and not work generally.

	/*
	while( fgets( buf, sizeof(buf), file ) )
	{
		data += buf;
	}
	*/

	char* buf = new char[ length+1 ];
	buf[0] = 0;

	if ( fread( buf, length, 1, file ) != 1 ) {
		delete [] buf;
		SetError( XML_ERROR_OPENING_FILE, 0, 0, XML_ENCODING_UNKNOWN );
		return false;
	}

	// Process the buffer in place to normalize new lines. (See comment above.)
	// Copies from the 'p' to 'q' pointer, where p can advance faster if
	// a newline-carriage return is hit.
	//
	// Wikipedia:
	// Systems based on ASCII or a compatible character set use either LF  (Line feed, '\n', 0x0A, 10 in decimal) or
	// CR (Carriage return, '\r', 0x0D, 13 in decimal) individually, or CR followed by LF (CR+LF, 0x0D 0x0A)...
	//		* LF:    Multics, Unix and Unix-like systems (GNU/Linux, AIX, Xenix, Mac OS X, FreeBSD, etc.), BeOS, Amiga, RISC OS, and others
    //		* CR+LF: DEC RT-11 and most other early non-Unix, non-IBM OSes, CP/M, MP/M, DOS, OS/2, Microsoft Windows, Symbian OS
    //		* CR:    Commodore 8-bit machines, Apple II family, Mac OS up to version 9 and OS-9

	const char* p = buf;	// the read head
	char* q = buf;			// the write head
	const char CR = 0x0d;
	const char LF = 0x0a;

	buf[length] = 0;
	while( *p ) {
		assert( p < (buf+length) );
		assert( q <= (buf+length) );
		assert( q <= p );

		if ( *p == CR ) {
			*q++ = LF;
			p++;
			if ( *p == LF ) {		// check for CR+LF (and skip LF)
				p++;
			}
		}
		else {
			*q++ = *p++;
		}
	}
	assert( q <= (buf+length) );
	*q = 0;

	Parse( buf, 0, encoding );

	delete [] buf;
	return !Error();
}


bool cXMLDocument::SaveFile( const char * filename ) const
{
	// The old c stuff lives on...
	FILE* fp = XMLFOpen( filename, "w" );
	if ( fp )
	{
		bool result = SaveFile( fp );
		fclose( fp );
		return result;
	}
	return false;
}


bool cXMLDocument::SaveFile( FILE* fp ) const
{
	if ( useMicrosoftBOM )
	{
		const unsigned char XML_UTF_LEAD_0 = 0xefU;
		const unsigned char XML_UTF_LEAD_1 = 0xbbU;
		const unsigned char XML_UTF_LEAD_2 = 0xbfU;

		fputc( XML_UTF_LEAD_0, fp );
		fputc( XML_UTF_LEAD_1, fp );
		fputc( XML_UTF_LEAD_2, fp );
	}
	Print( fp, 0 );
	return (ferror(fp) == 0);
}


void cXMLDocument::CopyTo( cXMLDocument* target ) const
{
	cXMLNode::CopyTo( target );

	target->error = error;
	target->errorId = errorId;
	target->errorDesc = errorDesc;
	target->tabsize = tabsize;
	target->errorLocation = errorLocation;
	target->useMicrosoftBOM = useMicrosoftBOM;

	cXMLNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		target->LinkEndChild( node->Clone() );
	}
}


cXMLNode* cXMLDocument::Clone() const
{
	cXMLDocument* clone = new cXMLDocument();
	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void cXMLDocument::Print( FILE* cfile, int depth ) const
{
	assert( cfile );
	for ( const cXMLNode* node=FirstChild(); node; node=node->NextSibling() )
	{
		node->Print( cfile, depth );
		fprintf( cfile, "\n" );
	}
}


bool cXMLDocument::Accept( cXMLVisitor* visitor ) const
{
	if ( visitor->VisitEnter( *this ) )
	{
		for ( const cXMLNode* node=FirstChild(); node; node=node->NextSibling() )
		{
			if ( !node->Accept( visitor ) )
				break;
		}
	}
	return visitor->VisitExit( *this );
}


const cXMLAttribute* cXMLAttribute::Next() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}

/*
XMLAttribute* cXMLAttribute::Next()
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}
*/

const cXMLAttribute* cXMLAttribute::Previous() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}

/*
XMLAttribute* cXMLAttribute::Previous()
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}
*/

void cXMLAttribute::Print( FILE* cfile, int /*depth*/, XML_STRING* str ) const
{
	XML_STRING n, v;

	EncodeString( name, &n );
	EncodeString( value, &v );

	if (value.find ('\"') == XML_STRING::npos) {
		if ( cfile ) {
		fprintf (cfile, "%s=\"%s\"", n.c_str(), v.c_str() );
		}
		if ( str ) {
			(*str) += n; (*str) += "=\""; (*str) += v; (*str) += "\"";
		}
	}
	else {
		if ( cfile ) {
		fprintf (cfile, "%s='%s'", n.c_str(), v.c_str() );
		}
		if ( str ) {
			(*str) += n; (*str) += "='"; (*str) += v; (*str) += "'";
		}
	}
}


int cXMLAttribute::QueryIntValue( int* ival ) const
{
	if ( XML_SSCANF( value.c_str(), "%d", ival ) == 1 )
		return XML_SUCCESS;
	return XML_WRONG_TYPE;
}

int cXMLAttribute::QueryDoubleValue( double* dval ) const
{
	if ( XML_SSCANF( value.c_str(), "%lf", dval ) == 1 )
		return XML_SUCCESS;
	return XML_WRONG_TYPE;
}

void cXMLAttribute::SetIntValue( int _value )
{
	char buf [64];
	#if defined(XML_SNPRINTF)
		XML_SNPRINTF(buf, sizeof(buf), "%d", _value);
	#else
		sprintf (buf, "%d", _value);
	#endif
	SetValue (buf);
}

void cXMLAttribute::SetDoubleValue( double _value )
{
	char buf [256];
	#if defined(XML_SNPRINTF)
		XML_SNPRINTF( buf, sizeof(buf), "%g", _value);
	#else
		sprintf (buf, "%g", _value);
	#endif
	SetValue (buf);
}

int cXMLAttribute::IntValue() const
{
	return atoi (value.c_str ());
}

double  cXMLAttribute::DoubleValue() const
{
	return atof (value.c_str ());
}


cXMLComment::cXMLComment( const cXMLComment& copy ) : cXMLNode( cXMLNode::TINYXML_COMMENT )
{
	copy.CopyTo( this );
}


void cXMLComment::operator=( const cXMLComment& base )
{
	Clear();
	base.CopyTo( this );
}


void cXMLComment::Print( FILE* cfile, int depth ) const
{
	assert( cfile );
	for ( int i=0; i<depth; i++ )
	{
		fprintf( cfile,  "    " );
	}
	fprintf( cfile, "<!--%s-->", value.c_str() );
}


void cXMLComment::CopyTo( cXMLComment* target ) const
{
	cXMLNode::CopyTo( target );
}


bool cXMLComment::Accept( cXMLVisitor* visitor ) const
{
	return visitor->Visit( *this );
}


cXMLNode* cXMLComment::Clone() const
{
	cXMLComment* clone = new cXMLComment();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void cXMLText::Print( FILE* cfile, int depth ) const
{
	assert( cfile );
	if ( cdata )
	{
		int i;
		fprintf( cfile, "\n" );
		for ( i=0; i<depth; i++ ) {
			fprintf( cfile, "    " );
		}
		fprintf( cfile, "<![CDATA[%s]]>\n", value.c_str() );	// unformatted output
	}
	else
	{
		XML_STRING buffer;
		EncodeString( value, &buffer );
		fprintf( cfile, "%s", buffer.c_str() );
	}
}


void cXMLText::CopyTo( cXMLText* target ) const
{
	cXMLNode::CopyTo( target );
	target->cdata = cdata;
}


bool cXMLText::Accept( cXMLVisitor* visitor ) const
{
	return visitor->Visit( *this );
}


cXMLNode* cXMLText::Clone() const
{
	cXMLText* clone = 0;
	clone = new cXMLText( "" );

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


cXMLDeclaration::cXMLDeclaration( const char * _version,
									const char * _encoding,
									const char * _standalone )
	: cXMLNode( cXMLNode::TINYXML_DECLARATION )
{
	version = _version;
	encoding = _encoding;
	standalone = _standalone;
}


#ifdef XML_USE_STL
cXMLDeclaration::cXMLDeclaration(	const std::string& _version,
									const std::string& _encoding,
									const std::string& _standalone )
	: cXMLNode( cXMLNode::TINYXML_DECLARATION )
{
	version = _version;
	encoding = _encoding;
	standalone = _standalone;
}
#endif


cXMLDeclaration::cXMLDeclaration( const cXMLDeclaration& copy )
	: cXMLNode( cXMLNode::TINYXML_DECLARATION )
{
	copy.CopyTo( this );
}


void cXMLDeclaration::operator=( const cXMLDeclaration& copy )
{
	Clear();
	copy.CopyTo( this );
}


void cXMLDeclaration::Print( FILE* cfile, int /*depth*/, XML_STRING* str ) const
{
	if ( cfile ) fprintf( cfile, "<?xml " );
	if ( str )	 (*str) += "<?xml ";

	if ( !version.empty() ) {
		if ( cfile ) fprintf (cfile, "version=\"%s\" ", version.c_str ());
		if ( str ) { (*str) += "version=\""; (*str) += version; (*str) += "\" "; }
	}
	if ( !encoding.empty() ) {
		if ( cfile ) fprintf (cfile, "encoding=\"%s\" ", encoding.c_str ());
		if ( str ) { (*str) += "encoding=\""; (*str) += encoding; (*str) += "\" "; }
	}
	if ( !standalone.empty() ) {
		if ( cfile ) fprintf (cfile, "standalone=\"%s\" ", standalone.c_str ());
		if ( str ) { (*str) += "standalone=\""; (*str) += standalone; (*str) += "\" "; }
	}
	if ( cfile ) fprintf( cfile, "?>" );
	if ( str )	 (*str) += "?>";
}


void cXMLDeclaration::CopyTo( cXMLDeclaration* target ) const
{
	cXMLNode::CopyTo( target );

	target->version = version;
	target->encoding = encoding;
	target->standalone = standalone;
}


bool cXMLDeclaration::Accept( cXMLVisitor* visitor ) const
{
	return visitor->Visit( *this );
}


cXMLNode* cXMLDeclaration::Clone() const
{
	cXMLDeclaration* clone = new cXMLDeclaration();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


void cXMLUnknown::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
		fprintf( cfile, "    " );
	fprintf( cfile, "<%s>", value.c_str() );
}


void cXMLUnknown::CopyTo( cXMLUnknown* target ) const
{
	cXMLNode::CopyTo( target );
}


bool cXMLUnknown::Accept( cXMLVisitor* visitor ) const
{
	return visitor->Visit( *this );
}


cXMLNode* cXMLUnknown::Clone() const
{
	cXMLUnknown* clone = new cXMLUnknown();

	if ( !clone )
		return 0;

	CopyTo( clone );
	return clone;
}


cXMLAttributeSet::cXMLAttributeSet()
{
	sentinel.next = &sentinel;
	sentinel.prev = &sentinel;
}


cXMLAttributeSet::~cXMLAttributeSet()
{
	assert( sentinel.next == &sentinel );
	assert( sentinel.prev == &sentinel );
}


void cXMLAttributeSet::Add( cXMLAttribute* addMe )
{
    #ifdef XML_USE_STL
	assert( !Find( XML_STRING( addMe->Name() ) ) );	// Shouldn't be multiply adding to the set.
	#else
	assert( !Find( addMe->Name() ) );	// Shouldn't be multiply adding to the set.
	#endif

	addMe->next = &sentinel;
	addMe->prev = sentinel.prev;

	sentinel.prev->next = addMe;
	sentinel.prev      = addMe;
}

void cXMLAttributeSet::Remove( cXMLAttribute* removeMe )
{
	cXMLAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node == removeMe )
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = 0;
			node->prev = 0;
			return;
		}
	}
	assert( 0 );		// we tried to remove a non-linked attribute.
}


#ifdef XML_USE_STL
cXMLAttribute* cXMLAttributeSet::Find( const std::string& name ) const
{
	for( cXMLAttribute* node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node->name == name )
			return node;
	}
	return 0;
}

cXMLAttribute* cXMLAttributeSet::FindOrCreate( const std::string& _name )
{
	cXMLAttribute* attrib = Find( _name );
	if ( !attrib ) {
		attrib = new cXMLAttribute();
		Add( attrib );
		attrib->SetName( _name );
	}
	return attrib;
}
#endif


cXMLAttribute* cXMLAttributeSet::Find( const char* name ) const
{
	for( cXMLAttribute* node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( strcmp( node->name.c_str(), name ) == 0 )
			return node;
	}
	return 0;
}


cXMLAttribute* cXMLAttributeSet::FindOrCreate( const char* _name )
{
	cXMLAttribute* attrib = Find( _name );
	if ( !attrib ) {
		attrib = new cXMLAttribute();
		Add( attrib );
		attrib->SetName( _name );
	}
	return attrib;
}


#ifdef XML_USE_STL
std::istream& operator>> (std::istream & in, cXMLNode & base)
{
	XML_STRING tag;
	tag.reserve( 8 * 1000 );
	base.StreamIn( &in, &tag );

	base.Parse( tag.c_str(), 0, XML_DEFAULT_ENCODING );
	return in;
}
#endif


#ifdef XML_USE_STL
std::ostream& operator<< (std::ostream & out, const cXMLNode & base)
{
	cXMLPrinter printer;
	printer.SetStreamPrinting();
	base.Accept( &printer );
	out << printer.Str();

	return out;
}


std::string& operator<< (std::string& out, const cXMLNode& base )
{
	cXMLPrinter printer;
	printer.SetStreamPrinting();
	base.Accept( &printer );
	out.append( printer.Str() );

	return out;
}
#endif


cXMLHandle cXMLHandle::FirstChild() const
{
	if ( node )
	{
		cXMLNode* child = node->FirstChild();
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::FirstChild( const char * value ) const
{
	if ( node )
	{
		cXMLNode* child = node->FirstChild( value );
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::FirstChildElement() const
{
	if ( node )
	{
		cXMLElement* child = node->FirstChildElement();
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::FirstChildElement( const char * value ) const
{
	if ( node )
	{
		cXMLElement* child = node->FirstChildElement( value );
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::Child( int count ) const
{
	if ( node )
	{
		int i;
		cXMLNode* child = node->FirstChild();
		for (	i=0;
				child && i<count;
				child = child->NextSibling(), ++i )
		{
			// nothing
		}
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::Child( const char* value, int count ) const
{
	if ( node )
	{
		int i;
		cXMLNode* child = node->FirstChild( value );
		for (	i=0;
				child && i<count;
				child = child->NextSibling( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::ChildElement( int count ) const
{
	if ( node )
	{
		int i;
		cXMLElement* child = node->FirstChildElement();
		for (	i=0;
				child && i<count;
				child = child->NextSiblingElement(), ++i )
		{
			// nothing
		}
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


cXMLHandle cXMLHandle::ChildElement( const char* value, int count ) const
{
	if ( node )
	{
		int i;
		cXMLElement* child = node->FirstChildElement( value );
		for (	i=0;
				child && i<count;
				child = child->NextSiblingElement( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return cXMLHandle( child );
	}
	return cXMLHandle( 0 );
}


bool cXMLPrinter::VisitEnter( const cXMLDocument& )
{
	return true;
}

bool cXMLPrinter::VisitExit( const cXMLDocument& )
{
	return true;
}

bool cXMLPrinter::VisitEnter( const cXMLElement& element, const cXMLAttribute* firstAttribute )
{
	DoIndent();
	buffer += "<";
	buffer += element.Value();

	for( const cXMLAttribute* attrib = firstAttribute; attrib; attrib = attrib->Next() )
	{
		buffer += " ";
		attrib->Print( 0, 0, &buffer );
	}

	if ( !element.FirstChild() )
	{
		buffer += " />";
		DoLineBreak();
	}
	else
	{
		buffer += ">";
		if (    element.FirstChild()->ToText()
			  && element.LastChild() == element.FirstChild()
			  && element.FirstChild()->ToText()->CDATA() == false )
		{
			simpleTextPrint = true;
			// no DoLineBreak()!
		}
		else
		{
			DoLineBreak();
		}
	}
	++depth;
	return true;
}


bool cXMLPrinter::VisitExit( const cXMLElement& element )
{
	--depth;
	if ( !element.FirstChild() )
	{
		// nothing.
	}
	else
	{
		if ( simpleTextPrint )
		{
			simpleTextPrint = false;
		}
		else
		{
			DoIndent();
		}
		buffer += "</";
		buffer += element.Value();
		buffer += ">";
		DoLineBreak();
	}
	return true;
}


bool cXMLPrinter::Visit( const cXMLText& text )
{
	if ( text.CDATA() )
	{
		DoIndent();
		buffer += "<![CDATA[";
		buffer += text.Value();
		buffer += "]]>";
		DoLineBreak();
	}
	else if ( simpleTextPrint )
	{
		XML_STRING str;
		cXMLBase::EncodeString( text.ValueTStr(), &str );
		buffer += str;
	}
	else
	{
		DoIndent();
		XML_STRING str;
		cXMLBase::EncodeString( text.ValueTStr(), &str );
		buffer += str;
		DoLineBreak();
	}
	return true;
}


bool cXMLPrinter::Visit( const cXMLDeclaration& declaration )
{
	DoIndent();
	declaration.Print( 0, 0, &buffer );
	DoLineBreak();
	return true;
}


bool cXMLPrinter::Visit( const cXMLComment& comment )
{
	DoIndent();
	buffer += "<!--";
	buffer += comment.Value();
	buffer += "-->";
	DoLineBreak();
	return true;
}


bool cXMLPrinter::Visit( const cXMLUnknown& unknown )
{
	DoIndent();
	buffer += "<";
	buffer += unknown.Value();
	buffer += ">";
	DoLineBreak();
	return true;
}

}
