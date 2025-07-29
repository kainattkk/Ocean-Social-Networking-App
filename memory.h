#pragma once
#include<SFML/Graphics.hpp>

#include"post.h"
class user;
class memory:public post
{
private:
    char* postText;
	int difference;
public:
	memory(char*,char*, char*,int);
    char* getMtext();
	void printMemory();
	void setDifference(int);
	int getDifference();
	~memory();
	void printMemory(sf::RenderWindow& window, sf::Font& font, float posX, float posY);
};