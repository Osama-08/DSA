#include<iostream>
//to get functions of current date and time
#include<ctime>
//defines constants with the limit of fundamental integral
#include <climits>
//for color functions and some other functions
#include<windows.h>
//for sleep function and some other functions
#include <conio.h>
#include <iomanip>
#include<fstream>
using namespace std;

//public variables to find shortest path
int source=0;//source index 
int arr[6];//array that keeps source index row values
int d[6]={INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX};//array that keeps the distance record
int routes[6][6]={
        		{0, 187, 0,377,0,894},
        		{187,0,1555,0,0,0},
        		{0,1555,0,1510,0,0},
        		{377,0,1510,0,338,0},
        		{0,0,0,338,0,632},
        		{894,0,0,0,632,0}};

/////////////////////////////////////////////STRUCTURES/////////////////////////////////////////////////////////

//structure to keep record of customers
struct customer{
	string name;
	string passportId;
	string cnic;
	int age;
	string phoneNumber;
	string from;
	string to;
	string seatType;
	string plane;
	customer *nextC=NULL;
	customer *prevC=NULL;
};
customer *cFirst=NULL, *cLast=NULL;


//structure to keep admin record
struct admin{
	string name;
	string userId;
	string password;
	string phoneNumber;
	string email;
	admin *nextA=NULL, *prevA=NULL;
};
admin *aFirst=NULL, *aLast=NULL;

//structure to keep record of all customers for plane isl-quetta
struct flights_isl_quetta{
	string customerName;
	string passportId;
	string to;
	string seatType;
	flights_isl_quetta *nextF=NULL, *prevF=NULL;
	
};
flights_isl_quetta *qtFirst=NULL, *qtLast=NULL;
//structure to keep record of all customers for plane isl-lahore
struct flights_isl_lhr{
	string customerName;
	string passportId;
	string to;
	string seatType;
	flights_isl_lhr *nextF=NULL, *prevF=NULL;
	
};
flights_isl_lhr *lhrFirst=NULL, *lhrLast=NULL;
//structure to keep record of all customers for plane isl-peshawar
struct flights_isl_peshawar{
	string customerName;
	string passportId;
	string to;
	string seatType;
	flights_isl_peshawar *nextF=NULL, *prevF=NULL;
	
};
flights_isl_peshawar *pshFirst=NULL, *pshLast=NULL;

//requested flights for plane A
struct Isl_Quetta{
	string customerName;
	string customerPhoneNumber;
	string cnic;
	string passportId;
	int age;
	string from;
	string to;
	string seatType;
	Isl_Quetta *nextF=NULL, *prevF=NULL;
	
};
Isl_Quetta *qFirst=NULL, *qLast=NULL;
//plane b
struct Isl_Lhr{
	string customerName;
	string customerPhoneNumber;
	string cnic;
	string passportId;
	int age;
	string from;
	string to;
	string seatType;
	Isl_Lhr *nextF=NULL, *prevF=NULL;
	
};
Isl_Lhr *lFirst=NULL, *lLast=NULL;
//plane c
struct Isl_Peshawar{
	string customerName;
	string customerPhoneNumber;
	string cnic;
	string passportId;
	int age;
	string from;
	string to;
	string seatType;
	Isl_Peshawar *nextF=NULL, *prevF=NULL;
	
};
Isl_Peshawar *pFirst=NULL, *pLast=NULL;

//structure for feedback
struct feedback{
	string passportId;
	string experience;
	string meal;
	string staff;
	string departure;
	feedback *fdNext=NULL;
};
feedback *fdFirst=NULL,*fdLast=NULL;
//Structure for criminals
struct criminals{
	string passportId;
	string name;
	string cnic;
	criminals *crNext=NULL;
};
criminals *crFirst=NULL,*crLast=NULL;

void AdminLogin();
void CustomerLogin();
void viewCustomers();
void viewFlights();
void bookFlight();
void Plane_Isl_Quetta(string);
void Plane_Isl_Peshawar(string);
void Plane_Isl_Lhr(string);
void viewRecentFlight();
int dijkastra(int);
void check(int, int, int,int[]);
int search(int, int[]);
void viewIslQuettaFlights();
void viewIslLahoreFlights();
void viewIslPeshawarFlights();
void bookedQuetta();
void bookedLahore();
void bookedpeshawar();
void addFlight();
void viewCustomerFlights();
void ViewFeedbacks();
void giveFeedback();
void AddCriminals();
void cancelFlights();
time_t time();
void QbookingReceipt(flights_isl_quetta *);
void LbookingReceipt(flights_isl_lhr *);
void PbookingReceipt(flights_isl_peshawar *);
void ViewCriminals();
void end_program();
/////////////////////////////////////////////////MAKE ADMIN METHOD//////////////////////////////////////////////
void makeAdmin(){
	admin *curr=new admin();
	curr->name="Admin";
	curr->phoneNumber="03369296704";
	curr->userId="Admin_01";
	curr->password="123";
	curr->email="Admin@gmail.com";
	aFirst=aLast=curr;
}

////////////////////////////////////////////////MAIN METHOD///////////////////////////////////////////////////
int main(){
	system("color 03");
	makeAdmin();
	int choice;


	do{
		cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	    cout<<"                                         WELCOME TO Friends AIRLINE MANAGEMENT SYSTEM                                       \n";
	    cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	    cout<<"\n\n";
		cout<<"\t\t\t\t\t ENTER 1 FOR ADMIN LOGIN\n";
		cout<<"\t\t\t\t\t ENTER 2 FOR CUSTOMER LOGIN\n";
		cout<<"\t\t\t\t\t ENTER 0 TO EXIT\n";
		cin>>choice;
		system("cls");
		if(choice==1){
			AdminLogin();
		}
		else if(choice==2){
			CustomerLogin();
		}
	}while(choice!=0);
	end_program();
}

