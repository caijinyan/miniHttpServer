#include "connection_manager.h"


namespace http
{
	namespace server
	{
		void connection_manager::start(connection_ptr c)
		{
			connections.insert(c);
			c->start();
		}
		void connection_manager::stop(connection_ptr c)
		{
			connections.erase(c);
			c->stop();
		}
		void connection_manager::stop_all()
		{
			//遍历 ，关闭所有的链接

			for (std::set<connection_ptr>::iterator it = connections.begin() ; it != connections.end() ; it ++ )
			{
				(*it)->stop();
			}
			connections.clear();
		}

	}
}

