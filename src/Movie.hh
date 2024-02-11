#ifndef MOVIE
#define MOVIE
#include <string>
#include <mutex>
#define MAX_CAPACITY 20
/**
 * @brief A class description of one movie
 */
class Movie
{
private:
    //! Title of the movie
    std::string movieName_;
    //! Array of available movie seats
    bool availableSeats_[MAX_CAPACITY];
    //! Mutex for secure data handling
    std::mutex mutex_;

public:
    /**
     * @brief Construct a new Movie object
     *
     * @param movieName Title of the movie
     */
    Movie(const std::string &movieName);
    /**
     * @brief Destroy the Movie object
     *
     */
    ~Movie();
    /**
     * @brief One seat reserve
     *
     * @param number Seat number
     * @return true - the reservation was successful
     * @return false - the reservation was unsuccessful
     */
    bool ReserveSeat(const unsigned int number);
    /**
     * @brief One seat release
     *
     * @param number Seat number
     * @return true - Release of one seat successfully
     * @return false - Release of one seat unsuccessful
     */
    bool ReleaseSeat(const unsigned int number);
    /**
     * @brief Reserve a few seats
     *
     * @param numbers Reserve list
     * @return true - The reservation was successful
     * @return false - The reservation was unsuccessful
     */
    bool BookSeats(const std::vector<unsigned int> numbers);
    /**
     * @brief Get the Available Seats List
     *
     * @return std::vector<int> List of available seats
     */
    std::vector<int> GetAvailableSeats();
    /**
     * @brief Get the Movie Title
     *
     * @return std::string Movie Title
     */
    std::string GetName();
};
#endif