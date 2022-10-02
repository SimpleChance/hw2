#include "clothing.h"

// Clothing constructor. Constructs a product with common member variables, then constructs a Clothing with size and brand
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{

}

// Clothing destructor
Clothing::~Clothing()
{

}

// returns the keywords associated with this article of clothing
std::set<std::string> Clothing::keywords() const
{
	// parses the author's name into strings of 2 or more characters at punctuation and adds them to the set.
	std::set<std::string> output = parseStringToWords(brand_);

	return output;
}

std::string Clothing::displayString() const
{
	// outputs a string with correct formatting.
	std::string output = name_ + "\n";
	output += "Size: " + size_ + " Brand: " + brand_ + "\n";
	output += std::to_string(price_) + " " + std::to_string(qty_) + " left.";

	return output;
}

void Clothing::dump(std::ostream& os)
{
	// displays the clothing information in database format.
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}