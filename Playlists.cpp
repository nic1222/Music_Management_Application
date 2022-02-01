#include "Playlists.h"

bool Playlists::hasPlaylistSong(string songTitle) //check if the song is already in the playlist
{
	if (head2 == NULL) {
		return false;
	}
	playlistSong* current = head2;
	while (current != NULL) {
		if (songTitle == current->song) {
			return true;
		}
		current = current->next;
	}
	return false;
}

bool Playlists::findPlaylist(string playlistName) { //check if the playlist is existed
	playlist* current = headPlaylist;
	while (current != NULL) {
		if (playlistName == current->playlistTitle) {
			return true;
			break;
		}
		current = current->next;
	}
	return false;
}


void Playlists::createPlaylist() {
	string playlistTitle;
	cout << "Enter a new playlist title to create: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, playlistTitle);
	if (headPlaylist != NULL) {
		if (Playlists::findPlaylist(playlistTitle)) {
			cout << "Playlist (" << playlistTitle << ") is existed!!" << endl;
		}
	}
	if (headPlaylist == NULL || !Playlists::findPlaylist(playlistTitle)) {
		playlist* newNode = new playlist;
		newNode->playlistTitle = playlistTitle;
		newNode->head2 = NULL;
		newNode->next = headPlaylist;
		headPlaylist = newNode;
		cout << "Playlist (" << playlistTitle << ") created successfully." << endl;
	}
}

void Playlists::viewPlaylist() {
	int size = 0;
	if (headPlaylist != NULL) {
		playlist* current = headPlaylist;
		cout << "Playlist(s): " << endl;
		while (current != NULL) {
			cout << size + 1 << ". " << current->playlistTitle << endl;
			size++;
			current = current->next;
		}
		cout << endl;
		cout << "Total " << size << " playlists." << endl;
	}
	else
		cout << "No playlist existed!" << endl;
}

void Playlists::viewPlaylistSong() {
	string p;
	int size = 0;
	bool playlistFound = false;
	cout << "Enter a playlist to view: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, p);
	playlist* pcurrent = headPlaylist;
	while (pcurrent != NULL) {
		if (p == pcurrent->playlistTitle) {
			playlistFound = true;
			break;
		}
		pcurrent = pcurrent->next;
	}
	if (playlistFound) {
		playlistSong* scurrent = pcurrent->head2;
		if (pcurrent->head2 != NULL) {
			cout << "Playlist (" << p << ") song(s): " << endl;
			while (scurrent != NULL) {
				cout << size + 1 << ". " << scurrent->song << endl;
				size++;
				scurrent = scurrent->next;
			}
			cout << "\nTotal " << size << " song(s)." << endl;
		}else
			cout << "No song in the playlist!" << endl;

	}
	else {
		cout << "Can't find the playlist..." << endl;
	}
}

void Playlists::deletePlaylistSong() {
	string p, song;
	bool found = false, pfound = false;
	cout << "Enter a playist to remove song: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, p);
	playlist* current = headPlaylist;
	while (current != NULL) {
		if (p == current->playlistTitle) {
			found = true;
			break;
		}
		current = current->next;
	}
	if (found) {
		cout << "Enter a song to remove from Playlist (" << p << "): ";
		getline(cin, song);
			playlistSong* sprev = NULL, * stoDelete = current->head2;
			while (stoDelete != NULL) {
				if (song == stoDelete->song) {
					pfound = true;
					break;
				}
				sprev = stoDelete;
				stoDelete = stoDelete->next;
			}
			if (pfound) {
				if (stoDelete == current->head2) {
					current->head2 = current->head2->next;
					delete stoDelete;
				}
				else {
					sprev->next = stoDelete->next;
					delete stoDelete;
				}
			}else
				cout << "Song (" << song << ") not existed in Playlist (" << p << ")." << endl;
		cout << "Song (" << song << ") is removed from Playlist (" << p << ")." << endl;
	}else
		cout << "Can't find the playlist..." << endl;
	
}

void Playlists::deletePlaylist() {
	string p;
	bool found = false;
	if (headPlaylist != NULL) {
		cout << "Enter a playlist to delete: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, p);
		if (Playlists::findPlaylist(p)) {
			playlist* prev = NULL, * toDelete = headPlaylist;
			while (toDelete != NULL) {
				if (toDelete->playlistTitle == p) {
					found = true;
					break;
				}
				prev = toDelete;
				toDelete = toDelete->next;
			}
			if (found) {
				if (toDelete == headPlaylist) {
					headPlaylist = headPlaylist->next;
					delete toDelete;
				}
				else {
					prev->next = toDelete->next;
					delete toDelete;
				}
				cout << "Playlist (" << p << ") is deleted!" << endl;
			}
		}
		else {
			cout << "Playlist (" << p << ") not found!" << endl;
		}
	}
	else
		cout << "No playlist existed." << endl;
}
