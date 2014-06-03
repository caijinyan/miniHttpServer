#include "http_reply.h"
#include <boost\lexical_cast.hpp>

namespace http
{
	namespace server
	{
		/////////////////////////////ȫ�ֱ���////////////////////

		//Ӧ�������һ��
		namespace statusString
		{
			const std::string ok = "HTTP/1.0 200 OK\r\n";
			const std::string bad_request ="HTTP/1.0 400 Bad Request\r\n";
			const std::string not_found ="HTTP/1.0 404 Not Found\r\n";
			////�Ѿ��������״̬��ȡ���ݣ���һ��
			std::string getStringByStatus(http_reply::status_type status)
			{
				std::string ret;
				switch (status)
				{
				case http::server::http_reply::ok:
					ret = ok;
					break;
				case http::server::http_reply::bad_request:
					ret = bad_request;
					break;
				case http::server::http_reply::not_found:
					ret = not_found;
					break;
				default:
					break;
				}
				return ret;
			}
		}

		//Ӧ��
		namespace stock_replies
		{
			const char ok[] ="";
			const char bad_request[] =
			  "<html>"
			  "<head><title>Bad Request</title></head>"
			  "<body><h1>400 Bad Request</h1></body>"
			  "</html>";
			const char not_found[] =
			  "<html>"
			  "<head><title>Not Found</title></head>"
			  "<body><h1>404 Not Found</h1></body>"
			  "</html>";

			const std::string to_string(http_reply::status_type status_)
			{
				std::string  ret;
				switch (status_)
				{
				case http::server::http_reply::ok:
					ret = ok;
					break;
				case http::server::http_reply::bad_request:
					ret = bad_request;
					break;
				case http::server::http_reply::not_found:
					ret = not_found;
					break;
				default:
					break;
				}
				return ret;
			}
		}

		namespace misc_string
		{
			//'\r\n'
			const char crlf[]={'\r','\n'};
			//ð�źͿո�
			const char colon_balank[] ={':',' '};
		}
		//////////////////////��Ա��������/////////////////////////////////////////////
		const std::vector<std::string> http_reply::getContex()
		{
			std::vector<std::string> ret;
			
			//�����һ��
			ret.push_back(statusString::getStringByStatus(status_));
			//��������ͷ��
			for ( std::size_t i = 0 ; i < header_.size() ; i++ )
			{
				ret.push_back(header_[i].name);
				ret.push_back(misc_string::colon_balank);
				ret.push_back(header_[i].value);
				ret.push_back(misc_string::crlf);
			}
			ret.push_back(misc_string::crlf);
			//���к������������
			ret.push_back(context);
			//��������
			return ret;
		}
		void http_reply::stock_replie(http_reply::status_type status)
		{
			status_ = status;

			context = stock_replies::to_string(status);

			header_.resize(2);
			header_[0].name = "Content-Length";
		    header_[0].value = boost::lexical_cast<std::string>(context.size());
			header_[1].name = "Content-Type";
			header_[1].value = "text/html";
		}

	}
}
