void PostoXiaoneiBlog()
	{
		HINTERNET hInternet = InternetOpen(L"MEIZU M8", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL); 
		bool hresult= 1;
		HINTERNET hSession = InternetConnect(hInternet, L"3g.renren.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

		CMzString content_M=this->m_pEdit.GetText();

		string content_S;
		WcharToChar(content_M.C_Str(),content_S);
		string content_S_1;
		GB2312ToUTF_8(content_S_1,(char*)content_S.c_str(),content_S.length());
		string content_U=urlEncoding(content_S_1);
		string data_s="title=%e7%ae%97%e6%b3%95&body=%e6%98%af%e7%ad%89%e7%ad%89&passwd=&post=%e5%8f%91%e5%b8%83";
		HINTERNET hRequest = HttpOpenRequest(hSession, L"POST", L"/blog/wnewblog.do?tsc=a952bdea52b451f1dc04ed028c1c9a8c&sid=fabfcf6605dede3115fb55e4d74c74954&cancel=list HTTP/1.1", NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, 0); 


		CMzString header_Content_Length(100);
		CMzString header_Content_Type = L"Content-Type:application/x-www-form-urlencoded\r\n";

		CMzString header =L"Accept-Encoding: gzip;q=1.0,identity;q=0.8\r\n";
		CMzString header_Refer=L"Referer: http://3g.renren.com/blog/wnewblog.do?cancel=list&htf=329&sid=fabfcf6605dede3115fb55e4d74c74954&0afdof\r\n";
		CMzString header_Charset=L"Accept-Charset: gb2312,utf-8;q=0.7,*;q=0.7\r\n";
		CMzString header_Agent=L"User-Agent: Mozilla/4.0 (compatible; MSIE 4.01; Windows CE; PPC)/UCWEB7.3.0.55/40/800\r\n";
		CMzString header_Connection=L"Connection: Keep-Alive\r\n";
		CMzString header_Cookie=L"Cookie: from=6000202; alxn=26607d2c4b1ecbadb3221094f6b638a1; mt=fabfcf6605dede3115fb55e4d74c74954\r\n";
//		CMzString header_Cookie=L"Cookie: from=6000202; alxn=26607d2c4b1ecbad697c5343c3fc542d5fbffc7fa5000890; mt=4601f782d8855a5571c360b7637ca78f8";

		wsprintf(header_Content_Length.C_Str(),L"Content-Length: 68\r\n");

		HttpAddRequestHeaders(hRequest,header_Content_Type,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Content_Length,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Refer,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Charset,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Agent,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Connection,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Cookie,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);

		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.c_str(),data_s.length());



		InternetCloseHandle(hRequest); 
		InternetCloseHandle(hSession); 
		InternetCloseHandle(hInternet);
	}


	void PostoSinaTwitter()
	{
		HINTERNET hInternet = InternetOpen(L"MEIZU M8", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL); 
		bool hresult= 1;
		HINTERNET hSession = InternetConnect(hInternet, L"api.t.sina.com.cn", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

		CMzString content_M=this->m_pEdit.GetText();
//		CMzString content_S(200);
//		CUrlEncodeUnicode::Encode(content_M.C_Str(),content_S.C_Str(),content_M.Length());

//		CString  data;
		string content_S;
		WcharToChar(content_M.C_Str(),content_S);
		string content_S_1;
		GB2312ToUTF_8(content_S_1,(char*)content_S.c_str(),content_S.length());
		string content_U=urlEncoding(content_S_1);
		string data_s="source=762290452&status="+content_U;
//		string data_s="source=762290452&status=%e5%93%88%e5%93%88";
//		
//		CMzString data_s(200);
//		wsprintf(data_s.C_Str(),L"source=762290452&status=%s",L"%e5%93%88%e5%93%88");
//		char data[200];
//		WideCharToMultiByte(CP_UTF8,0,content_S.C_Str(),content_S.Length(),data,200,0,0);
		

//		char data[100]="source=762290452&status=%ad%a4%e6%9d%a1%bf%a1%e6%81%af%e6%9d%a5%e8%87%aa%e9%ad%85%e6%97%8fM8";
		HINTERNET hRequest = HttpOpenRequest(hSession, L"POST", L"statuses/update.json", NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, 0); 

/*		CMzString usernamePassword =L"zy081314:zy222409";
		string passname_s,passname_base64;
		WcharToChar(usernamePassword.C_Str(),passname_s);
		passname_base64=Base64::encode(passname_s);
		CMzString header_passname(100);
		MultiByteToWideChar(CP_ACP, 0, passname_base64.c_str(), passname_base64.length(), header_passname.C_Str(), header_passname.Length());    
		wsprintf(header_passname.C_Str(),L"Authorization: Basic %s\r\n",header_passname.C_Str());
		MzMessageBoxV2(m_hWnd,header_passname, MZV2_MB_OK);       */

		CMzString header_Content_Length(100);
		CMzString header_Content_Type = L"Content-Type:application/x-www-form-urlencoded\r\n";

		CMzString header =L"Authorization: Basic enkwODEzMTRAc2luYS5jb206enkyMjI0MDk=\r\n";	
	   

		wsprintf(header_Content_Length.C_Str(),L"Content-Length: %d\r\n",data_s.length());
//		wsprintf(header_Content_Length.C_Str(),L"Content-Length: %d\r\n",data_s.Length());
		HttpAddRequestHeaders(hRequest,header_Content_Type,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Content_Length,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);

//		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.C_Str(),data_s.Length());
		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.c_str(),data_s.length());
//		hresult =HttpSendRequest(hRequest,NULL,0,data,strlen(data));
	//	wsprintf(data.C_Str(),L"%d",hresult);
	//	InternetWriteFile(hRequest, (LPVOID)data, data.Length(), NULL);
		

		HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, NULL, NULL);
		char inetBuffer[200];
		TCHAR buffer[200] ;
		_stprintf(buffer, _T("Tom") );  
		LPCTSTR strTmp ;
		DWORD dwRead=0;
	//	int n=20;
		// do
	    //  {
				BOOL bRead = InternetReadFile(hRequest,inetBuffer,200,&dwRead);         
				
			//		strcat(buffer,inetBuffer);	
			//	--n;
	    // }   
	   // while (n>=0);
		//			CMzString temp(100);
		//strcat(buffer,inetBuffer);
		
		//wsprintf(temp.C_Str(),L"%s%s%s",inetBuffer,L"oo",inetBuffer);

		MultiByteToWideChar(CP_UTF8,0,inetBuffer,-1,buffer,strlen(inetBuffer));
		strTmp = LPCTSTR(buffer);	    
	//	MzMessageBoxV2(m_hWnd,header_Content_Length, MZV2_MB_OK);
		CMzString feedBack(strTmp);
		if(feedBack.SubStr(2,7)==L"created")
		{
			MzMessageBoxV2(m_hWnd,L"成功发布到新浪微博!", MZV2_MB_OK);
		}
		else
		{
			MzMessageBoxV2(m_hWnd,L"发布失败!请重新发送!", MZV2_MB_OK);
		}
		//this->m_pEdit.SetText(strTmp);
		HttpEndRequest(hRequest, NULL, 0, 0);


		InternetCloseHandle(hRequest); 
		InternetCloseHandle(hSession); 
		InternetCloseHandle(hInternet);


	}

