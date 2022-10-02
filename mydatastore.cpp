#include "mydatastore.h"

MyDataStore::MyDataStore() : DataStore()
{

}


void MyDataStore::addProduct(Product* p) {
	// creates a set of keywords associated with a product
	std::set<std::string> kSet = p->keywords();
	// iterator to iterate through the sets
	std::set<std::string>::iterator it;

	products_.push_back(p); // track product in the products vector

	for(it = kSet.begin(); it != kSet.end(); ++it) {
		if(pMap.find(*it) == pMap.end()) { // no keyword found
			std::set<Product*> pSet; // new set to add
			pSet.insert(p);
			pMap.insert(std::make_pair(*it, pSet)); // inserts pSet into the map of products
		}

		else { // keyword found, insert product
			pMap[*it].insert(p);
		}
	}
}

// adds a user
void MyDataStore::addUser(User* u) {
	// vector of user's products
	std::vector<Product*> uProducts;
	// add user and product vector to cart_ map
	cart_.insert(std::make_pair(u, uProducts));
	// add the user and their name to the users_ map
	users_.insert(std::make_pair(u->getName(), u));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& keys, int type) {
	// new product vector, product set, and key set
	std::vector<Product*> pVector;
	std::set<Product*> pSet;
	std::set<Product*> kSet;

	//add a product to pSet for each key
	for(unsigned int i = 0; i < keys.size(); i++) {
		//AND
		if(type == 0) {
			//Initalize tSet
			kSet = pMap[keys[0]];
			pSet = pMap[keys[i]];
			kSet = setIntersection(kSet, pSet);
		}
		//OR
		else if(type == 1) { 
			pSet = pMap[keys[i]];
			kSet = setUnion(kSet, pSet);
		}
	}

	std::set<Product*>::iterator it;
	// add each product to the pVector
	for(it = kSet.begin(); it != kSet.end(); ++it) {
		pVector.push_back(*it);
	}

	return pVector;
}


//Reproduce the database file from the current Products and User values
void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << std::endl;

	for(unsigned int i = 0; i < products_.size(); i++) {
    (products_[i])->dump(ofile);
  }
	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;
	for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    ((it)->second)->dump(ofile);
  }
	ofile << "</users>" << std::endl;
}

// add a hit to the users cart
void MyDataStore::addCart(std::string u, std::string hString, std::vector<Product*> hits) {
	//If hits is empty, don't do anything
	if(hits.empty()) {
		std::cout << "No products available. Try searching for a product!" << std::endl;
		return;
	}

	//convert hString to integer
	unsigned int hNum = stoi(hString); 
	User* user;

	//check for too large of a hNum
	if(hNum > hits.size()) {
		std::cout << "Invalid hit number!" << std::endl;
		return;
	}

	//check for existing user
	if(users_.find(u) == users_.end()) {
		std::cout << "Error. User does not exist" << std::endl;
		return;
	}

	// add to user cart
	else {
		user = users_.find(u)->second;
		cart_[user].push_back(hits[hNum - 1]);
		return;
	}
}

//view the user's cart
void MyDataStore::viewCart(std::string u) {
	// gets all the information from a speicific user's cart
	User* user;
	user = users_.find(u)->second;
	std::vector<Product*> items = (cart_[user]);

	//check for an empty cart
	if (items.begin() == items.end()) {
		std::cout << "Cart is empty!" << std::endl;
    return;
	}

	//if not empty, contents of the cart are displayed
	for(std::vector<Product*>::iterator it = items.begin(); it != items.end(); ++it) {
    std::cout << (*it)->displayString() << std::endl;
    std::cout << std::endl;
  }
}

void MyDataStore::buyCart(std::string u) {

	// get the user's cart
	User* user;
	user = users_.find(u)->second;
	std::vector<Product*> items = (cart_[user]);

	//check for an epmty cart
	if (items.begin() == items.end()) { 
		std::cout << "Cart is empty!" << std::endl;
    return;
	}

	// vector to keep track of items the user could not afford
	std::vector<Product*> itemsLeft;

	for(std::vector<Product*>::iterator it = items.begin(); it != items.end(); ++it) {
		//check for insufficient funds
    if((*it)->getPrice() > user->getBalance()) {
			std::cout << user->getName() << " doesn't have enough money for: " << (*it)->getName() << " (" << (*it)->getPrice() << ")" << std::endl;
			itemsLeft.push_back(*it);
		}

		//check for qty in stock
		else if((*it)->getQty() == 0) {
			std::cout << "Currently out of stock: " << (*it)->getName() << std::endl;
		}

		else {
			user->deductAmount((*it)->getPrice());
			(*it)->subtractQty(1);
			std::cout << user->getName() << " has $" << user->getBalance() << " left." << std::endl;
		}
  }

	cart_[user] = itemsLeft;
	return;


}