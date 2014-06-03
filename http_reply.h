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
		//״̬
		namespace status
		{
			//����һ��״̬��ȫ�ֱ���

			
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
			//������������Ӧ���ĵ�ͷ��������ǣ�
			//1���ɹ���Ӧ�𷵻غ󣬼������ݼ���
			//2�����ɹ��ı��ģ��Ͳ������������
			std::vector<header> header_;

			std::string context;

			void stock_replie(status_type status);
			

		};

	}
}

#endif

