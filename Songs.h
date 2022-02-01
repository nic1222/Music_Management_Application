#pragma once
#include<iostream>
#include<string>
using namespace std;

struct song
{
	string title, singer;
	double duration;
	song* next;
};

class Songs
{
public:
	song* head = NULL;
	bool hasSong(string songTitle);

	void addSong();
	void displaySong();
};

