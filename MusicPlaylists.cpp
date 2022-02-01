#include<iostream>;
#include<string>;
#include"Songs.h";
#include"Playlists.h";
using namespace std;

Songs songs;
Playlists playlists;
void deleteSong();
void playlistSearch();
void addSongToPlaylist();
void playlistNavigation();

int main() 
{
	int opt = 0;
	do {
		cout << "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		cout << "|                                                              |" << endl;
		cout << "| ----------------- Welcome to Apple Music.. ----------------- |" << endl;
		cout << "|                                                              |" << endl;
		cout << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" << endl;
		cout << " ---------------------- Song Collection ----------------------" << endl;
		cout << "1.  Add Song\n2.  Display Song\n3.  Delete Song\n4.  Playlist Search" << endl;
		cout << " ------------------------- Playlists -------------------------" << endl;
		cout << "5.  Create Playlist\n6.  View Playlist\n7.  Delete Playlist\n8.  Add Song into Playlist\n9.  View Playlist Song(s)\n10. Delete Playlist Song\n11. Playlist Navigation\n0.  Exit" << endl;
		cin >> opt;

		while (cin.fail() || opt < 0 || opt > 11)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Input... Try again!" << endl;
			cin >> opt;
		}

		switch (opt) {
		case 1:
			songs.addSong();
			break;
		case 2:
			songs.displaySong();
			break;
		case 3: 
			deleteSong();
			break;
		case 4: 
			playlistSearch();
			break;
		case 5:
			playlists.createPlaylist();
			break;
		case 6:
			playlists.viewPlaylist();
			break;
		case 7: 
			playlists.deletePlaylist();
			break;
		case 8:
			addSongToPlaylist();
			break;
		case 9:
			playlists.viewPlaylistSong();
			break;
		case 10: 
			playlists.deletePlaylistSong();
			break;
		case 11:
			playlistNavigation();
			break;
		case 0:
			return 0;
		}
	} while (true);
}

void deleteSong() {
	string songTitle;
	bool found = false;
	bool foundPlaylistSong = false;
	bool pfound = false;
	if (songs.head != NULL) {
		cout << "Enter the song title to delete: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, songTitle);
		song* prev = NULL, * toDelete = songs.head; //delete song in collection
		while (toDelete != NULL) {
			if (toDelete->title == songTitle) {
				found = true;
				break;
			}
			prev = toDelete;
			toDelete = toDelete->next;
		}
		if (found) {
			playlist* current = playlists.headPlaylist; //delete song in playlist
			while (current != NULL) {
				playlistSong* sprev = NULL, * stoDelete = current->head2;
				while (stoDelete != NULL) {
					if (songTitle == stoDelete->song) {
						pfound = true;
						break;
					}
					sprev = stoDelete;
					stoDelete = stoDelete->next;
				}
				if (pfound) {
					if (stoDelete == current->head2 && current->head2!= NULL) {
						current->head2 = current->head2->next;
						delete stoDelete;
					}
					else if(sprev!=NULL) {
						sprev->next = stoDelete->next;
						delete stoDelete;
					}
				}
				current = current->next;
			}
			
			if (toDelete == songs.head) { //delete song in collection
				songs.head = songs.head->next;
				delete toDelete;
			}
			else {
				prev->next = toDelete->next;
				delete toDelete;
			}
			
			cout << "Song (" << songTitle << ") is deleted from collection and playlist." << endl;
		}
		else {
			cout << "Song (" << songTitle << ") not found!" << endl;
		}
	}
	else
		cout << "No song in the collection!" << endl;
}

void playlistSearch() {
	string songTitle;
	bool found;
	cout << "Enter a song to search for playlist: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, songTitle);
	if (songs.hasSong(songTitle)) {
		cout << songTitle << " - ";
		playlist* current = playlists.headPlaylist;
		while (current != NULL) {
			playlistSong* scurrent = current->head2;
			while (scurrent != NULL) {
				if (songTitle == scurrent->song) {
					cout << current->playlistTitle << ", ";
				}
				scurrent = scurrent->next;
			}
			current = current->next;
		}
	}
	else
		cout << "Song (" << songTitle << ") is not in the collection";
}

