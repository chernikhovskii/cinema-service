#ifndef CLIENT
#define CLIENT
#include <string>
#include <thread>
#include "BlockedQueue.hh"
#define CMD_SIZE 256
struct Payload
{
    Payload()
    {
        memset(payload_, 0, CMD_SIZE);
    }
    Payload(const char *payload, int len)
    {
        memset(payload_, 0, CMD_SIZE);
        if (len >= CMD_SIZE)
            len = CMD_SIZE - 1;
        memcpy(payload_, payload, len);
        len_ = len;
    }
    char payload_[CMD_SIZE];
    int len_;
};

class Client
{
private:
    std::string resOK = "OK";
    std::string resERROR = "ERROR";

    int connfd_;
    std::string selectedMovie_;
    int selectedTheaters_ = -1;
    bool run_;
    std::thread *readThread_;
    std::thread *writeThread_;
    BlockedQueue<Payload> readQueue_;
    BlockedQueue<Payload> writeQueue_;

    void ReadLoop();
    void WriteLoop();
    void ProcessLoop();

    std::string ViewAllPlayingMovies();
    std::string SelectMovie(const std::string &movie);
    std::string SeeAllTheatersShowingTheMovie();
    std::string SelectTheater(const int number);
    std::string SeeAvailableSeats();
    std::string BookAvailableSeats(const std::string &orderList);

    void Split(const std::string &src, char delim, std::vector<std::string> &result);
    bool StartsWith(const char *a, const char *b);

public:
    void Start();
    Client(int connfd);
    ~Client();
    void Finish();
};

#endif