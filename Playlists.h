#pragma once
#include<iostream>;
#include<string>;
using namespace std;

struct playlistSong {
	string song, singer;
	double duration;
	playlistSong* next;
};

struct playlist {
	string playlistTitle;
	playlistSong* head2;
	playlist* next;
};

class Playlists
{
public:
	playlist* headPlaylist = NULL;
	playlistSong* head2;
	bool hasPlaylistSong(string songTitle);
	bool findPlaylist(string playlistName);

	void createPlaylist();
	void viewPlaylist();
	void viewPlaylistSong();
	void deletePlaylistSong();
	void deletePlaylist();
};


