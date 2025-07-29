#include"memory.h"
#include<iostream>
using namespace std;
#include"helper.h"
#include"user.h"
#include"post.h"

memory::memory(char* id=nullptr,char* title=nullptr, char* text = nullptr,int a=0):post(id,title)
{
	int length = 0;
	length = helper::GetLength(text);
	this->postText = new char[length + 1];
	helper::copyString(postText, text, length);
	difference = a;
}

 char* memory:: getMtext()
{
	return postText;
}
memory::~memory()
{
	cout << "memory destructor called" << endl;
	if (postText != nullptr)
	{
		delete[] postText;
		postText = nullptr;
	}
}
void memory::printMemory()
{
	if (postText != nullptr)
	{
		cout << "~~~" << getPostOwner()->getName() << " shared a Memory~~~" << " (";
		cout << getNewDate()->getDay() << "/" << getNewDate()->getMonth() <<"/" << getNewDate()->getYear();
		cout << ")" << endl;
		cout << "\"" << getMtext() << "\"" << endl;
		cout << "           (" << getDifference() << " years ago)" << endl;
	}
}

void memory::printMemory(sf::RenderWindow& window, sf::Font& font, float posX, float posY)
{
    if (postText != nullptr)
    {
        // Convert char array to std::string
        std::string ownerName = getPostOwner()->getName();
        std::string memoryText = getMtext();
        std::string difference = std::to_string(getDifference());

        // Create and draw memory title
        sf::Text memoryTitle;
        memoryTitle.setFont(font);
        memoryTitle.setString("~~~" + ownerName + " shared a Memory~~~" + " (" +
            std::to_string(getNewDate()->getDay()) + "/" + std::to_string(getNewDate()->getMonth()) +
            "/" + std::to_string(getNewDate()->getYear()) + ")");
        memoryTitle.setCharacterSize(20);
        memoryTitle.setFillColor(sf::Color::Black);
        memoryTitle.setPosition(posX, posY);
        window.draw(memoryTitle);

        // Create and draw memory text
        sf::Text memoryTextSFML;
        memoryTextSFML.setFont(font);
        memoryTextSFML.setString("\"" + memoryText + "\"");
        memoryTextSFML.setCharacterSize(20);
        memoryTextSFML.setOutlineThickness(0.3f);
        memoryTextSFML.setFillColor(sf::Color::Black);
        memoryTextSFML.setPosition(posX, posY + 30.f); // Adjust position as needed
        window.draw(memoryTextSFML);

        // Create and draw time difference
        sf::Text timeDifferenceText;
        timeDifferenceText.setFont(font);
        timeDifferenceText.setString("(" + difference + " years ago)");
        timeDifferenceText.setCharacterSize(14);
        timeDifferenceText.setFillColor(sf::Color::Black);
        timeDifferenceText.setPosition(posX, posY + 60.f); // Adjust position as needed
        window.draw(timeDifferenceText);
    }
}


void memory::setDifference(int a)
{
	difference = a;
}
int memory:: getDifference()
{
	return difference;
}