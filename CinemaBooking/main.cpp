#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


enum SeatType { SILVER, GOLD, PLATINUM };


struct Seat {
    int seatNumber;
    bool isBooked;
    SeatType type;

    Seat(int number, SeatType seatType) : seatNumber(number), isBooked(false), type(seatType) {}
};


struct Show {
    int showId;
    string movieTitle;
    vector<Seat> seats;

    Show(int id, const string& title, int totalSeats) : showId(id), movieTitle(title) {
        for (int i = 1; i <= totalSeats; ++i) {
            SeatType type = (i <= 5) ? PLATINUM : (i <= 10) ? GOLD : SILVER;
            seats.emplace_back(i, type);
        }
    }

    void displaySeats() {
        cout << "Seats for show: " << movieTitle << "\n";
        for (auto& seat : seats) {
            cout << "Seat " << seat.seatNumber << " ["
                << (seat.type == PLATINUM ? "Platinum" : seat.type == GOLD ? "Gold" : "Silver")
                << "] - "
                << (seat.isBooked ? "Booked" : "Available") << "\n";
        }
    }

    bool bookSeat(int seatNum) {
        if (seatNum < 1 || seatNum > seats.size()) {
            cout << "Invalid seat number.\n";
            return false;
        }
        if (seats[seatNum - 1].isBooked) {
            cout << "Seat already booked.\n";
            return false;
        }
        seats[seatNum - 1].isBooked = true;
        return true;
    }
};


struct Movie {
    string title;
    string language;
    string genre;
    string releaseDate;
    vector<Show> shows;

    Movie(const string& t, const string& lang, const string& gen, const string& date)
        : title(t), language(lang), genre(gen), releaseDate(date) {
    }

    void addShow(Show show) {
        shows.push_back(show);
    }
};


struct Cinema {
    string name;
    map<string, Movie> movies;

    Cinema(const string& cinemaName) : name(cinemaName) {}

    void addMovie(const Movie& movie) {
        movies[movie.title] = movie;
    }

    void displayMovies() {
        cout << "Movies in " << name << ":\n";
        for (auto& pair : movies) {
            cout << "- " << pair.second.title << " (" << pair.second.genre << ", " << pair.second.language << ")\n";
        }
    }
};

// Booking System
class BookingSystem {
private:
    vector<Cinema> cinemas;

public:
    void addCinema(const Cinema& cinema) {
        cinemas.push_back(cinema);
    }

    void searchMovie(const string& title) {
        for (auto& cinema : cinemas) {
            if (cinema.movies.find(title) != cinema.movies.end()) {
                cout << "Found movie: " << title << " in cinema: " << cinema.name << "\n";
                return;
            }
        }
        cout << "Movie not found.\n";
    }

    void bookSeat(const string& cinemaName, const string& movieTitle, int showId, int seatNumber) {
        for (auto& cinema : cinemas) {
            if (cinema.name == cinemaName) {
                auto& movie = cinema.movies[movieTitle];
                for (auto& show : movie.shows) {
                    if (show.showId == showId) {
                        if (show.bookSeat(seatNumber)) {
                            cout << "Seat " << seatNumber << " booked successfully for movie: " << movieTitle << "\n";
                            return;
                        }
                        else {
                            return;
                        }
                    }
                }
            }
        }
        cout << "Booking failed.\n";
    }
};

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

    
    string cinemaName, movieTitle;
    int showId, seatNumber;

    cout << "Enter Cinema name: ";
    cin >> cinemaName;

    cout << "Enter Movie title: ";
    cin >> movieTitle;

    cout << "Enter Show ID: ";
    cin >> showId;

    cout << "Enter Seat number: ";
    cin >> seatNumber;

    system.bookSeat(cinemaName, movieTitle, showId, seatNumber);
    cinema.movies["Inception"].shows[0].displaySeats();

    return 0;
}
