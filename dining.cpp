#include "dining.h"

Dining::Dining() :
	name(""), fat(0), energy(0), price(0) {}

Dining::Dining(string name_, int fat_, int energy_, int price_) :
    name(name_), fat(max(0, fat_)), energy(max(0, energy_)), price(max(0, price_)) {}

string Dining::getName() const {
    return name;
}

int Dining::getFat() const {
    return fat;
}

int Dining::getEnergy() const {
    return energy;
}

int Dining::getPrice() const {
    return price;
}

void Dining::debug_print(int indent) const {
    string indent1 = string(indent, '\t');
    string indent2 = string(indent+1, '\t');

    cout << indent1 << "Dining:" << endl
         << indent2 << "name:" << name << endl
         << indent2 << "fat:" << fat << endl
         << indent2 << "energy:" << energy << endl
         << indent2 << "price:" << price << endl;
}

Dining Dining::operator+(const Dining& dining) {
    /*
     * dining1 + dining2
	 *
	 * add all other attributes (fat, energy, price)
	 *
     * if names of dining1, dining2 are different, set the name as dining1.name + dining2.name
     * otherwise, do not modify the name
     *
     * Add your code here
     * */
	Dining *new_dining = new Dining(*this);
	new_dining->fat+=dining.getFat();
	new_dining->energy+=dining.getEnergy();
	new_dining->price+=dining.getPrice();
	if(new_dining->name.empty())new_dining->name.append(dining.getName());
	else if(new_dining->name.compare(dining.getName())!=0){new_dining->name.append(dining.getName());}
	return *new_dining;
}

Dining& Dining::operator+=(const Dining& dining) {
	/*
	 * dining1 += dining2
	 *
	 * add all other attributes (fat, energy, price)
	 *
	 * if names of dining1, dining2 are different, set the name as dining1.name + dining2.name
	 * otherwise, do not modify the name
	 *
	 * Add your code here
	 * */
	*this = *this + dining;
//	this->fat+=dining.getFat();
//	this->energy+=dining.getEnergy();
//	this->price+=dining.getPrice();
//	if(this->name.compare(dining.getName())!=0){/*this->name.append("+");*/this->name.append(dining.getName());}
	return *this;
}

Dining& Dining::operator=(const Dining& dining) {
	/*
	 * Assign the input dining to this
	 *
	 * Add your code here!
	 */
	this->fat=dining.getFat();
	this->energy=dining.getEnergy();
	this->price=dining.getPrice();
	this->name=dining.getName();
	return *this;
}
