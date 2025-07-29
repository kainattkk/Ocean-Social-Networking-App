
#include"user.h"
#include"helper.h"
#include"page.h"
#include"comment.h"
#include"post.h"
#include"socialNetworkApp.h"
using namespace std;
#include<iostream>
#include<sstream>

user::user( const char* ids, const char* names)
{
    int length = 0;
    length = helper::GetLength(ids);
    this->uId = new char[length + 1];
    helper::copyString(uId, ids, length);
    length = 0;
    length = helper::GetLength(names);
    this->name = new char[length + 1];
    helper::copyString(name, names, length);
    friends = nullptr;
    likedPages = nullptr;
    totalFriends = 0;
    totalLikedPages = 0;
    uHomePage = nullptr;
    totalUPosts = 0;
}

user::user()
{
    uId = nullptr;
    name = nullptr;
    friends = nullptr;
    likedPages = nullptr;
    totalFriends = 0;
    totalLikedPages = 0;
    uHomePage = nullptr;
    totalUPosts = 0;
}
user::~user()
{
    cout << "user destructor called" << endl;
    if (uId != nullptr)
    {
        delete[]uId;
        uId = nullptr;
    }
    if (name != nullptr)
    {
        delete[]name;
        name = nullptr;
    }
    if (friends != nullptr)
    {
        for (int i = 0; i < totalFriends; i++)
        {
            friends[i] = nullptr;
        }
        delete[] friends;
        friends = nullptr;
    }
    if (likedPages != nullptr)
    {
        for (int i = 0; i < totalLikedPages; i++)
        {
            likedPages[i] = nullptr;
        }
        delete[] likedPages;
        likedPages = nullptr;
    }
    if (uHomePage != nullptr)
    {
        for (int i = 0; i < totalUPosts; i++)
        {
            uHomePage[i] = nullptr;
        }
        delete[] uHomePage;
        uHomePage = nullptr;
    }
}

char* user::getName()
{
    if(name!=nullptr)
    return name;
}
char* user::getUId()
{
    if (this != nullptr)
        return uId;
    else
        return nullptr;
}

user::user(user& rhs)
{
    this->totalFriends = rhs.totalFriends;
    this->totalLikedPages = rhs.totalLikedPages;
    this->totalUPosts = rhs.totalUPosts;
    int length = 0;
    if (rhs.uId != nullptr)
    {
        length = helper::GetLength(rhs.uId);
        this->uId = new char[length + 1];
        helper::copyString(uId, rhs.uId, length);
    }
    else { uId = nullptr; }
   
    if (rhs.name != nullptr)
    {

        length = 0;
        length = helper::GetLength(rhs.name);
        this->name = new char[length + 1];
        helper::copyString(name, rhs.name, length);
    }
    else { name = nullptr; }
    
    if (rhs.friends != nullptr)
    {
        friends = new user * [rhs.totalFriends];
        for (int i = 0; i < totalFriends; i++)
        {
            friends[i] = rhs.friends[i];
        }
    }
    else { friends = nullptr; }
    if (rhs.likedPages != nullptr)
    {
        likedPages = new page * [rhs.totalLikedPages];
        for (int i = 0; i < totalLikedPages; i++)
        {
            likedPages[i] = rhs.likedPages[i];
        }
    }
    else { likedPages = nullptr; }
    if (rhs.uHomePage != nullptr)
    {
        uHomePage = new post * [rhs.totalUPosts];
        for (int i = 0; i < totalUPosts; i++)
        {
            uHomePage[i] = rhs.uHomePage[i];
        }
    }
    else { uHomePage = nullptr; }
}
void user:: setUserIdAndName(const char* ids, const char* names)
{
    int length = 0;
    length = helper::GetLength(ids);
    this->uId = new char[length + 1];
    helper::copyString(uId, ids, length);
    length = 0;
    length = helper::GetLength(names);
    this->name = new char[length + 1];
    helper::copyString(name, names, length);

}

