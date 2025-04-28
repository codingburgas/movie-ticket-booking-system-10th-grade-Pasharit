#include "Show.h"
#include <iostream>

Show::Show(int id, const std::string& title, int totalSeats)
    : showId(id), movieTitle(title) {
    for (int i = 1; i <= totalSeats; ++i) {
        SeatType type = (i <= 5) ? PLATINUM : (i <= 10) ? GOLD : SILVER;
        seats.emplace_back(i, type);
    }
}

void Show::displaySeats() {
    std::cout << "Seats for show: " << movieTitle << "\n";
    for (auto& seat : seats) {
        std::cout << "Seat " << seat.seatNumber << " ["
            << (seat.type == PLATINUM ? "Platinum" : seat.type == GOLD ? "Gold" : "Silver")
            << "] - "
            << (seat.isBooked ? "Booked" : "Available") << "\n";
    }
}

bool Show::bookSeat(int seatNum) {
    if (seatNum < 1 || seatNum > seats.size()) {
        std::cout << "Invalid seat number.\n";
        return false;
    }
    if (seats[seatNum - 1].isBooked) {
        std::cout << "Seat already booked.\n";
        return false;
    }
    seats[seatNum - 1].isBooked = true;
    return true;
}