/////////////////////////////////////////////ADMIN LOGIN///////////////////////////////////////////////////////////
void AdminLogin(){
	
	string userN,pass;
	cout<<"ENTER YOUR USERNAME:\n";
	cin>>userN;
	cout<<"ENTER YOUR PASSWORD:\n";
	cin>>pass;
	system("pause");
	system("cls");
	if(aFirst->password==pass && aFirst->userId==userN){
		int choice;
		do{
			cout<<"------------------------------------------------------------------------------------------------------------------------\n";
			cout<<"                                          			ADMIN LOGIN                                                                   \n";
			cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
    		cout<<"\n\n";
			cout<<"\t\t\t\t ENTER 1 TO VIEW FLIGHTS BOOKED\n";
			cout<<"\t\t\t\t ENTER 2 TO VIEW CUSTOMERS RECORD\n";
			cout<<"\t\t\t\t ENTER 3 ADD CUSTOMERS TO FLIGHT\n";
			cout<<"\t\t\t\t ENTER 4 FOR VIEW FEEDBACKS\n";
			cout<<"\t\t\t\t ENTER 5 TO ADD CRIMINAL\n";
			cout<<"\t\t\t\t ENTER 6 TO VIEW CRIMINALS\n";
			cout<<"\t\t\t\t ENTER 0 TO EXIT\n";
			cin>>choice;
		
			if(choice==1){
				system("cls");
				viewFlights();
			}
			else if(choice==2){
				system("cls");
				viewCustomers();
			}
			else if(choice==3){
				system("cls");
				addFlight();
				
			}
			else if(choice==4){
				system("cls");
				ViewFeedbacks();
			}
			else if(choice==5){
				system("cls");
				AddCriminals();
			}
			else if(choice==6){
				system("cls");
				ViewCriminals();
			}
		}while(choice!=0);	
	}
	else{
		
		cout<<"\nWRONG USERNAME OR PASSWORD\n" ;
		system("pause");
	}
	
}

////////////////////////////////////////////Customer Login///////////////////////////////////////////////////////
void CustomerLogin(){
	int choice;
	do{
		cout<<"------------------------------------------------------------------------------------------------------------------------\n";
		cout<<"                                          			CUSTOMER LOGIN                                                                 \n";
		cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
			cout<<"\t\t\t\t ENTER 1 TO BOOK FLIGHT:\n";
			cout<<"\t\t\t\t ENTER 2 TO VIEW YOUR FLIGHTS RECORD:\n";
			cout<<"\t\t\t\t ENTER 3 TO GIVE FEEDBACK\n";
			cout<<"\t\t\t\t ENTER 4 TO CANCEL FLIGHT\n";
			cout<<"\t\t\t\t ENTER 0 TO EXIT\n";
			cin>>choice;
		
			if(choice==1){
				system("cls");
				bookFlight();
			}
			else if(choice==2){
				system("cls");
				viewCustomerFlights();
			}
			else if(choice==3){
				system("cls");
				giveFeedback();
			}
		    else if(choice==4){
				system("cls");
				cancelFlights();	
			}
			
	}while(choice!=0);	
}


///////////////////////////////////////////GIVE FEEDBACK/////////////////////////////////////////////////////////
void giveFeedback(){
 	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"                                                  	 FEEDBACK CORNER                                                      \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\n";
	feedback *fd=new feedback();
	cout<<"\t\t\t ENTER YOUR PASSPORT ID:";
	cin>>fd->passportId;
	cout<<"\t\t\t HOW WAS YOUR EXPERIENCE WITH Friends AIRLINE?";
	cin>>fd->experience;
	cout<<"\t\t\t HOW WAS THE MEAL?";
	cin>>fd->meal;
	cout<<"\t\t\t HOW WAS THE STAFF?";
	cin>>fd->staff;
	cout<<"\t\t\t WAS DEPARTURE ON TIME?";
	cin>>fd->departure;
	fstream f;
    f.open("feedback.txt",ios::app);
    
    f<<fd->passportId<<"\t"<<fd->experience<<"\t"<<fd->meal<<"\t"<<fd->staff<<"\t"<<fd->departure<<endl;
	if(fdFirst==NULL){
		fdFirst=fd;
		fdLast=fd;
	}
	else{
		fdLast->fdNext=fd;
		fd->fdNext=NULL;
		fdLast=fd;
	}
	f.close();
    cout<<"\nTHANK YOU! YOUR FEEDBACK HAS BEEN STORED\n\n";
}
/////////////////////////////////////////////VIEW FEEDBACK//////////////////////////////////////////////////////
void ViewFeedbacks(){
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"                                                         	FEEDBACKS                                                      \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\n";
    feedback *fd=new feedback();
    fstream f;
    f.open("feedback.txt",ios::in);
    if(!f){
    	cout<<"NO FEEDBACK\n";
    	return;
	}
    if(!f.eof())
    {
        f>>fd->passportId>>fd->experience>>fd->meal>>fd->staff>>fd->departure;
        fdFirst=fd;
        fdFirst->fdNext=NULL;
    }
    fd=new feedback();
    if(!f.eof()){
        f>>fd->passportId>>fd->experience>>fd->meal>>fd->staff>>fd->departure;
        fdLast=fd;
        fdFirst->fdNext=fdLast;
    }
    fdLast->fdNext=NULL;
    while(!f.eof())
    {
        fd=new feedback();
          f>>fd->passportId>>fd->experience>>fd->meal>>fd->staff>>fd->departure;
         fdLast->fdNext=fd;

         fdLast=fd;
        fdLast->fdNext=NULL;
    }
    f.close();
	if(fdFirst==NULL){
		cout<<"NO FEEDBACKS YET\n\n";
	}
	else{
		feedback *fd=fdFirst;
		while(fd!=NULL&&fd->fdNext!=NULL){
			cout<<"PASSPORT ID:"<<fd->passportId<<endl;
			cout<<"EXPERIENCE WITH Friends AIRLINE:"<<fd->experience<<endl;
			cout<<"MEAL:"<<fd->meal<<endl;
			cout<<"STAFF:"<<fd->staff<<endl;
			cout<<"DEPARTURE ON TIME:"<<fd->departure<<endl;
			cout<<"\n\n";
			fd=fd->fdNext;
		}
	}
}
////////////////////////////////////////////ADD CRIMINAL//////////////////////////////////////////////////////////
void AddCriminals(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                                       ADDING CRIMINAL RECORD                                                  \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\n";
	criminals *c=new criminals();
	cout<<"\t\t\t ENTER PASSPORT ID:";
	cin>>c->passportId;
	cout<<"\t\t\t ENTER NAME:";
	cin>>c->name;
	cout<<"\t\t\t ENTER CNIC:";
	cin>>c->cnic;
	fstream f;
	
    f.open("criminal.txt",ios::app);
    f<<c->passportId<<"\t";
    f<<c->name<<"\t"<<c->cnic<<endl;
   
	if(crFirst==NULL){
		crFirst=c;
		crLast=c;
	}
	else{
		crLast->crNext=c;
		c->crNext=NULL;
		crLast=c;
	}
	f.close();
    cout<<"\nCRIMINAL RECORD HAS BEEN STORED SUCCESSFULLY\n\n";

}
//////////////////////////////////////////////////VIEW CRIMINALS RECORD////////////////////////////////////////////////////
void ViewCriminals(){
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"                                                         	CRIMINALS                                                      \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\n";
    criminals *cc=new criminals();
    fstream f;
    
    f.open("criminal.txt",ios::in);
    if(!f){
    	cout<<"EMPTY"<<endl;
    	return;
	}
    if(!f.eof())
    {
        f>>cc->passportId;
        f>>cc->name>>cc->cnic;
        crFirst=cc;
        crFirst->crNext=NULL;
    }
    cc=new criminals();
    if(!f.eof()){
        f>>cc->passportId;
        f>>cc->name>>cc->cnic;
        crLast=cc;
        crFirst->crNext=crLast;
    }
    crLast->crNext=NULL;
    while(!f.eof())
    {
        cc=new criminals();
         f>>cc->passportId>>cc->name>>cc->cnic; 
         crLast->crNext=cc; 
         crLast=cc;
        crLast->crNext=NULL;

    }
    f.close();
	if(crFirst==NULL){
		cout<<"NO CRIMINALS YET\n\n";
	}
	else{
		criminals *c=crFirst;
		while(c!=NULL&&c->crNext!=NULL){
			cout<<"\t\t\t NAME:"<<c->name<<"\n";
			cout<<"\t\t\t PASSPORT ID:"<<c->passportId<<"\n";
			cout<<"\t\t\t CNIC:"<<c->cnic;
			cout<<"\n\n";
			c=c->crNext;
		}
	}
}
////////////////////////////////////////////VIEW CUSTOMERS METHOD/////////////////////////////////////////////////
void viewCustomers(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                                     	 CUSTOMERS RECORD                                                         \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\n";
	
    customer *cust= new customer();
		ifstream ff("customer.txt");
		
		if(!ff){
			cout<<"EMPTY!"<<endl;
			return;
		}
		   ff>>cust->passportId;
    ff>>cust->name>>cust->cnic>>cust->age>>cust->phoneNumber>>cust->from>>cust->to>>cust->seatType;
  
		while(!ff.eof()){
			cout<<"CUSTOMER NAME:"<<cust->name<<"\n";
		cout<<"CUSTOMER CNIC ID:"<<cust->cnic<<"\n";
		cout<<"CUSTOMER PASSPORT ID:"<<cust->passportId<<"\n";
		cout<<"CUSTOMER AGE:"<<cust->age<<"\n";
		cout<<"CUSTOMER PHONE NUMBER:"<<cust->phoneNumber<<"\n";
		cout<<"FLIGHT FROM:"<<cust->from<<"\n";
		cout<<"FLIGHT TO:"<<cust->to<<"\n";
    	cout<<"SEAT TYPE:"<<cust->seatType<<"\n";
		cout<<endl;
		cout<<endl;
	ff>>cust->passportId;
    ff>>cust->name>>cust->cnic>>cust->age>>cust->phoneNumber>>cust->from>>cust->to>>cust->seatType;
 
		}
   
	
}
///////////////////////////////////////////VIEW CUSTOMER FLIGHTS///////////////////////////////////////////////
void viewCustomerFlights(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                                       	CUSTOMER FLIGHTS                                                        \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\n";
	customer *cust=cFirst;
	string name;
	cout<<"\t\t\t\t ENTER YOUR NAME:";
	cin>>name;
	
	while(cust!=NULL){
		if(name==cust->name){
			//to view flights of the customer
			cout<<"\t\t\t FLIGHT FROM:"<<cust->from<<"\n";
			cout<<"\t\t\t FLIGHT TO:"<<cust->to<<"\n";
			cout<<"\t\t\t SEAT TYPE:"<<cust->seatType<<"\n";
			cout<<"\t\t\t PLANE:"<<cust->plane<<"\n";
			cout<<"\n";
	
		}
		cust=cust->nextC;
	}
	}

