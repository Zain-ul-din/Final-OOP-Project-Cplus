/*
  2nd Semeseter Project
  c++ Final Project Library Managment System
*/
#include<bits/stdc++.h>// This file includes all standard library
using namespace std;
// Class 
class Library{ // Parent Class
	public:
	Library(){}// default constructor
	 // paramatrized constructor
	 Library(string title,string writer,int id):title(title),writer_name(writer),book_id(id){
		time(&TimeNow); // Set Time to Now
		string str=ctime(&TimeNow); // Time Now to string
		for(auto it=str.begin();it!=(str.begin()+24);it++){
  	              publish_time.push_back(*it);// Copy in another string
                }
		in_stock=1;
		totalqt=1;
	}
	
	void To_Console(void) { // Display for all child's
		cout<<"\tBook Title : "<<this->title<<endl;
		cout<<"\tbook id : "<<this->book_id<<endl;
		cout<<"\tWriter Name : "<<this->writer_name<<endl;
		cout<<"\tIn Stock    : "<<this->in_stock<<endl;
		cout<<"\tTotal in Stock : "<<this->totalqt<<endl;
		cout<<"\tPublish Time : "<<this->publish_time<<endl;
	}
	
		// Set for all Child's
	void set_title(string it){title=it;}// set book Title
	void set_writer_name(string it) {writer_name=it;}// set WriterName
	void set_book_id(int it) {book_id=it;}// Set new id
	void set_time(string it) {publish_time=it;}// Set PublishTime
	
	string To_DataBase(void){ // Put Data to Files
		title.push_back('$');
		writer_name.push_back('$');
		stringstream ss;
		ss<<title<<writer_name<<book_id<<"$"<<totalqt<<"$"<<in_stock<<"$";
		return ss.str();
	}
	
	// return 
	string return_publish_time(void){ return publish_time;}
	int return_id(void){ return book_id;} // return Book id
	string return_title(void){return title;} // return Book title
	
	// set Stock
	unsigned int return_InStock(void) {return in_stock;}// return Stock in lib
	void set_bookqt(int it){// Set default value to new
	  totalqt=it; 
	  in_stock=it;
	}// set Total Qt
	void Add_qt( int it) {// Add new Qt
	  totalqt+=it; 
	  in_stock+=it;
	}
	void set_Instock( int it) {in_stock=it;}// while Fetching Data from file
	unsigned int return_TotalQt(void) {return totalqt;}// return Total
	void Issue_Book(void){in_stock=in_stock-1;}// Issue One Book
	void Add_InStock( int it){// Add Issue Book's Back
		in_stock+=it;
		in_stock = (in_stock > totalqt )? totalqt:in_stock;   
	}
    void Remove_Stock(int it){// Remove Book from Stock
    	in_stock = (it >in_stock)?0:(in_stock - it);
    	totalqt =  (it >totalqt)?0:(totalqt -it);
	}
	
	protected:// Var for all child
   	string title,writer_name; // book title , Writer Name 
   	string publish_time;// Time Now Using <time.h>
   	int book_id; // book id
   	time_t TimeNow;// Time Nowctime(&rawtime); 
   	int in_stock,totalqt;// in Stock or Total Book's
};// Super Class
class Programing_Books : public Library{// Child Class
public:
	// Constructor
    Programing_Books() {p_language="c++";}
    Programing_Books(string title,string writer,int id,string Language):Library(title,writer,id){
     this->p_language=Language;
    }
   // Display Super class Diplay + Tag Display
    void To_Console() {
     Library::To_Console();
     cout<<"\tPrograming Language : "<<p_language<<endl;// new in class
    }
  
  void set_p_language(string Language_Name){p_language=Language_Name;}// set
  
    string To_DataBase(void){// Put Data to Files (new Tag include)
 	p_language.push_back('$');
 	stringstream ss;
 	ss<<Library::To_DataBase()<<p_language<<publish_time;
 	return ss.str();
   }
   // return 
   string return_Tag(void){
   	return this->p_language;
   }
private:
	string p_language;// programing Langauge type
};
class Medical_Books : public Library{
	public:
	 // Constructor
	 Medical_Books () {about="Health";}
	 Medical_Books(string title,string writer,int id,string about):Library(title,writer,id),about(about){}
	 // Display
	 void To_Console() {// Super Class Toconsole +  Book Topic Toconsole
	 	Library::To_Console();
	 	cout<<"\tAbout : "<<about<<endl;
	 }
	 //set
	 void set_aboutBook(string it){
	 	this->about=it;
	 }
	 // return
	 string return_Tag(void){
	 	return about;
	 }
	 // Data base
	 string To_DataBase(void){// new about included
	 	about.push_back('$');
	 	stringstream ss;
	 	ss<<Library::To_DataBase()<<about<<publish_time;
	 	return ss.str();
	 }
	 private:
	 	string about; // Book Main Topic
};
class History_Books : public Library{
	public:
	 History_Books(string title,string writer,int id) : Library(title,writer,id) {} // Constructor
	// no thing new its use Super class Member's
};
class Islamic_Books : public Library{
	public:
	 Islamic_Books(string title,string writer,int id):Library(title,writer,id){} // Constructor
	// no thing new its use Super class Member's
};

/*         Algo Find Duplicate id             */
  template<class T>//using generics where,T is iterator
	bool CheckId(T first,T last,int &title){ // Check If Duplicate ID Found
		while(first != last){
			if(first->return_id()== title){
		       cout<<"\tId Already Taken ";
			   return true; // id Found
			}
			first++;
		}
		return false; // Id not Found
	}
	
