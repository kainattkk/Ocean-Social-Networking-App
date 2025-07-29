#include"activity.h"
#include"helper.h"
#include<iostream>
using namespace std;

activity::activity()
{
	type = 0;
	value = nullptr;
}
activity::~activity()
{
	cout << "activity destructor called" << endl;
	if (value != nullptr)
	{
		delete[] value;
		value = nullptr;
	}
}

activity::activity(int t, char* v)
{
	type = t;
	int length = 0;
	length = helper::GetLength(v);
	this->value = new char[length + 1];
	helper::copyString(value, v, length);
}
void activity::setActivity(int t, char* v)
{
	type = t;
	int length = 0;
	length = helper::GetLength(v);
	if (value != nullptr)
	{
		delete[] value;
	}
	this->value = new char[length + 1];
	helper::copyString(value, v, length);
}

void activity::displayActivity()
{
	if (type == 1)
	{
		cout << "feeling " << value << endl;
	}
	else if (type == 2)
	{
		cout << "thinking about " << value << endl;
	}
	else if (type == 3)
	{
		cout << "making " << value << endl;
	}
	else if (type == 4)
	{
		cout << "celebrating " << value << endl;
	}
}
std::string activity::getValue()
{
	if (value != nullptr)
	{
		if (type == 1)
		{
			std::string re = "feeling " + std::string(value);
			return re;
		}
		else if (type == 2)
		{
			std::string re = "thinking about " + std::string(value);
			return re;
		}
		else if (type == 3)
		{
			std::string re = "making " + std::string(value);
			return re;
		}
		else if (type == 4)
		{
			std::string re = "celebrating " + std::string(value);
			return re;
		}
	}
	else return "";
}

std::string activity::getNoTypeValue()
{
	if (value != nullptr)
	{
		if (type == 1)
		{
			std::string re = std::string(value);
			return re;
		}
		else if (type == 2)
		{
			std::string re = std::string(value);
			return re;
		}
		else if (type == 3)
		{
			std::string re = std::string(value);
			return re;
		}
		else if (type == 4)
		{
			std::string re = std::string(value);
			return re;
		}
	}
	else return "";
}

int activity::getType()
{
	return type;
}