///////////////////////////////////////////VIEW FLIGHTS METHOD/////////////////////////////////////////////////
void viewFlights(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                                       VIEW FLIGHTS                                                            \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	viewIslQuettaFlights();
	viewIslLahoreFlights();
	viewIslPeshawarFlights();
	
}	
void viewIslQuettaFlights(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                         VIEWING FLIGHTS IN PLANE ISLAMABAD-QUETTA                                             \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
		fstream ff;
    Isl_Quetta *temp=new Isl_Quetta();
    ff.open("quettaflight.txt",ios::in);
    if(!ff){
    	cout<<"\t\t\t\t THE PLANE IS EMPTY\n";
    	return;
	}
	
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    
	while(!ff.eof()){
		cout<<"\t\t\t\t CUSTOMER NAME:"<<temp->customerName<<"\n";
			cout<<"\t\t\t\t CUSTOMER PASSPORT-ID:"<<temp->passportId<<"\n";
			cout<<"\t\t\t\t CUSTOMER SEAT TYPE:"<<temp->seatType<<"\n";
			cout<<"\t\t\t\t CUSTOMER DESTINATION:"<<temp->to<<"\n";
			cout<<"\n";
		 ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    
	}

    ff.close();

	}
void viewIslLahoreFlights(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                         VIEWING FLIGHTS IN PLANE ISLAMABAD-LAHORE                                             \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
		fstream ff;
    Isl_Lhr *temp=new Isl_Lhr();
    ff.open("lahoreflight.txt",ios::in);
  if(!ff){
  cout<<"\t\t\t\t THE PLANE IS EMPTY\n";
    	return;
	}
	
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    
	while(!ff.eof()){
		cout<<"\t\t\t\t CUSTOMER NAME:"<<temp->customerName<<"\n";
			cout<<"\t\t\t\t CUSTOMER PASSPORT-ID:"<<temp->passportId<<"\n";
			cout<<"\t\t\t\t CUSTOMER SEAT TYPE:"<<temp->seatType<<"\n";
			cout<<"\t\t\t\t CUSTOMER DESTINATION:"<<temp->to<<"\n";
			cout<<"\n";
		 ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    
	}

    ff.close();
	
}
void viewIslPeshawarFlights(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                         VIEWING FLIGHTS IN PLANE ISLAMABAD-PESHAWAR                                             \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
		fstream ff;
    Isl_Peshawar *temp=new Isl_Peshawar();
    ff.open("peshawarflight.txt",ios::in);
     if(!ff){
  cout<<"\t\t\t\t THE PLANE IS EMPTY\n";
    	return;
	}
	
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    
	while(!ff.eof()){
		cout<<"\t\t\t\t CUSTOMER NAME:"<<temp->customerName<<"\n";
			cout<<"\t\t\t\t CUSTOMER PASSPORT-ID:"<<temp->passportId<<"\n";
			cout<<"\t\t\t\t CUSTOMER SEAT TYPE:"<<temp->seatType<<"\n";
			cout<<"\t\t\t\t CUSTOMER DESTINATION:"<<temp->to<<"\n";
			cout<<"\n";
		 ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    
	}

    ff.close();
	
	
}

