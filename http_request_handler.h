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

			//����·����
			std::string path;

			//��Uriת��Ϊ����·����
			bool decodeUrl(const std::string url );

			//��ȡ�ļ��е�����
			bool getFileContex(std::string& context);
		};
	}
}

