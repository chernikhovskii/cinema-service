#include "Client.hh"
#include "Cinema.hh"
#include <unistd.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <sstream>

Client::Client(int connfd) : connfd_(connfd), run_(true)
{
}

Client::~Client()
{
}
void Client::Start()
{
    std::cout << __func__ << std::endl;
    readThread_ = new std::thread(&Client::ReadLoop, this);
    writeThread_ = new std::thread(&Client::WriteLoop, this);
    writeThread_ = new std::thread(&Client::ProcessLoop, this);
}

void Client::ReadLoop()
{
    fd_set readSet;
    while (run_)
    {

        char payload[CMD_SIZE];
        int payloadlen;
        timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        FD_ZERO(&readSet);
        FD_SET(connfd_, &readSet);
        if (select(connfd_ + 1, &readSet, nullptr, nullptr, &timeout) > 0)
        {
            if (FD_ISSET(connfd_, &readSet))
            {
                payloadlen = read(connfd_, &payload, CMD_SIZE);
                if (payloadlen > 0)
                {
                    Payload p(payload, payloadlen);
                    readQueue_.push(p);
                }
            }
        }
    }
}

void Client::WriteLoop()
{
    Payload payload;
    while (run_)
    {
        if (writeQueue_.pop(payload))
        {
            write(connfd_, payload.payload_, payload.len_);
        }
    }
}

void Client::ProcessLoop()
{

    while (run_)
    {
        Payload payload;
        if (readQueue_.pop(payload))
        {
            if (payload.len_ > 0 && payload.payload_[0] == 'C')
            {
                std::string answer;
                switch (payload.payload_[1])
                {
                case '0':
                    answer = ViewAllPlayingMovies();
                    break;
                case '1':
                    answer = SelectMovie(&payload.payload_[2]);
                    break;
                case '2':
                    answer = SeeAllTheatersShowingTheMovie();
                    break;
                case '3':
                {
                    stringstream ss;
                    int num;
                    string str(&payload.payload_[2]);
                    ss << str;
                    ss >> num;
                    answer = SelectTheater(num);
                }
                break;
                case '4':
                    answer = SeeAvailableSeats();
                    break;
                case '5':
                    answer = BookAvailableSeats(&payload.payload_[2]);
                    break;
                default:
                    break;
                }
                writeQueue_.push({answer.c_str(), (int)answer.size()});
            }
        }
    }
}

void Client::Finish()
{
    run_ = false;
    if (readThread_->joinable())
    {
        readThread_->join();
        delete readThread_;
    }

    if (writeThread_->joinable())
    {
        writeThread_->join();
        delete writeThread_;
    }
    readQueue_.stop();
    writeQueue_.stop();
}

std::string Client::ViewAllPlayingMovies()
{
    std::string answer;
    Cinema *cinema = Cinema::GetInstance();
    auto res = cinema->GetMovieList();
    for (auto r : res)
    {
        cout << r << " " << r.size() << endl;
        if (!answer.empty())
        {
            answer += ',';
        }
        answer += r;
    }
    return answer;
}

std::string Client::SelectMovie(const string &movie)
{
    std::string answer;
    Cinema *cinema = Cinema::GetInstance();
    auto res = cinema->GetMovieList();
    if (res.find(movie) != res.end())
    {
        selectedMovie_ = movie;
        answer = resOK + " " + movie;
    }
    else
    {
        selectedMovie_.clear();
        answer = resERROR;
    }
    return answer;
}

std::string Client::SeeAllTheatersShowingTheMovie()
{
    std::string answer;
    Cinema *cinema = Cinema::GetInstance();
    if (selectedMovie_.empty())
    {
        selectedMovie_.clear();
        answer = resERROR;
    }
    else
    {
        auto res = cinema->GetTheatersListShowingMovie(selectedMovie_);
        if (res.empty())
        {
            answer = resERROR + " Empty";
        }
        for (auto r : res)
        {
            if (!answer.empty())
            {
                answer += ',';
            }
            answer += to_string(r);
        }
    }
    return answer;
}
std::string Client::SelectTheater(int number)
{
    std::string answer;
    Cinema *cinema = Cinema::GetInstance();
    auto theatersList = cinema->GetTheatersListShowingMovie(selectedMovie_);
    auto res = std::find(theatersList.begin(), theatersList.end(), number);
    if (res != theatersList.end())
    {
        selectedTheaters_ = number;
        answer = resOK + " " + to_string(number);
    }
    else
    {
        selectedTheaters_ = -1;
        answer = resERROR;
    }
    return answer;
}

std::string Client::SeeAvailableSeats()
{
    std::string answer;
    Cinema *cinema = Cinema::GetInstance();
    auto res = cinema->GetAvailableSeats(selectedTheaters_);
    for (auto r : res)
    {
        if (!answer.empty())
        {
            answer += ',';
        }
        answer += to_string(r);
    }
    return answer;
}

void Client::Split(const std::string &src, char delim, std::vector<std::string> &result)
{
    std::string part;
    std::stringstream ss(src);
    while (getline(ss, part, delim))
    {
        if (part.size())
        {
            result.push_back(part);
        }
    }
}

std::string Client::BookAvailableSeats(const std::string &tickets)
{
    Cinema *cinema = Cinema::GetInstance();
    std::string answer;
    std::vector<std::string> ticketList;
    Split(tickets, ',', ticketList);

    std::vector<unsigned int> ticketListNum;
    for (auto t : ticketList)
    {
        stringstream ss;
        int num;
        ss << t;
        ss >> num;
        ticketListNum.push_back(num);
    }
    bool res = cinema->BookAvailableSeats(selectedTheaters_, ticketListNum);
    answer = res ? resOK : resERROR;
    return answer;
}