#include "Movie.hh"
#include <iostream>
Movie::Movie(const std::string &movieName) : movieName_(movieName), availableSeats_()
{
}

Movie::~Movie()
{
}

bool Movie::ReserveSeat(const unsigned int number)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    if (number < MAX_CAPACITY)
    {
        if (availableSeats_[number] == false)
        {
            availableSeats_[number] = true;
            return true;
        }
    }
    return false;
}

bool Movie::ReleaseSeat(const unsigned int number)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    if (number < MAX_CAPACITY)
    {
        if (availableSeats_[number] == true)
        {
            availableSeats_[number] = false;
            return true;
        }
    }
    return false;
}

std::vector<int> Movie::GetAvailableSeats()
{
    const std::lock_guard<std::mutex> lock(mutex_);
    std::vector<int> availableList;
    for (int i = 0; i < MAX_CAPACITY; i++)
    {
        if (availableSeats_[i] == false)
            availableList.push_back(i);
    }
    return availableList;
}

std::string Movie::GetName()
{
    return movieName_;
}

bool Movie::BookSeats(const std::vector<unsigned int> numbers)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    for (auto number : numbers)
    {
        if (number >= MAX_CAPACITY || availableSeats_[number] == true)
        {
            return false;
        }
    }
    for (auto number : numbers)
    {
        availableSeats_[number] = true;
    }
    return true;
}
