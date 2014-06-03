#include "server.h"

int main()
{
	std::cout<<"输入本机Ip："<<std::endl;
	std::string addr;
	std::cin>>addr;
	std::cout<<"输入端口号："<<std::endl;
	int port;
	std::cin>>port;
	std::cout<<"输入文件根目录："<<std::endl;
	std::string path;
	std::cin>>path;
	//5是自定义的线程数
	std::cout<<"working. ."<<std::endl;
	http::server::server sr(addr,port,path,5);

	sr.run();

	return 0;

}