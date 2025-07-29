#pragma once
#include<string>

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class user;
class page;
class post;
class comment;
class memory;

class socialNetworkApp
{
private:
	//static arrays for file reading
	static user** users;
	static page** pages;
	static post** posts;
	static comment** rComments;
	static memory** memories;
	static int use;
	static int nPosts;
	static int nPages;
	static int nComments;
	static int nMemories;

public:

	//constructors and destructors
	~socialNetworkApp();
	static void deleteArrays();

	//functions
	static void loadData();
	static void run();
	static user* setCurrentUser(std::string,sf::Text&);
};
