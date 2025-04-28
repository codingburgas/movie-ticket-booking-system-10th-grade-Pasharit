#include "BookingSystem.h"
#include <iostream>

void BookingSystem::addCinema(const Cinema& cinema) {
    cinemas.push_back(cinema);
}

void BookingSystem::searchMovie(const std::string& title) {
    for (auto& cinema : cinemas) {
        if (cinema.movies.find(title) != cinema.movies.end()) {
            std::cout << "Found movie: " << title << " in cinema: " << cinema.name << "\n";
            return;
        }
    }
    std::cout << "Movie not found.\n";
}

void BookingSystem::bookSeat(const std::string& cinemaName, const std::string& movieTitle, int showId, int seatNumber) {
    for (auto& cinema : cinemas) {
        if (cinema.name == cinemaName) {
            auto& movie = cinema.movies[movieTitle];
            for (auto& show : movie.shows) {
                if (show.showId == showId) {
                    if (show.bookSeat(seatNumber)) {
                        std::cout << "Seat " << seatNumber << " booked successfully for movie: " << movieTitle << "\n";
                        return;
                    }
                    else {
                        return;
                    }
                }
            }
        }
    }
    std::cout << "Booking failed.\n";
}
