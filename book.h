#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product{ //Book is a public Product
	public:
		// Virtual functions from product base class must be redefined for derived class.
		Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
		~Book();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os);

	private:
		// member variables that pertain to ONLY books.
		std::string isbn_;
		std::string author_;
};
#endif