void user::addFriend(user* obj)
{
    if (friends == nullptr)
    {
        friends = new user * [1];
        friends[0] = obj;
        totalFriends++;
    }
    else {
        user** temp = new user * [totalFriends];
        for (int i = 0; i < totalFriends; i++)
        {
            temp[i] = friends[i];
        }
        for (int i = 0; i < totalFriends; i++)
        {
            friends[i] = nullptr;
        }
        delete[] friends;
        totalFriends++;
        friends = new user * [totalFriends];
        for (int i = 0; i < totalFriends-1; i++)
        {
            friends[i] = temp[i];
        }
        friends[totalFriends - 1] = obj;
        for (int i = 0; i < totalFriends - 1; i++)
        {
            temp[i] = nullptr;
        }
        delete[] temp;
    }
}

void user::addLikedPage(page* obj)
{
    if (likedPages == nullptr)
    {
        likedPages = new page * [1];
        likedPages[0] = obj;
        totalLikedPages++;
    }
    else {
        page** temp = new page * [totalLikedPages];
        for (int i = 0; i < totalLikedPages; i++)
        {
            temp[i] = likedPages[i];
        }
        for (int i = 0; i < totalLikedPages; i++)
        {
            likedPages[i] = nullptr;
        }
        delete[] likedPages;
        totalLikedPages++;
        likedPages = new page * [totalLikedPages];
        for (int i = 0; i < totalLikedPages - 1; i++)
        {
            likedPages[i] = temp[i];
        }
        likedPages[totalLikedPages - 1] = obj;
        for (int i = 0; i < totalLikedPages - 1; i++)
        {
            temp[i] = nullptr;
        }
        delete[] temp;
    }
}

void  user::printFriends(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont)
{
    sf::Text pageTitle;
    pageTitle.setFont(tFont);
    pageTitle.setString(std::string(this->getName()) + "-Friends");
    pageTitle.setCharacterSize(60);
    pageTitle.setFillColor(sf::Color(51, 77, 77, 255));
    pageTitle.setPosition(300.f, 70.f);
    window.draw(pageTitle);
    sf::Text friendListText;
    friendListText.setFont(font);
    friendListText.setCharacterSize(40);
    friendListText.setFillColor(sf::Color::Black);
    friendListText.setPosition(340.f, 250.f); // Adjust position as needed

    std::stringstream friendListStream;

    // Check if the user has friends
    if (friends == nullptr)
    {
        friendListStream << "User has no friends.\n";
    }
    else
    {
        // Loop through the friends and add them to the string stream
        for (int i = 0; i < totalFriends; i++)
        {
            friendListStream << friends[i]->getUId() << " - " << friends[i]->getName() << "\n";
        }
    }

    // Set the string to the text object
    friendListText.setString(friendListStream.str());

    // Draw the friend list text on the render window
    window.draw(friendListText);
}


void user::printLikedPages(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont)
{
    sf::Text pageTitle;
    pageTitle.setFont(tFont);
    pageTitle.setString(std::string(this->getName()) + "-Liked Pages");
    pageTitle.setCharacterSize(60);
    pageTitle.setFillColor(sf::Color(51, 77, 77, 255));
    pageTitle.setPosition(350.f, 120.f);
    window.draw(pageTitle);
    sf::Text pagesListText;
    pagesListText.setFont(font);
    pagesListText.setCharacterSize(40);
    pagesListText.setFillColor(sf::Color::Black);
    pagesListText.setPosition(340.f, 240.f); // Adjust position as needed
    std::stringstream pagesListStream;

    // Check if the user has friends
    if (likedPages == nullptr)
    {
        pagesListStream << "User has no friends.\n";
    }
    else
    {
        // Loop through the friends and add them to the string stream
        for (int i = 0; i < totalLikedPages; i++)
        {
            pagesListStream << likedPages[i]->getPageId() << " - " << likedPages[i]->getPageTitle() << "\n";
        }
    }
    // Set the string to the text object
    pagesListText.setString(pagesListStream.str());

    // Draw the friend list text on the render window
    window.draw(pagesListText);

}

void user::addPostToUHomePage(post* obj)
{
    if (uHomePage == nullptr)
    {
        uHomePage = new post * [1];
        uHomePage[0] = obj;
        totalUPosts++;
    }
    else {
        post** temp = new post * [totalUPosts];
        for (int i = 0; i < totalUPosts; i++)
        {
            temp[i] = uHomePage[i];
        }
        for (int i = 0; i < totalUPosts; i++)
        {
            uHomePage[i] = nullptr;
        }
        delete[] uHomePage;
        totalUPosts++;
        uHomePage = new post * [totalUPosts];
        for (int i = 0; i < totalUPosts - 1; i++)
        {
            uHomePage[i] = temp[i];
        }
        uHomePage[totalUPosts - 1] = obj;
        for (int i = 0; i < totalUPosts - 1; i++)
        {
            temp[i] = nullptr;
        }
        delete[] temp;
    }
}

