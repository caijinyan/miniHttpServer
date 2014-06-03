#pragma once
#include <string>
#include <vector>

#include "request.h"

#ifndef HTTP_REPLY_H
#define HTTP_REPLY_H

namespace http
{
	namespace server
	{
		//状态
		namespace status
		{
			//定义一个状态的全局变量

			
		}
		

		struct http_reply
		{
		public:

			enum status_type
			{
				ok=200,\
				bad_request = 400,\
				not_found = 404
			} status_;
			const std::vector<std::string> getContex();
			//仅仅用来生产应答报文的头部，如果是：
			//1、成功的应答返回后，加上内容即可
			//2、不成功的报文，就不用添加内容了
			std::vector<header> header_;

			std::string context;

			void stock_replie(status_type status);
			

		};

	}
}

#endif

