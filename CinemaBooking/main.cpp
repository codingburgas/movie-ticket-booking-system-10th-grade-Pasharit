#include <iostream>
#include "../include/BookingSystem.h"

int main() {
    BookingSystem system;

    Cinema cinema("Dream Cinemas");

    Movie movie("Inception", "English", "Sci-Fi", "2010-07-16");

    Show morningShow(1, "Inception", 15);
    Show eveningShow(2, "Inception", 15);

    movie.addShow(morningShow);
    movie.addShow(eveningShow);

    cinema.addMovie(movie);
    system.addCinema(cinema);

    cinema.displayMovies();
    system.searchMovie("Inception");

    cinema.movies["Inception"].shows[0].displaySeats();
    system.bookSeat("Dream Cinemas", "Inception", 1, 3);
    cinema.movies["Inception"].shows[0].displaySeats();

    return 0;
}