int user:: getTotalUPosts()
{
    return totalUPosts;
}

void user::displayUHomePage(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont,sf::Sprite& cat)
{
    if (this != nullptr)
    {
        // Convert user name to std::string
        std::string userName = this->getName();

        // Display user name and home page title
        sf::Text pageTitle;
        pageTitle.setFont(tFont);
        pageTitle.setString(userName + "-Home Page:");
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(sf::Color(51, 77, 77, 255));
        pageTitle.setPosition(300.f, 70.f);
        window.draw(pageTitle);

        // Display each post on the home page if available
        if (totalUPosts > 0)
        {
            int leftColumnX = 10; // X-coordinate for the left column
            int rightColumnX = 500; // X-coordinate for the right column
            int postCount = 0; // Keep track of the number of posts displayed

            for (int i = 0; i < totalUPosts; i++)
            {
                // Render post memory
                uHomePage[i]->printMemory(window, font, leftColumnX, 150.f + postCount * 200.f);

                // Render user activities if available
                if (uHomePage[i]->getActivities()->getValue() != "")
                {
                    std::string act = uHomePage[i]->getActivities()->getValue();
                    sf::Text activitiesText;
                    activitiesText.setFont(font);
                    activitiesText.setOutlineThickness(0.3f);
                    activitiesText.setString(userName + " is " + act);
                    activitiesText.setCharacterSize(20);
                    activitiesText.setFillColor(sf::Color::Black);
                    activitiesText.setPosition(leftColumnX, 60.f + postCount * 200.f + 170.f); // Adjust position as needed
                    window.draw(activitiesText);
                }
                else {
                    sf::Text activitiesText;
                    activitiesText.setFont(font);
                    activitiesText.setOutlineThickness(0.3f);
                    activitiesText.setString(userName + " shared: " );
                    activitiesText.setCharacterSize(20);
                    activitiesText.setFillColor(sf::Color::Black);
                    activitiesText.setPosition(leftColumnX, 60.f + postCount * 200.f + 170.f); // Adjust position as needed
                    window.draw(activitiesText);
                }

                // Convert post text to std::string
                std::string postTextString = "\"" + std::string(uHomePage[i]->getPostText()) + "\"" ;

                // Render post text
                sf::Text postText;
                postText.setFont(font);
                postText.setString(postTextString);
                postText.setCharacterSize(20);
                postText.setFillColor(sf::Color::Black);
                postText.setPosition(leftColumnX, 60.f + postCount * 200.f + 200.f); // Adjust position as needed
                window.draw(postText);

                // Convert shared date to std::string
                std::string sharedDateString = "(" + uHomePage[i]->getSharedDateAsString() + ")";

                // Render shared date
                sf::Text sharedDateText;
                sharedDateText.setFont(font);
                sharedDateText.setString(sharedDateString);
                sharedDateText.setCharacterSize(15);
                sharedDateText.setFillColor(sf::Color::Black);
                sharedDateText.setPosition(leftColumnX, 70.f + postCount * 200.f + 230.f); // Adjust position as needed
                window.draw(sharedDateText);

                // Render comments
                uHomePage[i]->displayComment(window, font, leftColumnX, 60.f + postCount * 200.f + 260.f);

                // Increment post count
                postCount++;

                // If three posts are displayed in the left column, move to the right column
                if (postCount == 3)
                {
                    leftColumnX = rightColumnX;
                    postCount = 0;
                }
            }
        }
        else
        {
            // Render message if no posts available
            sf::Text noPostsMessage;
            noPostsMessage.setFont(font);
            noPostsMessage.setString("User has not posted yet.");
            noPostsMessage.setCharacterSize(50);
            noPostsMessage.setFillColor(sf::Color::Black);
            noPostsMessage.setPosition(40.f, 200.f); // Adjust position as needed
            window.draw(noPostsMessage);
            window.draw(cat);
        }
    }
    else
    {
        // If user is not selected, display a message
        sf::Text errorMessage;
        errorMessage.setFont(tFont);
        errorMessage.setString("You need to select a user first.");
        errorMessage.setCharacterSize(20);
        errorMessage.setFillColor(sf::Color::Black);
        errorMessage.setPosition(10.f, 10.f);
        window.draw(errorMessage);
    }
}