/*           Function's             */
     // Add Books 
  void Add_ProgramingBook(vector<Programing_Books> &vec){//Add Programing Book
  	int id; string temp; unsigned int Qt;
  	string title,writer,language;// temp Var
  	cout<<"\tEnter Title of Book : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,title);
  	cout<<"\tEnter Writer Name : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,writer);
  	cout<<"\tEnter Id (Num) : ";
  	do {
       cin>>temp;
       id=stoi(temp);
	} while( CheckId(vec.begin(),vec.end(),id) );// while Duplicate Found
  	cout<<"\tEnter Programing Language Name : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,language);
  	cout<<"\tEnter Quantity of Book's : ";
  	cin>>Qt;
  	Programing_Books obj(title,writer,id,language);
  	obj.set_bookqt(Qt);
  	vec.push_back(obj);// add to our List
  }

  void Add_HistoryBook(vector<History_Books> &vec){// Add MEdical Book
  	int id; string temp; unsigned int Qt;
  	string title,writer,language;// temp Var
  	cout<<"\tEnter Title of Book : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,title);
  	cout<<"\tEnter Writer Name : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,writer);
  	cout<<"\tEnter Id (Num) : ";
  	do{
       cin>>temp;
       id=stoi(temp);
	 }while( CheckId(vec.begin(),vec.end(),id) );// while Duplicate Found
	 cout<<"\tEnter Quantity of Book's : ";
  	 cin>>Qt;
  	 History_Books obj(title,writer,id);
  	 obj.set_bookqt(Qt);
  	 vec.push_back(obj);// add to our List
  }
  
  void Add_MedicalBook(vector<Medical_Books> &vec){// Add History book's
  	int id; string temp; int Qt;
  	string title,writer,language,about;// temp Var
  	cout<<"\tEnter Title of Book : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,title);
  	cout<<"\tEnter Writer Name : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,writer);
  	cout<<"\tEnter Id (Num) : ";
  	do{
       cin>>temp;
       id=stoi(temp);
	 }while( CheckId(vec.begin(),vec.end(),id) );// while Duplicate Found
  	cout<<"\tEnter Topic of Book : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,about);
  	cout<<"\tEnter Quantity of Book's : ";
  	cin>>Qt;
  	Medical_Books obj(title,writer,id,about);
  	obj.set_bookqt(Qt);
  	vec.push_back(obj);// add to our List
  }
  
  void Add_IslamicBook(vector<Islamic_Books> &vec){// Add Islamic  book's
  	string temp; int id; int Qt;
  	string title,writer,language;// temp Var
  	cout<<"\tEnter Title of Book : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,title);
  	cout<<"\tEnter Writer Name : ";
  	cin.sync(); // to Prevent default buffer
  	getline(cin,writer);
  	cout<<"\tEnter Id (Num) : ";
  	do{
       cin>>temp;
       id=stoi(temp);
	}while( CheckId(vec.begin(),vec.end(),id) );// while Duplicate Found
	 cout<<"\tEnter Quantity of Book's : ";
  	 cin>>Qt;
  	 Islamic_Books obj(title,writer,id);
  	 obj.set_bookqt(Qt);
  	 vec.push_back(obj);// add to our List
  }
  
  // Fetching Data From 4 Files
  void GET_Programing_Books(vector<Programing_Books>&);
  void GET_Medical_Books(vector<Medical_Books>&);
  void GET_History_Books(vector<History_Books>&);
  void GET_Islamic_Books(vector<Islamic_Books>&);
  
     
	/*   Algo      Used in Func     */
	template<class T,typename t>// using generics where,T is iterator
	T GetBookBYid(T first,T last , t &id){// Find Book By id
		while(first != last){
			if(first->return_id() == id)// Same as( *first.return_id() )
			   return first;
			first++;
		}
		return last;
	}
	
   /*     Display Func      */
    void AskUserChoice(void){
   	    cout<<"\tDisplay All Book            --1"<<endl;
  		cout<<"\tFind Book By Id             --2"<<endl;
  		cout<<"\tFind Book By Name           --3"<<endl;
    }
    
	template<class T>// this Single Func is UseFul for Every Class
	void DisplayAll(T First,T Last){// Display  All Book's
	    if(First == Last){
	    	cout<<"\t !!!Sorry Nothing Found"<<endl;
		}
		while(First != Last){
			cout<<setfill('-')<<setw(100)<<" \n";
			First->To_Console();
			cout<<setfill('-')<<setw(100)<<" \n";
			First++;
		}
	}
    
    template<class T,typename Tag >// this Single Func is UseFul for Every Class
    void DisplayByTag(T First,T Last,Tag &Str){// Find Book By Langauge Name
    	bool Found = false;// Check to if nothing Found
		while(First != Last){
    		if(First->return_Tag() == Str){
    			Found=true;// If Content FOund
    			cout<<setfill('-')<<setw(100)<<" \n";
    			First->To_Console();
    			cout<<setfill('-')<<setw(100)<<" \n";
			}
			First++;
		}
		if(!Found) 
		cout<<"\t!!Sorry No Thing Found By this Tag "<<endl;
	}
	
	template<class T>// this Single Func is UseFul for Every Class
	void Ask_BookIssue(T &vec){// Ask User Choice to Issue book
		int id; char C;
		cout<<"\tDo You want Book Y?N  : ";
		cin>>C;
		if(C=='y' or C=='Y'){
			cout<<"\tEnter Book Id : ";
			cin>>id;
			auto it = GetBookBYid(vec.begin(),vec.end(),id);
			if(it != vec.end()){
				if(it->return_InStock()!=0 && it->return_TotalQt()!=0){
    	            cout<<setfill('-')<<setw(130)<<" \n\n"; 
    	            cout<<"\t"<<it->return_title()<<" "<<"has Been Issued "<<endl;
    	            cout<<setfill('-')<<setw(130)<<" \n\n";
    	            it->Issue_Book();// Delete One Book From Stock
                }// if
                else cout<<"\t!!! Book Is Already Issue"<<endl;
			}
			else cout<<"\tInvalid Id No Book Have this id : "<<id<<endl;
		}// if
	}
	
	template<class T>// this Single Func is UseFul for Every Class
	void DisplayBookBYid(T &vec){// Ask For id & Display
		int id;
  		system("cls");
  		cout<<"\tEnter ID_ ";
  		cin>>id;
  		auto it=GetBookBYid(vec.begin(),vec.end(),id);// using Func
  		if(it != vec.end()){
  			cout<<setfill('-')<<setw(100)<<"\n";
  			it->To_Console();
  			cout<<setfill('-')<<setw(100)<<"\n";
		} else cout<<"\t!!!No Book Found By this Id"<<endl;
	}
	
	template<class T>// this Single Func is UseFul for Every Class
	void DisplayBookBYtitle(T &vec){// Ask For id & Display
		string Name; bool Find=false;
  		system("cls");
  		cout<<"\tEnter Book Title _ ";
  		cin.sync();
  		getline(cin,Name);
  		for(auto it = vec.begin(); it != vec.end(); it++)
  			if(it->return_title() == Name){
  				Find=true;
  			   cout<<setfill('-')<<setw(120)<<"\n"<<endl;
  			   it->To_Console();
  			   cout<<setfill('-')<<setw(120)<<"\n"<<endl;
			}
  		if(!Find)
  		   cout<<"\t !! Sorry Nothing Found With this Title "<<endl;
	}
	void BookSection(void){// this Single Func is UseFul for Every Class
        cout<<"\tPrograming Books --1"<<endl;
        cout<<"\tMedical Books    --2"<<endl;
        cout<<"\tHistory Books    --3"<<endl;
        cout<<"\tIslamic Books    --4"<<endl;
	}
	/*    Admin Section Func */
	void Admin_Choice(void){// Display Func for 4 Section of Lib
		cout<<"\tApply Change For_Each    --0"<<endl;
        cout<<"\tDisplay All Book         --1"<<endl;
        cout<<"\tDelete Book By ID        --2"<<endl;
        cout<<"\tSearch Book By ID        --3"<<endl;
        cout<<"\tSearch Book By Title     --4"<<endl;
        cout<<"\tModify Book (Only by ID) --5"<<endl;
        cout<<"\tAdd New Book             --6"<<endl;
	}
	
	template<class T> // this Single Func is UseFul for Every Class
	void Delete_Book(T &vec){ // Delete Book By ID
		int id;
		char C;
		cout<<"\tEnter Id to Delete Book _";
		cin>>id;
		auto it = GetBookBYid(vec.begin(),vec.end(),id);
		if(it != vec.end()){
			cout<<"------------------------------------------"<<endl;
			 it->To_Console();
			cout<<"------------------------------------------"<<endl;
			cout<<"\tEnter Are You Sure Y/N : ";
			cin>>C;
			  if(C=='Y' || C =='y'){
			    vec.erase(it);// delete Book
			    cout<<"\t All Set "<<endl;
			  }
			    else cout<<"\t ' - ' Never Mind "<<endl;
		}  else cout<<"\t!!Sorry No Book Found having this ID "<<endl;
	}
	
	template<class T> // this Single Func is UseFul for Every Class
	void Mofiy_Book(T &vec){
		int id,choice;
		string str,Time;
		cout<<"\t Enter Id of Book _ ";
		cin>>id;
		auto it = GetBookBYid(vec.begin(),vec.end(),id);
		if(it != vec.end()) {
		cout<<"\tYou Selected"<<endl;
	    cout<<"---------------------------------------------"<<endl;
	        it->To_Console();
	    cout<<"----------------------------------------------"<<endl<<"\n";
		cout<<"\t Modify Book "<<endl;
		cout<<"\t Set New Quantity       -- 1"<<endl;
		cout<<"\t Set New Book Title     -- 2"<<endl;
		cout<<"\t Set New Writer Name    -- 3"<<endl;
		cout<<"\t Set Pulish Time to Now -- 4"<<endl;
		cout<<"\t Add Stock              -- 5"<<endl;
		cout<<"\t Put Issue Book's Back  -- 6"<<endl;
		cout<<"\t Remove Stock           ---7"<<endl;
		cout<<"\t <0 for Exit> Make Choice _ ";
		cin>>choice;
		//var
		string Writer,title;
		switch(choice){
		  case 1:// set Qt
		  	int Qt;
		  	cout<<"\tEnter New Qt to Set _ ";
		  	cin>>Qt;
		  	it->set_bookqt(Qt);
		  	cout<<"\tHas been Set "<<endl;
		  break;
		  case 2:// Set Publish Time
		  	cout<<"\tEnter New Title of Book _ ";
		  	cin.sync();
		  	getline(cin,title);
		  	it->set_title(title);
		  	cout<<"\tHas been Set "<<endl;
		  break;
		  case 3:// Set Writer Name
		  	cout<<"\tEnter New WriterName _ ";
		  	cin.sync();
		  	getline(cin,Writer);
		  	it->set_writer_name(Writer);
		  	cout<<"\tSet SuccessFully"<<endl;
		  break;
		  case 4:// set Time to Now
		  	time_t TimeNow;// Time Now
		  	time(&TimeNow);// set Time Acording to System
			 str = ctime(&TimeNow);// temp
			for(auto it = str.begin() ; it != (str.begin()+24) ; it++)
				Time.push_back(*it);// Copy Time into NEW Str
		  	it->set_time(Time);
		  	cout<<"\t New Time Set SucessFully : "<<ctime(&TimeNow)<<endl; 
		  break;
		  case 5:// Add At
		    int Count;
		  	cout<<"\tALready in Stock : "<<it->return_TotalQt()<<" Book's"<<endl;
		  	cout<<"\tEnter Amount you Want to Add _ ";
		  	cin>>Count;
		  	it->Add_qt(Count);
		  	cout<<"\tNow in Stock : "<<it->return_TotalQt()<<" Book's"<<endl;
		  break;
		  case 6: // put Issue book Back
		  	int Book_C;
		  	cout<<"\tToatal Books Issue : "<<(it->return_TotalQt() - it->return_InStock()) <<endl;
		  	cout<<"\tEnter Amount You Want to Put Back  _ ";
			cin>>Book_C;
			Book_C= (Book_C > it->return_TotalQt())?it->return_TotalQt():Book_C;
			it->Add_InStock(Book_C);
			cout<<"\t All Set "<<endl;
			break;
		  case 7:// Remove Book From Stock
		  	int var;// var to remove 
		  	cout<<"\tALready in Stock : "<<it->return_TotalQt()<<" Book's"<<endl;
		  	cout<<"\tEnter Amount you Want to Remove _ ";
		  	cin>>var;
		  	it->Remove_Stock(var);// call MEm to remove
		  	cout<<"\tNow in Stock : "<<it->return_TotalQt()<<" Book's"<<endl;
		  break;
		  default:	
		  cout<<"\tNever Mind "<<endl;
		} // Switch
	  }// if Find
	  else{
	  	cout<<"! No book found By this ID"<<endl;// if Book not Found
	  }
	} // Func
	
	// For Each
	template<class T>// this Single Func is UseFul for Every Class
    void ForEach(T &vec){// Apply changes for Every Book in Section
    	int C; char c;
    	cout<<"\tDelete ALl Book's ---1"<<endl;
    	cout<<"\tPut All Issue Back --2"<<endl;
    	cout<<"\tShow Issue Book's  --3"<<endl;
    	cout<<"\tMake Choice _ ";
    	cin>>C;
    	if(C==1){// Delete ALl book's
    		cout<<"\tAre You Sure to delete All Book's From this Section Y/N !!  : ";
    		cin>>c;
    		 if(c=='y' or c=='Y')
    		   vec.clear();
    		else cout<<"\t Never Mind "<<endl;
		}
		else if(C == 2){// Put all Issue Book's Back
			cout<<"\tAre You Sure to put all issued book's Back Y/N _ ";
			cin>>c;
			if(c=='y' or c=='Y'){
				for_each(vec.begin(),vec.end(),[](auto &obj){
    		    	obj.set_Instock(obj.return_TotalQt());//set_Instock
				});
				cout<<"\t All Set"<<endl;
			}
    		else cout<<"\t ' _ ' Never Mind "<<endl;
		} else if(C==3){
			bool IsFound=false;
			for(auto &it : vec){
				if(it.return_TotalQt() != it.return_InStock()){
					IsFound =true;
					cout<<"----------------------------------------"<<endl;
					   it.To_Console();
					cout<<"----------------------------------------"<<endl;
				}
			}
			if(!IsFound){cout<<"\t Sorry NoThing Found"<<endl;}
		}
		else cout<<"\t InValid Choice !! "<<endl;
	}
	
	/*   section Func   */
	template<class T>// this Single Func is UseFul for Two Classes
	void Student_Section(T &vec,char &Choice){
		AskUserChoice();
  		cout<<"\t Make Choice _ ";
  		cin>>Choice;
  		if(Choice == '1'){// I Display ALL Books
  			DisplayAll(vec.begin(),vec.end());
		}
  		else if(Choice == '2'){// I Display Book By id
  			DisplayBookBYid(vec);
		}
		else if(Choice == '3'){// I Display Book By Name
			DisplayBookBYtitle(vec);
		}
		else cout<<"\t!!Invalid Choice "<<endl;
  	  	Ask_BookIssue(vec); // I Issue Book
	}
 /* File Emp Test */
 bool is_Empty(std::ifstream& pFile){return pFile.peek() == ifstream::traits_type::eof();}
  enum FileType{
 	Islamicbooks_File,
 	MedicalBooks_File,
 	HistoryBooks_File,
 	ProgramingBooks_File
 };
 void MakeDirs(FileType fileType,bool isContainDir=true){
 	cout<<"\nData Base Not Found Program is trying to make new data base please Wait .. "<<endl;
 	cout<<"You may need to put some books for intial Setup !"<<endl;
 	cout<<"\n\n \t\t\t\tLOADING ... \t\t\t"<<endl;
 	
 	
    
 	
 	if(not isContainDir)
 	 system("mkdir Data_Base");
 	// Testing
 	fstream fs;
 	switch(fileType){
 		case FileType::ProgramingBooks_File:
 	        fs.open("Data_Base/ProgramingBooks.text",ios_base::out);
 			 return;
 		case FileType::HistoryBooks_File:
 	        fs.open("Data_Base/HistoryBooks.text",ios_base::out);	
 			  return;
 		case FileType::Islamicbooks_File:
 	        fs.open("Data_Base/islamicBooks.text",ios_base::out);
 			  return;
 		case FileType::MedicalBooks_File:
 	        fs.open("Data_Base/medicalBooks.text",ios_base::out);
 			  return;
	}
 }

