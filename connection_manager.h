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
			//所有连接的集合
			std::set<http::server::connection_ptr> connections;
		public:
			//启动一个connect
			void start(connection_ptr  c);

			//关闭一个连接
			void stop(connection_ptr c);

			//关闭所有的连接
			void stop_all();
		};
	}
}


#endif
