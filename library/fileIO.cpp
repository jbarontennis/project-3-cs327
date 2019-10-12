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
books.clear();
	fstream myfile;
	string line;
	string test;
	try{
		myfile.open(filename,ios::in);
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
						if(tracker>4){
							return BOOK_NOT_IN_COLLECTION;
						}
						info[tracker] = token;
						tracker++;
					}
					book bok;
					bok.book_id = stoi(info[0]);
					bok.title = info[1];
					bok.author = info[2];
					if (info[3] == "0") {
						bok.state = UNKNOWN;
					} else if (info[3] == "1") {
						bok.state = IN;
					} else if (info[3] == "2") {
						bok.state = OUT;
					}
					bok.loaned_to_patron_id = stoi(info[3]);
					books.push_back(bok);

			}
		}
		else{
			return COULD_NOT_OPEN_FILE;
					}
	}catch(exception& e){
		return COULD_NOT_OPEN_FILE;
	}
	myfile.close();
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
	myfile.open(filename,ios::trunc);
	if(myfile.is_open()){
		if(books.size() == 0){
			return NO_BOOKS_IN_LIBRARY;
		}
		for(book tmp:books){
			myfile<<to_string(tmp.book_id) + "," + tmp.title + "," + tmp.author + "," + to_string(tmp.state)+ ","+ to_string(tmp.loaned_to_patron_id) + "\n";
		}
	}
	else{
		return COULD_NOT_OPEN_FILE;
	}
	}catch(exception& e){
		return COULD_NOT_OPEN_FILE;
	}
	myfile.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();
	fstream myfile;
			string line;
			string test;
			try{
				myfile.open(filename,ios::in);
				if(myfile.is_open()){
					if(myfile.peek() == std::ifstream::traits_type::eof()){
						return NO_PATRONS_IN_LIBRARY;
					}
					while(myfile.peek()!=EOF){
						getline(myfile, line);
						string token;
							stringstream ss(line);
							string info[3];
							int tracker = 0;
							while(getline(ss, token, ',')){
								if(tracker>2){
									return PATRON_NOT_ENROLLED;
								}
								info[tracker] = token;
								tracker++;
							}
							patron bok;
							bok.patron_id = stoi(info[0]);
							bok.name = info[1];
							bok.number_books_checked_out = stoi(info[2]);
							patrons.push_back(bok);

					}
				}
				else{
					return COULD_NOT_OPEN_FILE;
							}
			}catch(exception& e){
				return COULD_NOT_OPEN_FILE;
			}
			myfile.close();
		return SUCCESS;


}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	ofstream myfile;
		try{
		myfile.open(filename,ios::trunc);
		if(myfile.is_open()){
			if(patrons.size() == 0){
				return NO_BOOKS_IN_LIBRARY;
			}
			for(patron tmp:patrons){
				myfile<<to_string(tmp.patron_id) + "," + tmp.name + "," + to_string(tmp.number_books_checked_out) + "\n";
			}
		}
		else{
			return COULD_NOT_OPEN_FILE;
		}
		}catch(exception& e){
			return COULD_NOT_OPEN_FILE;
		}
		myfile.close();
	return SUCCESS;
}
