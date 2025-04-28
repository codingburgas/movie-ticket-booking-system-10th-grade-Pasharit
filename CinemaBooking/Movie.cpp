#include "Movie.h"

Movie::Movie(const std::string& t, const std::string& lang, const std::string& gen, const std::string& date)
    : title(t), language(lang), genre(gen), releaseDate(date) {
}

void Movie::addShow(Show show) {
    shows.push_back(show);
}