/*
  TODOS :
     Make this work
*/
 static void PrintWelcomeText () {
	std::cout << "Welcome to Book Store" << std::endl;
	std::cout << "Please select an option" << std::endl;
	std::cout << "1. Add Book" << std::endl;
	std::cout << "2. Remove Book" << std::endl;
	std::cout << "3. Display All Books" << std::endl;
	std::cout << "4. Display Book By ID" << std::endl;
	std::cout << "5. Display Book By Name" << std::endl;
	std::cout << "6. Issue Book" << std::endl;
	std::cout << "7. Return Book" << std::endl;
	std::cout << "8. Display Issued Books" << std::endl;
	std::cout << "9. Display Returned Books" << std::endl;
	std::cout << "10. Display All Books By Section" << std::endl;
 }

/*
  TODOS:
    Add Logic to swicth statements
*/
void UnitTests () {
	std::cout << "Unit Tests" << std::endl;
	std::cout << "1. Add Book" << std::endl;
	std::cout << "2. Remove Book" << std::endl;
	std::cout << "3. Display All Books" << std::endl;
	std::cout << "4. Display Book By ID" << std::endl;
	std::cout << "5. Display Book By Name" << std::endl;
	std::cout << "6. Issue Book" << std::endl;
	std::cout << "7. Return Book" << std::endl;
	std::cout << "8. Display Issued Books" << std::endl;
	std::cout << "9. Display Returned Books" << std::endl;
	std::cout << "10. Display All Books By Section" << std::endl;
	std::cout << "11. Exit" << std::endl;

	std::cout << "Please select an option" << std::endl;

	int option;
	std::cin >> option;
	switch (option) {
	case 1:
		std::cout << "Add Book" << std::endl;
		break;
	case 2:
		std::cout << "Remove Book" << std::endl;
		break;			
	case 3:
		std::cout << "Display All Books" << std::endl;
		break;
	case 4:
		std::cout << "Display Book By ID" << std::endl;
		break;
	case 5:
		std::cout << "Display Book By Name" << std::endl;
		break;
	case 6:		
		std::cout << "Issue Book" << std::endl;
		break;
	case 7:
		std::cout << "Return Book" << std::endl;
		break;
	case 8:
		std::cout << "Display Issued Books" << std::endl;
		break;
	case 9:
		std::cout << "Display Returned Books" << std::endl;
		break;
	case 10:
		std::cout << "Display All Books By Section" << std::endl;
		break;
	case 11:
		std::cout << "Exit" << std::endl;
		break;
	default:
		std::cout << "Invalid option" << std::endl;
		break;
	}

}

