#pragma once
#include <vector>
#include "Cinema.h"

class BookingSystem {
private:
    std::vector<Cinema> cinemas;

public:
    void addCinema(const Cinema& cinema);
    void searchMovie(const std::string& title);
    void bookSeat(const std::string& cinemaName, const std::string& movieTitle, int showId, int seatNumber);
};

