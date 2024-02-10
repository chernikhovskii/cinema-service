#ifndef CINEMA
#define CINEMA
#include <map>
#include <vector>
#include <mutex>
#include <set>
#include "Movie.hh"

class Cinema
{
private:
    Cinema();
    std::vector<Movie *> movieList_;
    std::mutex mutex_;
    std::string SelectedMovie_;
    std::string SelectedTheater_;
    static Cinema *cinema_;

public:
    Cinema(Cinema &other) = delete;
    void operator=(const Cinema &) = delete;
    static Cinema *GetInstance();

    ~Cinema();
    void AddMovie(const std::string &name);
    std::set<std::string> GetMovieList();
    std::vector<int> GetTheatersListShowingMovie(const std::string &name);
    std::vector<int> GetAvailableSeats(int number);
    bool BookAvailableSeats(int theaterNumber, std::vector<unsigned int> number);
};
#endif