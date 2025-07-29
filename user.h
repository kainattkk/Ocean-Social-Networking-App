#pragma once
#include<SFML/Graphics.hpp>

class page;
class post;

class user
{
private:
	char* uId;
	char* name;
	user** friends;
	page** likedPages;
protected:
	post** uHomePage;
	int totalUPosts;
	int totalFriends;
	int totalLikedPages;
public:
	user();
	user( const char*,const  char*);
	void setUserIdAndName(const char*, const char*);
	void addFriend(user*);
	void addLikedPage(page*);
	void printFriends(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont);
	void printLikedPages(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont);
	char* getName();
	char* getUId();
	user(user&);
	void addPostToUHomePage(post*);
	void displayUHomePage(sf::RenderWindow& window, sf::Font& font,sf::Font& tFont,sf::Sprite&);
	void displayTimeLine(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont);
	void displayFriendPosts(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont, int, int, int,float);
	~user();
	int getTotalUPosts();
};