// Driver Code
int main(){
   //	var 
   vector<Programing_Books> LibP;// Programing book's var
   vector<Medical_Books>    LibM;// Medical book's var 
   vector<History_Books>    LibH;// History Bool's var
   vector<Islamic_Books>    LibI;// Islamic book's var
   /*   Fetch data From Files  */
    GET_Programing_Books(LibP);// P Book's
    GET_Medical_Books(LibM);// M Book's
    GET_History_Books(LibH);// H Book's
    GET_Islamic_Books(LibI);// I Book's
   /*     Main   */
   int UChoice;// var For Main CHoice
   cout<<"\t\tWelcome to Library "<<endl;
   cout<<"\t\tAdmin Section      ---1"<<endl;
   cout<<"\t\tLogin As Student   ---2"<<endl;
   cout<<"\t\t Make Choice _  ";
   cin>>UChoice;
  /*       Main     */
   if(UChoice==1){// if Selec for Admin
        int Book_Choice;
        cout<<"\tEnter Section You Want to Modify "<<endl;
        BookSection();// Func admin For Book Selection
        cout<<"\t<0 for exit> Make Choice _ ";
        cin>>Book_Choice;// Get Choice
        int choice;// In Switch (Choice)
      switch(Book_Choice){
  	     case 1://Programing Book's
  	       do{
  	       	   system("pause");
  	       	   system("cls");
  	           cout<<"You Selected Progarmign Section "<<endl;
  	     	   Admin_Choice();// Func Ask Admin for Selection abt
  	     	   cout<<"\tDisplay Books By Language Name --7"<<endl;
  	     	   cout<<"\t<8 for Exit> Make Choice _ ";
  	     	   cin>>choice;// Get Choice 
  	     	   if(choice == 0){// p Apply Change for all Book's in section
  	     	  	 ForEach(LibP);
			   }
  	     	   else if(choice ==1){ // P Display All
  	     		 DisplayAll(LibP.begin(),LibP.end());
			   }
			   else if(choice == 2){ //  p Delete Book by id
				Delete_Book(LibP);
			   }
			   else if(choice == 3){ // p Display Book by Id
				DisplayBookBYid(LibP);
			   }
			   else if(choice == 4){ // p Display Book by Title
				DisplayBookBYtitle(LibP);
			   }
			   else if(choice == 5){ // p Modify Book
			    Mofiy_Book(LibP);
			   }
			   else if(choice == 6){ // P Add Book's
			      [](auto &vec){// Using Lamda
			    	 int Count;// Count to Get How many book's Admin Want to Enter
			    	 cout<<"\t How Many Book's You Want to Add _ ";
			    	 cin>>Count;// Get Count
			    	for(int i=0;i<Count;i++)
			    	   Add_ProgramingBook(vec);// Func to add Book to Lib
			       }(LibP);
			   }
			  else if(choice  == 7){ // P Display By Tag
			  	  [](auto &vec){
			  	  	string Tag;
			  	    cout<<"\tEnter Progarming Language _ ";
			  	    cin.sync();
			  	    getline(cin,Tag);// Get Progarming lan name
			  	    DisplayByTag(vec.begin(),vec.end(),Tag);
			      }(LibP);
			 }
			else {
				choice = 8;
				cout<<"\tInvalid Choice  --  Exit "<<endl;
			}
	   }while(choice != 8);// For Go back  
  	     break;// P Sec
  	     case 2:// Medical Books
  	       do{
  	       	system("pause");
  	       	system("cls");
  	     	Admin_Choice();// Ask abt Admin Selection
  	     	cout<<"\tDisplay Books By Topic --7"<<endl;
  	     	cout<<"\t<8 for Exit> Make Choice _ ";
  	     	cin>>choice;// get Choice
  	     	if(choice ==0){// Apply Changes for all Book in this sec
  	     		ForEach(LibM);
			}
  	     	else if(choice ==1){ //M Display All
  	     		DisplayAll(LibM.begin(),LibM.end());
			}
			else if(choice == 2){ // M Delete Book by id
				Delete_Book(LibM);
			}
			else if(choice == 3){ // M Display Book by Id
				DisplayBookBYid(LibM);
			}
			else if(choice == 4){ // M Display Book by Title
				DisplayBookBYtitle(LibM);
			}
			else if(choice == 5){ // M Modify Book
				Mofiy_Book(LibM);
			}
			else if(choice == 6){// M Add Book's
			   [](auto &vec){
			    	int Count;
			    	cout<<"\t How Many Book's You Want to Add _ ";
			    	cin>>Count;
			    	for(int i=0;i<Count;i++)
			    	   Add_MedicalBook(vec);
			     }(LibM);
			}
			else if(choice  == 7){// M Display By Tag
				[] (auto &vec) {
			  	string Tag;
			  	cout<<"\tEnter Topic _ ";
			  	cin.sync();
			  	getline(cin,Tag);
			  	DisplayByTag(vec.begin(),vec.end(),Tag);
			    }(LibM);
			}
			else {
				cout<<"\tInvalid Choice  --  Exit "<<endl;
				choice =8;
			}
		}while(choice != 8 ); // to go back
			break;// M Sec
  	     case 3:// History Book's
  	      do{
  	       	system("pause");
  	       	system("cls");
  	       	cout<<"You Selected Islamic Book's"<<endl;
  	     	Admin_Choice();// Ask Choice
  	     	cout<<"\t<8 for Exit> Make Choice _ ";
  	     	cin>>choice;// get Choice
  	     	if(choice == 0){
  	     		ForEach(LibH);
			}
  	        else if(choice ==1){ // H Display All
  	     		DisplayAll(LibH.begin(),LibH.end());
			}
			else if(choice == 2){ // H Delete Book by id
				Delete_Book(LibH);
			}
			else if(choice == 3){ // H Display Book by Id
				DisplayBookBYid(LibH);
			}
			else if(choice == 4){ // H Display Book by Title
				DisplayBookBYtitle(LibH);
			}
			else if(choice == 5){ // H Modify Book
				Mofiy_Book(LibH);
			} 
			else if(choice == 6){ // H add Book's
				[](auto &Vec){
			    	int Count;
			    	cout<<"\t How Many Book's You Want to Add _ ";
			    	cin>>Count;
			    	for(int i=0;i<Count;i++)
			    	   Add_HistoryBook(Vec);
			     }(LibH);
			}// else if
			else {
				choice=8;
				cout<<"Invalid Choice  --  Exit "<<endl;
			}
		}while(choice !=8);
  	     break;// H sec
  	     case 4:// Islamic Book's
  	       do{
  	       	system("pause");
  	       	system("cls");
  	       	cout<<"You Selected Islamic Book's"<<endl;
  	     	Admin_Choice();// Ask Choice
  	     	cout<<"\t<8 for Exit> Make Choice _ ";
  	     	cin>>choice;// get Choice
  	     	if(choice == 0){
  	     		ForEach(LibI);
			}
  	        else if(choice ==1){ // I Display All
  	     		DisplayAll(LibI.begin(),LibI.end());
			}
			else if(choice == 2){ // I Delete Book by id
				Delete_Book(LibI);
			}
			else if(choice == 3){ // I Display Book by Id
				DisplayBookBYid(LibI);
			}
			else if(choice == 4){ // I Display Book by Title
				DisplayBookBYtitle(LibI);
			}
			else if(choice == 5){ // I Modify Book
				Mofiy_Book(LibI);
			} 
			else if(choice == 6){ // I add Book's
				[](auto &Vec){
			    	int Count;
			    	cout<<"\t How Many Book's You Want to Add _ ";
			    	cin>>Count;
			    	for(int i=0;i<Count;i++)
			    	   Add_IslamicBook(Vec);
			     }(LibI);
			}// else if
			else {
				choice=8;
				cout<<"Invalid Choice  --  Exit "<<endl;
			}
		}while(choice !=8);
  	     break;
  	       default:
  	      	cout<<"\t\t !!! Invalid Choice "<<endl;
      }// switch*/
   }//Admin If
    // User or Student
   else if(UChoice==2){
    int Book_choice;
    do{
   	  system("pause");
      system("cls");
      cout<<"\tWhat Type of Book You Want"<<endl;
      BookSection();
      cout<<"\t<0 for Exit> Make Choice _ ";
      cin>>Book_choice; system("cls");
      char Choice;// In Switch
     switch(Book_choice){
  	 case 1:// Progarming book's
  		 cout<<"\tYou Selected Programing Books "<<endl;
  		 AskUserChoice();// Dp Func
  		 cout<<"\tFind Books By Language Name --4"<<endl;
  		 cout<<"\t Make Choice _ ";
  		 cin>>Choice;
  		 if(Choice == '1'){// P Display All Books
  			DisplayAll(LibP.begin(),LibP.end());
		 }
  		else if(Choice == '2'){// P Find Book By ID
  			DisplayBookBYid(LibP);
		}
		else if(Choice == '3'){ // P FInd Book By Name
			DisplayBookBYtitle(LibP);
		}
		else if(Choice == '4'){// P Display Books By tag
		    system("cls");
			[](auto &vec){
			   string Tag;
		       cout<<"\tEnter Programing Language Name : ";
			   cin.sync();
			   getline(cin,Tag);
			   DisplayByTag(vec.begin(),vec.end(),Tag);
		    }(LibP);
		}
		else {
			cout<<"\t!!Invalid Choice "<<endl;
		}
        Ask_BookIssue(LibP); // M Issue Book
  	break;
  	case 2:// Medical Boook
  		cout<<"\tYou Selected Medical Books"<<endl;
  		AskUserChoice();// Dp Func
  		cout<<"\tFind Book By TaG           --4"<<endl;
  		cout<<"\t Make Choice _ ";
  		cin>>Choice;
  		if(Choice == '1'){// M Display ALl Books
  			DisplayAll(LibM.begin(),LibM.end());
		}
  		else if(Choice == '2'){// M Display Book By id
  			DisplayBookBYid(LibM);
		}
		else if(Choice == '3'){// M Display Book By Name
			DisplayBookBYtitle(LibM);
		}
		else if(Choice == '4'){// M Display Book By TaG
			system("cls");
			[](auto &vec){
			  string Tag;
			  cout<<"\tEnter Book Topic : ";
			  cin>>Tag;
			  DisplayByTag(vec.begin(),vec.end(),Tag);
		    }(LibM);
		}
		else cout<<"\t!!Invalid Choice "<<endl;
  		Ask_BookIssue(LibM); // M Issue Book
   break;
   case 3:// History Book's
  		cout<<"\tYou Selected Hsitory Books"<<endl;
  		Student_Section(LibH,Choice);// Calling same func as I
  	break;
  	case 4:// Islamic Book's
  		cout<<"\tYou Selected Islamic Books"<<endl;
  		Student_Section(LibI,Choice);// Calling same func as H
  	break;
  	    default:
  		Book_choice=0;
  		cout<<"Invalid Choice ----Exit"<<endl;
      }// Switch
   }while(Book_choice!=0);// while Loop
  } // Emp else If*/
  
  else{ 	cout<<"\t\t!!Invalid Choice --Exit"<<endl; } // Main Else
  
/*              Put Data to Files                     */
    
    	ofstream outa;// Progarming Book's
    	outa.open("Data_Base/ProgramingBooks.text",ios_base::out);
    	if(!outa.is_open()) {cout<<"Progarming Lib File Not Find"<<endl; exit(0);}
	    if(!LibP.empty()){
    	        for_each(LibP.begin(),LibP.end(),[&outa](auto obj){
    		     outa<<obj.To_DataBase()<<endl;
		});  
	    }
	        outa.close();
	
    	ofstream outb;// Medical Book's
    	outb.open("Data_Base/medicalBooks.text",ios_base::out);
    	if(!outb.is_open()) {cout<<"Progarming Lib File Not Find"<<endl; exit(0);}
		if(!LibM.empty()){
    	            for_each(LibM.begin(),LibM.end(),[&outb](auto obj){
    		            outb<<obj.To_DataBase()<<endl;
		    });
	  }
	       outb.close();
	
    	ofstream outc;// History book's
    	outc.open("Data_Base/HistoryBooks.text",ios_base::out);
    	if(!outc.is_open()) {cout<<"Progarming Lib File Not Find"<<endl; exit(0);}
	if(!LibH.empty()){
    	        for_each(LibH.begin(),LibH.end(),[&outc](auto obj){
    		     outc<<obj.To_DataBase()<<obj.return_publish_time()<<endl;
		}); 
	 }
	     outc.close();
	
    	ofstream outd;// Islamice Book's
    	outd.open("Data_Base/islamicBooks.text",ios_base::out);
    	if(!outd.is_open()) {cout<<"Progarming Lib File Not Find"<<endl; exit(0);}
	if(!LibI.empty()){
    	        for_each(LibI.begin(),LibI.end(),[&outd](auto obj){
    		       outd<<obj.To_DataBase()<<obj.return_publish_time()<<endl;
		});  
	}
	outd.close();
	
} // Main
/* Func for Fetch Data From File*/
 void GET_Programing_Books(vector<Programing_Books> &vec){// get Data From File
	ifstream in;// Fstream obj
	string var[7];
	//Data_Base/  for test Remove this
	in.open("Data_Base/ProgramingBooks.text",ios_base::in);
	if(!in.is_open()){cout<<"DataBase Error"<<endl;  MakeDirs(FileType::ProgramingBooks_File,false);} // If File not Found
	if(!is_Empty(in)){// if Data Present in File
		while(getline(in,var[0],'$')){// title writernam id bool language time
			for(int i=1;i<6;i++)
			  getline(in,var[i],'$');
			getline(in,var[6],'\n');
			[var](auto &vec){// lamda
			    Programing_Books obj(var[0],var[1],stoi(var[2]),var[5]);
			    obj.set_bookqt(stoi(var[3]));// Set Total Book Qt
			    obj.set_Instock(stoi(var[4]));// Set In Stock
			    obj.set_time(var[6]); // Set Time
		        vec.push_back(obj);
			}(vec);// Lamda
	   }//while
		in.close();
	}
	else { // No thing found in File
	    in.close();
		cout<<"\t\t !!!! No Data Found in Programingbooks Library Data_Base Please Enter 1 Books to Continue"<<endl;
		for(int i=0;i<1;++i){// For 2 Times
		   cout<<"Enter Book -- "<<i+1<<endl;
		   Add_ProgramingBook(vec);// Add Book
		   system("cls");
	    }// for
	}// else
  }// Func
  void GET_Medical_Books(vector<Medical_Books> &vec){// get Data From File
    string var[7]; 
	ifstream in;// Fstream obj
	in.open("Data_Base/medicalBooks.text",ios_base::in);// Remove for test
	if(!in.is_open()){cout<<"DataBase Error"<<endl; MakeDirs(FileType::MedicalBooks_File);} // If File not Found
	if(!is_Empty(in)){// read Data if Data Present
		while(getline(in,var[0],'$')){
			for(int i=1;i<6;i++)
			  getline(in,var[i],'$');
			getline(in,var[6],'\n');// Time at the end
			    [var](auto &vec){// lamda
			      Medical_Books obj(var[0],var[1],stoi(var[2]),var[5]);
			      obj.set_bookqt(stoi(var[3]));// Set Total Book Qt
			      obj.set_Instock(stoi(var[4]));// Set In Stock
			      obj.set_time(var[6]); // Set Time
		          vec.push_back(obj);
			    }(vec);// Lamda
				//cout<<var[0]<<" "<<var[1]<<" "<<var[2]<<" "<<var[3]<<" "<<var[4]<<" "<<var[5]<<" "<<var[6]<<endl;
		}// while
		in.close();
	 }
	 else{ // No thing found in File
	    in.close();
		cout<<"\t\t !!!! No Data Found in MedicalBooks Library Data_Base Please Enter 1 Books to Continue"<<endl;
		for(int i=0;i<1;++i){
		   cout<<"Enter Book -- "<<i+1<<endl;
		   Add_MedicalBook(vec);// Add Book
		   system("cls");
	    }// for
	  }// else
  }// func
  void GET_History_Books(vector<History_Books> &vec){// get Data From File
    string var[6]; 
	ifstream in;// Fstream obj
	in.open("Data_Base/HistoryBooks.text",ios_base::in);// remove for test
	if(!in.is_open()){cout<<"DataBase Error"<<endl; MakeDirs(FileType::HistoryBooks_File);} // If File not Found
	if(!is_Empty(in)){
			// title$writer$id$totalqt$stock$time
		while(getline(in,var[0],'$')){
			for(int i=1;i<5;i++)
			  getline(in,var[i],'$');
			getline(in,var[5],'\n');
			    [var](auto &vec){// lamda
			      History_Books obj(var[0],var[1],stoi(var[2]));
			      obj.set_bookqt(stoi(var[3]));// Set Total Book Qt
			      obj.set_Instock(stoi(var[4]));// Set In Stock
			      obj.set_time(var[5]); // Set Time
		          vec.push_back(obj);
			    }(vec);// Lamda
				//cout<<var[0]<<" "<<var[1]<<" "<<var[2]<<" "<<var[3]<<" "<<var[4]<<" "<<var[5]<<endl;
		}
		in.close();
	}
	else{ // No thing found in File
	   in.close();
		cout<<"\t\t !!!! No Data Found in History Books Library Data_Base Please Enter 1 Books to Continue"<<endl;
		for(int i=0;i<1;++i){
		   cout<<"Enter Book -- "<<i+1<<endl;
		   Add_HistoryBook(vec);// Add Book
		   system("cls");
	    }// for
	}// else
  }
  void GET_Islamic_Books(vector<Islamic_Books> &vec){// get Data From File
    string var[6]; 
	ifstream in;// Fstream obj
	in.open("Data_Base/islamicBooks.text",ios_base::in);
	if(!in.is_open()){cout<<"DataBase Error"<<endl; MakeDirs(FileType::Islamicbooks_File);} // If File not Found
	if(!is_Empty(in)){// If Data Prsent in File
		while(getline(in,var[0],'$')){
			for(int i=1;i<5;i++)
			  getline(in,var[i],'$');
			getline(in,var[5],'\n');
			    [var](auto &vec){// lamda
			      Islamic_Books obj(var[0],var[1],stoi(var[2]));
			      obj.set_bookqt(stoi(var[3]));// Set Total Book Qt
			      obj.set_Instock(stoi(var[4]));// Set In Stock
			      obj.set_time(var[5]); // Set Time
		          vec.push_back(obj);
			    }(vec);// Lamda
		}
		in.close();
	}
     else{ // No thing found in File
	        in.close();
		cout<<"\t\t !!!! No Data Found in Islamic Books Library Data_Base Please Enter 1 Books to Continue"<<endl;
		for(int i=0;i<1;++i){
		   cout<<"Enter Book -- "<<i+1<<endl;
		   Add_IslamicBook(vec);// Add Book
		   system("cls");
	    }// for
	}// else
  }   
        //  Name$writer$id$bool$VAR$Time Data Format in Files


