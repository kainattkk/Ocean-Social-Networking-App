#include"page.h"
#include"helper.h"
#include"post.h"
#include"user.h"
#include"comment.h"
#include<iostream>
using namespace std;

page::page()
{
        pageId = nullptr;
        owner = nullptr;
        title = nullptr;
        pHomePage = nullptr;
        totalLikes = 0;
        totalPPosts = 0;   
}
page::page(const char* ids,const char* name)
{
    int length = 0;
    length = helper::GetLength(ids);
    this->pageId = new char[length + 1];
    helper::copyString(pageId, ids, length);
    length = 0;
    length = helper::GetLength(name);
    this->title = new char[length + 1];
    helper::copyString(title, name, length);
    totalLikes = 0;
    pHomePage = nullptr;
    owner = nullptr;
    totalPPosts = 0;
}
page::~page()
{
    cout << "page destructor called" << endl;
    if (pageId != nullptr)
    {
        delete[] pageId;
        pageId = nullptr;
    }
    if (title != nullptr)
    {
        delete[] title;
        title = nullptr;
    }
    if (pHomePage != nullptr)
    {
        for (int i = 0; i < totalPPosts; i++)
        {
            pHomePage[i] = nullptr;
        }
        delete[] pHomePage;
        pHomePage = nullptr;
    }
    if (owner != nullptr)
    {
        owner = nullptr;
    }
}
void  page::setOwner(user* obj)
{
    owner = obj;
}

void page::changeUser(user* obj)
{
    setOwner(obj);
}

char* page::getPageId()
{
    if (this!=nullptr)
        return pageId;
    else
        return nullptr;
}
char* page::getPageTitle()
{
    return title;
}

char* page::getOwnerName()
{
    return owner->getUId();
}

void page::addPostToHomePage(post* obj)
{
    if (pHomePage == nullptr)
    {
        pHomePage = new post * [1];
        pHomePage[0] = obj;
        totalPPosts++;
    }
    else {
        post** temp = new post * [totalPPosts];
        for (int i = 0; i < totalPPosts; i++)
        {
            temp[i] = pHomePage[i];
        }
        for (int i = 0; i < totalPPosts; i++)
        {
            pHomePage[i] = nullptr;
        }
        delete[] pHomePage;
        totalPPosts++;
        pHomePage = new post * [totalPPosts];
        for (int i = 0; i < totalPPosts - 1; i++)
        {
            pHomePage[i] = temp[i];
        }
        pHomePage[totalPPosts - 1] = obj;
        for (int i = 0; i < totalPPosts - 1; i++)
        {
            temp[i] = nullptr;
        }
        delete[] temp;
    }
}
user* page:: getOwner()
{
    return owner;
}

void page::displayHomePage(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont)
{
    // Display page title and home page title
    std::string pageTitle = this->getPageTitle();
    sf::Text pageTitleText;
    pageTitleText.setFont(tFont);
    pageTitleText.setString(pageTitle + "-Home Page:");
    pageTitleText.setCharacterSize(60);
    pageTitleText.setFillColor(sf::Color(51, 77, 77, 255));
    pageTitleText.setPosition(300.f, 70.f);
    window.draw(pageTitleText);

    // Iterate through each post on the home page
    for (int i = 0; i < totalPPosts; i++)
    {
        // Render user activities if available
        if (pHomePage[i]->getActivities()->getValue() != "")
        {
            std::string activitiesString = std::string(this->getPageTitle()) + " is " + pHomePage[i]->getActivities()->getValue();
            sf::Text activitiesText;
            activitiesText.setFont(font);
            activitiesText.setOutlineThickness(0.3f);
            activitiesText.setString(activitiesString);
            activitiesText.setCharacterSize(20);
            activitiesText.setFillColor(sf::Color::Black);
            activitiesText.setPosition(10.f, 150.f + i * 200.f); // Adjust position as needed
            window.draw(activitiesText);
        }

        // Render post text
        std::string postTextString = "\"" + std::string(pHomePage[i]->getPostText()) + "\"";
        sf::Text postText;
        postText.setFont(font);
        postText.setString(postTextString);
        postText.setCharacterSize(20);
        postText.setFillColor(sf::Color::Black);
        postText.setPosition(10.f, 180.f + i * 200.f); // Adjust position as needed
        window.draw(postText);

        // Render shared date
        sf::Text sharedDateText;
        sharedDateText.setFont(font);
        sharedDateText.setString("(" + pHomePage[i]->getSharedDateAsString() + ")");
        sharedDateText.setCharacterSize(15);
        sharedDateText.setFillColor(sf::Color::Black);
        sharedDateText.setPosition(10.f, 210.f + i * 200.f); // Adjust position as needed
        window.draw(sharedDateText);

        // Render comments
        pHomePage[i]->displayComment(window, font, 10.f, 240.f + i * 200.f);
    }
}

void page::displayLikedPosts(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont, int d, int m, int y, float xOffset, float yOffset)
{
    float postY = yOffset; // Initial Y-coordinate for the posts

    for (int i = 0; i < totalPPosts; i++)
    {
        if (pHomePage[i]->getSharedDate()->getMonth() == m && pHomePage[i]->getSharedDate()->getYear() == y)
        {
            if (pHomePage[i]->getSharedDate()->getDay() == d || pHomePage[i]->getSharedDate()->getDay() == d - 1)
            {
                std::string postString;

                // Construct the post string
                if (pHomePage[i]->getActivities()->getValue() != "")
                {
                    std::string act = pHomePage[i]->getActivities()->getValue();
                    sf::Text activitiesText;
                    activitiesText.setFont(font);
                    activitiesText.setOutlineThickness(0.3f);
                    activitiesText.setString(std::string(this->getPageTitle()) + " is " + act);
                    activitiesText.setCharacterSize(20);
                    activitiesText.setFillColor(sf::Color::Black);
                    activitiesText.setPosition(xOffset, postY); // Adjust position as needed
                    window.draw(activitiesText);
                }
                else
                {
                    sf::Text activitiesText;
                    activitiesText.setFont(font);
                    activitiesText.setOutlineThickness(0.3f);
                    activitiesText.setString(std::string(this->getPageTitle()) + " shared: ");
                    activitiesText.setCharacterSize(20);
                    activitiesText.setFillColor(sf::Color::Black);
                    activitiesText.setPosition(xOffset, postY); // Adjust position as needed
                    window.draw(activitiesText);
                }
                postString = "\"" + std::string(pHomePage[i]->getPostText()) + "\"";

                // Render the post string using SFML
                sf::Text postText;
                postText.setFont(font);
                postText.setString(postString);
                postText.setCharacterSize(20);
                postText.setFillColor(sf::Color::Black);
                postText.setPosition(xOffset, postY+30); // Set the position
                window.draw(postText);

                sf::Text sharedDateText;
                sharedDateText.setFont(font);
                sharedDateText.setString("(" + pHomePage[i]->getSharedDateAsString() + ")");
                sharedDateText.setCharacterSize(15);
                sharedDateText.setFillColor(sf::Color::Black);
                sharedDateText.setPosition(xOffset, postY + 60.f); // Adjust position as needed
                window.draw(sharedDateText);

                // Update the vertical offset for the comments
                float commentY = postY + postText.getLocalBounds().height + 10.f;

                // Display comments
                pHomePage[i]->displayComment(window, font, xOffset, postY+90);

                // Update the vertical offset for the next post
                postY += 195;
            }
        }
    }
}
