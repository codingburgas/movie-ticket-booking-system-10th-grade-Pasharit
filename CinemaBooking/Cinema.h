#pragma once
#include <string>
#include <map>
#include "Movie.h"

class Cinema {
public:
    std::string name;
    std::map<std::string, Movie> movies;

    Cinema(const std::string& cinemaName);
    void addMovie(const Movie& movie);
    void displayMovies();
};

