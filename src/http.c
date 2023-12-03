// http.c

#include "http.h"
#include <stdio.h>
#include <string.h>
// 请完成这个函数
// 这个函数的参数是一个字符串，表示原始的请求，你可以用printf打印看看是啥
// 这个函数的返回值是response，表示输出的响应，你需要按照格式来自行构造
// 理论上，你写完这个函数，编译运行，能通过访问 http://127.0.0.1 来交互
// 你可以尝试着让你写的函数去访问htdocs里面的网页，方法是通过读取文件
// 如果你不会写，可以试试最暴力地方法，先自己构造一个静态的response在浏览器里看看效果
// 如果你实在不会，可以在answer文件夹里参考答案，然后自己独立实现出来
char *http_process(char *request) {
	static char response[4096]; // 如果1024不够用你还可以自己添加->4096
	//char response[8192];
	char file_buffer[1024];
	char line[512];//假设1行不会超过512个字符
	*response = '\0';
	printf("%s", request);//会爆烫烫烫

	FILE* file;



	file = fopen("src/htdocs/index.html", "r");//由于Visual Studio工程文件夹设在了exlab1，所以路径需要加上src/
	//file = fopen("htdocs/index.html", "r");//不加的话正好作为404 Not Found的演示
	if (file)
	{
		strcat(response, "HTTP/1.1 200 OK\r\n");//CR+LF Carriage Return Line Feed
		strcat(response, "Server: ExLab1\r\n");
		strcat(response, "Connection: keep-alive\r\n");
		strcat(response, "Content-type: text/html\r\n");

		strcat(response, "\r\n");//To End the Response Header
		while (fgets(line, sizeof(line), file))
			strcat(response, line);
	}
	else
	{
		file = fopen("src/htdocs/404.html", "r");
		if (file)
		{
			strcat(response, "HTTP/1.1 404 Not Found\r\n");
			strcat(response, "Server: ExLab1\r\n");
			strcat(response, "Connection: close\r\n");
			strcat(response, "Content-type: text/html\r\n");

			strcat(response, "\r\n");
			while (fgets(line, sizeof(line), file))
				strcat(response, line);
		}
	}

		//strcat(response, "404 Not Found\r\n");
	fclose(file);
	return response;
}
