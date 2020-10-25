#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef pair<int, int> duration_type;

template <typename T>
class Schedule {
public:
	typedef map<duration_type, T> schedule_type;
	typedef typename schedule_type::iterator schedule_it;
    typedef typename schedule_type::const_iterator schedule_const_it;

    Schedule(int start = 0, int end = 24);
    ~Schedule();

	vector<T> operator()(int start, int end);

    int size() const;

    bool isFree(int start, int end);

	void mergeSameContinuous();
    void insert(int start, int end, T item);
    bool remove(int start, int end);
    void remove(string name);

    T summarize(string name, int &total_time) const;

	void debug_print(int indent = 0) const;

private:
    int min_time;
    int max_time;
    schedule_type values;
};

template <typename T>
Schedule<T>::Schedule(int start, int end) {
	min_time = start;
	max_time = end;
}

template <typename T>
Schedule<T>::~Schedule() {
	values.clear();
}

template <typename T>
int Schedule<T>::size() const {
	/*
	 * get the size of values
	 * optional: size() will return size_t, to resolve the warning of implicit conversion, you may use static_cast to convert it to int
	 *
	 * Add your code here!
	 */
	return (int)values.size();
}

template <typename T>
vector<T> Schedule<T>::operator()(int start, int end) {
    /*
	 * return a vector of T objects whose durations are inside [start, end]
	 * you need to keep the order of the objects!
	 * if [start, end] is invalid, i.e. start >= end, return an empty vector: vector<T>() 
     * if there is no object inside [start, end], return an empty vector: vector<T>() 
	 *  
     * Add your code here!
     * */
//	cerr<<"bug1"<<endl;
	if(start>=end)return vector<T>();
	std::vector<T> find;
	for(schedule_const_it i = values.begin();
			i !=values.end();
			i++){
		if(std::get<0>(i->first)>=start
				&&std::get<1>(i->first)<=end){
			find.push_back(i->second);
//			cerr<<"count"<<endl;
		}
	}
	return find;
}

template <typename T>
bool Schedule<T>::isFree(int start, int end) {
	/*
	 * if start time is not smaller than end time, return false
	 * if start time is smaller than min_time, return false
	 * if end time is larger than max_time, return false
	 * if [start, end] has collision with any activity in schedule, return false
	 *     [1, 3] and [3, 4] have no collision
	 * otherwise (i.e. [start, end] doesn't have collision with any activity), return true
	 *
	 * Add your code here!
	 * */
	if(start>=end)return false;
	if(start<min_time || end>max_time)return false;
//	if(this->operator()(start,end)!=vector<T>())return false;//might have problem!
//	else return true;
	for(schedule_const_it i = values.begin();
			i !=values.end();
			i++){
		if((start<std::get<0>(i->first)
				&&end>std::get<0>(i->first))
			||(start<std::get<1>(i->first)
				&&end>std::get<1>(i->first))
			||(std::get<0>(i->first)<=start
				&&std::get<1>(i->first)>=end)){
			return false;
		}
	}
	return true;
}

template <typename T>
void Schedule<T>::mergeSameContinuous() {
	/*
	 * merge items with same name AND continuous durations
	 * more detailed instructions can be found on the website
	 *
	 * Add your code here!
	 */
	schedule_const_it i = values.begin();
	schedule_const_it j = values.begin();
	j++;
//	cerr<<"merge"<<endl;
	std::vector<duration_type> find_pair;
	for(;
			j !=values.end();
//			i++,j++
			){
//		cerr<<"i ";
//		cerr<<std::get<0>(i->first)<<" "<<std::get<1>(i->first)<<endl;
//		cerr<<"j ";
//		cerr<<std::get<0>(j->first)<<" "<<std::get<1>(j->first)<<endl;
		if(std::get<1>(i->first)==std::get<0>(j->first)
				&&(i->second.getName().compare(j->second.getName()))==0){
			std::pair<int,int>temp(std::get<0>(i->first),std::get<1>(j->first));
//			cerr<<std::get<0>(temp)<<" "<<std::get<1>(temp)<<endl;
			T *tempT = new T;
			*tempT = i->second;
			*tempT += j->second;
			values.erase(j);
			values.insert(std::pair<duration_type,T>(temp,*tempT));
			values.erase(i);
			i = values.begin();
			j = values.begin();
			j++;
		}
		else {i++;j++;}
	}
//	cerr<<"end?"<<endl;
}

