#pragma once
#include <string>
#include <vector>
#include "Show.h"

class Movie {
public:
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
    std::vector<Show> shows;

    Movie(const std::string& t, const std::string& lang, const std::string& gen, const std::string& date);
    void addShow(Show show);
};

