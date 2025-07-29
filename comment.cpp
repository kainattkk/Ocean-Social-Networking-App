#include"comment.h"
#include"user.h"
#include"helper.h"
#include"post.h"
#include<iostream>
using namespace std;

comment::comment()
{
	cId = nullptr;
	cText = nullptr;
	cOwner=nullptr;
	cPost=nullptr;
	cPage = nullptr;
	runtime = false;
}
comment::comment(char* ids,char* names)
{
	int length = 0;
	length = helper::GetLength(ids);
	this->cId = new char[length + 1];
	helper::copyString(cId, ids, length);
	length = 0;
	length = helper::GetLength(names);
	this->cText = new char[length + 1];
	helper::copyString(cText, names, length);
	cOwner=nullptr;
	cPost=nullptr;
	cPage = nullptr;
	runtime = false;
}
comment::~comment()
{
	cout << "comment destructor called" << endl;
	if (this->cId != nullptr)
	{
		delete[] cId;
		cId = nullptr;
	}
	if (this->cText != nullptr)
	{
		delete[] cText;
		cText = nullptr;
	}
	cOwner = nullptr;
	cPage = nullptr;
	cPost = nullptr;
}
void comment::setcId(char* ids)
{
	if (cId != nullptr)
		delete[] cId;
	int length = 0;
	length = helper::GetLength(ids);
	this->cId = new char[length + 1];
	helper::copyString(cId, ids, length);
}
void comment::setcText(char* names)
{
	if (cText != nullptr)
		delete[] cText;
	int length = 0;
	length = helper::GetLength(names);
	this->cText = new char[length + 1];
	helper::copyString(cText, names, length);
}
char* comment::getcId()
{
	return cId;
}
char* comment::getcText()
{
	return cText;
}

void comment::setcOwner(user* obj)
{
	cOwner = obj;
}
void comment::setcPost(post* obj)
{
	
	cPost = obj;
}
void comment::setcPage(page* obj)
{
	cPage = obj;
}
user* comment::getcOwner()
{
	if (this != nullptr)
		return cOwner;
	else return nullptr;
}
page* comment::getcPage()
{
	if (this != nullptr)
		return cPage;
	else return nullptr;

}
post* comment::getcPost()
{
	if (this != nullptr)
		return cPost;
	else return nullptr;
}

void comment::printComment()
{
	
	cout << "\""<<cText << "\""<<endl;
}

void comment::setRuntime(bool b)
{
	runtime = b;
}

bool comment::getRuntime()
{
	return runtime;
}
char* comment::getCommentText()
{
	return cText;
}