//////////////////////////////////////////////ADD FLIGHT METHOD//////////////////////////////////////////////////
void addFlight(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                                         ADDING FLIGHTS                                                        \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	bookedQuetta();
	bookedLahore();
	bookedpeshawar();
	
}
//////////////////////////////////////////////BOOK FLIGHT METHOD/////////////////////////////////////////////////
void bookFlight(){
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                                                           BOOK FLIGHTS                                                        \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	cout<<"ORIGINITED:: ISLAMABAD                                                                                                         \n";
	cout<<"------------------------------------------------------------------------------------------------------------------------------ \n";
	cout<<"                    Peshawar                             Karachi                                                               \n";
	cout<<"                    Lahore                               Multan                                                                \n";
	cout<<"                                        Quetta                                                                                 \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	string city;
	int indexx=-1;
	int parent;
a:	cout<<"\nENTER CITY WHERE YOU WANT TO TRAVEL:";
	cin>>city;
	
	if(city=="Peshawar" || city=="peshawar"){
		indexx=1;
	}
	else if(city=="Karachi" || city=="karachi"){
		indexx=2;
	}
	else if(city=="Lahore" || city=="lahore"){
		indexx=3;
	}
	else if(city=="Multan" || city=="multan"){
		indexx=4;
	}
	else if(city=="Quetta" || city=="quetta"){
		indexx=5;
	}
	else{
		cout<<"WRONG CITY NAME!\n";
          goto a;

	}
	
	parent=dijkastra(indexx);
	
	//peshawar tak ka shortest distance
	if(indexx==1 && parent==0 ) 
	{
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Peshawar ";
		Plane_Isl_Peshawar("Peshawar");
	} 
	else if(indexx==1 && parent==3){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Lahore ";
		Plane_Isl_Lhr("Peshawar");
	}
	else if(indexx==1 && parent==5){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Quetta ";
		Plane_Isl_Quetta("Peshawar");
	}
	//karachi tak ka shortest distance
	if(indexx==2 && parent==1){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Peshawar ";
		Plane_Isl_Peshawar("Karachi");
	}
	
	else if(indexx==2 && parent==3){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Lahore ";
		Plane_Isl_Lhr("Karachi");
	}
	else if(indexx==2 && parent==5){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Quetta ";
		Plane_Isl_Quetta("Karachi");
	}
	//Lahore tak ka shortest distance
	if(indexx==3 && parent==0 ) 
	{
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Lahore ";
		Plane_Isl_Lhr("Lahore");
	} 
	else if(indexx==3 && parent==1){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Peshawar ";
		Plane_Isl_Peshawar("Lahore");
	}
	else if(indexx==3 && parent==5){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Quetta ";
		Plane_Isl_Quetta("Lahore");
	}
	//Multan tak ka shortest distance
	if(indexx==4 && parent==1){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Peshawar ";
		Plane_Isl_Peshawar("Multan");
	}
	
	else if(indexx==4 && parent==3){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Lahore ";
		Plane_Isl_Lhr("Multan");
	}
	else if(indexx==4 && parent==5){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Quetta ";
		Plane_Isl_Quetta("Multan");
	}
	//Quetta tak ka shortest distance
	if(indexx==5 && parent==0 ) 
	{
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Quetta ";
		Plane_Isl_Quetta("Quetta");
	} 
	else if(indexx==5 && parent==1){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Peshawar ";
		Plane_Isl_Peshawar("Quetta");
	}
	else if(indexx==5 && parent==3){
		cout<<"\nYOU WILL BE TRAVELLING FROM PLANE:Islamabad To Lahore ";
		Plane_Isl_Lhr("Quetta");
	}
}
void Plane_Isl_Quetta(string to){
	int choice;
	int s;
	string cri,nam,pass;
	Isl_Quetta *temp=new Isl_Quetta();
	cout<<"\nENTER YOUR NAME:";
	cin>>temp->customerName;
	cout<<"ENTER YOUR AGE:";
	cin>>temp->age;
	cout<<"ENTER YOUR PASSPORT ID:";
	cin>>temp->passportId;
	cout<<"ENTER YOUR CNIC NUMBER:";
	cin>>temp->cnic;
	
   ifstream ca("criminal.txt");
	ca>>pass>>nam>>cri;
	if(!ca){
		goto n;
	}
	while(!ca.eof()){
		if(cri==temp->cnic){
				cout<<"\n*****YOU CAN NOT BOOK FLIGHT! YOU ARE IN BLACK LIST*****\n\n";
			return;
		}
		ca>>pass>>nam>>cri;
	}
	ca.close();
	n:
	cout<<"ENTER YOUR PHONE NUMBER:";
	cin>>temp->customerPhoneNumber;
	
	temp->from="Islamabad";
	temp->to=to;
	
	cout<<"\nDO YOU WANT TO BOOK ECONOMICAL OR BUSINESS CLASS SEATS?\n";
	cout<<"PRESS 1 FOR BUSINESS CLASS:\n";
	cout<<"PRESS 2 for ECONOMICLA CLASS:\n";
	cin>>s;
	if(s==1){
		temp->seatType="Business";
	}
	else{
		temp->seatType="Economical";
	}
	ofstream ff;
    ff.open("quetta.txt",ios::app);
    ff<<temp->passportId<<"\t";
    ff<<temp->customerName<<"\t"<<temp->cnic<<"\t"<<temp->age<<"\t"<<temp->customerPhoneNumber<<"\t"<<temp->from<<"\t"<<temp->to<<"\t"<<temp->seatType<<endl;
	if(qFirst==NULL){
		qFirst=temp;
		qLast=temp;
		
	}
	else{
		temp->prevF=qLast;
		temp->nextF=NULL;
		qLast->nextF=temp;
		qLast=temp;
	}
  ff.close();
	cout<<"\n PROCESSING....\n";
	cout<<"\n ADMIN WILL LATER ADD YOU INTO FLIGHT AFTER CHECKING YOUR PROFILE\n";
	Sleep(3000);

	
	
}
void Plane_Isl_Lhr(string to){
	int choice,s;
	string cri,pass,nam;
	Isl_Lhr *temp=new Isl_Lhr();
	cout<<"\nENTER YOUR NAME:";
	cin>>temp->customerName;
	cout<<"ENTER YOUR AGE:";
	cin>>temp->age;
	cout<<"ENTER YOUR PASSPORT ID:";
	cin>>temp->passportId;
	cout<<"ENTER YOUR CNIC NUMBER:";
	cin>>temp->cnic;
	ifstream ca("criminal.txt");
	ca>>pass>>nam>>cri;
	if(!ca){
		goto n;
	}
	while(!ca.eof()){
		if(cri==temp->cnic){
				cout<<"\n*****YOU CAN NOT BOOK FLIGHT! YOU ARE IN BLACK LIST*****\n\n";
			return;
		}
		ca>>pass>>nam>>cri;
	}
	ca.close();
	n:
	cout<<"ENTER YOUR PHONE NUMBER:";
	cin>>temp->customerPhoneNumber;
	
	temp->from="Islamabad";
	temp->to=to;
	
	cout<<"\nDO YOU WANT TO BOOK ECONOMICAL OR BUSINESS CLASS SEATS?\n";
	cout<<"PRESS 1 FOR BUSINESS CLASS:\n";
	cout<<"PRESS 2 for ECONOMICAL CLASS:\n";
	cin>>s;
	if(s==1){
		temp->seatType="Business";
	}
	else{
		temp->seatType="Economical";
	}
	fstream ff;
    ff.open("Lahore.txt",ios::app);
    ff<<temp->passportId<<"\t";
    ff<<temp->customerName<<"\t"<<temp->cnic<<"\t"<<temp->age<<"\t"<<temp->customerPhoneNumber<<"\t"<<temp->from<<"\t"<<temp->to<<"\t"<<temp->seatType<<endl;
    ff.close();
	if(lFirst==NULL){
		lFirst=temp;
		lLast=temp;
		lLast->nextF=NULL;
		lLast->prevF=NULL;
	}
	else{
		
		temp->prevF=lLast;
		temp->nextF=NULL;
		lLast->nextF=temp;
		lLast=temp;
	}	

	cout<<"\n PROCESSING....\n";
	cout<<"\n ADMIN WILL LATER ADD YOU INTO FLIGHT AFTER CHECKING YOUR PROFILE\n";
	Sleep(3000);
}
void Plane_Isl_Peshawar(string to){
	int choice;
	int seat;
	string cri,nam,pass;
	Isl_Peshawar *temp=new Isl_Peshawar();
	cout<<"\nENTER YOUR NAME:";
	cin>>temp->customerName;
	cout<<"ENTER YOUR AGE:";
	cin>>temp->age;
	cout<<"ENTER YOUR PASSPORT ID:";
	cin>>temp->passportId;
	cout<<"ENTER YOUR CNIC NUMBER:";
	cin>>temp->cnic;
	ifstream ca("criminal.txt");
	ca>>pass>>nam>>cri;
	if(!ca){
		goto n;
	}
	while(!ca.eof()){
		if(cri==temp->cnic){
				cout<<"\n*****YOU CAN NOT BOOK FLIGHT! YOU ARE IN BLACK LIST*****\n\n";
			return;
		}
		ca>>pass>>nam>>cri;
	}
	ca.close();
	n:
	cout<<"ENTER YOUR PHONE NUMBER:";
	cin>>temp->customerPhoneNumber;
	
	temp->from="Islamabad";
	temp->to=to;
	
	cout<<"\nDO YOU WANT TO BOOK ECONOMICAL OR BUSINESS CLASS SEATS?\n";
	cout<<"PRESS 1 FOR BUSINESS CLASS:\n";
	cout<<"PRESS 2 for ECONOMICLA CLASS:\n";
	cin>>seat;
	if(seat==1){
		temp->seatType="Business";
	}
	else{
		temp->seatType="Economical";
	}
		fstream ff;
    ff.open("Peshawar.txt",ios::app);
    ff<<temp->passportId<<"\t";
    ff<<temp->customerName<<"\t"<<temp->cnic<<"\t"<<temp->age<<"\t"<<temp->customerPhoneNumber<<"\t"<<temp->from<<"\t"<<temp->to<<"\t"<<temp->seatType<<endl;
    ff.close();
	if(pFirst==NULL){
		pFirst=temp;
		pLast=temp;
		
	}
	else{
		temp->prevF=pLast;
		temp->nextF=NULL;
		pLast->nextF=temp;
		pLast=temp;
	}
	cout<<"\n PROCESSING....\n";
	cout<<"\n ADMIN WILL LATER ADD YOU INTO FLIGHT AFTER CHECKING YOUR PROFILE\n";
	Sleep(3000);	
}
//popping top 50 elements from request flight list
void bookedQuetta(){
	
	
	fstream ff;
    Isl_Quetta *temp=new Isl_Quetta();
    ff.open("quetta.txt",ios::in);
    if(!ff){
    	return;
	}
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	qFirst=temp;
        qFirst->nextF=NULL;
    }
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	qLast=temp;
        
        qLast->prevF=qFirst;
        qFirst->nextF=qLast;
        qLast->nextF=NULL;
    }
   
    while(!ff.eof())
    {
   
    ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    		qLast->nextF=temp;
        temp->prevF=qLast;
        qLast=temp;
        qLast->nextF=NULL;	
    }
    ff.close();
	
