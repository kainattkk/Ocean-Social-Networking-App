#include"helper.h"
#include"page.h"
#include"post.h"
#include"user.h"
#include"comment.h"
#include<string>
#include<iostream>
#include"socialNetworkApp.h"
using namespace std;


post::post()
{
	postId = nullptr;
	description = nullptr;
	numOfULikes = 0;
	likedByPeeps = nullptr;
    numOfPLikes = 0;
    likedByPages = nullptr;
	postOwner = nullptr;
	postPage = nullptr;
    numOfLikes = 0;
    activities=new activity;
    newDate = new date;
    sharedDate = new date;
    totalComments = 0;
    comments=nullptr;
}

post::post(char* ids, char* name)
{
    int length = 0;
    length = helper::GetLength(ids);
    this->postId = new char[length + 1];
    helper::copyString(postId, ids, length);
    length = 0;
    length = helper::GetLength(name);
    this->description = new char[length + 1];
    helper::copyString(description, name, length);
    numOfULikes = 0;
    likedByPeeps = nullptr;
    numOfPLikes = 0;
    numOfLikes = 0;
    likedByPages = nullptr;
    postOwner = nullptr;
    postPage = nullptr;
    activities = new activity;
    newDate = new date;
    sharedDate = new date;
    totalComments = 0;
    comments=nullptr;
}

post::~post()
{
    cout << "Post destructor called" << endl;
    postOwner = nullptr;
    postPage = nullptr;
    if (postId != nullptr)
    {
        delete[] postId;
        postId = nullptr;
    }
    if (description!= nullptr)
    {
        delete[] description;
        description = nullptr;
    }
    if (likedByPeeps != nullptr)
    {
        for (int i = 0; i < numOfULikes; i++)
        {
            likedByPeeps[i] = nullptr;
        }
        delete[] likedByPeeps;
        likedByPeeps = nullptr;
    }
    if (likedByPages != nullptr)
    {
        for (int i = 0; i < numOfPLikes; i++)
        {
            likedByPages[i] = nullptr;
        }
        delete[] likedByPages;
        likedByPages = nullptr;
    }
    if (comments != nullptr)
    {
        for (int i = 0; i < totalComments; i++)
        {
            if (comments[i]->getRuntime() == true)
            {   
                delete comments[i];
                comments[i] = nullptr;
            }
            else {
                comments[i] = nullptr;
            }
        }
    }
    delete sharedDate;
    delete newDate;
    delete activities;
}

void post::addULike(user* obj,sf::Text& tt)
{
    bool exists = false;
    if (likedByPeeps == nullptr)
    {
        likedByPeeps = new user * [1];
        likedByPeeps[0] = obj;
        numOfULikes++;
        numOfLikes++;
        tt.setString(std::string(this->getPostId()) + " has been liked successfully.");
    }
    else {
        if (numOfLikes < 10)
        {
            for (int i = 0; i < numOfULikes; i++)
            {
                if (likedByPeeps[i]->getUId() != nullptr)
                {
                    if (helper::compareStrings(likedByPeeps[i]->getUId(), obj->getUId()))
                    {
                        exists = true;
                    }
                }
            }
            if (exists == false)
            {
                user** temp = new user * [numOfULikes];
                for (int i = 0; i < numOfULikes; i++)
                {
                    temp[i] = likedByPeeps[i];
                }
                for (int i = 0; i < numOfULikes; i++)
                {
                    likedByPeeps[i] = nullptr;
                }
                delete[] likedByPeeps;
                numOfULikes++;
                numOfLikes++;
                likedByPeeps = new user * [numOfULikes];
                for (int i = 0; i < numOfULikes - 1; i++)
                {
                    likedByPeeps[i] = temp[i];
                }
                likedByPeeps[numOfULikes - 1] = obj;
                tt.setString(std::string(this->getPostId()) + " has been liked successfully.");
                for (int i = 0; i < numOfULikes - 1; i++)
                {
                    temp[i] = nullptr;
                }
                delete[] temp;
            }
            else {
                tt.setString(std::string(obj->getName()) + " has already liked this post.");
            }
        }
            else {
            tt.setString("Like limit exceeded. Can not add more likes.");
            }
    }
}

