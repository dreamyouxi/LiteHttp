



#include "Utils.h"
#include "windows.h"




string  toAscii(LPWSTR str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str,
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)* (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str,
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}





string decodeHex(string s)
{
	//scan for hex

	size_t strLen = s.size();

	string ret;
	ret.reserve(strLen);

	unsigned int outputIndex = 0;
	char c;
	unsigned char hexDigits[2];
	unsigned char hexValues[2];
	unsigned int i;
	for (i = 0; i < strLen; i++)
	{
		c = s.c_str()[i];
		if (c == '%')
		{
			hexDigits[0] = s.c_str()[++i];
			hexDigits[1] = s.c_str()[++i];

			if (hexDigits[0] == ' ')
				hexValues[0] = 0;

			if (hexDigits[0] >= 'A' && hexDigits[0] <= 'F')
				hexValues[0] = hexDigits[0] - 'A' + 10;
			else if (hexDigits[0] >= 'a' && hexDigits[0] <= 'f')
				hexValues[0] = hexDigits[0] - 'a' + 10;
			else
				hexValues[0] = hexDigits[0] - '0';

			if (hexDigits[1] >= 'A' && hexDigits[1] <= 'F')
				hexValues[1] = hexDigits[1] - 'A' + 10;
			else if (hexDigits[1] >= 'a' && hexDigits[1] <= 'f')
				hexValues[1] = hexDigits[1] - 'a' + 10;
			else
				hexValues[1] = hexDigits[1] - '0';

			s[outputIndex++] = hexValues[0] * 16 + hexValues[1];
		}
		else
		{
			s[outputIndex++] = c;
		}
	}

	s[outputIndex] = 0;

	return s;


}






string  Utils::decodeURL(string utf8)
{

	// UTF8(3bit form url ) TO UTF16(2bit)
	string xx = decodeHex(utf8);


	unsigned char  *str = (unsigned char *)xx.c_str();

	int cchUTF16 = ::MultiByteToWideChar(
		CP_UTF8,                // convert from UTF-8
		0,						// Flags
		(LPCSTR)str,            // source UTF-8 string
		strlen((const char *)str) + 1,                 // total length of source UTF-8 string,
		// in CHAR's (= bytes), including end-of-string \0
		NULL,                   // unused - no conversion done in this step
		0                       // request size of destination buffer, in WCHAR's
		);

	if (cchUTF16 == 0)
	{
		return "";
	}


	WCHAR *  pszUTF16 = new WCHAR[cchUTF16];

	int result = ::MultiByteToWideChar(
		CP_UTF8,                // convert from UTF-8
		0,						// Buffer
		(LPCSTR)str,            // source UTF-8 string
		strlen((const char *)str) + 1,                 // total length of source UTF-8 string,
		// in CHAR's (= bytes), including end-of-string \0
		pszUTF16,               // destination buffer
		cchUTF16                // size of destination buffer, in WCHAR's
		);


	string ret = toAscii(pszUTF16);//UTF16 TO ASCII
	delete pszUTF16;
	return  ret;


}







