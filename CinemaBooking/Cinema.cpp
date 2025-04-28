#include "Cinema.h"
#include <iostream>

Cinema::Cinema(const std::string& cinemaName) : name(cinemaName) {}

void Cinema::addMovie(const Movie& movie) {
    movies[movie.title] = movie;
}

void Cinema::displayMovies() {
    std::cout << "Movies in " << name << ":\n";
    for (auto& pair : movies) {
        std::cout << "- " << pair.second.title << " (" << pair.second.genre << ", " << pair.second.language << ")\n";
    }
}
