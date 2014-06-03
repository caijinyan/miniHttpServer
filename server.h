#pragma once
#include <boost\asio.hpp>
#include <string>
#include <boost\noncopyable.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\bind.hpp>
#include <boost\asio\buffer.hpp>
#include <boost\thread.hpp>

#include "connection.h"
#include "connection_manager.h"


namespace http
{
namespace server
{

//////////////////////////////////////////////////
using namespace boost::asio;

class server: private boost::noncopyable
{
public:
	explicit server(const std::string &addr,const int& port, std::string & root_dictor,unsigned );
	void run();
	~server(void);
private:

	//Io_service ����
	boost::asio::io_service io_service_;

	//�û������ͻ��˵�����
	boost::asio::ip::tcp::acceptor acceptor_;


	
	//�������ݵĲ�������
	void handle_accept(const boost::system::error_code &ec);


	connection_manager connection_mgr;

	http::server::connection_ptr new_connection_;

	std::string doc_root;

	unsigned thread_pool_size;

	
};



//////////////////////////////////////////////////
}
}
