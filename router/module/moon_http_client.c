#include "moon_http_client.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Check whether the character is permitted in scheme string
	*/
	static int moon_is_scheme_char(int c)
	{
		return (!isalpha(c) && '+' != c && '-' != c && '.' != c) ? 0 : 1;
	}

	/**
	 * function desc:
	 *	Retrieves the IP adress of a hostname
	 */
	static char* moon_hostname_to_ip(char *hostname)
	{
		int errnum = 0;
		char *ip = "0.0.0.0";
		struct hostent *h;
	#ifdef _WIN32
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
		{
			errnum = WSAGetLastError();
			printf("Can't init socket\n");
			return NULL;
		}
	#endif
		if ((h=gethostbyname(hostname)) == NULL) 
		{  
			printf("gethostbyname");
			errnum = WSAGetLastError();
			return NULL;
		}
		return inet_ntoa(*((struct in_addr *)h->h_addr_list[0]));
	}

	/**
	 *	Free memory of parsed url
	 */
	static void moon_parsed_url_free(p_parsed_url purl)
	{
		if ( NULL != purl ) 
		{
			if ( NULL != purl->scheme ) free(purl->scheme);
			if ( NULL != purl->host ) free(purl->host);
			if ( NULL != purl->port ) free(purl->port);
			if ( NULL != purl->path )  free(purl->path);
			if ( NULL != purl->query ) free(purl->query);
			if ( NULL != purl->fragment ) free(purl->fragment);
			if ( NULL != purl->username ) free(purl->username);
			if ( NULL != purl->password ) free(purl->password);
			free(purl);
		}
	}

	/**
	 *	Parses a specified URL and returns the structure named 'parsed_url'
	 *	Implented according to:
	 *	RFC 1738 - http://www.ietf.org/rfc/rfc1738.txt
	 *	RFC 3986 -  http://www.ietf.org/rfc/rfc3986.txt
	 */
	p_parsed_url moon_parse_url(const char *url)
	{
		/* Define variable */
		p_parsed_url purl;
		const char *tmpstr;
		const char *curstr;
		int len;
		int i;
		int userpass_flag;
		int bracket_flag;
		char *ip = NULL;

		/* Allocate the parsed url storage */
		purl = (parsed_url*)malloc(sizeof(parsed_url));
		if ( NULL == purl ) 
		{
			return NULL;
		}
		purl->scheme = NULL;
		purl->host = NULL;
		purl->port = NULL;
		purl->path = NULL;
		purl->query = NULL;
		purl->fragment = NULL;
		purl->username = NULL;
		purl->password = NULL;
		curstr = url;

		/*
		 * <scheme>:<scheme-specific-part>
		 * <scheme> := [a-z\+\-\.]+
		 *             upper case = lower case for resiliency
		 */
		/* Read scheme */
		tmpstr = strchr(curstr, ':');
		if ( NULL == tmpstr ) 
		{
			moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
		
			return NULL;
		}

		/* Get the scheme length */
		len = tmpstr - curstr;

		/* Check restrictions */
		for ( i = 0; i < len; i++ ) 
		{
			if (moon_is_scheme_char(curstr[i]) == 0) 
			{
				/* Invalid format */
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
		}
		/* Copy the scheme to the storage */
		purl->scheme = (char*)malloc(sizeof(char) * (len + 1));
		if ( NULL == purl->scheme ) 
		{
			moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
		
			return NULL;
		}

		(void)strncpy(purl->scheme, curstr, len);
		purl->scheme[len] = '\0';

		/* Make the character to lower if it is upper case. */
		for ( i = 0; i < len; i++ ) 
		{
			purl->scheme[i] = tolower(purl->scheme[i]);
		}

		/* Skip ':' */
		tmpstr++;
		curstr = tmpstr;

		/*
		 * //<user>:<password>@<host>:<port>/<url-path>
		 * Any ":", "@" and "/" must be encoded.
		 */
		/* Eat "//" */
		for ( i = 0; i < 2; i++ ) 
		{
			if ( '/' != *curstr ) 
			{
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
			curstr++;
		}

		/* Check if the user (and password) are specified. */
		userpass_flag = 0;
		tmpstr = curstr;
		while ( '\0' != *tmpstr ) 
		{
			if ( '@' == *tmpstr ) 
			{
				/* Username and password are specified */
				userpass_flag = 1;
				break;
			} 
			else if ( '/' == *tmpstr ) 
			{
				/* End of <host>:<port> specification */
				userpass_flag = 0;
				break;
			}
			tmpstr++;
		}

		/* User and password specification */
		tmpstr = curstr;
		if ( userpass_flag ) 
		{
			/* Read username */
			while ( '\0' != *tmpstr && ':' != *tmpstr && '@' != *tmpstr ) 
			{
				tmpstr++;
			}
			len = tmpstr - curstr;
			purl->username = (char*)malloc(sizeof(char) * (len + 1));
			if ( NULL == purl->username ) 
			{
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
			(void)strncpy(purl->username, curstr, len);
			purl->username[len] = '\0';

			/* Proceed current pointer */
			curstr = tmpstr;
			if ( ':' == *curstr ) 
			{
				/* Skip ':' */
				curstr++;
            
				/* Read password */
				tmpstr = curstr;
				while ( '\0' != *tmpstr && '@' != *tmpstr ) 
				{
					tmpstr++;
				}
				len = tmpstr - curstr;
				purl->password = (char*)malloc(sizeof(char) * (len + 1));
				if ( NULL == purl->password ) 
				{
					moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
					return NULL;
				}
				(void)strncpy(purl->password, curstr, len);
				purl->password[len] = '\0';
				curstr = tmpstr;
			}
			/* Skip '@' */
			if ( '@' != *curstr ) 
			{
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
			curstr++;
		}

		if ( '[' == *curstr ) 
		{
			bracket_flag = 1;
		} 
		else 
		{
			bracket_flag = 0;
		}
		/* Proceed on by delimiters with reading host */
		tmpstr = curstr;
		while ( '\0' != *tmpstr ) {
			if ( bracket_flag && ']' == *tmpstr )
 			{
				/* End of IPv6 address. */
				tmpstr++;
				break;
			} 
			else if ( !bracket_flag && (':' == *tmpstr || '/' == *tmpstr) ) 
			{
				/* Port number is specified. */
				break;
			}
			tmpstr++;
		}
		len = tmpstr - curstr;
		purl->host = (char*)malloc(sizeof(char) * (len + 1));
		if ( NULL == purl->host || len <= 0 ) 
		{
			moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
			return NULL;
		}
		(void)strncpy(purl->host, curstr, len);
		purl->host[len] = '\0';
		curstr = tmpstr;

		/* Is port number specified? */
		if ( ':' == *curstr ) 
		{
			curstr++;
			/* Read port number */
			tmpstr = curstr;
			while ( '\0' != *tmpstr && '/' != *tmpstr ) 
			{
				tmpstr++;
			}
			len = tmpstr - curstr;
			purl->port = (char*)malloc(sizeof(char) * (len + 1));
			if ( NULL == purl->port ) 
			{
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
			(void)strncpy(purl->port, curstr, len);
			purl->port[len] = '\0';
			curstr = tmpstr;
		}
		else
		{
			//http or https
			if (strcmp("http",purl->scheme) == 0)
			{
				purl->port = (char*)malloc(3);
				memset(purl->port,0,3);
				strcpy(purl->port,"80");
			}
			else if (strcmp("https",purl->scheme) == 0)
			{
				purl->port = (char*)malloc(4);
				memset(purl->port,0,4);
				strcpy(purl->port,"443");
			}
		}
	
		/* Get ip */
		ip = moon_hostname_to_ip(purl->host);
		purl->ip = ip;
	
		/* Set uri */
		purl->uri = (char*)url;

		/* End of the string */
		if ( '\0' == *curstr ) 
		{
			return purl;
		}

		/* Skip '/' */
		if ( '/' != *curstr ) 
		{
			moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
			return NULL;
		}
		curstr++;

		/* Parse path */
		tmpstr = curstr;
		while ( '\0' != *tmpstr && '#' != *tmpstr  && '?' != *tmpstr ) 
		{
			tmpstr++;
		}
		len = tmpstr - curstr;
		purl->path = (char*)malloc(sizeof(char) * (len + 1));
		if ( NULL == purl->path ) 
		{
			moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
			return NULL;
		}
		(void)strncpy(purl->path, curstr, len);
		purl->path[len] = '\0';
		curstr = tmpstr;

		/* Is query specified? */
		if ( '?' == *curstr ) 
		{
			/* Skip '?' */
			curstr++;
			/* Read query */
			tmpstr = curstr;
			while ( '\0' != *tmpstr && '#' != *tmpstr ) 
			{
				tmpstr++;
			}
			len = tmpstr - curstr;
			purl->query = (char*)malloc(sizeof(char) * (len + 1));
			if ( NULL == purl->query ) 
			{
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
			(void)strncpy(purl->query, curstr, len);
			purl->query[len] = '\0';
			curstr = tmpstr;
		}

		/* Is fragment specified? */
		if ( '#' == *curstr ) 
		{
			/* Skip '#' */
			curstr++;
			/* Read fragment */
			tmpstr = curstr;
			while ( '\0' != *tmpstr ) 
			{
				tmpstr++;
			}
			len = tmpstr - curstr;
			purl->fragment = (char*)malloc(sizeof(char) * (len + 1));
			if ( NULL == purl->fragment )
 			{
				moon_parsed_url_free(purl); fprintf(stderr, "Error on line %d (%s)\n", __LINE__, __FILE__);
				return NULL;
			}
			(void)strncpy(purl->fragment, curstr, len);
			purl->fragment[len] = '\0';
			curstr = tmpstr;
		}
		return purl;
	}

	/**
	 * 函数说明：
	 *  发起http请求
	 * 参数：
	 *  http_headers：请求头部
	 *  purl：请求地址结构
	 * 返回值：
	 *  返回响应体
	 */
	static http_response* _http_request(const char *http_headers, const parsed_url *purl)
	{
		/* Declare variable */
		char *body = NULL;
		int sent = 0;
		int errnum = 0;
		int sock;
		int tmpres;
		char buf[BUFSIZ+1];
		struct sockaddr_in *remote;
		http_response *hresp = NULL;
		char *response = NULL;
		char BUF[BUFSIZ];
		size_t recived_len = 0;
		char *status_line = NULL;
		char *status_code = NULL;
		char *status_text = NULL;
		char *headers = NULL;
		unsigned long length = 0;
#ifdef _WIN32
		WSADATA wsaData;
#endif

		/* Parse url */
		if(purl == NULL)
		{
			printf("Unable to parse url");
			return NULL;
		}

		/* Allocate memeory for htmlcontent */
		hresp = (http_response*)malloc(sizeof(http_response));
		if(hresp == NULL)
		{
			printf("Unable to allocate memory for htmlcontent.");
			return NULL;
		}
		hresp->body = NULL;
		hresp->request_headers = NULL;
		hresp->response_headers = NULL;
		hresp->status_code = NULL;
		hresp->status_text = NULL;
		hresp->request_uri = NULL;
		/*window need init socket*/
#ifdef _WIN32
		if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
		{
			errnum = WSAGetLastError();
			printf("Can't init socket\n");
			http_response_free(hresp);
			return NULL;
		}
#endif
		/* Create TCP socket */
		if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		{
			printf("Can't create TCP socket\n");
			http_response_free(hresp);
			return NULL;
		}

		/* Set remote->sin_addr.s_addr */
		remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
		remote->sin_family = AF_INET;
		tmpres = inet_pton(AF_INET, purl->ip, (void *)(&(remote->sin_addr.s_addr)));
		if( tmpres < 0)
		{
			printf("Can't set remote->sin_addr.s_addr\n");
			return NULL;
		}
		else if(tmpres == 0)
		{
			printf("Not a valid IP");
			return NULL;
		}
		remote->sin_port = htons(atoi(purl->port));

		/* Connect */
		if(connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0)
		{
			printf("Could not connect");
			return NULL;
		}

		/* Send headers to server */	
		while(sent < strlen(http_headers))
		{
			tmpres = send(sock, http_headers+sent, strlen(http_headers)-sent, 0);
			if(tmpres == -1)
			{
				printf("Can't send headers");
				return NULL;
			}
			sent += tmpres;
		}

		/* Recieve into response*/
		response = (char*)malloc(1);
		memset(response,0,1);
		while((recived_len = recv(sock, BUF, BUFSIZ-1, 0)) > 0)
		{
			BUF[recived_len] = '\0';
			length = strlen(response) + strlen(BUF) + 1;
			response = (char*)realloc(response,length);
			sprintf(response, "%s%s", response, BUF);
		}
		if (recived_len < 0)
		{
			free(http_headers);
#ifdef _WIN32
			closesocket(sock);
#else
			close(sock);
#endif
			printf("Unabel to recieve");
			return NULL;
		}

		/* Reallocate response */
		response = (char*)realloc(response, strlen(response) + 1);

		/* Close socket */
#ifdef _WIN32
		closesocket(sock);
#else
		close(sock);
#endif
		/* Parse status code and text */
		status_line = get_until(response, "\r\n");
		status_line = str_replace("HTTP/1.1 ", "", status_line);
		status_code = str_ndup(status_line, 4);
		status_code = str_replace(" ", "", status_code);
		status_text = str_replace(status_code, "", status_line);
		status_text = str_replace(" ", "", status_text);
		hresp->status_code = status_code;
		hresp->status_code_int = atoi(status_code);
		hresp->status_text = status_text;

		/* Parse response headers */	
		headers = get_until(response, "\r\n\r\n");
		hresp->response_headers = headers;

		/* Assign request headers */
		hresp->request_headers = http_headers;

		/* Assign request url */
		hresp->request_uri = purl;

		/* Parse body */
		body = strstr(response, "\r\n\r\n");
		body = str_replace("\r\n\r\n", "", body);
		hresp->body = body;

		/* Return response */
		return hresp;
	}

	/**
	 *	Handles redirect if needed for get requests
	 */
	static http_response* _handle_redirect_get(http_response* hresp, char* custom_headers,const char* param_name[],const char* param_value[],int param_count)
	{
		if(hresp->status_code_int > 300 && hresp->status_code_int < 399)
		{
			char *token = strtok(hresp->response_headers, "\r\n");
			while(token != NULL)
			{
				if(str_contains(token, "Location:"))
				{
					/* Extract url */
					char *location = str_replace("Location: ", "", token);
					return http_do_get(location, custom_headers,param_name,param_value,param_count);
				}
				token = strtok(NULL, "\r\n");
			}
		}
		else
		{
			/* We're not dealing with a redirect, just return the same structure */
			return hresp;
		}
	}

	/**
	 *	Handles redirect if needed for post requests
	 */
	http_response* _handle_redirect_post(http_response* hresp,const char* custom_headers,const char *post_data)
	{
		if(hresp->status_code_int > 300 && hresp->status_code_int < 399)
		{
			char *token = strtok(hresp->response_headers, "\r\n");
			while(token != NULL)
			{
				if(str_contains(token, "Location:"))
				{
					/* Extract url */
					char *location = str_replace("Location: ", "", token);
					return http_do_post(location, custom_headers, post_data);
				}
				token = strtok(NULL, "\r\n");
			}
		}
		else
		{
			/* We're not dealing with a redirect, just return the same structure */
			return hresp;
		}
	}

	/**
	 * 函数说明：
	 *   发起get请求
	 * 参数：
	 *   url：请求的url地址
	 *   custom_header：自定义头部
	 *   paramName：请求的参数名称列表
	 *   paramValue：请求的参数值列表
	 *   paramCount：参数数量
	 * 返回值：
	 *   返回响应的结构体指针，使用完成之后需要调用http_response_free进行释放
	 */
	http_response* http_do_get(const char* url,const char* custom_headers,const char* param_name[],const char* param_value[],int param_count)
	{
		/* Declare variable */
		char *http_headers = NULL;
		char *upwd = NULL;
		char *base64 = NULL;
		char *auth_header = NULL;
		http_response *hresp = NULL;
		/* Parse url */
		parsed_url *purl = moon_parse_url(url);
		if(purl == NULL)
		{
			printf("Unable to parse url");
			return NULL;
		}


		http_headers = (char*)malloc(1024);

		/* Build query/headers */
		if(purl->path != NULL)
		{
			if(purl->query != NULL)
			{
				sprintf(http_headers, "GET /%s?%s HTTP/1.1\r\nHost:%s\r\nConnection:close\r\n", purl->path, purl->query, purl->host);
			}
			else
			{
				sprintf(http_headers, "GET /%s HTTP/1.1\r\nHost:%s\r\nConnection:close\r\n", purl->path, purl->host);
			}
		}
		else
		{
			if(purl->query != NULL)
			{
				sprintf(http_headers, "GET /?%s HTTP/1.1\r\nHost:%s\r\nConnection:close\r\n", purl->query, purl->host);
			}
			else
			{
				sprintf(http_headers, "GET / HTTP/1.1\r\nHost:%s\r\nConnection:close\r\n", purl->host);
			}
		}

		/* Handle authorisation if needed */
		if(purl->username != NULL)
		{
			/* Format username:password pair */
			upwd = (char*)malloc(1024);
			sprintf(upwd, "%s:%s", purl->username, purl->password);
			upwd = (char*)realloc(upwd, strlen(upwd) + 1);

			/* Base64 encode */
			base64 = base64_encode(upwd);

			/* Form header */
			auth_header = (char*)malloc(1024);
			sprintf(auth_header, "Authorization: Basic %s\r\n", base64);
			auth_header = (char*)realloc(auth_header, strlen(auth_header) + 1);

			/* Add to header */
			http_headers = (char*)realloc(http_headers, strlen(http_headers) + strlen(auth_header) + 2);
			sprintf(http_headers, "%s%s", http_headers, auth_header);
		}

		/* Add custom headers, and close */
		if(custom_headers != NULL)
		{
			sprintf(http_headers, "%s%s\r\n", http_headers, custom_headers);
		}
		else
		{
			sprintf(http_headers, "%s\r\n", http_headers);
		}
		http_headers = (char*)realloc(http_headers, strlen(http_headers) + 1);

		/* Make request and return response */
		hresp = _http_request(http_headers, purl);
		if (hresp == NULL)
		{
			return NULL;
		}
		/* Handle redirect */

		return _handle_redirect_get(hresp, custom_headers,param_name,param_value,param_count);
	}


	/**
	 * 函数说明：
	 *   发起post请求
	 * 参数：
	 *   url：请求的url地址
	 *   custom_headers：自定义请求头
	 *   post_data：请求的post参数数据
	 * 返回值：
	 *   返回响应的结构体指针，使用完成之后需要调用http_response_free进行释放
	 */
	http_response* http_do_post(const char* url,const char* custom_headers,const char *post_data)
	{
		/* Declare variable */
		char *http_headers = NULL;
		char *upwd = NULL;
		char *base64 = NULL;
		char *auth_header = NULL;
		http_response *hresp = NULL;
		/* Parse url */
		parsed_url *purl = NULL;
		purl = moon_parse_url(url);
		if(purl == NULL)
		{
			printf("Unable to parse url");
			return NULL;
		}


		http_headers = (char*)malloc(1024);

		/* Build query/headers */
		if(purl->path != NULL)
		{
			if(purl->query != NULL)
			{
				sprintf(http_headers, "POST /%s?%s HTTP/1.1\r\nHost:%s\r\nConnection:close\r\nContent-Length:%zu\r\nContent-Type:application/json\r\n", purl->path, purl->query, purl->host, strlen(post_data));
			}
			else
			{
				sprintf(http_headers, "POST /%s HTTP/1.1\r\nHost:%s\r\nConnection:close\r\nContent-Length:%d\r\nContent-Type:application/json\r\n", purl->path, purl->host, strlen(post_data));
			}
		}
		else
		{
			if(purl->query != NULL)
			{
				sprintf(http_headers, "POST /?%s HTTP/1.1\r\nHost:%s\r\nConnection:close\r\nContent-Length:%zu\r\nContent-Type:application/json\r\n", purl->query, purl->host, strlen(post_data));
			}
			else
			{
				sprintf(http_headers, "POST / HTTP/1.1\r\nHost:%s\r\nConnection:close\r\nContent-Length:%d\r\nContent-Type:application/json\r\n", purl->host, strlen(post_data));
			}
		}

		/* Handle authorisation if needed */
		if(purl->username != NULL)
		{
			/* Format username:password pair */
			upwd = (char*)malloc(1024);
			sprintf(upwd, "%s:%s", purl->username, purl->password);
			upwd = (char*)realloc(upwd, strlen(upwd) + 1);

			/* Base64 encode */
			base64 = base64_encode(upwd);

			/* Form header */
			auth_header = (char*)malloc(1024);
			sprintf(auth_header, "Authorization: Basic %s\r\n", base64);
			auth_header = (char*)realloc(auth_header, strlen(auth_header) + 1);

			/* Add to header */
			http_headers = (char*)realloc(http_headers, strlen(http_headers) + strlen(auth_header) + 2);
			sprintf(http_headers, "%s%s", http_headers, auth_header);
		}

		if(custom_headers != NULL)
		{
			sprintf(http_headers, "%s%s\r\n", http_headers, custom_headers);
			sprintf(http_headers, "%s\r\n%s", http_headers, post_data);
		}
		else
		{
			sprintf(http_headers, "%s\r\n%s", http_headers, post_data);
		}
		http_headers = (char*)realloc(http_headers, strlen(http_headers) + 1);

		/* Make request and return response */
		hresp = _http_request(http_headers, purl);
		if (hresp == NULL)
		{
			return NULL;
		}

		/* Handle redirect */
		return _handle_redirect_post(hresp, custom_headers, post_data);
	}

	/**
	 * 函数说明：
	 *   释放响应结构的内存
	 * 参数：
	 *   p_http_response：响应结构指针
	 */
	void http_response_free(http_response* p_http_response)
	{
		if(p_http_response != NULL)
		{
			if(p_http_response->request_uri != NULL) moon_parsed_url_free(p_http_response->request_uri);
			if(p_http_response->body != NULL) free(p_http_response->body);
			if(p_http_response->status_code != NULL) free(p_http_response->status_code);
			if(p_http_response->status_text != NULL) free(p_http_response->status_text);
			if(p_http_response->request_headers != NULL) free(p_http_response->request_headers);
			if(p_http_response->response_headers != NULL) free(p_http_response->response_headers);
			free(p_http_response);
		}
	}

#ifdef __cplusplus
}
#endif