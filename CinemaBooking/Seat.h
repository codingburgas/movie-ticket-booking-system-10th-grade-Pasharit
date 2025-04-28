#pragma once
#include <iostream>

enum SeatType { SILVER, GOLD, PLATINUM };

struct Seat {
    int seatNumber;
    bool isBooked;
    SeatType type;

    Seat(int number, SeatType seatType);
};

