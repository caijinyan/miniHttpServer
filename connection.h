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
//�������Ĵ�С
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

	//��ʼ������
	void start();

	//�ر�socket
	void stop();
private:
	//������
	boost::array<char,10240> buffer_;

	//��ȡ�����Ĳ�������
	void handle_read(const boost::system::error_code &ec, std::size_t bytes_transferred);

	//д����������ĺ���
	void handle_write(const boost::system::error_code &ec);

	//���ڷ������ݵĻ�����
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


