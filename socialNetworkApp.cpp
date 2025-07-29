
#include<fstream>
#include<iostream>
using namespace std;
#include"user.h"
#include"post.h"
#include"socialNetworkApp.h"
#include"page.h"
#include"comment.h"
#include"activity.h"
#include"memory.h"
#include"helper.h"
#include"date.h"
#include"memory.h"

ifstream iusers("Users.txt");
ifstream ipages("Pages.txt");
ifstream iposts("Posts.txt");
ifstream icomments("Comments.txt");

user** socialNetworkApp::users = nullptr;
page** socialNetworkApp::pages = nullptr;
post** socialNetworkApp::posts = nullptr;
comment** socialNetworkApp::rComments = nullptr;
memory** socialNetworkApp::memories = nullptr;
int socialNetworkApp::use = 0;
int socialNetworkApp::nPosts = 0;
int socialNetworkApp::nPages = 0;
int socialNetworkApp::nComments = 0;
int socialNetworkApp::nMemories = 0;


void socialNetworkApp::loadData()
{
	iusers >> use;
	users = new user * [use];
	char* buffer = new char[15];
	char* first = new char[15];
	char* last = new char[15];
	char* name = new char[70];
	int length = 0;

	for (int i = 0; i < use; i++)
	{
		iusers >> buffer;
		iusers >> first;
		iusers >> last;
		length = 0;
		int fname = 0, lname = 0;
		length = helper::GetLength(buffer);
		fname = helper::GetLength(first);
		lname = helper::GetLength(last);
		helper::Namer(name, first, last);
		users[i] = new user(buffer, name);
	}

	ipages >> nPages;
	pages = new page * [nPages];
		for (int i = 0; i < nPages; i++)
		{
			ipages >> buffer;
			ipages.ignore();
			length = 0;
			ipages.getline(name, 80);
			pages[i] = new page(buffer, name);
			ipages >> buffer;
			bool bingo = false;
			for (int j = 0; j < use; j++) {
				if (helper::compareStrings(buffer, users[j]->getUId())) {
					bingo = true;
					pages[i]->setOwner(users[j]);
					break;
				}
			}
		}

	const char delimiter[3] = "-1";
	bool found = false;
	for (int i = 0; i < use; i++) {
		do {
			iusers >> buffer;
			if (helper::compareStrings(buffer, delimiter) == 1) {
				break;
			}
			found = false;
			for (int j = 0; j < use; j++) {
				if (helper::compareStrings(buffer, users[j]->getUId())) {
					found = true;
					users[i]->addFriend(users[j]);
					break;
				}
			}
		} while (helper::compareStrings(buffer, delimiter) != 1);

		do {
			iusers >> buffer;
			if (helper::compareStrings(buffer, delimiter) == 1) {
				break;
			}
			found = false;
			for (int j = 0; j < nPages; j++) {
				if (helper::compareStrings(buffer, pages[j]->getPageId())) {
					found = true;
					users[i]->addLikedPage(pages[j]);
					break;
				}
			}
		} while (helper::compareStrings(buffer, delimiter) != 1);
	}
	iposts >> nPosts;
	posts = new post * [nPosts];
	for (int i = 0; i < nPosts; i++)
	{
		sf::Text dummy;
		int type = 0;
		iposts >> type;
		iposts >> buffer;
		int day, month, year;
		iposts >> day;
		iposts >> month;
		iposts >> year;
		iposts.ignore();
		iposts.getline(name, 80);
		posts[i] = new post(buffer, name);
		posts[i]->setSharedDate(day, month, year);
		bool bingo = false;
		if (type == 1)
		{
			iposts >> buffer;
			if (buffer[0] == 'u')
			{
				for (int j = 0; j < use; j++) {

					if (helper::compareStrings(buffer, users[j]->getUId())) {
						bingo = true;
						posts[i]->setPostOwner(users[j]);
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < nPages; j++) {
					if (helper::compareStrings(buffer, pages[j]->getPageId())) {
						bingo = true;
						posts[i]->setPostPage(pages[j]);
						break;
					}
					
				}
			}
			do {
				iposts >> buffer;
				if (buffer[0] == 'u')
				{
					if (helper::compareStrings(buffer, delimiter) == 1) {
						break;
					}
					found = false;
					for (int j = 0; j < use; j++) {
						if (helper::compareStrings(buffer, users[j]->getUId())) {
							found = true;
							posts[i]->addULike(users[j],dummy);
							break;
						}
					}
				}
				else
				{
					if (helper::compareStrings(buffer, delimiter) == 1) {
						break;
					}
					found = false;
					for (int j = 0; j < nPages; j++) {
						if (helper::compareStrings(buffer, pages[j]->getPageId())) {
							found = true;
							posts[i]->addPLike(pages[j]);
							break;
						}
					}

				}
			} while (helper::compareStrings(buffer, delimiter) != 1);
		}
		else if (type == 2)
		{
			int activit = 0;
			iposts >> activit;
			iposts.ignore();
			iposts.getline(name, 80);
			posts[i]->setActivities(activit, name);
			iposts >> buffer;
			if (buffer[0] == 'u')
			{
				for (int j = 0; j < use; j++) {
					if (helper::compareStrings(buffer, users[j]->getUId())) {
						bingo = true;
						posts[i]->setPostOwner(users[j]);
						break;
					}
				}
			}
			else if(buffer[0]=='p')
			{
				for (int j = 0; j < nPages; j++) {
					if (helper::compareStrings(buffer, pages[j]->getPageId())) {
						bingo = true;
						posts[i]->setPostPage(pages[j]);
						break;
					}
				}
			}
			do {
				iposts >> buffer;
				if (buffer[0] == 'u')
				{
					if (helper::compareStrings(buffer, delimiter) == 1) {
						break;
					}
					found = false;
					for (int j = 0; j < use; j++) {
						if (helper::compareStrings(buffer, users[j]->getUId())) {
							found = true;
							posts[i]->addULike(users[j],dummy);
							break;
						}
					}
				}
				else if(buffer[0]=='p')
				{
					if (helper::compareStrings(buffer, delimiter) == 1) {
						break;
					}
					found = false;
					for (int j = 0; j < nPages; j++) {
						if (helper::compareStrings(buffer, pages[j]->getPageId())) {
							found = true;
							posts[i]->addPLike(pages[j]);
							break;
						}
					}

				}
			} while (helper::compareStrings(buffer, delimiter) != 1);

		}		
	}
	icomments >> nComments;
	rComments = new comment * [nComments];
	for (int i = 0; i < nComments; i++)
	{
		icomments >> buffer;
		icomments >> first;
		icomments >> last;
		icomments.ignore();
		icomments.getline(name, 70);
		rComments[i] = new comment(buffer, name);
		if (last[0] == 'u')
		{
			for (int j = 0; j < use; j++) {
				if (helper::compareStrings(last, users[j]->getUId())) {
					rComments[i]->setcOwner(users[j]);
					break;
				}
			}
		}
		else if(last[0]=='p'){
			for (int j = 0; j < nPages; j++) {
				if (helper::compareStrings(last, pages[j]->getPageId())) {
					rComments[i]->setcPage(pages[j]);
					break;
				}
			}
		}
		for (int j = 0; j < nPosts; j++) {
			if (helper::compareStrings(first, posts[j]->getPostId())) {
				rComments[i]->setcPost(posts[j]);
				break;
			}
		}		
	}
	for (int i = 0; i < nComments; i++)
	{
		for (int j = 0; j < nPosts; j++)
		{
			if (helper::compareStrings(posts[j]->getPostId(), rComments[i]->getcPost()->getPostId()))
			{
				posts[j]->addComment(rComments[i]);
				break;
			}
		}
	}
	for (int i = 0; i < nPosts; i++)
	{
		
			if (posts[i]->getPostPage() != nullptr)
			{
				for (int j = 0; j < nPages; j++)
				{
					if (helper::compareStrings(posts[i]->getPostPage()->getPageId(), pages[j]->getPageId()))
					{
						pages[j]->addPostToHomePage(posts[i]);
						break;
					}
				}
			}
			else if (posts[i]->getPostOwner()->getUId() != nullptr)
			{
				for (int j = 0; j < use; j++)
				{
					if (helper::compareStrings(posts[i]->getPostOwner()->getUId(), users[j]->getUId()))
					{
						users[j]->addPostToUHomePage(posts[i]);
						break;
					}
				}
			}
		
	}

	if(buffer)
	delete[] buffer;
	if(first)
	delete[] first;
	if(last)
	delete[] last;
}

user* socialNetworkApp::setCurrentUser(string str,sf::Text& successfulSetup)
{
	char* selection = new char[str.length() + 1]; // Allocate memory for the char array
	// Using strcpy_s
	strcpy_s(selection, str.length() + 1, str.c_str());
	for (int j = 0; j < use; j++) {
		if (helper::compareStrings(selection, users[j]->getUId())) {
			successfulSetup.setString(str + " set up as current user successfully!");
			delete[] selection;
			return users[j];
		}
		else
		{
			successfulSetup.setString("user not found!");
		}
	}
	return nullptr;
}

socialNetworkApp::~socialNetworkApp()
{
	cout << "socialNetworkApp destructor called" << endl;
}

void socialNetworkApp::run()
{
	//main program initializations
	int currentDay = 15;
	int currentMonth = 11;
	int currentYear = 2017;
	bool yes = false;
	char* select = new char[10];
	char* text = new char[30];
	memories = new memory * [10];
	user* currentUser = nullptr;
	bool flag = false;	



	sf::VideoMode videoMode;
	videoMode.height = 800;
	videoMode.width = 1200;
	sf::RectangleShape box1;
	sf::RectangleShape loginBox;
	sf::RectangleShape inputBox;
	sf::RenderWindow window(videoMode, "Social Network App", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
	//mouse positions
	sf::Vector2i mousePosW;
	sf::Vector2f mousePosView;
	//Texts
	sf::Font font;
	sf::Font tFont;
	sf::Text name;
	sf::Text login;
	sf::Text inputText;
	sf::Text inputTextTitle;
	sf::Text menuText[12];
	sf::Text menuTitle;
	sf::Text successfulSetup;
	sf::Text pressEnter;
	sf::Text currentDate;
	font.loadFromFile("Fonts/Rushfordclean-rgz89.otf");
	if (!font.loadFromFile("Fonts/Rushfordclean-rgz89.otf")) // Load a font
	{
		cout << "Failed to load font!" << std::endl;
	}
	tFont.loadFromFile("Fonts/Arial.ttf");
	if (!tFont.loadFromFile("Fonts/Arial.ttf")) // Load a font
	{
		cout << "Failed to load font!" << std::endl;
	}
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Texture texture5;
	sf::Texture texture6;
	if (!texture1.loadFromFile("cat.png")) // Replace "image.png" with your image file path
	{
		// Handle error if image loading fails
		cout << "Failed to load cat1!" << std::endl;
	}
	if (!texture2.loadFromFile("cat1.png"))
	{
		cout << "Failed to load cat1!" << std::endl;
	}
	if (!texture3.loadFromFile("cat2.png"))
	{
		cout << "Failed to load cat1!" << std::endl;
	}
	if (!texture4.loadFromFile("blackCat.png"))
	{
		cout << "Failed to load cat1!" << std::endl;
	}
	if (!texture5.loadFromFile("whiteCat.png"))
	{
		cout << "Failed to load cat1!" << std::endl;
	}
	if (!texture6.loadFromFile("brownCat.png"))
	{
		cout << "Failed to load cat1!" << std::endl;
	}
	// Create a sprite and associate it with the texture
	sf::Sprite cat1(texture1);
	sf::Sprite cat2(texture2);
	sf::Sprite cat3(texture3);
	sf::Sprite cat4(texture4);
	sf::Sprite cat5(texture5);
	sf::Sprite cat6(texture6);

	// Set the position of the sprite
	cat1.setPosition(400.f, 390.f); // Adjust position as needed
	cat1.setScale(0.5f, 0.5f); // Adjust scale factors as needed
	cat1.setScale(0.5f, 0.5f);
	cat1.setScale(0.08f, 0.08f);

	cat2.setPosition(420.f, 300.f); 
	cat2.setScale(0.07f, 0.07f);

	cat3.setPosition(400.f, 350.f); 
	cat3.setScale(0.05f, 0.05f);

    cat4.setPosition(450.f, 420.f);
	cat4.setScale(0.06f, 0.06f);

	cat5.setPosition(750.f, 350.f); // Adjust position as needed
	cat5.setScale(0.05f, 0.05f);
	
	cat6.setPosition(470.f, 390.f); // Adjust position as needed
	cat6.setScale(0.06f, 0.06f);

	box1.setSize(sf::Vector2f(600.f, 220.f));
	box1.setPosition(sf::Vector2f(270.f, 140.f));
	box1.setFillColor(sf::Color(92, 138, 138, 255));
	box1.setOutlineColor(sf::Color(71, 107, 107, 200));
	box1.setOutlineThickness(2.f);

	loginBox.setSize(sf::Vector2f(300.f, 100.f));
	loginBox.setPosition(sf::Vector2f(440.f, 500.f));
	loginBox.setFillColor(sf::Color(92, 138, 138, 255));
	loginBox.setOutlineColor(sf::Color(71, 107, 107, 200));
	loginBox.setOutlineThickness(2.f);

	name.setFont(font);
	name.setString("Ocean");
	name.setCharacterSize(140); // Set the size of the text
	name.setFillColor(sf::Color(51, 77, 77, 255)); // Set the color of the text
	name.setPosition(420.f, 160.f); // Set the position of the text

	login.setFont(font);
	login.setString("LOGIN");
	login.setCharacterSize(90); 
	login.setFillColor(sf::Color(51, 77, 77, 255)); 
	login.setPosition(490.f, 490.f);
	
	inputBox.setSize(sf::Vector2f(400.f, 100.f));
	inputBox.setPosition(380.f, 155.f);
	inputBox.setFillColor(sf::Color::White);
	inputBox.setOutlineThickness(2.f);
	inputBox.setOutlineColor(sf::Color::Black);

	inputText.setFont(tFont);
	inputText.setCharacterSize(50);
	inputText.setFillColor(sf::Color::Black);
	inputText.setPosition(400.f, 165.f);

	sf::Text pText;
	pText.setFont(tFont);
	pText.setCharacterSize(50);
	pText.setFillColor(sf::Color::Black);
	pText.setPosition(400.f, 165.f);

	sf::Text cText;
	cText.setFont(tFont);
	cText.setCharacterSize(50);
	cText.setFillColor(sf::Color::Black);
	cText.setPosition(400.f, 165.f);

	inputTextTitle.setFont(font);
	inputTextTitle.setString("Enter User ID");
	inputTextTitle.setCharacterSize(60); // Set the size of the text
	inputTextTitle.setFillColor(sf::Color(51, 77, 77, 255)); // Set the color of the text
	inputTextTitle.setPosition(440.f, 70.f); // Set the position of the text

	menuTitle.setFont(font);
	menuTitle.setString("Select an option");
	menuTitle.setCharacterSize(60); // Set the size of the text
	menuTitle.setFillColor(sf::Color(51, 77, 77, 255)); // Set the color of the text
	menuTitle.setPosition(420.f, 80.f); // Set the position of the text

	successfulSetup.setFont(font);
	successfulSetup.setCharacterSize(60); 
	successfulSetup.setFillColor(sf::Color(51, 77, 77, 255));
	successfulSetup.setPosition(135.f, 100.f);

	pressEnter.setFont(font);
	pressEnter.setCharacterSize(50);
	pressEnter.setString("Press enter to continue");
	pressEnter.setFillColor(sf::Color(51, 77, 77, 255));
	pressEnter.setPosition(350.f, 650.f);

	currentDate.setFont(font);
	currentDate.setCharacterSize(20);
	currentDate.setString("System Date : 15/11/2017");
	currentDate.setFillColor(sf::Color(51, 77, 77, 255));
	currentDate.setPosition(950.f, 750.f);

	//a vector to store the user IDs and names
	std::vector<sf::Text> userTexts;
	sf::Text userText;
	sf::Vector2f startPosition(185.f, inputText.getPosition().y + inputText.getCharacterSize() + 70.f);

	// Define the spacing between rows and columns
	float rowSpacing = 45.f;
	float columnSpacingX = 450.f;
	float columnSpacingY = 80.f;

	// Populate userTexts vector and set positions
	for (int i = 0; i < use; ++i) {
		sf::Text userText;
		userText.setFont(tFont);
		userText.setCharacterSize(28);
		userText.setFillColor(sf::Color(51, 67, 67, 255));
		userText.setString((std::string(users[i]->getUId()) + " - " + std::string(users[i]->getName())).c_str());

		// Calculate position based on row and column
		int row = i / 2;
		int column = i % 2;
		userText.setPosition(startPosition.x + column * columnSpacingX, startPosition.y + row * rowSpacing);

		// Add userText to userTexts vector
		userTexts.push_back(userText);
	}

	//a string array to store the menu
	string menuOptions[12] = {
	"Set Current User",
	"View Home of Current User",
	"Like a Post",
	"View the List of People who Liked a Post",
	"Comment on a Post",
	"View a Post",
	"Share a Memory",
	"View User's Timeline",
	"View Friend List",
	"View Liked Pages",
	"View Page",
	"Exit App"
	};

	// Set up menu text properties
	for (int i = 0; i < 12; ++i) {
		menuText[i].setFont(font);
		menuText[i].setCharacterSize(40);
		menuText[i].setFillColor(sf::Color(51, 67, 67, 255));
		menuText[i].setString(menuOptions[i]);
		if (i < 6)
		{
			menuText[i].setPosition(100.f, 190.f + i * 80.f); // Adjust position as needed
		}
		else {
			menuText[i].setPosition(window.getSize().x - 420.f, 190.f + (i - 6) * 80.f); // Adjust position as needed
		}
	}


	// Display prompt to enter the ID of the post
	sf::Text promptText;
	promptText.setFont(font);
	promptText.setCharacterSize(60);
	promptText.setFillColor(sf::Color(51, 77, 77, 255));
	promptText.setPosition(150.f, 70.f); // Adjust position as needed
	window.draw(promptText);

	// Define a vector to store post texts
	std::vector<sf::Text> postTexts;

	// Define the starting position for the posts
	sf::Vector2f postStartPosition(300.f, 300.f);

	// Define the spacing between posts
	float postSpacingY = 70.f;

	// Populate postTexts vector and set positions
	for (int i = 0; i < nPosts; ++i) {
		sf::Text postText;
		postText.setFont(tFont);
		postText.setCharacterSize(28);
		postText.setFillColor(sf::Color(51, 67, 67, 255));
		postText.setString(std::string(posts[i]->getPostId()));

		// Calculate position based on index
		int row = i / 2;
		int column = i % 2;
		postText.setPosition(postStartPosition.x + column * columnSpacingX, postStartPosition.y + row * postSpacingY);


		// Add postText to postTexts vector
		postTexts.push_back(postText);
	}

	// Define a vector to store post texts
	std::vector<sf::Text> pageTexts;

	// Define the starting position for the posts
	sf::Vector2f pageStartPosition(300.f, 300.f);

	// Define the spacing between posts
	float pageSpacingY = 70.f;

	// Populate pageTexts vector and set positions
	for (int i = 0; i < nPages; ++i) {
		sf::Text pageText;
		pageText.setFont(tFont);
		pageText.setCharacterSize(28);
		pageText.setFillColor(sf::Color(51, 67, 67, 255));
		pageText.setString(std::string(pages[i]->getPageId()));

		// Calculate position based on index
		int row = i / 2;
		int column = i % 2;
		pageText.setPosition(pageStartPosition.x + column * columnSpacingX, pageStartPosition.y + row * pageSpacingY);


		// Add pageText to pageTexts vector
		pageTexts.push_back(pageText);
	}

	sf::Text postFound;
	postFound.setFont(font);
	postFound.setCharacterSize(50);
	postFound.setFillColor(sf::Color(51, 77, 77, 255));
    postFound.setPosition(175.f,200.f);

	//mouse coordinates
	mousePosW = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(mousePosW);

	string userInput; // To store user input
	string pInput;
	string cInput;
	//different bools for different options to work with sfml

	// Load the click sound
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Sounds/mouseClick.mp3")) {
		// Handle loading error
		cout << "mouse sound not loaded." << endl;
	}

	sf::Sound clickSound;
	clickSound.setBuffer(buffer);

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("Sounds/keyboardClick.mp3")) {
		// Handle loading error
		cout << "key sound not loaded." << endl;
	}

	sf::Sound keySound;
	keySound.setBuffer(buffer2);

	bool elementsVisible = true;
	bool enterUser = false;
	bool menuVisible = false;
	bool successfulSetupBool = false;
	bool home = false;
	bool showPosts = false;
	bool postBool = false;
	bool postIDFound = false; // Variable to track if post ID is found
	bool likesOnPost = false;
	bool displayLikes = false;
	bool commentOnPost = false;
	bool cTextBool = false;
	bool commentAdded = false;
	bool seePost = false;
	bool showPost = false;
	bool addMemory = false;
	bool addMemoryText = false;
	bool mAdded = false;
	bool displayTimeline = false;
	bool seeFriends = false;
	bool seeLikedPages = false;
	bool seePage = false;
	bool foundPage = false;
	bool closeWindow = false;
	bool angry = false;
	char* selection = nullptr;

	int selectedOption = -1; // To store the index of the selected menu option
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				keySound.play();
				if (event.key.code == sf::Keyboard::Escape) {
					closeWindow = true;
				}
			
				else if (event.key.code == sf::Keyboard::Enter) {
					if (enterUser) {
						enterUser = false;
						successfulSetupBool = true;
						
						currentUser = setCurrentUser(userInput, successfulSetup);
						
					}
					else if (successfulSetupBool)
					{
						successfulSetupBool = false;
						if (currentUser == nullptr) {
							//userInput = "";
							//inputText.setString("");
							enterUser = true;
						}
						else
						{
							enterUser = false;
							menuVisible = true;
						}

					}
					else if (showPosts)
					{
						 selection = new char[pInput.length() + 1]; // Allocate memory for the char array
						// Using strcpy_s
						strcpy_s(selection, pInput.length() + 1, pInput.c_str());
						for (int j = 0; j < nPosts; j++) {
							if (helper::compareStrings(selection, posts[j]->getPostId())) {
								posts[j]->addULike(currentUser,postFound);
								postIDFound = true; // Set flag if post ID is found
							}
						}
						if (postIDFound == false)
						{
							postFound.setString("post not found");
							angry = true;
						}
						else
						{
							angry = false;
						}
						showPosts = false;
						postBool = true;
						delete[] selection;
						postIDFound = false;
					}
					else if(home == true)
					{
						home = false;
						pressEnter.setCharacterSize(50);
						pressEnter.setPosition(350.f, 650.f);
						menuVisible = true;
					}
					else if (postBool == true)
					{
						postBool = false;
						menuVisible = true;
					}
					else if (likesOnPost == true)
					{
						likesOnPost = false;
						displayLikes = true;
					}
					else if (displayLikes == true)
					{
						displayLikes = false;
						menuVisible = true;
					}
					else if (commentOnPost == true)
					{

						selection = new char[pInput.length() + 1]; // Allocate memory for the char array
						strcpy_s(selection, pInput.length() + 1, pInput.c_str());
						commentOnPost = false;
						cTextBool = true;
						
					}
					else if (cTextBool)
					{
						angry = false;
						postIDFound = false;
						char* cText = new char[cInput.length() + 1];
						strcpy_s(cText, cInput.length() + 1, cInput.c_str());
						postFound.setString("");
						for (int j = 0; j < nPosts; j++) {
							if (helper::compareStrings(selection, posts[j]->getPostId())) {
								posts[j]->addRuntimeComment(currentUser, cText,postFound);
								postIDFound = true;
							}
						}
						if (postIDFound == false)
						{
							postFound.setString("post not found");
							angry = true;
						}
						if (selection)
							delete[] selection;
						if (cText)
							delete[] cText;
						cTextBool = false;
						commentAdded = true;
					}
					else if (commentAdded)
					{
						commentAdded = false;
						menuVisible = true;
					}
					else if (seePost)
					{
						seePost = false;
						showPost = true;
					}
					else if (showPost)
					{
						showPost = false;
						menuVisible = true;
					}
					else if (addMemory)
					{
						addMemory = false;
						addMemoryText = true;
					}
					else if (addMemoryText)
					{
						addMemoryText = false;
						mAdded = true;
						yes = false;
						selection = new char[pInput.length() + 1]; // Allocate memory for the char array
						strcpy_s(selection, pInput.length() + 1, pInput.c_str());
						char* mText = new char[cInput.length() + 1];
						strcpy_s(mText, cInput.length() + 1, cInput.c_str());
						for (int i = 0; i < nPosts; i++)
						{
							if (helper::compareStrings(selection, posts[i]->getPostId())) {
								if (posts[i]->getPostOwner()->getUId() != nullptr)
								{
									if (helper::compareStrings(currentUser->getUId(), posts[i]->getPostOwner()->getUId()))
									{
										yes = true;
										memories[nMemories] = new memory(posts[i]->getPostId(), posts[i]->getPostText(), mText, 0);
										currentUser->addPostToUHomePage(memories[nMemories]);
										memories[nMemories]->setPostOwner(currentUser);
										memories[nMemories]->setDifference(currentYear - posts[i]->getSharedDate()->getYear());
										memories[nMemories]->setNewDate(currentDay, currentMonth, currentYear);
										memories[nMemories]->setSharedDate(posts[i]->getSharedDate()->getDay(), posts[i]->getSharedDate()->getMonth(), posts[i]->getSharedDate()->getYear());
										if (posts[i]->getActivities()->getValue() != "")
										{
											std::string activitiesString = posts[i]->getActivities()->getNoTypeValue();

											char* activitiesCharArray = new char[activitiesString.size() + 1];
											strcpy_s(activitiesCharArray, activitiesString.size() + 1, activitiesString.c_str());
											memories[nMemories]->setActivities(posts[i]->getActivities()->getType(), activitiesCharArray);
											delete[] activitiesCharArray;
										}
										nMemories++;
										postFound.setString("Memory added successfully.");
										break;
									}
								}
							}
						}
						if (yes == false)
						{
							postFound.setPosition(145.f, 200.f);
							postFound.setString("Please enter an ID of the post owned by " + std::string( currentUser->getName()));
							angry = true;
						}
						else
						{
							angry = false;
						}

					}
					else if (mAdded == true)
					{
						mAdded = false;
						menuVisible = true;
						postFound.setPosition(175.f, 200.f);
					}
					else if (displayTimeline == true)
					{
						pressEnter.setCharacterSize(50);
						pressEnter.setPosition(350.f, 650.f);
						displayTimeline = false;
						menuVisible = true;
					}
					else if (seeLikedPages)
					{
						seeLikedPages = false;
						menuVisible = true;
					}
					else if (seeFriends)
					{
						seeFriends = false;
						menuVisible = true;
					}
					else if (seePage)
					{
						seePage = false;
						foundPage = true;
					}
					else if (foundPage)
					{
						foundPage = false;
						menuVisible = true;
					}
					else if (closeWindow)
					{
						window.close();
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				clickSound.play();
				if (event.mouseButton.button == sf::Mouse::Left) {					
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);
					
					if (loginBox.getGlobalBounds().contains(mousePosView)) {
						elementsVisible = false;
						enterUser = true;
					}
					else if (menuVisible)
					{
						for (int i = 0; i < 12; ++i) {
							if (menuText[i].getGlobalBounds().contains(mousePosView)) {
								selectedOption = i+1;
								menuVisible = false;
								break;
							}
						}
						if (selectedOption == 1)
						{
							
								enterUser = true;
								inputText.setString("");
								userInput = "";
							
						}
						else if (selectedOption == 2)
						{
							home = true;
						}
						else if (selectedOption == 3)
						{
							pInput = "";
							pText.setString("");
							showPosts = true;
						} 
						else if (selectedOption == 4)
						{
							likesOnPost = true;
							pInput = "";
							pText.setString("");
						}
						else if (selectedOption == 5)
						{
							commentOnPost = true;
							pInput = "";
							pText.setString("");
							cInput = "";
							cText.setString("");
						}
						else if (selectedOption == 6)
						{
							seePost = true;
							pInput = "";
							pText.setString("");
						}
						else if (selectedOption == 7)
						{
							addMemory = true;
							pInput = "";
							pText.setString("");
							cInput = "";
							cText.setString("");
						}
						else if (selectedOption == 8)
						{
							displayTimeline = true;
						}
						else if (selectedOption == 9)
						{
							seeFriends = true;
						}
						else if (selectedOption == 10)
						{
							seeLikedPages = true;
						}
						else if (selectedOption == 11)
						{
							seePage = true;
							pText.setString("");
							pInput = "";
						}
						else if (selectedOption == 12)
						{
							closeWindow = true;
						}
					}
					
				}
				break;
			case sf::Event::TextEntered:
				keySound.play();
				if ((enterUser) && event.text.unicode < 128) { // Ensure ASCII characters
					if (event.text.unicode == '\b' && !userInput.empty()) { // Handle backspace
						userInput.pop_back();
					}
					else if (event.text.unicode != '\b') { // Exclude backspace character
						userInput += static_cast<char>(event.text.unicode);
					}
					inputText.setString(userInput);
				}
				else if((showPosts || likesOnPost || commentOnPost ||seePost || addMemory ||seePage) && event.text.unicode < 128)
				{
					if (event.text.unicode == '\b' && !pInput.empty()) { // Handle backspace
						pInput.pop_back();
					}
					else if (event.text.unicode != '\b') { // Exclude backspace character
						pInput += static_cast<char>(event.text.unicode);
					}
					pText.setString(pInput);
				}
				else if ((cTextBool || addMemoryText) && event.text.unicode < 128) { // Ensure ASCII characters
					if (event.text.unicode == '\b' && !cInput.empty()) { // Handle backspace
						cInput.pop_back();
					}
					else if (event.text.unicode != '\b') { // Exclude backspace character
						cInput += static_cast<char>(event.text.unicode);
					}
					cText.setString(cInput);
				}
				break;
			default:
				break;
			}
		}

		// Clear the window
		window.clear(sf::Color(133, 173, 173, 128));
		// Draw the elements if they are still visible
		if (elementsVisible) {
			
			window.draw(box1);
			window.draw(loginBox);
			window.draw(name);
			window.draw(login);
		}
		else if (enterUser == true)
		{
			window.draw(inputBox);
			window.draw(inputText);
			window.draw(inputTextTitle);
			for (const auto& text : userTexts) {
				window.draw(text);
			}
			window.draw(currentDate);
		}
		else if (successfulSetupBool)
		{
			window.draw(successfulSetup);
			window.draw(pressEnter);
			window.draw(currentDate);
			window.draw(cat2);
		}
		else if (menuVisible)
		{
			window.draw(menuTitle);
			for (int i = 0; i < 12; i++)
			{
				window.draw(menuText[i]);
				window.draw(currentDate);
			}
		}
		else if (home == true)
		{
			currentUser->displayUHomePage(window, tFont, font,cat4);
			pressEnter.setCharacterSize(35);
			pressEnter.setPosition(450.f, 750.f);
			window.draw(pressEnter);
			window.draw(currentDate);

		}
		else if (showPosts == true)
		{
			promptText.setString("Enter the ID of the post you want to like:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(pText);
			for (const auto& text : postTexts) {
				window.draw(text);
			}
			window.draw(currentDate);
		}
		else if (postBool == true)
		{
			window.draw(postFound);
			if (angry==true)
			{
				window.draw(cat3);
			}
			else
				window.draw(cat1);
			window.draw(pressEnter);
			window.draw(currentDate);
		}
		else if (likesOnPost == true)
		{
			promptText.setString("Enter the ID of the post to see liked list:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(pText);
			for (const auto& text : postTexts) {
				window.draw(text);
			}
			window.draw(currentDate);
		}
		else if (displayLikes == true)
		{
			bool postexists = false;
			char* selection = new char[pInput.length() + 1]; // Allocate memory for the char array
			// Using strcpy_s
			strcpy_s(selection, pInput.length() + 1, pInput.c_str());
			for (int j = 0; j < nPosts; j++) {
				if (helper::compareStrings(selection, posts[j]->getPostId())) {
					posts[j]->addedLikes(window,tFont,font);
					postexists = true;
					window.draw(cat5);
				}
			}
			if (postexists == false)
			{
				promptText.setString("post not found");
				window.draw(promptText);
				window.draw(cat3);
			}

			delete[] selection;
			window.draw(currentDate);
			window.draw(pressEnter);
		}
		else if (commentOnPost)
		{
			promptText.setString("Enter the ID of the post to comment:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(pText);
			for (const auto& text : postTexts) {
				window.draw(text);
			}
			window.draw(currentDate);
		}
		else if (cTextBool)
		{
			promptText.setString("Enter the text for your comment:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(cat6);
			window.draw(cText);
			window.draw(currentDate);
		}
		else if (commentAdded == true)
		{
			window.draw(postFound);
			if (angry == true)
			{
				window.draw(cat3);
			}
			else
				window.draw(cat1);
			window.draw(pressEnter);
			window.draw(currentDate);
		}
		else if (seePost == true)
		{
			promptText.setString("Enter the ID of the post to comment:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(pText);
			for (const auto& text : postTexts) {
				window.draw(text);
			}
			window.draw(currentDate);

		}
		else if (showPost == true)
		{
			selection = new char[pInput.length() + 1]; // Allocate memory for the char array
			strcpy_s(selection, pInput.length() + 1, pInput.c_str());
			for (int j = 0; j < nPosts; j++) {
				if (helper::compareStrings(selection, posts[j]->getPostId())) {
					posts[j]->viewPost(window,tFont,font);
					postIDFound = true;
				}
			}
			if (postIDFound == false)
			{
				postFound.setString("post not found");
				window.draw(cat3);
				window.draw(postFound);
			}
			else
			{
				window.draw(cat5);
			}
			delete[] selection;
			postIDFound = false;
			window.draw(pressEnter);
			window.draw(currentDate);
		}
		else if (addMemory)
		{
			promptText.setString("Enter the ID of the post to share a Memory:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(pText);
			for (const auto& text : postTexts) {
				window.draw(text);
			}
			window.draw(currentDate);

		}
		else if (addMemoryText)
		{
			promptText.setString("Enter the text for your memory:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(cat4);
			window.draw(cText);
			window.draw(currentDate);

		}
		else if (mAdded)
		{
			window.draw(postFound);
			if(angry)
			window.draw(cat3);
			else
			{
				window.draw(cat6);
			}
			window.draw(pressEnter);
			window.draw(currentDate);
			}
		else if (displayTimeline)
		{
			currentUser->displayTimeLine(window,tFont,font);
			pressEnter.setCharacterSize(35);
			pressEnter.setPosition(450.f, 750.f);
			window.draw(pressEnter);
			window.draw(currentDate);
		}
		else if (seeFriends)
		{
			currentUser->printFriends(window,tFont,font);
			window.draw(pressEnter);
			window.draw(currentDate);
			window.draw(cat5);
		}
		else if (seeLikedPages)
		{
			currentUser->printLikedPages(window,tFont,font);
			window.draw(pressEnter);
			window.draw(currentDate);
			window.draw(cat5);
		}
		else if (seePage)
		{
			promptText.setString("Enter the ID of the page you want to view:");
			window.draw(promptText);
			window.draw(inputBox);
			window.draw(pText);
			for (const auto& text : pageTexts) {
				window.draw(text);
			}
			window.draw(currentDate);
		}
		else if (foundPage)
		{
			selection = new char[pInput.length() + 1]; // Allocate memory for the char array
			// Using strcpy_s
			strcpy_s(selection, pInput.length() + 1, pInput.c_str());
			for (int j = 0; j < nPages; j++) {
				if (helper::compareStrings(selection, pages[j]->getPageId())) {
					pages[j]->displayHomePage(window,tFont,font);
					postIDFound = true; // Set flag if post ID is found
				}
			}
			if (postIDFound == false)
			{
				postFound.setString("page not found");
				window.draw(postFound);
				window.draw(cat3);
			}
			else {
				window.draw(cat1);
			}
			postIDFound = false;
			window.draw(pressEnter);
			window.draw(currentDate);
			delete[] selection;
			}
		else if (closeWindow)
		{
			promptText.setString("Until next time");
			window.draw(promptText);
			window.draw(pressEnter);
			window.draw(cat2);
		}
		// Display the window
		window.display();
		
	}
	delete[] select;
	select = nullptr;
	delete[] text;
	text = nullptr;
	if (currentUser != nullptr)
	{
		currentUser = nullptr;
	}
}

void socialNetworkApp::deleteArrays()
{
	for (int i = 0; i < use; i++)
	{
		delete users[i];
	}
	delete[] users;
	users = nullptr;
	for (int i = 0; i < nPages; i++)
	{
		delete pages[i];
	}
	delete[] pages;
	pages = nullptr;
	for (int i = 0; i < nPosts; i++)
	{
		delete posts[i];
	}
	delete[] posts;
	posts = nullptr;
	for (int i = 0; i < nComments; i++)
	{
		delete rComments[i];
	}
	delete[] rComments;
	rComments = nullptr;
	for (int i = 0; i < nMemories; i++)
	{
		delete memories[i];
	}
	delete[] memories;
	memories = nullptr;
}