fstream w;
    w.open("quettaflight.txt",ios::app);
    ofstream cu("customer.txt",ios::app);
    
    Isl_Quetta *top=qFirst;
	int i=0;
    while(top!=NULL && i<50){
			
			flights_isl_quetta *temp=new flights_isl_quetta();
			customer *cust=new customer();	
			temp->customerName=top->customerName;
			temp->passportId=top->passportId;
			temp->seatType=top->seatType;
			temp->to=top->to;
		
			if(qtFirst==NULL){
				qtFirst=qtLast=temp;
				qtLast->prevF=NULL;
				qtLast->nextF=NULL;
			}
			else{
				qtLast->nextF=temp;
				temp->prevF=qtLast;
				qtLast=temp;
				temp->nextF=NULL;
				
			}
		
		//adding to customer list
			cust->name=top->customerName;
			cust->age=top->age;
			cust->cnic=top->cnic;
			cust->passportId=top->passportId;
			cust->phoneNumber=top->customerPhoneNumber;
			cust->from=top->from;
			cust->to=top->to;
			cust->seatType=top->seatType;
			cust->plane="ISL-QUETTA";

			if(cFirst==NULL){
				cFirst=cust;
				cLast=cust;
			}
			else{
				cLast->nextC=cust;
				cust->nextC=NULL;
				cLast=cust;
			}
			
			w<<cust->passportId<<"\t";
            w<<cust->name<<"\t"<<cust->cnic<<"\t"<<cust->age<<"\t"<<cust->phoneNumber<<"\t"<<cust->from<<"\t"<<cust->to<<"\t"<<cust->seatType<<endl;
		    cu<<cust->passportId<<"\t";
            cu<<cust->name<<"\t"<<cust->cnic<<"\t"<<cust->age<<"\t"<<cust->phoneNumber<<"\t"<<cust->from<<"\t"<<cust->to<<"\t"<<cust->seatType<<endl;
  
			qFirst=qFirst->nextF;
			top=qFirst;
			i++;
		QbookingReceipt(temp);
		
		
	}
    cu.close();
    remove("quetta.txt");
   
	cout<<"\n PROCESSING....\n";
	Sleep(3000);
	
	
}
//popping top 50 elements from request flight list
void bookedLahore(){
	fstream ff;
    Isl_Lhr *temp=new Isl_Lhr();
    ff.open("lahore.txt",ios::in);
    if(!ff){
    	return;
	}
    if(!ff.eof())
    {
    ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	lFirst=temp;
        lFirst->nextF=NULL;
    }
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	lLast=temp;
        
        lLast->prevF=lFirst;
        lFirst->nextF=lLast;
        lLast->nextF=NULL;
    }
    while(!ff.eof())
    {
        ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	lLast->nextF=temp;
        temp->prevF=lLast;
        lLast=temp;
        lLast->nextF=NULL;
    }
    ff.close();
	Isl_Lhr *top=lFirst;
	ofstream cu("customer.txt",ios::app);
