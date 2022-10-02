#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : public Product{ //Movie is a public Product
	public:
		// Virtual functions from product base class must be redefined for derived class.
		Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
		~Movie();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os);

	private:
		// member variables that pertain to ONLY movies.
		std::string genre_;
		std::string rating_;
};
#endif