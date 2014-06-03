#pragma once
#include <string>
#include <fstream>

#include "request.h"
#include "http_reply.h"



namespace http
{
	namespace server
	{

		class http_request_handler
		{
		public:
			explicit http_request_handler( std::string & doc_root);
			void handle_request(const request& req , http_reply& rep);
		private:

			//本地路径名
			std::string path;

			//将Uri转换为本地路径名
			bool decodeUrl(const std::string url );

			//读取文件中的类容
			bool getFileContex(std::string& context);
		};
	}
}