fstream w("lahoreflight.txt",ios::app);
	for(int i=0;i<50;i++){
		if(top!=NULL){
			flights_isl_lhr *temp=new flights_isl_lhr();
			customer *cust=new customer();
			
			temp->customerName=top->customerName;
			temp->passportId=top->passportId;
			temp->seatType=top->seatType;
			temp->to=top->to;
			
			if(lhrFirst==NULL){
				lhrFirst=temp;
				lhrLast=temp;
				lhrLast->nextF=NULL;
			}
			else{
				lhrLast->nextF=temp;
				temp->nextF=NULL;
				lhrLast=temp;
				lhrLast->nextF=NULL;
			}
			
		
			cust->name=top->customerName;
			cust->age=top->age;
			cust->cnic=top->cnic;
			cust->passportId=top->passportId;
			cust->phoneNumber=top->customerPhoneNumber;
			cust->from=top->from;
			cust->to=top->to;
			cust->seatType=top->seatType;
			cust->plane="ISL-LAHORE";
		
			if(cFirst==NULL){
				cFirst=cust;
				cLast=cust;
			}
			else{
				cLast->nextC=cust;
				cust->nextC=NULL;
				cLast=cust;
			}
			w<<cust->passportId<<"\t";
            w<<cust->name<<"\t"<<cust->cnic<<"\t"<<cust->age<<"\t"<<cust->phoneNumber<<"\t"<<cust->from<<"\t"<<cust->to<<"\t"<<cust->seatType<<endl;
        	cu<<cust->passportId<<"\t";
            cu<<cust->name<<"\t"<<cust->cnic<<"\t"<<cust->age<<"\t"<<cust->phoneNumber<<"\t"<<cust->from<<"\t"<<cust->to<<"\t"<<cust->seatType<<endl;
  
			lFirst=lFirst->nextF;
			top=lFirst;
			LbookingReceipt(temp);
		}
	}
	w.close();
	cu.close();
	remove("lahore.txt");
	cout<<"\n PROCESSING....\n";
	Sleep(3000);
	
}
//popping top 50 elements from request flight list
void bookedpeshawar(){
		fstream ff;
    Isl_Peshawar *temp=new Isl_Peshawar();
    ff.open("Peshawar.txt",ios::in);
    if(!ff){
    	return;
	}
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	pFirst=temp;
        pFirst->nextF=NULL;
    }
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	pLast=temp;
       
        pLast->prevF=pFirst;
        pFirst->nextF=pLast;
         pLast->nextF=NULL;
    }
    while(!ff.eof())
    {

        ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	pLast->nextF=temp;
        temp->prevF=pLast;
        pLast=temp;
        pLast->nextF=NULL;
    }
    ff.close();
    fstream w;
    ofstream cu("customer.txt",ios::app);
     w.open("peshawarflight.txt",ios::app);
	Isl_Peshawar *top=pFirst;
	
	
	for(int i=0;i<50;i++){
		
		if(top !=NULL){
			flights_isl_peshawar *temp=new flights_isl_peshawar();
			customer *cust= new customer();
			
			temp->customerName=top->customerName;
			temp->passportId=top->passportId;
			temp->seatType=top->seatType;
			temp->to=top->to;
			
			if(pshFirst==NULL){
				pshFirst=temp;
				pshLast=temp;
				pshLast->nextF=NULL;
			}
			else{
				pshLast->nextF=temp;
				temp->nextF=NULL;
				pshLast=temp;
				pshLast->nextF=NULL;
			}
			
			cust->name=top->customerName;
			cust->age=top->age;
			cust->cnic=top->cnic;
			cust->passportId=top->passportId;
			cust->phoneNumber=top->customerPhoneNumber;
			cust->from=top->from;
			cust->to=top->to;
			cust->seatType=top->seatType;
			cust->plane="ISL_PESHAWAR";
		
			if(cFirst==NULL){
				cFirst=cust;
				cLast=cust;
			}
			else{
				cLast->nextC=cust;
				cust->nextC=NULL;
				cLast=cust;
			}
			w<<cust->passportId<<"\t";
            w<<cust->name<<"\t"<<cust->cnic<<"\t"<<cust->age<<"\t"<<cust->phoneNumber<<"\t"<<cust->from<<"\t"<<cust->to<<"\t"<<cust->seatType<<endl;
		 	cu<<cust->passportId<<"\t";
            cu<<cust->name<<"\t"<<cust->cnic<<"\t"<<cust->age<<"\t"<<cust->phoneNumber<<"\t"<<cust->from<<"\t"<<cust->to<<"\t"<<cust->seatType<<endl;
  
		
			pFirst=pFirst->nextF;
			top=pFirst;
			PbookingReceipt(temp);
		}
			
	}
     w.close();
     cu.close();
	remove("Peshawar.txt");
	cout<<"\n PROCESSING....\n";
	Sleep(3000);
	
}

////////////////////////////////////////////DIJKASTRA METHOD///////////////////////////////////////////////////