void post::addPLike(page* obj)
{
    if (likedByPeeps == nullptr)
    {
        likedByPages = new page * [1];
        likedByPages[0] = obj;
        numOfPLikes++;
        numOfLikes++;
    }
    else {
        if (numOfLikes < 10)
        {
            page** temp = new page * [numOfPLikes];
            for (int i = 0; i < numOfPLikes; i++)
            {
                temp[i] = likedByPages[i];
            }
            for (int i = 0; i < numOfPLikes; i++)
            {
                likedByPages[i] = nullptr;
            }
            delete[] likedByPages;
            numOfPLikes++;
            numOfLikes++;
            likedByPages = new page * [numOfPLikes];
            for (int i = 0; i < numOfPLikes - 1; i++)
            {
                likedByPages[i] = temp[i];
            }
            likedByPages[numOfPLikes - 1] = obj;
            for (int i = 0; i < numOfPLikes - 1; i++)
            {
                temp[i] = nullptr;
            }
            delete[] temp;
        }
        else {
            cout << "Like limit exceeded. Can not add more likes." << endl;
        }
    }

}
void post::peopleWhoLiked()
{
    if (likedByPeeps != nullptr)
    {
        for (int i = 0; i < numOfULikes; i++)
        {
            cout << likedByPeeps[i]->getUId() << "-" << likedByPeeps[i]->getName() << endl;
        }
    }
}
void post::pagesWhoLiked()
{
    if (likedByPages != nullptr)
    {
        for (int i = 0; i < numOfPLikes; i++)
        {
            cout << likedByPages[i]->getPageId() << "-" << likedByPages[i]->getPageTitle() << endl;
        }
    }
}

void post::viewPost(sf::RenderWindow& window, sf::Font& font, sf::Font& tFont)
{
    if (this != nullptr)
    {
        sf::Text pageTitle;
        pageTitle.setFont(tFont);
        pageTitle.setString(std::string(this->getPostId()));
        pageTitle.setCharacterSize(60);
        pageTitle.setFillColor(sf::Color(51, 77, 77, 255));
        pageTitle.setPosition(480.f, 70.f);
        window.draw(pageTitle);
        // Create a text object for displaying post information
        sf::Text postInfo;
        postInfo.setFont(font);
        postInfo.setCharacterSize(25);
        postInfo.setFillColor(sf::Color::Black);

        // Check if there are activities associated with the post
        if (this->getActivities()->getValue() != "")
        {
            // Construct the activity string
            std::string activityString;
            if (this->getPostOwner() != nullptr)
                activityString += std::string(this->getPostOwner()->getName()) + " is ";
            else if (this->getPostPage() != nullptr)
                activityString += std::string(this->getPostPage()->getPageTitle()) + " is ";
            activityString += this->getActivities()->getValue();

            // Set the activity string to postInfo
            postInfo.setString(activityString);
        }
        else
        {
            // Construct the shared message
            std::string sharedMessage;
            if (this->getPostOwner() != nullptr)
                sharedMessage += std::string(this->getPostOwner()->getName()) + " shared ";
            else if (this->getPostPage() != nullptr)
                sharedMessage += std ::string(this->getPostPage()->getPageTitle()) + " shared " ;

            // Set the shared message to postInfo
            postInfo.setString(sharedMessage);
        }

        // Set the position of postInfo
        postInfo.setPosition(330.f, 250.f);

        // Draw postInfo to the window
        window.draw(postInfo);

        // Create a text object for displaying the post text
        sf::Text postText;
        postText.setFont(font);
        postText.setCharacterSize(20);
        postText.setFillColor(sf::Color::Black);
        postText.setString("\"" + std::string( this->getPostText()) + "\"");
        postText.setPosition(330.f, 280.f);
        window.draw(postText);

        // Create a text object for displaying the shared date
        sf::Text sharedDateText;
        sharedDateText.setFont(font);
        sharedDateText.setCharacterSize(15);
        sharedDateText.setFillColor(sf::Color::Black);
        sharedDateText.setString("(" + this->getSharedDateAsString() + ")");
        sharedDateText.setPosition(330.f, 310.f);
        window.draw(sharedDateText);

        // Display comments
        this->displayComment(window, font, 330.f, 340.f);
    }
}

