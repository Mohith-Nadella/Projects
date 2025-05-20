#include<bits/stdc++.h>
using namespace std;
class Book{
    private:
    string isbn;
    int copiesAvailable;
    int totalCopies;
    public:
    string title;
    string author;
    // default constructor
    Book(){
        title="UnknownTitle";
        author= "UnknownAuthor";
        isbn="ISBN";
        copiesAvailable=0;
        totalCopies=5;

    }
    // constructor with all inputs
    Book(string t,string a,string i,int ca,int tc){
        title=t;
        author=a;
        isbn=i;
        copiesAvailable=ca;
        totalCopies=tc;
    }
    //constructor for copying other book
    Book(Book &b,string new_isbn){
        title=b.title;
        author=b.author;
        isbn=new_isbn;
        copiesAvailable=b.copiesAvailable;
        totalCopies=b.totalCopies;
    }
    // getter functions
    string get_isbn(){
        return isbn;
    }
    int get_copiesAvailable(){
        return copiesAvailable;
    }
    int get_totalCopies(){
        return totalCopies;
    }
    // function for updating copies
    void updateCopies(int change_in_copies){
        if(copiesAvailable+change_in_copies<0||totalCopies+change_in_copies<0){
            cout<<"Invalid request! Count becomes negative"<<endl;
            return ;
        }else{
            copiesAvailable+=change_in_copies;
            totalCopies+=change_in_copies;
        }
    }
    // checking borrowbook is valid
    bool borrowBook(){
        if(copiesAvailable>0){
            copiesAvailable--;
            return true;
        }else{
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
    }
    // checking return book is valid
    bool returnBook(){
        if(copiesAvailable<totalCopies){
            copiesAvailable++;
            return true;
        }else{
            cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
            return false;
        }
    }
    // function for printing details
    void printDetails(){
        cout<<title<<" "<<author<<endl;
    }
};
class Member{
    private:
    string memberId;
    map<string,int> borrowedBooks;
    int borrowLimit;
    public:
    string name;
    //default constructor
    Member(){}
    // constructor with all arguments
    Member(string mi,string mn,int bl){
        memberId=mi;
        name=mn;
        borrowLimit=bl;
    }
    // constructor with no borrow limit
    Member(string mi,string mn){
        memberId=mi;
        name=mn;
        borrowLimit=3;
    }
    //getter function for memberId;
    string get_ID(){
        return memberId;
    }
    //checking borrowbook is valid
    bool borrowBook(string req_isbn){
        if(borrowLimit>0){
            borrowedBooks[req_isbn]++;
            borrowLimit--;
            return true;
        }else{
            cout<<"Invalid request! Borrow limit exceeded"<<endl;
            return false;
        }
    }
    // checking returnbook is valid
    bool returnBook(string req_isbn){
        if(borrowedBooks.find(req_isbn)!=borrowedBooks.end()){
            borrowedBooks[req_isbn]--;
            if(borrowedBooks[req_isbn]==0){
                borrowedBooks.erase(req_isbn);
            }
            borrowLimit++;
            return true;
        }else{
            cout<<"Invalid request! Book not borrowed"<<endl;
            return false;
        }
    }
    // print function to print member details
    void printDetails(){
        for(auto itr:borrowedBooks){
            cout<<memberId<<" "<<name<<" "<<itr.first<<" "<<itr.second<<endl;
        }
    }

};
class Library{
    private:
    vector<Book> books;
    vector<Member> members;
    // maps for mapping (isbn,book) and (memberId,member)
    map<string,Book*> isbn_book;
    map<string,Member*> id_member;
    public:
    // variables for no of different books and no of members
    int ib=0;
    int im=0;
    //default function
    Library(){
        books.resize(50);
        members.resize(150);
    }
    // getter functions for maps
    map<string,Book*> get_isbn_book(){
        return isbn_book;
    }
    map<string,Member*> get_id_member(){
        return id_member;
    }
    //function for adding book
    bool addBook(Book& newBook){
        string newbook_isbn=newBook.get_isbn();
        if(isbn_book.find(newbook_isbn)==isbn_book.end()){
            books[ib]=newBook;
            isbn_book[newbook_isbn]=&books[ib];
            ib++;
            return true;
        }else{
            cout<<"Invalid request! Book with same isbn already exists"<<endl;
            return false;
        }
    }
    //function for registering member
    bool registerMember(Member& newMember){
        string newMember_ID=newMember.get_ID(); 
        if(id_member.find(newMember_ID)==id_member.end()){
            members[im]=newMember;
            id_member[newMember_ID]=&members[im];
            im++;
            return true;
        }else{
            cout<<"Invalid request! Member with same id already exists"<<endl;
            return false;
        }
    }
    // function to assign book to member
    bool borrowBook(string memID, string bookISBN){
        if(isbn_book.find(bookISBN)==isbn_book.end())
        return false;
        bool book_available=isbn_book[bookISBN]->borrowBook();
        if(!book_available){
            return false;
        }
        if(id_member.find(memID)==id_member.end())
        return false;
        bool member_can_borrow=id_member[memID]->borrowBook(bookISBN);
        if(!member_can_borrow){
            isbn_book[bookISBN]->returnBook();
            return false;
        }
        return true;
    }
    // function for returning the book
    bool returnBook(string memID,string bookISBN){
        if(isbn_book.find(bookISBN)==isbn_book.end())
        return false;
        bool book_can_be_returned=isbn_book[bookISBN]->returnBook();
        if(!book_can_be_returned){
            return false;
        }
        if(id_member.find(memID)==id_member.end())
        return false;
        bool member_have_that_book=id_member[memID]->returnBook(bookISBN);
        if(!member_have_that_book){
            isbn_book[bookISBN]->borrowBook();
            return false;
        }
        return true;
    }
    //print function to print library details
    void printLibraryDetails(){
        for(int i=0;i<ib;i++){
            cout<<books[i].title<<" "<<books[i].author<<" "<<books[i].get_copiesAvailable()<<endl;
        }
        for(int i=0;i<im;i++){
            cout<<members[i].get_ID()<<" "<<members[i].name<<endl;
        }
    }

};
int main() {
    Library lib;
    string s;
    while(cin>>s){
        if(s=="Book"){
            string s1;
            cin>>s1;
            if(s1=="None"){
                Book b;
                lib.addBook(b);
            }else if(s1=="ExistingBook"){
                string old_isbn,new_isbn;
                cin>>old_isbn>>new_isbn;
                Book* existing_book=lib.get_isbn_book()[old_isbn];
                Book b(*existing_book,new_isbn);
                lib.addBook(b);
            }else{
                string a,i;
                int ca,tc;
                cin>>a>>i>>ca>>tc;
                Book b(s1,a,i,ca,tc);
                lib.addBook(b);
            }
        }else if(s=="UpdateCopiesCount"){
            string updating_book_isbn;
            int newcount;
            cin>>updating_book_isbn>>newcount;
            Book *b=lib.get_isbn_book()[updating_book_isbn];
            b->updateCopies(newcount);
        }else if(s=="Member"){
            string s1;
            cin>>s1;
            if(s1=="NoBorrowLimit"){
                string id,n;
                cin>>id>>n;
                Member m(id,n);
                lib.registerMember(m);
            }else{
                string n;
                int bl;
                cin>>n>>bl;
                Member m(s1,n,bl);
                lib.registerMember(m);
            }
        }else if(s=="Borrow"){
            string id,i;
            cin>>id>>i;
            lib.borrowBook(id,i);
        }else if(s=="Return"){
            string id,i;
            cin>>id>>i;
            lib.returnBook(id,i);
        }else if(s=="PrintBook"){
            string i;
            cin>>i;
           lib.get_isbn_book()[i]->printDetails();
        }else if(s=="PrintMember"){
            string id;
            cin>>id;
            lib.get_id_member()[id]->printDetails();
        }else if(s=="PrintLibrary"){
            lib.printLibraryDetails();
        }else if(s=="Done"){
            break;
        }
    }
    return 0;
}