void user::displayTimeLine(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont)
{
    // Display user's name and timeline title
    std::string userName = this->getName();
    sf::Text timelineTitle;
    timelineTitle.setFont(tFont);
    timelineTitle.setString(userName + "-TimeLine:");
    timelineTitle.setCharacterSize(60);
    timelineTitle.setFillColor(sf::Color(51, 77, 77, 255));
    timelineTitle.setPosition(300.f, 70.f);
    window.draw(timelineTitle);

    // Display friend posts
    float friendYOffset = 200.f; // Initial vertical offset for friend posts

    // Display each friend's posts
    for (int i = 0; i < totalFriends; i++)
    {
        friends[i]->displayFriendPosts(window, font, tFont, 15, 11, 2017, friendYOffset);
        // Adjust vertical offset for next friend's posts
        friendYOffset += 195.f; // Add spacing between friend posts
    }

    // Display liked page posts on the right column
    float rightColumnXOffset = 550.f; // Horizontal offset for liked page posts
    float likedPageYOffset = 200.f; // Initial vertical offset for liked page posts
    for (int i = 0; i < totalLikedPages; i++)
    {
        likedPages[i]->displayLikedPosts(window, font, tFont, 15, 11, 2017, rightColumnXOffset, likedPageYOffset);
        // Adjust vertical offset for next liked page posts
        likedPageYOffset += 195.f; // Add spacing between liked page posts
    }
}

void user::displayFriendPosts(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont, int day, int month, int year, float yOffset)
{
    float postY = yOffset; // Initial Y-coordinate for the posts

    for (int i = 0; i < totalUPosts; i++)
    {
        if (uHomePage[i]->getSharedDate()->getMonth() == month && uHomePage[i]->getSharedDate()->getYear() == year)
        {
            if (uHomePage[i]->getSharedDate()->getDay() == day || uHomePage[i]->getSharedDate()->getDay() == day - 1)
            {
                // Render post memory
                uHomePage[i]->printMemory(window, font, 20.f, postY);

                // Render user activities if available
                if (uHomePage[i]->getActivities()->getValue() != "")
                {
                    std::string act = uHomePage[i]->getActivities()->getValue();
                    sf::Text activitiesText;
                    activitiesText.setFont(font);
                    activitiesText.setOutlineThickness(0.3f);
                    activitiesText.setString(std::string(this->getName()) + " is " + act);
                    activitiesText.setCharacterSize(20);
                    activitiesText.setFillColor(sf::Color::Black);
                    activitiesText.setPosition(20.f, postY ); // Adjust position as needed
                    window.draw(activitiesText);
                }
                else
                {
                    sf::Text activitiesText;
                    activitiesText.setFont(font);
                    activitiesText.setOutlineThickness(0.3f);
                    activitiesText.setString(std::string(this->getName()) + " shared: ");
                    activitiesText.setCharacterSize(20);
                    activitiesText.setFillColor(sf::Color::Black);
                    activitiesText.setPosition(20.f,postY); // Adjust position as needed
                    window.draw(activitiesText);
                }
                // Render post text
                sf::Text postText;
                postText.setFont(font);
                postText.setString("\"" + std::string(uHomePage[i]->getPostText())+ "\"" );
                postText.setCharacterSize(20);
                postText.setFillColor(sf::Color::Black);
                postText.setPosition(20.f, postY + 30.f); // Adjust position as needed
                window.draw(postText);

                // Render shared date
                sf::Text sharedDateText;
                sharedDateText.setFont(font);
                sharedDateText.setString("(" + uHomePage[i]->getSharedDateAsString() + ")");
                sharedDateText.setCharacterSize(15);
                sharedDateText.setFillColor(sf::Color::Black);
                sharedDateText.setPosition(20.f, postY + 60.f); // Adjust position as needed
                window.draw(sharedDateText);

                // Render comments
                uHomePage[i]->displayComment(window, font, 10.f, postY + 90.f);

                // Update the Y-coordinate for the next post
                postY += 195.f; // Add vertical spacing between posts
            }
        }
    }
}