void post::addedLikes(sf::RenderWindow& window, sf::Font& font,sf::Font& tFont)
{
    if (likedByPeeps != nullptr || likedByPages != nullptr)
    {
        // Display "Post liked by:"
        sf::Text likedByText("Post liked by:", tFont, 60);
        likedByText.setFillColor(sf::Color(51, 77, 77, 255));
        likedByText.setPosition(400.f, 100.f);
        window.draw(likedByText);

        // Display people who liked the post
        if (likedByPeeps != nullptr)
        {
            float yOffset = 300.f;
            for (int i = 0; i < numOfULikes; i++)
            {
                sf::Text likedByUserText(std::string(likedByPeeps[i]->getUId()) + "-" + std::string(likedByPeeps[i]->getName()), font, 30);
                likedByUserText.setFillColor(sf::Color::Black);
                likedByUserText.setPosition(410.f, yOffset);
                window.draw(likedByUserText);
                yOffset += 50.f;
            }
        }

        // Display pages who liked the post
        if (likedByPages != nullptr)
        {
            float yOffset = 300.f + (numOfULikes * 30.f) + 70.f; // Adjust yOffset based on the number of users who liked
            for (int i = 0; i < numOfPLikes; i++)
            {
                sf::Text likedByPageText(std::string(likedByPages[i]->getPageId()) + "-" + std::string(likedByPages[i]->getPageTitle()), font, 30);
                likedByPageText.setFillColor(sf::Color::Black);
                likedByPageText.setPosition(410.f, yOffset);
                window.draw(likedByPageText);
                yOffset += 50.f;
            }
        }
    }
    else {
        // Display message if the post has not been liked yet
        sf::Text notLikedText("The post has not been liked yet.", tFont, 50);
        notLikedText.setFillColor(sf::Color::Black);
        notLikedText.setPosition(50.f, 200.f);
        window.draw(notLikedText);
    }
}
void post::setSharedDate(int d, int m, int y)
{
    sharedDate->setDate(d, m, y);
}

void  post::setPostOwner(user* obj)
{
    postOwner = obj;
}
void  post::setPostPage(page* obj)
{
    postPage = obj;
}

user* post::getPostOwner()
{
    if (postOwner != nullptr)
        return postOwner;
    else return nullptr;
}
page* post::getPostPage()
{
    if (postPage != nullptr)
        return postPage;
    else return nullptr;
}

void post::setActivities(int a, char* text)
{
    activities->setActivity(a, text);
}

activity* post::getActivities()
{
    return activities;
}

comment** post::getComments()
{
    return comments;
}

void post::printActivities()
{
    if (this->activities->getValue() != "")
    {
        activities->displayActivity();
    }
}

char* post::getPostId()
{
    if (this != nullptr)
        return this->postId;
    else return nullptr;
}
char* post::getPostText()
{
    if (this != nullptr)
        return this->description;
    else return nullptr;
}

void post::displaySharedDate()
{
    sharedDate->printDate();
}

void post::addComment(comment* obj)
{
    if (comments == nullptr)
    {
        comments = new comment * [1];
        comments[0] = obj;
        totalComments++;
    }
    else {
        if (totalComments < 10)
        {
            comment** temp = new comment * [totalComments];
            for (int i = 0; i < totalComments; i++)
            {
                temp[i] = comments[i];
            }
            for (int i = 0; i < totalComments; i++)
            {
                comments[i] = nullptr;
            }
            delete[] comments;
            totalComments++;
            comments = new comment * [totalComments];
            for (int i = 0; i < totalComments - 1; i++)
            {
                comments[i] = temp[i];
            }
            comments[totalComments - 1] = obj;
            for (int i = 0; i < totalComments - 1; i++)
            {
                temp[i] = nullptr;
            }
            delete[] temp;
        }
        else {
            cout << "Comment limit exceeded. Can not add more comments." << endl;
        }
    }
}

