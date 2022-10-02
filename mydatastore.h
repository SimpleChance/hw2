#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"

class MyDataStore : public DataStore {
	public:
		// Constructor
		MyDataStore();
		// add a product
		void addProduct(Product* prod);
		// add a user
		void addUser(User* user);
		// search keywords with an AND or OR argument
		std::vector<Product*> search(std::vector<std::string>& keys, int type);
		// recreates the database file from the current products and users
		void dump(std::ostream& ofile);
		// adds a searched product to the cart
		void addCart(std::string u, std::string hstring, std::vector<Product*> hits);
		// displays the cart
		void viewCart(std::string u);
		// buy itmes in the cart (if balance allows)
		void buyCart(std::string u);

	private:
		// vector of product objects
		std::vector<Product*> products_;
		// map of names and user objects
		std::map<std::string, User*> users_;
		// map of users and their vector of products
		std::map<User*, std::vector<Product*>> cart_;
		// map of sets of products
		std::map<std::string, std::set<Product*>> pMap;
};
#endif