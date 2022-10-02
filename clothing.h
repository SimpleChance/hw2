#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product{ //Clothing is a public Product
	public:
		// Virtual functions from product base class must be redefined for derived class.
		Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
		~Clothing();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os);

	private:
		// member variables that pertain to ONLY clothing.
		std::string size_;
		std::string brand_;
};
#endif