#ifndef CLIENT
#define CLIENT
#include <string>
#include <thread>
#include "BlockedQueue.hh"

#define CMD_SIZE 256

/**
 * @brief Payload for client-server communication with a limited message length
 *
 */
struct Payload
{
    /**
     * @brief Construct a new Payload
     *
     */
    Payload()
    {
        memset(payload_, 0, CMD_SIZE);
    }
    /**
     * @brief Construct a new Payload object
     *
     * @param payload
     * @param len
     */
    Payload(const char *payload, int len)
    {
        memset(payload_, 0, CMD_SIZE);
        if (len >= CMD_SIZE)
            len = CMD_SIZE - 1;
        memcpy(payload_, payload, len);
        len_ = len;
    }
    //! Command array
    char payload_[CMD_SIZE];
    //! Command len
    int len_;
};

class Client
{
private:
    //! basic response message on success
    std::string resOK = "OK";
    //! basic response message on fail
    std::string resERROR = "ERROR";
    //! File descriptor connection
    int connfd_;
    //! Title of the selected movie
    std::string selectedMovie_;
    //! Theater room number
    int selectedTheaters_;
    //! To terminate client threads
    bool run_;

    //! Thread to read a message from a client
    std::thread *readThread_;
    //! Thread for sending a message to a client
    std::thread *writeThread_;
    //! Thread for processing commands from the client
    std::thread *processThread_;

    //! Read message queue
    BlockedQueue<Payload> readQueue_;
    //! Write message queue
    BlockedQueue<Payload> writeQueue_;

    /**
     * @brief Reading messages from the client
     *
     */
    void ReadLoop();
    /**
     * @brief Writing message to a client
     *
     */
    void WriteLoop();
    /**
     * @brief Processing commands from the client
     *
     */
    void ProcessLoop();

    /**
     * @brief Get a movie list
     *
     * @return std::string client command result
     */
    std::string ViewAllPlayingMovies();
    /**
     * @brief Сhoose a movie
     *
     * @param movie The title of the movie
     * @return std::string client command result
     */
    std::string SelectMovie(const std::string &movie);
    /**
     * @brief Пet a list of theaters with the movie
     *
     * @return std::string client command result
     */
    std::string SeeAllTheatersShowingTheMovie();
    /**
     * @brief Сhoose a movie theater
     *
     * @param number theater number
     * @return std::string client command result
     */
    std::string SelectTheater(const int number);
    /**
     * @brief Get a list of available places
     *
     * @return std::string client command result
     */
    std::string SeeAvailableSeats();
    /**
     * @brief Book seats
     *
     * @param orderList booking list
     * @return std::string client command result
     */
    std::string BookAvailableSeats(const std::string &orderList);
    /**
     * @brief Split a string into substrings
     *
     * @param src Split line
     * @param delim Delimiter character
     * @param result Vector to save the result
     */
    void Split(const std::string &src, char delim, std::vector<std::string> &result);
    /**
     * @brief substring comparison function
     *
     * @param a substring num 1
     * @param b substring num 2
     * @return true
     * @return false
     */
    bool StartsWith(const char *a, const char *b);

public:
    /**
     * @brief Сlient instance launch
     *
     */
    void Start();
    /**
     * @brief Construct a new Client object
     *
     * @param connfd
     */
    Client(int connfd);
    /**
     * @brief Destroy the Client object
     *
     */
    ~Client();
    /**
     * @brief Сlient instance shutdown
     *
     */
    void Finish();
};

#endif