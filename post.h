#pragma once
#include"activity.h"
#include"date.h"
#include<SFML/Graphics.hpp>

class user;
class comment;
class page;

class post
{
private:
	char* postId;
	char* description;
	int numOfULikes;
	int numOfPLikes;
	int numOfLikes;
	activity* activities;
	user** likedByPeeps;
	page** likedByPages;
	date* sharedDate;
	date* newDate;
	user* postOwner;
	page* postPage;
protected:
	comment** comments;
	int totalComments;
public:
	post();
	post(char*, char*);
	char* getPostId();
	char* getPostText();
	void addULike(user*,sf::Text&);
	void addPLike(page*);
	void peopleWhoLiked();
	void pagesWhoLiked();
	void addedLikes(sf::RenderWindow& window, sf::Font& font,sf:: Font& tFont);
	void setSharedDate(int, int, int);
	void displaySharedDate();
	date* getSharedDate();
	void addComment(comment*);
	void displayComments();
	void setPostOwner(user*);
	void setPostPage(page*);
	user* getPostOwner();
	page* getPostPage();
	void setActivities(int ,char*);
	activity* getActivities();
	void printActivities();
	comment** getComments();
	void viewPost(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont);
	void addRuntimeComment(user*,char*,sf::Text&);
	virtual void printMemory(sf::RenderWindow& window, sf::Font& font, float posX, float posY);
	void setNewDate(int, int, int);
	date* getNewDate();
	~post();
	std::string getSharedDateAsString();
	void displayComment(sf::RenderWindow& window, sf::Font& font,float posX, float posY);
	int getTotalComments();
	void setComments(comment**);
};

