#include "movie.h"

// Movie constructor. Constructs a product with common member variables, then constructs a Movie with genre and rating
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)
{

}

// Movie destructor
Movie::~Movie()
{

}

// returns the keywords associated with this movie
std::set<std::string> Movie::keywords() const
{
	// parses the movie's genre into strings of 2 or more characters at punctuation and adds them to the set.
	std::set<std::string> output = parseStringToWords(genre_);

	return output;
}

std::string Movie::displayString() const
{
	// outputs a string with correct formatting.
	std::string output = name_ + "\n";
	output += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
	output += std::to_string(price_) + " " + std::to_string(qty_) + " left.";

	return output;
}

void Movie::dump(std::ostream& os)
{
	// displays the movie information in database format.
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}