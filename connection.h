#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include <boost\asio.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\enable_shared_from_this.hpp>
#include <boost\noncopyable.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>
#include <boost\asio\buffer.hpp>


#include "http_request_handler.h"
#include "request_parser.h"
#include "request.h"
#include "http_reply.h"


namespace http
{
namespace server
{

	class  connection_manager;

const int buf_size = 10240;
//缓冲区的大小
class connection
	: public boost::enable_shared_from_this<connection>,\
      private boost::noncopyable
{
private:
	boost::asio::ip::tcp::socket socket_;

	http_request_handler request_hand_;
public:
	connection(boost::asio::io_service & ios_ , std::string doc_root,connection_manager& conection_mgr_);
	~connection(void);
	boost::asio::ip::tcp::socket& socket();

	//开始读函数
	void start();

	//关闭socket
	void stop();
private:
	//缓冲区
	boost::array<char,10240> buffer_;

	//读取结束的操作函数
	void handle_read(const boost::system::error_code &ec, std::size_t bytes_transferred);

	//写操作结束后的函数
	void handle_write(const boost::system::error_code &ec);

	//用于发送数据的缓冲区
	std::string buf_;

	request_parser request_parser_;

	request request_;

	connection_manager& conection_mgr;

	http_reply rep;
};

typedef boost::shared_ptr<connection> connection_ptr;
}
}

#endif


