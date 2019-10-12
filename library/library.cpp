#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

#include "../includes_usr/library.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/fileIO.h"
using namespace std;

//NOTE: please ensure patron and book data are loaded from disk before calling the following
//NOTE: also make sure you save patron and book data to disk any time you make a change to them
//NOTE: for files where data is stored see constants.h BOOKFILE and PATRONFILE
std::vector<book> books;
std::vector<patron> patrons;
/*
 * clear books and patrons containers
 * then reload them from disk 
 */
void reloadAllData(){
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, BOOKFILE.c_str());
}

/* checkout a book to a patron
 * first load books and patrons from disk
 * make sure patron enrolled (patronid is assigned to a patron in patrons container)
 * make sure book in collection (bookid is assigned to a book in books container)
 * 
 * see if patron can check out any more books 
 * 	if not return TOO_MANY_OUT patron has the MAX_BOOKS_ALLOWED_OUT
 * 	
 * if so then check the book out to the patron, set the following fields for the book in the
 * books container
 * book.loaned_to_patron_id = patronid;
 * book.state = OUT;
 * 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 *         PATRON_NOT_ENROLLED
 * 		   BOOK_NOT_IN_COLLECTION
 *         TOO_MANY_OUT patron has the max number of books allowed checked out
 */
int checkout(int bookid, int patronid){
	int bok = -5;
	int patrn = -5;
	bool patronIsValid = false;
	bool bookIsValid = false;
	for(unsigned int i = 0;i<books.size();i++){
		if(bookid == books[i].book_id){
			bok = i;
			bookIsValid = true;
		}
	}
	for(unsigned int i = 0;i<patrons.size();i++){
		if(patronid == patrons[i].patron_id){
			patrn = i;
			patronIsValid = true;
		}
	}
	if(!patronIsValid){
		return PATRON_NOT_ENROLLED;
	}
	if(!bookIsValid){
		return BOOK_NOT_IN_COLLECTION;
	}
	if(patrons[patrn].number_books_checked_out >= MAX_BOOKS_ALLOWED_OUT){
		return TOO_MANY_OUT;
	}else{
		patrons[patrn].number_books_checked_out++;
	}
	books[bok].loaned_to_patron_id = patronid;
	books[bok].state = OUT;
	saveBooks(books, BOOKFILE.c_str());
	savePatrons(patrons, PATRONFILE.c_str());
	return SUCCESS;
}

/* check a book back in 
 * first load books and patrons from disk
 * make sure book in collection (bookid is assigned to a book in books container)
 *  	
 * if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
 * then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;
 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 * 		   BOOK_NOT_IN_COLLECTION
 */
int checkin(int bookid){
	bool bookIsValid = false;
	int book = -5;
	//int patron = -5;
	reloadAllData();
	/*if(books.size()>0 && patrons.size()>0){

	}*/
	for(unsigned int i = 0;i<books.size();i++){
		if(books[i].book_id == bookid){
			book = i;
			bookIsValid = true;
		}
	}
	if(!bookIsValid){
		return BOOK_NOT_IN_COLLECTION;
	}
	for(unsigned int i = 0;i<patrons.size();i++){
			if(patrons[i].patron_id == bookid){
				patrons[i].number_books_checked_out--;
			}
		}

	books[book].loaned_to_patron_id = NO_ONE;
	books[book].state = IN;
	saveBooks(books, BOOKFILE.c_str());
	savePatrons(patrons, PATRONFILE.c_str());
	return SUCCESS;
}

/*
 * enroll a patron, duplicate names are fine as patrons are uniquely identified by their patronid
 * first load books and patrons from disk
 * create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
 * then push the patron onto the patrons container
 * save all changes to the patrons container to disk
 * return 
 *    the patron_id of the person added
 */
int enroll(std::string &name){
	reloadAllData();
	patron pat;
	pat.name = name;
	pat.number_books_checked_out = 0;
	pat.patron_id = patrons.size();
	patrons.push_back(pat);
	savePatrons(patrons, PATRONFILE.c_str());
	return pat.patron_id;
}

/*
 * the number of books in the books container
 * (ie. if 3 books returns 3)
 * 
 */
int numbBooks(){
	return books.size();
}

/*
 * the number of patrons in the patrons container
 * (ie. if 3 patrons returns 3)
 */
int numbPatrons(){
	return patrons.size();
}

/*the number of books patron has checked out
 *
 *returns a positive number indicating how many books are checked out 
 *        or PATRON_NOT_ENROLLED         
 */
int howmanybooksdoesPatronHaveCheckedOut(int patronid){
	for(patron pat:patrons){
		if(pat.patron_id == patronid){
			return pat.number_books_checked_out;
		}
	}
	return PATRON_NOT_ENROLLED;
}

/* search through patrons container to see if patronid is there
 * if so returns the name associated with patronid in the variable name
 * 
 * returns SUCCESS found it and name in name
 *         PATRON_NOT_ENROLLED no patron with this patronid
 */
int whatIsPatronName(std::string &name,int patronid){
	bool found = false;
	for(patron pat:patrons){
			if(pat.patron_id == patronid){
				name = pat.name;
				found = true;
			}
		}
	if(!found){
		return PATRON_NOT_ENROLLED;
	}
	return SUCCESS;
}

