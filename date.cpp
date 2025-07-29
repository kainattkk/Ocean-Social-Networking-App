#include"date.h"
#include<iostream>
using namespace std;

date::date()
{
	day = 0;
	month = 0;
	year = 0;
}

date::date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

void date::printDate()
{
	cout << day << "/" << month << "/" << year;
}

void date::setDate(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

int date::getDay()
{
	return day;
}
int date::getMonth()
{
	return month;
}
int date::getYear()
{
	return year;
}
date::~date()
{
	cout << "date destructor called" << endl;
}

std::string date::toString() {
	return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}