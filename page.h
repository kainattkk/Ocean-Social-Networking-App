#pragma once
#include<SFML/Graphics.hpp>

class user;
class post;

class page
{
private:
	char* pageId;
	user* owner;
	char* title;
	int totalLikes;
protected:
	post** pHomePage;
	int totalPPosts;

public:
	page(const char*,const char*);
	page();
	void changeUser(user*);
	void setOwner(user*);
	char* getPageId();
	char* getPageTitle();
	char* getOwnerName();
	void addPostToHomePage(post*);
	void displayHomePage(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont);
	user* getOwner();
	void displayLikedPosts(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont,int,int,int,float,float);
	~page();
};