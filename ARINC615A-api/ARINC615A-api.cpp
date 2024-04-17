// ARINC615A-api.cpp: 定义应用程序的入口点。
//

#include "ARINC615A-api.h"
#include "singleton.h"
#include "threadpool.h"
#include "asio.hpp"
#include <thread>
#include <future>
using namespace std;

void print(const asio::error_code&) {
	spdlog::logger& logger = Singleton<spdlog::logger>::Instance();
	logger.critical("hello world");
}

int initTftpServer(int x) {
	//TODO
	spdlog::logger& logger = Singleton<spdlog::logger>::Instance();
	logger.critical("in TftpServer");
	asio::io_context io;
	asio::steady_timer t(io, asio::chrono::seconds(5));
	t.async_wait(&print);
	io.run();
	return 1;
}




int main()
{
	ThreadPool threadPool(4);
	threadPool.submit(initTftpServer, 5);
	threadPool.init();
	/*auto tftpServer = std::async(std::launch::async, initTftpServer);*/
	spdlog::logger& logger = Singleton<spdlog::logger>::Instance();
	logger.critical("in main");
	while (true) {
		int op;
		cin >> op;
		switch (op) {
		case 1:
			//FIND
			//threadPool.submit();
			break;
		case 2:
			//INFORMATION
			break;
		case 3:
			//UPLOAD
			break;
		case 4:
			//MDOWNLOAD
			break;
		case 5:
			//ODOWNLOAD
			break;
		default:
			break;
		}
	}
	return 0;
}
