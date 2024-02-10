#ifndef SERVICE
#define SERVICE
#include <unistd.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "BlockedQueue.hh"
#include "Cinema.hh"
#include "Client.hh"
class Service
{
private:
    sockaddr_in serv_;
    int servfd_;
    BlockedQueue<int> readQueue_;
    sockaddr cli_;
    socklen_t siz_;
    bool loopRun_;
    std::vector<Client *> clientList_;

public:
    Service(/* args */);
    ~Service();
    void Init();
    void Run();
    void ReadLoop();
};
#endif