#pragma once
class user;
class post;
class page;

class comment
{
private:
	char* cId;
	user* cOwner;
	char* cText;
	post* cPost;
	page* cPage;
	bool runtime;

public:
	comment();
	comment(char*, char*);
	void setcId(char*);
	char* getcId();
	void setcText(char*);
	char* getcText();
	void setcOwner(user*);
	void setcPost(post*);
	user* getcOwner();
	post* getcPost();
	void setcPage(page*);
	page* getcPage();
	void printComment();
	~comment();
	void setRuntime(bool);
	bool getRuntime();
	char* getCommentText();

};