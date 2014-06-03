#include "server.h"
#include <boost\bind.hpp>


namespace http
{
namespace server
{

//////////////////////////////////////////////////
server::server(const std::string& addr,const int& port, std::string & doc_root_,unsigned thread_pool_size_):
	io_service_(),\
	acceptor_(io_service_),\
	connection_mgr(),\
	doc_root(doc_root_),\
	new_connection_(new connection(io_service_,doc_root_,connection_mgr)),\
	thread_pool_size(thread_pool_size_)
{
	  boost::asio::ip::tcp::resolver resolver(io_service_);
	  boost::asio::ip::tcp::resolver::query query(addr,boost::lexical_cast<std::string>(port));
	  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	  acceptor_.open(endpoint.protocol());
	  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	  acceptor_.bind(endpoint);
	  //开始监听
	  acceptor_.listen();
	  //异步接受链接
	  acceptor_.async_accept(new_connection_->socket(),\
		  boost::bind(&server::handle_accept, this,\
			boost::asio::placeholders::error));
}


server::~server(void)
{
	
}

void server::run()
{
	std::vector<boost::shared_ptr<boost::thread> > threads;
	
	for (std::size_t i = 0; i < thread_pool_size; ++i)
	{
		
		boost::shared_ptr<boost::thread> thread(new boost::thread( boost::bind(&boost::asio::io_service::run, &io_service_)));
		
		threads.push_back(thread);
	 
	}
	 
	for (std::size_t i = 0; i < threads.size(); ++i)
		
		threads[i]->join();
}

void server::handle_accept(const boost::system::error_code& ec)
{

	if(! ec)
	{
		std::cout<<"new connection: "<<new_connection_->socket().remote_endpoint().address().to_string()<<std::endl;
		/*开始处理数据了*/
		connection_mgr.start(new_connection_);

		new_connection_.reset(new connection(io_service_,doc_root,connection_mgr));

		/*继续接受新的链接*/
		acceptor_.async_accept(\
			new_connection_->socket(),\
			boost::bind(&server::handle_accept, this,\
			boost::asio::placeholders::error));
		
		
		//输出链接信息
		
	}
}

//////////////////////////////////////////////////
}
}