int dijkastra(int indexOfCity){	
	int parent=-1,parentdistanceFromSource;
	//creating an array that would store the values of source row
    for(int i=0;i<6;i++){
    	
    	if(i==source){
    		arr[i]=0;
		}
		else{
			if(routes[source][i]>0){
				arr[i]=routes[source][i];
			}
			else{
				arr[i]=INT_MAX;
			}
		}
	}
	//copying source index array into distance array
	for(int i=0;i<6;i++){
		
		d[i]=arr[i];
	}
	
	//source index array checking
	for(int i=0;i<6;i++){
	
		if(arr[i]>0 && arr[i]!=INT_MAX){
			check(arr[i],i,0,d);
		}
	}
	
	//checking distance of nodes that are not found yet
	for(int i=0;i<6;i++){
		
		if(d[i]==INT_MAX){
			search(i,d);
		}
	}
	
	
	for(int i=0;i<6;i++){
		
		if(routes[i][indexOfCity]!=0){
			parentdistanceFromSource=d[i];
			if((parentdistanceFromSource+routes[i][indexOfCity])==d[indexOfCity]){
				parent=i;
			}
		}
	}
	return parent;
}
////////////////////////////////////////CHECK METHOD FOR DIJKASTRA/////////////////////////////////////////////////////////////
void check(int value, int index, int i,int d[]){
	int distance=0;
	if(i<6){
		if(i!=source && i!=index){
			if(routes[index][i] >0){
				distance=routes[index][i]+value;
				if(distance<d[i]){
					d[i]=distance;
				}
			}
		}
		check(value,index,++i,d);
	}
}
///////////////////////////////////////////SEARCH METHOD FOR DIJKASTRA////////////////////////////////////////////////////////
int search(int x, int d[]){
	int distance=0;
	for(int i=0;i<6;i++){
		if(routes[i][x]>0 && d[i]!=INT_MAX){
			distance=d[i]+routes[i][x];
			if(distance<d[x]){
				d[x]=distance;
			}
		
		}
	
	}
}
/////////////////////////////////////////CANCEL FLIGHT METHODS//////////////////////////////////////////////////
int SearchCustomerList(string pp){
	customer *p=cFirst;
	int num;
	while(p!=NULL){
		if(p->passportId==pp){
			num=1;
			break;
		}
		else{
			p=p->nextC;
		}
	}
	if(num==1){
		return num;
	}
	else{
		return 0;
	}
}
int SearchQuettaList(string pp){
	Isl_Quetta *p=qFirst;
	int num=0;
	while(p!=NULL){
		if(p->passportId==pp){
			num=1;
			break;
		}
		else{
			p=p->nextF;
		}
	}
	if(num==1){
		
		return num;
		
	}
	else{
		
		return 0;
	}
}

