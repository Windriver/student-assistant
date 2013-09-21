/*
implements URL Encode/decode with unicode char be encoded to %uxxxx
designed by pclion 2009.2.22

*/


#include "stdafx.h"
#include "CUrlEncodeUnicode.h"

TCHAR CUrlEncodeUnicode::toHex(BYTE val)
{
	if (val>9) return _T('A')+val-10;
	return _T('0')+val;
}

void CUrlEncodeUnicode::toHexByte(BYTE val, LPTSTR buf)
{
	buf[0] = _T('%');
	buf[1] = toHex(val>>4);
	buf[2] = toHex(val & 15);
}

void CUrlEncodeUnicode::toHexWord(WORD val, LPTSTR buf)
{
	buf[0] = _T('%');
	buf[1] = _T('u');
	buf[2] = toHex(val>>12);
	buf[3] = toHex((val>>8) & 15);
	buf[4] = toHex((val>>4) & 15);
	buf[5] = toHex(val & 15);
}

BYTE CUrlEncodeUnicode::fromHex(TCHAR c)
{
	if (c>=0 && c <= _T('9')) return c - _T('0');
	if (c>=_T('A') && c<=_T('F')) return c-_T('A')+10;
	return 0;

}

BYTE CUrlEncodeUnicode::fromHexByte(LPCTSTR ptr)
{
	if (!ptr[0] || !ptr[1]) return 0;
	return (fromHex(ptr[0])<<4) | fromHex(ptr[1]);
}

WORD CUrlEncodeUnicode::fromHexWord(LPCTSTR ptr)
{
	if (!ptr[0] || !ptr[1] || !ptr[2] || !ptr[3]) return 0;
	return (fromHex(ptr[0])<<12) | (fromHex(ptr[1])<<8) | (fromHex(ptr[2])<<4) | fromHex(ptr[3]);
}

//funtion: encoding inurl to outurl, only cgi parameters been encoded(part of after '?')
//size is count of ourl, MUST > 0
//if outurl is insufficiency, trancation it, and return false. always end with null
//return : true(normal) / false(trancation)
bool CUrlEncodeUnicode::Encode(LPCWSTR inurl, LPTSTR outurl, size_t size)
{
	bool ret = false;
	LPTSTR p=outurl , pend = &outurl[size-1];
	WORD c;
	//copy until '?'
	while(1) {
		if (p==pend) goto toend;
		if ((c=*inurl++)==0) goto toendok;
		if (c==L'?') break;
		*p++ = (char)c;
	}
	*p++ = (char)c;
	//transform unsafe chars and unicode char
	while(c=*inurl++) {
		switch (c) {
			// unsafe chars = " \"<>#{}|\\^~[]`"
			// see: http://www.blooberry.com/indexdot/html/topics/urlencoding.htm
			case L' ':
				if (p >= pend) goto toend;
				*p++ = _T('+');break;
			case L'\"':
			case L'<':
			case L'>':
			case L'#':
			case L'{':
			case L'}':
			case L'|':
			case L'\\':
			case L'^':
			case L'~':
			case L'[':
			case L']':
			case L'`':
				if (p+3 >= pend) goto toend;
				toHexByte((BYTE)c, p); p+=3; break;
			default:
				if (c > 255) {	//-> %uxxxx
					if (p+6 > pend) goto toend;
					toHexWord((WORD)c, p);
					p+=6;
				} else if (c > 127) {	//->%XX
					if (p+3 > pend) goto toend;
					toHexByte((BYTE)c, p);
					p+=3;
				}else {
					if (p >= pend) goto toend;
					*p++ = (char)c;
				}
		}//switch
	}//while
toendok:
	ret = true;
toend:
	*p = 0;
	return ret;
}//Encode()

bool CUrlEncodeUnicode::Decode(LPCTSTR inurl, LPWSTR outurl, size_t size)
{
	//
	bool ret = false;
	LPWSTR p=outurl;
	LPVOID pend = &outurl[size-1];
	WORD c;

	while(c=*inurl++) {
		if (p==pend) goto toend;
		switch (c) {
			case _T('%'):
				if (*inurl == _T('u')) {
					*p = c = fromHexWord(++inurl);//unsuccess, return 0
					if (c==0) goto toend;
					inurl += 4;
				}else {
					*p = c = fromHexByte(inurl);
					if (c==0) goto toend;
					inurl += 2;
				}
				break;
			case _T('+'):
				*p = L' ';break;
			default:
				*p = c;
		}//switch
		p++;
	}//while
	ret = true;
toend:
	*p = 0;
	return ret;
}//Decode()



