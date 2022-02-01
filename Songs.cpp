#include "Songs.h"

bool Songs::hasSong(string songTitle) //check if the song is already in the song collection
{
	if (head == NULL) {
		return false;
	}
	song* current = head;
	while (current != NULL) {
		if (songTitle == current->title) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void Songs::addSong()
{
	string songTitle;
	cout << "Enter new song title: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, songTitle);
	if (Songs::hasSong(songTitle)) {
		cout << "Song (" << songTitle << ") is already in the collection!!" << endl;
		return;
	}
	song* newNode = new song;
	newNode->title = songTitle;
	cout << "Enter the singer: ";
	getline(cin, newNode->singer);
	cout << "Enter song duration (in seconds): ";
	cin >> newNode->duration;
	while (cin.fail()) {
		cout << "Enter song duration (in seconds): ";
		cin.clear();
		cin.ignore();
		cin >> newNode->duration;
	}
	cout << "Song (" << songTitle << ") added successfully." << endl;
	newNode->next = head;
	head = newNode;
}

void Songs::displaySong()
{
	int n = 0;
	if (head != NULL) {
		cout << "Songs Collection :" << endl;
		song* current = head;
		while (current != NULL) {
			cout << n + 1 << ". " << current->title << " (";
			cout << current->duration << "s) ------ ";
			cout << current->singer << endl;
			current = current->next;
			n++;
		}
		cout << "Total " << n << " song(s) in collection." << endl;
	}
	else
		cout << "No song in the collection!" << endl;
}
