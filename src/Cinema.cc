#include "Cinema.hh"
#include <iostream>
#include <set>

using namespace std;
Cinema *Cinema::cinema_ = nullptr;

Cinema *Cinema::GetInstance()
{
    if (cinema_ == nullptr)
    {
        cinema_ = new Cinema();
    }
    return cinema_;
}

Cinema::Cinema(/* args */)
{
    cout << ("Cinema service run") << endl;
}

Cinema::~Cinema()
{
}

void Cinema::AddMovie(const std::string &name)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    Movie *movie = new Movie(name);
    movieList_.push_back(movie);
}

std::set<std::string> Cinema::GetMovieList()
{
    std::set<std::string> list;
    for (auto movie : movieList_)
    {
        list.insert(movie->GetName());
    }
    return list;
}

std::vector<int> Cinema::GetTheatersListShowingMovie(const std::string &name)
{
    std::vector<int> theatersList;
    for (size_t i = 0; i < movieList_.size(); i++)
    {
        if (movieList_[i]->GetName() == name)
        {
            theatersList.push_back(i);
        }
    }
    return theatersList;
}

std::vector<int> Cinema::GetAvailableSeats(int theaterNumber)
{
    std::vector<int> res;
    if ((unsigned int)theaterNumber < movieList_.size())
    {
        res = movieList_[theaterNumber]->GetAvailableSeats();
    }
    return res;
}

bool Cinema::BookAvailableSeats(int theaterNumber, std::vector<unsigned int> number)
{
    std::cout << "Cinema" << __func__ << std::endl;
    bool res = false;
    if ((unsigned int)theaterNumber < movieList_.size())
    {
        res = movieList_[theaterNumber]->BookSeats(number);
    }
    return res;
}