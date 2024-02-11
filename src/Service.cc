#include "Service.hh"
#include <iostream>

#include <thread>
#include <string>

using namespace std;
Service::Service(/* args */)
{
}

Service::~Service()
{
}
void Service::Init()
{

    Cinema *cinema = Cinema::GetInstance();
    cinema->AddMovie("Alien");
    cinema->AddMovie("Gladiator");
    cinema->AddMovie("Jaws");
    cinema->AddMovie("Titanic");
    cinema->AddMovie("Jaws");

    bzero(&serv_, sizeof(serv_));
    serv_.sin_family = AF_INET;
    serv_.sin_port = htons(3345);
    inet_aton("127.0.0.1", &(serv_.sin_addr));

    servfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int bindRes = ::bind(servfd_, (sockaddr *)(&serv_), sizeof(serv_));
    cout << "Bind returned: " << bindRes << endl;

    listen(servfd_, 5);
    siz_ = sizeof(cli_);
    loopRun_ = true;
}

void Service::Run()
{
    std::thread readThread(&Service::ReadLoop, this);
    readThread.detach();
    int connfd;
    while (loopRun_)
    {
        if ((connfd = accept(servfd_, &cli_, &siz_)) >= 0)
        {
            readQueue_.push(connfd);
            cout << "Accept, connfd: " << connfd << endl;
        }
    }
}

void Service::ReadLoop()
{
    while (loopRun_)
    {
        int connfd;
        if (readQueue_.pop(connfd))
        {
            Client *client = new Client(connfd);
            client->Start();
            clientList_.push_back(client);
        }
    }
}
