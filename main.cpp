#include "server.h"

int main()
{
	std::cout<<"���뱾��Ip��"<<std::endl;
	std::string addr;
	std::cin>>addr;
	std::cout<<"����˿ںţ�"<<std::endl;
	int port;
	std::cin>>port;
	std::cout<<"�����ļ���Ŀ¼��"<<std::endl;
	std::string path;
	std::cin>>path;
	//5���Զ�����߳���
	std::cout<<"working. ."<<std::endl;
	http::server::server sr(addr,port,path,5);

	sr.run();

	return 0;

}