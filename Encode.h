#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

typedef unsigned char BYTE;

inline BYTE toHex(const BYTE &x)
{
return x > 9 ? x + 55: x + 48;
}

string urlEncoding( string &sIn )
{
     cout << "size: " << sIn.size() << endl;
     string sOut;
     for( int ix = 0; ix < sIn.size(); ix++ )
     {
         BYTE buf[4];
         memset( buf, 0, 4 );
         if( isalnum( (BYTE)sIn[ix] ) )
         {
             buf[0] = sIn[ix];
         }
         else if ( isspace( (BYTE)sIn[ix] ) )
         {
             buf[0] = '+';
         }
         else
         {
             buf[0] = '%';
             buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
             buf[2] = toHex( (BYTE)sIn[ix] % 16);
         }
         sOut += (char *)buf;
     }
     return sOut;
}

void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer)
{
    ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
    return;
}

void UnicodeToUTF_8(char* pOut,WCHAR* pText)
{
    // ע�� WCHAR�ߵ��ֵ�˳��,���ֽ���ǰ�����ֽ��ں�
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}

//GB2312 תΪ UTF-8
void GB2312ToUTF_8(string& pOut,char *pText, int pLen)
{
    char buf[4];
    memset(buf,0,4);

    pOut.clear();

    int i = 0;
    while(i < pLen)
    {
        //�����Ӣ��ֱ�Ӹ��ƾͿ���
        if( pText[i] >= 0)
        {
            char asciistr[2]={0};
            asciistr[0] = (pText[i++]);
            pOut.append(asciistr);
        }
        else
        {
            WCHAR pbuffer;
            Gb2312ToUnicode(&pbuffer,pText+i);

            UnicodeToUTF_8(buf,&pbuffer);

            pOut.append(buf);

            i += 2;
        }
    }

    return;
}

//��str����Ϊ��ҳ�е� UTF-8 url encode ,Ӣ�Ĳ��䣬�������ֽ�  ��%3D%AE%88

string UrlUTF8(char * str)
{
    string tt;
    string dd;
    GB2312ToUTF_8(tt,str,(int)strlen(str));

    size_t len=tt.length();
    for (size_t i=0;i<len;i++)
    {
        if(isalnum((BYTE)tt.at(i)))
        {
            char tempbuff[2]={0};
            sprintf(tempbuff,"%c",(BYTE)tt.at(i));
            dd.append(tempbuff);
        }
        else if (isspace((BYTE)tt.at(i)))
        {
            dd.append("+");
        }
        else
        {
            char tempbuff[4];
            sprintf(tempbuff,"%%%X%X",((BYTE)tt.at(i)) >>4,((BYTE)tt.at(i)) %16);
            dd.append(tempbuff);
        }

    }
    return dd;
}

//wchar �� char ���ת��
void WcharToChar(WCHAR* pIn,string &pOut)
{  

    DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,pIn,-1,NULL,0,NULL,FALSE);

    // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
    char *psText = new char[dwNum];

    WideCharToMultiByte (CP_OEMCP,NULL,pIn,-1,psText,dwNum,NULL,FALSE);

    pOut = psText; //�󹦸��
    
    delete []psText;


}
