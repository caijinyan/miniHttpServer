#include "http_request_handler.h"
#include "http_reply.h"
#include <iostream>
#include <sstream>


namespace http
{
	namespace server
	{
		http_request_handler::http_request_handler( std::string & doc_root):path(doc_root)
		{}
		void http_request_handler::handle_request(const request& req ,http_reply & rep)
		{
			rep.status_ = http_reply::status_type::ok;
			if(decodeUrl(req.uri) == false)
			{
				rep.stock_replie(http_reply::status_type::bad_request);
				return;
			}
			if(path[path.size() -1] == '/')
			{
				path += "index.html";
			}
			
			//����Ӧ���ĵ�����
			if ( false == getFileContex(rep.context) )
			{
				rep.stock_replie(http_reply::status_type::not_found);
			}
			
			std::cout<<"path =" <<path<<std::endl;
			return;
		}


		bool http_request_handler::getFileContex(std::string& context)
		{
			std::ifstream inf(path.c_str());
			if ( !inf )
			{
				return false;
			}
			char ch;
			while(inf.get(ch))
			{
				context.push_back(ch);
			}
			return true;
		}

		bool http_request_handler::decodeUrl(const std::string url)
		{
			// url = " /search?hl=zh-CN&source=hp&q=domety&aq=f&oq="
			//��ȡ�ʺ�֮ǰ���ַ���������path�󣬳�Ϊ����·��

			std::string tmpStr,tmpStr1;

			int index = url.find_first_of('?');
			//���û���ҵ�������ôuil�ӵ����ݾ����ļ�·��
			if ( index == -1)
			{
				tmpStr = url;
			}
			else
				tmpStr = url.substr(0, index);

			for (std::size_t i = 0; i < tmpStr.size(); ++i)
			{
				if (tmpStr[i] == '%')
				{
					  if (i + 3 <= tmpStr.size())
					  {
							int value = 0;
							std::istringstream is(tmpStr.substr(i + 1, 2));
							if (is >> std::hex >> value)
							{
								tmpStr1 += static_cast<char>(value);
								  i += 2;
							}
							else
							{
								  return false;
							}
					  }
					  else
					  {
							return false;
					  }
				}
				else if (tmpStr[i] == '+')
				{
					tmpStr1 += ' ';
				}
				else
				{
					tmpStr1 += tmpStr[i];
				}
			}
			path = path + tmpStr1;
			return true;
		}
	}
}