template <typename T>
void Schedule<T>::insert(int start, int end, T item) {
	/*
	 * first add item to values if [start, end] is free, then merge adjacent items with same name (std::map is sorted by default)
	 *
	 * Add your code here!
	 * */
//	std::pair<int,int>temp(start,end);
//	const duration_type *temp = new duration_type(start,end);
	duration_type temp;
	temp.first = start;
	temp.second = end;
//	values.insert(temp,item);
	values.insert(std::pair<duration_type,T>(temp,item));
	this->mergeSameContinuous();
}

template <typename T>
bool Schedule<T>::remove(int start, int end) {
    /*
     * Remove items which are inside [start, end]
	 * return false if the input start >= end, otherwise return true
	 * 
     * Add your code here!
     * */
	if(start>=end)return false;
//	std::vector<T> find= this->operator ()(start,end);
//	if(find.begin()==find.end())return false;
	std::vector<duration_type> find_pair;
	for(schedule_const_it i = values.begin();
			i !=values.end();
			i++){
//		cerr<<i->second.getName()<<endl;
		if(std::get<0>(i->first)>=start
				&&std::get<1>(i->first)<=end){
////			find.push_back(i->second);
//			values.erase(i);
			find_pair.push_back(i->first);
//			cerr<<find_pair.back().first<<" "<<find_pair.back().second<<endl;
		}
	}
	while(!find_pair.empty()){
		values.erase(find_pair.back());
		find_pair.pop_back();
	}
	return true;
}

template <typename T>
void Schedule<T>::remove(string name) {
	/*
	 * Remove items whose names are the same as the input name
	 *
	 * Add your code here!
	 * */
//	cout<<"call function"<<endl;
	std::vector<duration_type> find_pair;
	for(schedule_const_it i = values.begin();
			i !=values.end();
			i++){
//		cout<<i->second.getName()<<endl;
		if(name.compare(i->second.getName())==0){
//			cout<<"remove "<<i->second.getName()<<endl;
			find_pair.push_back(i->first);
		}
	}
	while(!find_pair.empty()){
		values.erase(find_pair.back());
		find_pair.pop_back();
	}
}

template <typename T>
T Schedule<T>::summarize(string name, int &total_time) const {
	/*
     * If items A, B, D, F in schedule have the same name
     *   1. Calculate the total time of A, B, D, F by summing their durations 
	 *       (duration_of_an_item = end_time - start_time). And assign the result to total_time
     *   2. Return a new item which is calculated by A + B + D + F.
     * If there is no item with name, return an initialized object (its variables do not matter) and keep total_time as 0.
	 *
	 * You might init a new T object and use operator += to sum selected objects
	 *
	 * Add your code here!
	 * */
	T *newobj = new T;
	for(schedule_const_it i = values.begin();
			i !=values.end();
			i++){
		if(name.compare(i->second.getName())==0){
			*newobj+=i->second;
			total_time+=(std::get<1>(i->first)-std::get<0>(i->first));
		}
	}
	return *newobj;
}

template<typename T>
void Schedule<T>::debug_print(int indent) const {
    string indent1 = string(indent, '\t');

    for (schedule_const_it cit = values.begin(); cit != values.end(); ++cit) {
		cout << indent1 << "duration [" << cit->first.first << ", " << cit->first.second << "]:" << endl;
		cit->second.debug_print(indent + 1);
	}
}

#endif //SCHEDULE_H
