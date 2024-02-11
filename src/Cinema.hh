#ifndef CINEMA
#define CINEMA
#include <map>
#include <vector>
#include <mutex>
#include <set>
#include "Movie.hh"

/**
 * @brief Movie сinema class
 *
 */
class Cinema
{
private:
    /**
     * @brief Construct a new Cinema object
     *
     */
    Cinema();
    //! List of theaters with movies
    std::vector<Movie *> movieList_;
    //! Mutex for secure data handling
    std::mutex mutex_;
    //! Pointer to a unique class
    static Cinema *cinema_;

public:
    Cinema(Cinema &other) = delete;
    void operator=(const Cinema &) = delete;
    /**
     * @brief Get the Instance of unique class
     *
     * @return Cinema*
     */
    static Cinema *GetInstance();
    /**
     * @brief Destroy the Cinema object
     *
     */
    ~Cinema();
    /**
     * @brief Add a movie theater with a movie
     *
     * @param name Movie Title
     */
    void AddMovie(const std::string &name);
    /**
     * @brief Get the movie list
     *
     * @return std::set<std::string> list of movie
     */
    std::set<std::string> GetMovieList();
    /**
     * @brief Get the theaters list showing movie
     *
     * @param name Movie Title
     * @return std::vector<int> list of theaters with the provided movie
     */
    std::vector<int> GetTheatersListShowingMovie(const std::string &name);
    /**
     * @brief Get the available seats
     *
     * @param number theater number
     * @return std::vector<int> list of available seats
     */
    std::vector<int> GetAvailableSeats(int number);
    /**
     * @brief Book available seats
     *
     * @param theaterNumber theater number
     * @param number reservation list
     * @return true - The reservation was successful
     * @return false - The reservation was unsuccessful
     */
    bool BookAvailableSeats(int theaterNumber, std::vector<unsigned int> number);
};
#endif