/*
// After 6 Month DSA Progress



// Helper Class
template<class T>
class Node{
public:
    T data;
    Node *prev , *next;
};

// Doubly Linked List
template<class T> class DLinkedList{
public:
     DLinkedList(void){
         head = nullptr;
         tail = nullptr;
     }

     // Push
     void Push(T& data){
         Node<T>* newNode = new Node<T>{data , nullptr , nullptr};

         // null case
         if(head == nullptr && tail == nullptr){
             head = newNode;
             tail = newNode;
             return;
         }

         newNode->next = head;
         head->prev = newNode;
         head = newNode;
     }

     //Push Back
     void Push_Back(T& data){
         Node<T>* newNode = new Node<T>{data , nullptr , nullptr};

         // null case
         if(head == nullptr && tail == nullptr){
             head = newNode;
             tail = newNode;
             return;
         }

         newNode->prev = tail;
         tail->next = newNode;
         tail = newNode;
     }

     // push's After a given Node
     void Push_After(Node<T>* node , T& data){

         // case Node is Last Element
         if(node->next == nullptr){
             Push_Back(data);
             return;
         }
         cout<<"I have Control"<<endl;
         Node<T>* newNode = new Node<T>{data , nullptr , nullptr};

         newNode->next = node->next;
         newNode->prev = node;

         node->next->prev = newNode;
         node->next = newNode;
     }

     // Push's Before a given Node
     void Push_Before(Node<T>* node , T& data){
         // case node is First Element
         if(node->prev == nullptr){
             Push(data);
             return;
         }

         Node<T>* newNode = new Node<T>{data , nullptr , nullptr};

         newNode->prev = node->prev;
         newNode->next = node;

         node->prev->next = newNode;
         node->prev = newNode;
     }

     /* Deletion From linkedList */
