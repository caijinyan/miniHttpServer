

#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP


#include "connection_manager.h"
#include "connection.h"


#include <boost\bind.hpp>

namespace http
{
namespace server
{


	connection::connection(boost::asio::io_service & ios_,std::string doc_root,connection_manager& conection_mgr_):
		socket_(ios_),\
		request_hand_(doc_root),
		conection_mgr(conection_mgr_)
	{

	}


	connection::~connection(void)
	{
	}

	boost::asio::ip::tcp::socket& connection::socket()
	{
		return socket_;
	}
	void connection::handle_write(const boost::system::error_code &ec)
	{
		if(ec != boost::asio::error::operation_aborted)
		{
			conection_mgr.stop(shared_from_this());
		}
	}
	void connection::handle_read(const boost::system::error_code &ec, std::size_t bytes_transferred)
	{
		boost::tribool result;
		 boost::tie(result, boost::tuples::ignore) =\
					request_parser_.parse(request_, buffer_.data(),buffer_.data() + bytes_transferred);
		
		if (result)
		{//解析成功

			request_hand_.handle_request(request_,rep);
			std::vector<std::string> tmpData = rep.getContex();
			for (std::vector<std::string> ::iterator it = tmpData.begin() ; it != tmpData.end(); ++it)
			{
				buf_ += (*it);
			}
			socket_.async_write_some(\
				boost::asio::buffer(buf_),boost::bind(&connection::handle_write,shared_from_this(),boost::asio::placeholders::error));
		}
		else if(!result)
		{
			//如果请求失败
			rep.stock_replie(http_reply::status_type::bad_request);
			std::vector<std::string> tmpData = rep.getContex();
			for (std::vector<std::string> ::iterator it = tmpData.begin() ; it != tmpData.end(); ++it)
			{
				buf_ += (*it);
			}
			socket_.async_write_some(\
				boost::asio::buffer(buf_),boost::bind(&connection::handle_write,shared_from_this(),boost::asio::placeholders::error));

		}
		else
		{//不确定状态，继续读数据
			socket_.async_read_some(\
				boost::asio::buffer(buffer_),\
				boost::bind(&connection::handle_read,shared_from_this(),\
				boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred)   );
		//bytes_transferred 保存了传输字节的数量
		}	
	}

	void connection::start()
	{
		socket_.async_read_some(\
			boost::asio::buffer(buffer_),\
			boost::bind(&connection::handle_read,shared_from_this(),\
			boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred)   );
		//bytes_transferred 保存了传输字节的数量
	}
	void connection::stop()
	{
		//取消socket链接
		socket_.close();
	}


}
}

#endif
