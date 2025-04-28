#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <thread>

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
                            cout << "Booking failed.\n";
                            return;
                        }
                    }
                }
            }
        }
        cout << "Booking failed.\n";
    }
};

class PaymentSystem {
public:
    static void processPayment() {
        cout << "\nChoose Payment Method:\n";
        cout << "1. Cash\n";
        cout << "2. Credit Card\n";
        cout << "Enter option (1 or 2): ";
        int option;
        cin >> option;

        switch (option) {
        case 1:
            cout << "Payment successful by Cash.\n";
            break;
        case 2:
            cout << "Processing Credit Card payment...\n";
            cout << "Payment successful by Card.\n";
            break;
        default:
            cout << "Invalid payment option.\n";
            break;
        }
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

    cout << "\nWelcome to the Booking System!\n";
    cinema.displayMovies();

    string movieTitle;
    cout << "\nEnter the movie you want to watch: ";
    getline(cin >> ws, movieTitle);

    system.searchMovie(movieTitle);

    int showId;
    cout << "Enter the show ID you want to attend (e.g., 1 or 2): ";
    cin >> showId;

    int seatNumber;
    cout << "Enter the seat number you want to book: ";
    cin >> seatNumber;

    string confirmation;
    cout << "\nConfirm booking within 15 seconds (Y/N): ";

    auto start = chrono::steady_clock::now();
    bool inputReceived = false;

    thread inputThread([&]() {
        getline(cin >> ws, confirmation);
        inputReceived = true;
        });

    while (!inputReceived) {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
        if (elapsed > 15) {
            cout << "\nTime exceeded! Booking cancelled.\n";
            inputThread.detach();
            return 0;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    inputThread.join();

    if (confirmation == "Y" || confirmation == "y") {
        system.bookSeat("Dream Cinemas", movieTitle, showId, seatNumber);
        PaymentSystem::processPayment();

        cout << "\nFinal Seat Status:\n";
        cinema.movies[movieTitle].shows[showId - 1].displaySeats();
    }
    else {
        cout << "\nBooking cancelled by user.\n";
    }

    return 0;
}