int SearchLhrList(string pp){
	Isl_Lhr *p=lFirst;
	int num;
	while(p!=NULL){
		if(p->passportId==pp){
			num=1;
			break;
		}
		else{
			p=p->nextF;
		}
	}
	if(num==1){
		return num;
	}
	else{
		return 0;
	}
}
int SearchPeshawarList(string pp){
	Isl_Peshawar *p=pFirst;
	int num;
	while(p!=NULL){
		if(p->passportId==pp){
			num=1;
			break;
		}
		else{
			p=p->nextF;
		}
	}
	if(num==1){
		return num;
	}
	else{
		return 0;
	}
}
/////////////////////////////////////////////////CANCEL FLIGHT///////////////////////////////////////////////////////
void cancelFlights(){
	
	string pp;
	cout<<"\nEnter your passport id: ";
	cin>>pp;
	
	//Search in customer list first
	int FoundCust=SearchCustomerList(pp);
	if (FoundCust==1){
		cout<<"\nFlight cannot be cancelled once booked!";
	}
	else{
		fstream ff;
    Isl_Quetta *temp=new Isl_Quetta();
    ff.open("quetta.txt",ios::in);
    if(ff){
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	qFirst=temp;
        qFirst->nextF=NULL;
    }
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	qLast=temp;
        
        qLast->prevF=qFirst;
        qFirst->nextF=qLast;
        qLast->nextF=NULL;
    }
   
    while(!ff.eof())
    {
   
    ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    		qLast->nextF=temp;
        temp->prevF=qLast;
        qLast=temp;
        qLast->nextF=NULL;	
    }
    ff.close();
    
	}
    
		int FoundQuetta=SearchQuettaList(pp);
		if (FoundQuetta==1){
			
	
			Isl_Quetta *p=qFirst;
			while(p->passportId!=pp){
				p=p->nextF;
			}
			if (p==qFirst){
				qFirst=qFirst->nextF;
				delete p;
				cout<<"FLIGHT IS CANCELLED\n";
			}
			else if (p==qLast){
				qLast=qLast->prevF;
				delete p;
				cout<<"FLIGHT IS CANCELLED\n";
			}
			else{
				Isl_Quetta *a=p->prevF;
				Isl_Quetta *b=p->nextF;
				a->nextF=b;
				b->prevF=a;
				delete p;
				cout<<"FLIGHT IS CANCELLED\n";
			}
			
				remove("quetta.txt");
			ofstream fs("quetta.txt",ios::app);
				
				Isl_Quetta *n=qFirst;
			while(n!=NULL){
				    fs<<n->passportId<<"\t";
    fs<<n->customerName<<"\t"<<n->cnic<<"\t"<<n->age<<"\t"<<n->customerPhoneNumber<<"\t"<<n->from<<"\t"<<n->to<<"\t"<<n->seatType<<endl;
         n=n->nextF;
			}	
		}
		else{
			
				fstream ff;
    Isl_Lhr *temp=new Isl_Lhr();
    ff.open("lahore.txt",ios::in);
    if(ff){
    	if(!ff.eof())
    {
    ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	lFirst=temp;
        lFirst->nextF=NULL;
    }
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	lLast=temp;
        
        lLast->prevF=lFirst;
        lFirst->nextF=lLast;
        lLast->nextF=NULL;
    }
    while(!ff.eof())
    {
        ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	lLast->nextF=temp;
        temp->prevF=lLast;
        lLast=temp;
        lLast->nextF=NULL;
    }
    ff.close();
   
	}
    
			int FoundLhr=SearchLhrList(pp);
			if(FoundLhr==1){
			
				Isl_Lhr *p=lFirst;
				while(p->passportId!=pp){
					p=p->nextF;
				}
				cout<<"\n"<<p->passportId;
				if (p==lFirst){
					
					lFirst=lFirst->nextF;
					delete p;
					cout<<"FLIGHT IS CANCELLED\n";
				}
				else if (p==lLast){
					
					lLast=lLast->prevF;
					delete p;
					cout<<"FLIGHT IS CANCELLED\n";
				}
				else{
				
					Isl_Lhr *a=p->prevF;
					Isl_Lhr *b=p->nextF;
					a->nextF=b;
					b->prevF=a;
					delete p;
					cout<<"FLIGHT IS CANCELLED\n";
				}
				
				 remove("lahore.txt");
			ofstream fs("lahore.txt",ios::app);
				
				Isl_Lhr *n=lFirst;
			while(n!=NULL){
				    fs<<n->passportId<<"\t";
    fs<<n->customerName<<"\t"<<n->cnic<<"\t"<<n->age<<"\t"<<n->customerPhoneNumber<<"\t"<<n->from<<"\t"<<n->to<<"\t"<<n->seatType<<endl;
               n=n->nextF;
			}	
			}
			else{
				
				fstream ff;
    Isl_Peshawar *temp=new Isl_Peshawar();
    ff.open("Peshawar.txt",ios::in);
    if(!ff){
    	return;
	}
   
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	pFirst=temp;
        pFirst->nextF=NULL;
    }
    if(!ff.eof())
    {
         ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	pLast=temp;
       
        pLast->prevF=pFirst;
        pFirst->nextF=pLast;
         pLast->nextF=NULL;
    }
    while(!ff.eof())
    {

        ff>>temp->passportId;
    ff>>temp->customerName>>temp->cnic>>temp->age>>temp->customerPhoneNumber>>temp->from>>temp->to>>temp->seatType;
    	pLast->nextF=temp;
        temp->prevF=pLast;
        pLast=temp;
        pLast->nextF=NULL;
    }
    ff.close();
    
				int FoundPeshawar=SearchPeshawarList(pp);
				if(FoundPeshawar==1){
					
					Isl_Peshawar *p=pFirst;
					while(p->passportId!=pp){
						p=p->nextF;
					}
					if (p==pFirst){
						pFirst=pFirst->nextF;
						delete p;
						cout<<"FLIGHT IS CANCELLED\n";
					}
					else if (p==pLast){
						pLast=pLast->prevF;
						delete p;
						cout<<"FLIGHT IS CANCELLED\n";
					}
					else{
						Isl_Peshawar *a=p->prevF;
						Isl_Peshawar *b=p->nextF;
						a->nextF=b;
						b->prevF=a;
						delete p;
						cout<<"FLIGHT IS CANCELLED\n";
					}
					
				remove("Peshawar.txt");
			ofstream fs("Peshawar.txt",ios::app);
				
				Isl_Peshawar *n=pFirst;
			while(n!=NULL){
				    fs<<n->passportId<<"\t";
    fs<<n->customerName<<"\t"<<n->cnic<<"\t"<<n->age<<"\t"<<n->customerPhoneNumber<<"\t"<<n->from<<"\t"<<n->to<<"\t"<<n->seatType<<endl;
              n=n->nextF;
			}	
				}
			}
		}
	}
}
//////////////////////////////////BOOKING RECEIPT METHODS///////////////////////////////////////
void QbookingReceipt(flights_isl_quetta *temp){
	
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"                                                           BOOKING RECEIPT                                        \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	cout<<"\nMR/MISS "<<temp->customerName<<" WELCOME TO Fiends AIRLINE!\n YOUR FLIGHT HAS BEEN BOOKED\n";
    cout<<"TRAVELLING FROM:ISLAMABAD\n";
	cout<<"TRAVELLING TO:"<<temp->to<<"\n";	
	cout<<"SEAT TYPE:"<<temp->seatType<<"\n";
    //for current date/time
    time_t date_time = time(0);
	//convert date_time to string form
    char* dt = ctime(&date_time);
    cout << "DATE AND TIME FOR YOUR FLIGHT IS: " << dt <<"\n";
}
void LbookingReceipt(flights_isl_lhr *temp){
	
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"                                                           BOOKING RECEIPT                                        \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	cout<<"\nMR/MISS "<<temp->customerName<<" WELCOME TO Friends AIRLINE!\n YOUR FLIGHT HAS BEEN BOOKED\n";
    cout<<"TRAVELLING FROM:ISLAMABAD\n";
	cout<<"TRAVELLING TO:"<<temp->to<<"\n";	
	cout<<"SEAT TYPE:"<<temp->seatType<<"\n";
    //for current date/time
    time_t date_time = time(0);
	//convert date_time to string form
    char* dt = ctime(&date_time);
    cout << "DATE AND TIME FOR YOUR FLIGHT IS: " << dt <<"\n";
}
void PbookingReceipt(flights_isl_peshawar *temp){
	
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"                                                           BOOKING RECEIPT                                        \n";
	cout<<"-------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n";
	cout<<"\nMR/MISS "<<temp->customerName<<" WELCOME TO Friends AIRLINE!\n YOUR FLIGHT HAS BEEN BOOKED\n";
    cout<<"TRAVELLING FROM:ISLAMABAD\n";
	cout<<"TRAVELLING TO:"<<temp->to<<"\n";	
	cout<<"SEAT TYPE:"<<temp->seatType<<"\n";
    //for current date/time
    time_t date_time = time(0);
	//convert date_time to string form
    char* dt = ctime(&date_time);
    cout << "DATE AND TIME FOR YOUR FLIGHT IS: " << dt <<"\n";
}
void end_program()
{
	system("cls");

	cout << "\n\n\n\n\t\t\t\t\t WAIT FOR A MOMENT , PROGRAM IS GOING TO CLOSE ! ";
	Sleep(3000);
	cout << "\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@     @@         @@     @@@@@@@@@@@@            \n";
	cout << "\t\t\t\t\t@@        @@      @@       @@      @@                         \n";
	cout << "\t\t\t\t\t@@        @@       @@     @@       @@                         \n";
	cout << "\t\t\t\t\t@@@@@@@@@@@@        @@   @@        @@                         \n";
	cout << "\t\t\t\t\t@@          @@       @@ @@         @@@@@@@@@               \n";
	cout << "\t\t\t\t\t@@          @@        @@@          @@                         \n";
	cout << "\t\t\t\t\t@@          @@        @@@          @@                         \n";
	cout << "\t\t\t\t\t@@@@@@@@@@@@          @@@          @@@@@@@@@@@@            \n";

	cout << endl;

	cout << "\n\n\t\t\t\t\t" << setw(58) << setfill('~') << "~" << endl;
	cout << "\t\t\t\t\t||        - MUHAMMAD OSAMA ABBASI                       ||\n";
	cout << "\t\t\t\t\t||        - HASNAIN ALI BASHIR                          ||\n";
	cout << "\t\t\t\t\t||        - HAMZA QADIR                                 ||\n";
	cout << "\t\t\t\t\t||        - SAAD ALI MUBARAK                            ||\n";
	cout << "\t\t\t\t\t" << setw(58) << setfill('~') << "~" << endl;
	cout << "\n\n\t\t\t\t\tPress any key to continue . . .";
	_getch();
	exit(1);
}