/*
     // Deletes N Node
     void Remove(Node<T>* node){

         if(node == head) // Case first element
             head = head->next;
         if(node == tail) // Case last element
             tail = tail->prev;

         if(node->prev != nullptr)
             node->prev->next = node->next;
         if(node->next != nullptr)
             node->next->prev = node->prev;

         delete node;
     }

     // Delete's Top Node of LinkedList
     void Pop(void){
         if(IsEmpty()) return; // case no element's in linkedlist

         Node<T>* temp = head;

         head = head->next;
         head->prev = nullptr;

         delete temp;
     }

     // Delete's Last Node of LinkedList
     void RemoveFromLast(void){
         if(IsEmpty()) return;// case no element's in linkedlist

         Node<T>* temp = tail;

         tail = tail->prev;
         tail->prev = nullptr;

         delete temp;
     }

     // Search in Linked List
     Node<T>* IsContainNode(const T& matchData , bool startFromTail = false) const{
         if(IsEmpty())return nullptr; // Null Case

         // finds element in linked List starts from head
         if(!startFromTail){
             Node<T>* itr = head;
             while(itr != nullptr){
                 if(itr->data == matchData) return itr;
                 itr = itr->next;
             }
             return nullptr; // On Not Found
         }
         // finds element from the linkedlist starts from tail
         else{
             Node<T>* itr = head;
             while(itr != nullptr){
                 if(itr->data == matchData) return itr;
                 itr = itr->prev;
             }
             return nullptr;// On Not Found
         }
     }
*/
     /* Utilities Functions */
/*
     // returns linkedlist is empty
     bool IsEmpty() const{ return head == nullptr && tail == nullptr;}

     // returns linked List is contains element N
     bool Contains(const T& Data) const {return IsContainNode(Data);}

    // IO operator OverLoad Recommended
     void Display(void){
        if(IsEmpty())return;

        Node<T>* itr =head;
        while(itr!= nullptr){
            cout<<" "<<itr->data<<" "<<endl;
            itr = itr->next;
        }

        cout<<endl;
     }
private:
    Node<T> *head , *tail;
};

int main(){
    DLinkedList<int> dLinkedList;
    int e(2) , e1(3) , e2(6) , e3(7);
    dLinkedList.Push_Back(e);
    dLinkedList.Push(e2);
    dLinkedList.Push_Before(dLinkedList.IsContainNode(e2) , e1);
    dLinkedList.Display();
}
*/
