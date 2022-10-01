#include "book.h"

// Book constructor. Constructs a product with common member variables, then constructs a Book with isbn and author
Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
	Product(category, name, price, qty),
	isbn_(isbn),
	author_(author)
{

}

// Book destructor
Book::~Book()
{

}

// returns the keywords associated with this book
std::set<std::string> Book::keywords()
{
	// parses the author's name into strings of 2 or more characters at punctuation and adds them to the set.
	std::set<std::string> output = parseStringToWords(author_);
	// isbn is also added
	output.insert(isbn_);

	return output;
}

std::string Book::displayString()
{
	// outputs a string with correct formatting.
	std::string output = name_ + "\n";
	output += "Author: " + author_ + " ISBN: " + isbn_ + "\n";
	output += std::to_string(price_) + " " + std::to_string(qty_) + " left.";

	return output;
}

void Book::dump(std::ostream& os)
{
	// displays the book information in database format.
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}