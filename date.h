#include<string>
#pragma once
class date 
{
private:
	int day;
	int month;
	int year;
public:
	date();
	date(int, int, int);
	void printDate();
	void setDate(int,int,int);
	int getDay();
	int getMonth();
	int getYear();
	~date();
	std::string toString();
};