#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
    int clifd;
    clifd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(3345);
    inet_aton("127.0.0.1", &(serv.sin_addr));

    connect(clifd, (sockaddr *)(&serv), sizeof(serv)); // blocking call
    int n, m;
    char data[256];
    char recvd[256];
    for (;;)
    {
        fgets(data, 100, stdin);
        data[strlen(data) - 1] = 0;
        n = strlen(data);
        cout << "You have written " << n << endl; // this returns the correct value
        write(clifd, data, n);

        n = read(clifd, recvd, 256);
        recvd[n] = 0;
        cout << "Server echoed back " << n << " " << string(recvd) << endl; // this doesn't get displayed
    }
}