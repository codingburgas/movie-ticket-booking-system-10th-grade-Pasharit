#include "Seat.h"

Seat::Seat(int number, SeatType seatType)
    : seatNumber(number), isBooked(false), type(seatType) {
}
