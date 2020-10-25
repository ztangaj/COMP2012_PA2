#include "workout.h"

Workout::Workout() :
	name(""), fat_change(0), muscle_change(0), energy_change(0) {}

Workout::Workout(string name_, int fat_change_, int muscle_change_, int energy_change_) :
    name(name_), fat_change(fat_change_), muscle_change(muscle_change_), energy_change(energy_change_) {}

string Workout::getName() const {
    return name;
}

int Workout::getFatChange() const {
    return fat_change;
}

int Workout::getMuscleChange() const {
    return muscle_change;
}

int Workout::getEnergyChange() const {
    return energy_change;
}

void Workout::debug_print(int indent) const {
    string indent1 = string(indent, '\t');
    string indent2 = string(indent+1, '\t');

	cout << indent1 << "Workout:" << endl
	    << indent2 << "name:" << name << endl
		<< indent2 << "fat_change:" << fat_change << endl
		<< indent2 << "muscle_change:" << muscle_change << endl
		<< indent2 << "energy_change:" << energy_change << endl;
}

Workout Workout::operator+(const Workout& workout) {
	/*
	 * workout1 + workout2
	 *
	 * add all other attributes (fat_change, muscle_change, energy_change)
	 *
	 * if name of workout1 is different from name of workout2, set the name as workout1.name + workout2.name
	 * otherwise, do not modify the name
	 *
	 * Add your code here
	 * */
//	cout<<"operator+"<<endl;
	Workout* new_workout = new Workout(*this);
	new_workout->fat_change+=workout.getFatChange();
	new_workout->muscle_change+=workout.getMuscleChange();
	new_workout->energy_change+=workout.getEnergyChange();
	if(new_workout->name.empty())new_workout->name.append(workout.getName());
	else if(new_workout->name.compare(workout.getName())!=0){new_workout->name.append(workout.getName());}
	return *new_workout;
}

Workout& Workout::operator+=(const Workout& workout) {
    /*
     * workout1 += workout2
	 *
	 * add all other attributes (fat_change, muscle_change, energy_change)
	 *
	 * if name of workout1 is different from name of workout2, set the name as workout1.name + workout2.name
	 * otherwise, do not modify the name
	 *
	 * Add your code here
     * */
//	cout<<"operator+="<<endl;
	*this = *this + workout;
//	this->fat_change+=workout.getFatChange();
//	this->muscle_change+=workout.getMuscleChange();
//	this->energy_change+=workout.getEnergyChange();
//	if(this->name.compare(workout.getName())!=0){/*this->name.append("+");*/this->name.append(workout.getName());}
	return *this;
}

Workout& Workout::operator=(const Workout& workout) {
	/*
	 * Assign the input workout to this
	 *
	 * Add your code here!
	 */
	this->fat_change=workout.getFatChange();
	this->muscle_change=workout.getMuscleChange();
	this->energy_change=workout.getEnergyChange();
	this->name=workout.getName();
	return *this;
}
