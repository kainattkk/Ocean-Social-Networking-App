#pragma once
#include<string>

class activity
{
private:
	int type;
	char* value;
public:
	activity();
	~activity();
	activity(int, char*);
	void displayActivity();
	void setActivity(int, char*);
	std::string getValue();
	int getType();	
	std::string getNoTypeValue();
};