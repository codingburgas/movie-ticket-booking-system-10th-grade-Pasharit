#pragma once
#include <vector>
#include <string>
#include "Seat.h"

class Show {
public:
    int showId;
    std::string movieTitle;
    std::vector<Seat> seats;

    Show(int id, const std::string& title, int totalSeats);
    void displaySeats();
    bool bookSeat(int seatNum);
};


