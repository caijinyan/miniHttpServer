#ifndef HTTP_CONNECTION_MANAGER_HPP
#define HTTP_CONNECTION_MANAGER_HPP



#pragma once
#include <set>
#include "connection.h"

namespace http
{
	namespace server
	{
		class connection_manager:private boost::noncopyable
		{
		private:
			//�������ӵļ���
			std::set<http::server::connection_ptr> connections;
		public:
			//����һ��connect
			void start(connection_ptr  c);

			//�ر�һ������
			void stop(connection_ptr c);

			//�ر����е�����
			void stop_all();
		};
	}
}


#endif
