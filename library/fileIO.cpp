#include "../includes_usr/fileIO.h"
#include <fstream>
#include <sstream>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	fstream myfile;
	string line;
	string test;
	try{
		myfile.open(filename);
		if(myfile.is_open()){
			if(myfile.peek() == std::ifstream::traits_type::eof()){
				return NO_BOOKS_IN_LIBRARY;
			}
			while(myfile.peek()!=EOF){
				getline(myfile, line);
				string token;
					stringstream ss(line);
					string info[5];
					int tracker = 0;
					while(getline(ss, token, ',')){
						info[tracker] = token;
						tracker++;
					}
					book bok;
					bok.book_id = stoi(info[0]);
					bok.title = info[1];
					bok.author = info[2];
					books.push_back(bok);

			}
		}
		else{
			return COULD_NOT_OPEN_FILE;
					}
	}catch(exception& e){
		return COULD_NOT_OPEN_FILE;
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream myfile;
	try{
	myfile.open(filename);
	if(myfile.is_open()){
		if(books.size() == 0){
			return NO_BOOKS_IN_LIBRARY;
		}
		for(book tmp:books){
			myfile<<tmp.book_id + "," + tmp.title + "," + tmp.author + "," + "1,-2" + "/n";
		}
	}
	else{
		return COULD_NOT_OPEN_FILE;
	}
	}catch(exception& e){
		return COULD_NOT_OPEN_FILE;
	}
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	return SUCCESS;
}
