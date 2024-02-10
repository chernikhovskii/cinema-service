#ifndef MOVIE
#define MOVIE
#include <string>
#include <mutex>
#define MAX_CAPACITY 20
class Movie
{
private:
    std::string movieName_;
    bool availableSeats_[MAX_CAPACITY];
    std::mutex mutex_;

public:
    Movie(const std::string &movieName);
    Movie();
    ~Movie();
    bool ReserveSeat(const unsigned int number);
    bool ReleaseSeat(const unsigned int number);
    bool BookSeats(const std::vector<unsigned int> numbers);
    std::vector<int> GetAvailableSeats();
    std::string GetName();
};
#endif