void post::displayComments()
{
 
    for (int i = 0; i < totalComments; i++)
    {
        if (comments[i] != nullptr)
        {
            cout << "                     ";
            if(comments[i]->getcOwner()!=nullptr)
            cout << comments[i]->getcOwner()->getName() << " wrote: ";
            else if (comments[i]->getcPage() != nullptr)
                cout << comments[i]->getcPage()->getPageTitle() << " wrote: ";
            comments[i]->printComment();
        }
    }
}
int post::getTotalComments()
{
    return totalComments;
}

void post::setComments(comment** umm)
{
    if(umm!=nullptr)
    comments = umm;
}
void post::displayComment(sf::RenderWindow& window, sf::Font& font, float posX, float posY)
{
    for (int i = 0; i < totalComments; i++)
    {
        if (comments[i] != nullptr)
        {
            // Convert char array to std::string
            std::string commentOwnerName;
            if (comments[i]->getcOwner() != nullptr)
                commentOwnerName = comments[i]->getcOwner()->getName();
            std::string commentPageTitle;
            if (comments[i]->getcPage() != nullptr)
                commentPageTitle = comments[i]->getcPage()->getPageTitle();
            std::string commentText = comments[i]->getCommentText();

            // Create and draw comment text
            sf::Text commentTextSFML;
            commentTextSFML.setFont(font);
            if (!commentOwnerName.empty())
                commentTextSFML.setString("                     " + commentOwnerName + " wrote: " + commentText);
            else if (!commentPageTitle.empty())
                commentTextSFML.setString("                     " + commentPageTitle + " wrote: " + commentText);
            commentTextSFML.setCharacterSize(16);
            commentTextSFML.setFillColor(sf::Color::Black);
            commentTextSFML.setPosition(posX, posY);
            window.draw(commentTextSFML);

            // Increment Y position for next comment
            posY += 30.f; // Adjust spacing as needed
        }
    }
}
date* post::getSharedDate()
{
    return sharedDate;
}

std::string post::getSharedDateAsString() {
    if (sharedDate != nullptr) {
        return sharedDate->toString();
    }
    else {
        return "Date not set";
    }
}

void post::addRuntimeComment(user* owner, char* text,sf::Text& tt)
{
  
 
    if (comments == nullptr)
    {
        comments = new comment * [1];
        comments[0] = new comment (text, text);
        comments[0]->setcOwner(owner);
        tt.setString(std::string("Comment added successfully."));
        totalComments++;

    }
    else {
        if (totalComments < 10)
        {
            comment** temp = new comment * [totalComments];
            for (int i = 0; i < totalComments; i++)
            {
                temp[i] = comments[i];
            }
            for (int i = 0; i < totalComments; i++)
            {
                comments[i] = nullptr;
            }
            delete[] comments;
            totalComments++;
            comments = new comment * [totalComments];
            for (int i = 0; i < totalComments - 1; i++)
            {
                comments[i] = temp[i];
            }
            comments[totalComments - 1] = new comment(text, text);
            comments[totalComments - 1]->setRuntime(true);
            comments[totalComments - 1]->setcOwner(owner);
            tt.setString(std::string("Comment added successfully."));
            for (int i = 0; i < totalComments - 1; i++)
            {
                temp[i] = nullptr;
            }
            delete[] temp;
        }
        else {
            tt.setString(std::string("Comment limit exceeded. Can not add more comments."));
        }
    }
}
void post::printMemory(sf::RenderWindow& window, sf::Font& font, float posX, float posY)
{

}

void post:: setNewDate(int d, int m, int y)
{
    newDate->setDate(d, m, y);
}

date* post::getNewDate()
{
    return newDate;
}