/**********************************************************************
 *    > File Name    : http.cpp
 *    > Author       : qujiale
 *    > Created Time : 2019年09月23日 星期一 15时50分48秒
 *    > Description  : 实现一个简单的HTTP服务器 
 **********************************************************************/
#include <sstream>
#include "tcpsocket.hpp"

int main()
{
    TcpSocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind("0.0.0.0",9000));
    CHECK_RET(sock.Listen());
    while(1)
    {
        TcpSocket clisock;
        if(sock.Accept(clisock) == false)
        {
            continue;
        }
        string buf;
        clisock.Recv(buf);
        cout << "req:[" << buf << "]" << endl;
        string body = "<html><body><h1>屈佳乐好帅</h1></body></html>";
        body += "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />";
        string first = "HTTP/1.1 200 OK\r\n";
        std::stringstream ss;
        ss << "Content-Length: " << body.size() << "\r\n";
        //ss << "Location: https://v.qq.com/\r\n";
        string head = ss.str();
        string blank = "\r\n";

        clisock.Send(first);
        clisock.Send(head);
        clisock.Send(blank);
        clisock.Send(body);
        clisock.Close();
    }
    sock.Close();
    return 0;
}


