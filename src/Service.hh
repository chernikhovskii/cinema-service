#ifndef SERVICE
#define SERVICE
#include <arpa/inet.h>
#include "BlockedQueue.hh"
#include "Cinema.hh"
#include "Client.hh"
class Service
{
private:
    //! server socket address
    sockaddr_in serv_;
    //! socket file descriptor
    int servfd_;
    //! Client queue
    BlockedQueue<int> readQueue_;
    //! client socket address
    sockaddr cli_;
    //! client socket size
    socklen_t siz_;
    //! Thread life value
    bool loopRun_;
    //! Client list (further used for secure memory clearing)
    std::vector<Client *> clientList_;

public:
    /**
     * @brief Construct a new Service object
     *
     */
    Service();
    /**
     * @brief Destroy the Service object
     *
     */
    ~Service();
    /**
     * @brief  Service initialization
     *
     */
    void Init();
    /**
     * @brief Start of the service
     *
     */
    void Run();
    /**
     * @brief thread for creating new client
     *
     */
    void ClientCreateLoop();
};
#endif