void addSongToPlaylist() {
	string playlistTitle, songToAdd;
	bool playlistFound = false, songInCollection = false, duplicate = false;
	playlistSong* scurrent = playlists.head2;
	playlist* playlistcurrent = playlists.headPlaylist;
	song* ccurrent = songs.head;
	cout << "Enter a playlist: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, playlistTitle);
	while (playlistcurrent != NULL) {
		if (playlistcurrent->playlistTitle == playlistTitle) {
			playlistFound = true;
			break;
		}
		playlistcurrent = playlistcurrent->next;
	}
	if (playlistFound) {
		cout << "Enter a song to add into the playlist: ";
		getline(cin, songToAdd);
		while (ccurrent != NULL) {
			if (ccurrent->title == songToAdd) {
				songInCollection = true;
				break;
			}
			ccurrent = ccurrent->next;
		}
		if (songInCollection) {
			scurrent = playlistcurrent->head2;
			if (scurrent != NULL) {
				while (scurrent != NULL) {
					if (songToAdd == scurrent->song) {
						duplicate = true;
						break;
					}
					scurrent = scurrent->next;
				}
			}
			if (scurrent == NULL || duplicate == false) {
				playlistSong* newNode = new playlistSong;
				newNode->song = ccurrent->title;
				newNode->singer = ccurrent->singer;
				newNode->duration = ccurrent->duration;
				newNode->next = playlistcurrent->head2;
				playlistcurrent->head2 = newNode;
				cout << "Song (" << songToAdd << ") is added into Playlist (" << playlistTitle << ")." << endl;
			}
			else {
				cout << "Song (" << songToAdd << ") is already in the Playlist (" << playlistTitle << ")." << endl;
			}

		}
		else {
			cout << "Song (" << songToAdd << ") is not in the collection!!" << endl;
		}
	}
	else {
		cout << "Can't find the playlist..." << endl;
	}
}

void playlistNavigation() {
	int opt = 0;
	bool songPlaying = false, playlistFound = false;
	string playlistTitle;
	cout << "Enter a playlist: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, playlistTitle);
	playlist* pcurrent = playlists.headPlaylist;
	while (pcurrent != NULL) {
		if (playlistTitle == pcurrent->playlistTitle) {
			playlistFound = true;
			break;
		}
		pcurrent = pcurrent->next;
	}
	if (playlistFound) {
		playlistSong* prev = NULL, * current = pcurrent->head2;
		if (current != NULL) {
			do {
				cout << "\n_______ Playlist Navigation - " << playlistTitle << " _______" << endl;
				cout << "1. Play / Pause\n2. Next Song\n3. Previous Song\n4. Exit to Main Menu" << endl;
				cin >> opt;

				while (cin.fail() || opt < 0 || opt > 4)
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid Input... Try again!" << endl;
					cin >> opt;
				}
				switch (opt) {
				case 1:
					if (songPlaying == false) {
						cout << "\tNow playing ----- " << current->song << endl;
						songPlaying = true;
					}
					else {
						cout << "\tPause ----- " << current->song << endl;
						songPlaying = false;
					}
					break;
				case 2:
					if (current->next != NULL) {
						prev = current;
						current = current->next;
						cout << "\tNext Song --- " << current->song << endl;
					}
					else
						cout << "\t" << current->song << " is the last song of Playlist (" << playlistTitle << ")." << endl;
					break;
				case 3:
					if (current != pcurrent->head2) {
						prev = pcurrent->head2;
						while (prev->next != current) {
							prev = prev->next;
						}
						current = prev;
						cout << "\tPrevious Song --- " << current->song << endl;
					}
					else
						cout << "\t" << current->song << " is the first song of Playlist (" << playlistTitle << ")." << endl;
					break;
				case 4:
					return;
				}
			} while (true);
		}
		else {
			cout << "Playlist (" << playlistTitle << ") is empty." << endl;
		}
	}
	else {
		cout << "Can't find the playlist..." << endl;
	}
}