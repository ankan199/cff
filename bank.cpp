#include<iostream>
#include<fstream>
//#include<cstdlib>
using namespace std;
class account_query
{              //to create a bank management system in c++
	private:
		char accntnmbr[20];
		char firstnm[10];
		char lstnm[10];
		float tot_bal;
	public:
		void read_data();
		void show_data();
		void write_rec();
		void read_rec();
		void search_rec();
		void edit_rec();
		void delete_rec();
};
void account_query::read_data() //inheritance optr. for function.
{
	cout<<"enter account number\n";
	cin>>accntnmbr;
	cout<<"enter first name\n";
	cin>>firstnm;
	cout<<"enter last name\n";
	cin>>lstnm;
	cout<<"enter balance\n";
	cin>>tot_bal;
	cout<<endl;
}
void account_query::show_data()
{
	cout<<"account number: "<<accntnmbr<<endl;
	cout<<"first name: "<<firstnm<<endl;
	cout<<"last name: "<<lstnm<<endl;
	cout<<"current balance: "<<tot_bal<<endl;
	cout<<"............................................."<<endl;
}
void account_query::write_rec()    // writing in a file
{
	ofstream outfl;
	outfl.open("record.doc",ios::binary|ios::app);
	read_data();
	outfl.write(reinterpret_cast<char *>(this),sizeof(*this));
	outfl.close();
}
void account_query::read_rec()  /// reading a file
{
	ifstream infl;
	infl.open("record.doc",ios::binary);
	if(!infl)
	{
		cout<<"error in opening file"<<endl;
		return;
	}
	cout<<"\n******data from file*******"<<endl;
	while(!infl.eof())
	{
		if(infl.read(reinterpret_cast<char *>(this),sizeof(*this))>0)
		{
			show_data();
		}
	}
	infl.close();
}
void account_query::search_rec()
{
	int n;
	ifstream infl;
	infl.open("record.doc",ios::binary);
	if(!infl)
	{
		cout<<"file not found/error in opening file\n"<<endl;
		return;
	}
	infl.seekg(0,ios::end);
	int count=infl.tellg()/sizeof(*this);
	cout<<"\n there are "<<count<<" record in the file";
	cout<<"\n enter record number to search: ";
	cin>>n;
	infl.seekg((n-1)*sizeof(*this));
	infl.read(reinterpret_cast<char *>(this),sizeof(*this));
	show_data();
}
void account_query::edit_rec()    //using f stream
{
	int n;
	fstream iofl;
	iofl.open("record.doc",ios::in|ios::binary);
	if(!iofl)
	{
		cout<<"error in opening file\n";
		return;
	}
	iofl.seekg(0,ios::end);
	int count=iofl.tellg()/sizeof(*this);
	cout<<"there are "<<count<<" record in this file\n";
	cout<<"\n enter record number to edit :";
	cin>>n;
	iofl.seekg((n-1)*sizeof(*this));
	iofl.read(reinterpret_cast<char*>(this),sizeof(*this));
	cout<<" record "<<n<<" has following data"<<endl;
	show_data();
	iofl.close();
	iofl.open("record.doc",ios::out|ios::in|ios::binary);
	iofl.seekp((n-1)*sizeof(*this));
	cout<<"\n enter data to modify "<<endl;
	read_data();
	iofl.write(reinterpret_cast<char*>(this),sizeof(*this));
}
void account_query::delete_rec() // using ifstream
{
	int n;
	ifstream infl;
	infl.open("record.doc",ios::binary);
	if(!infl)
	{
		cout<<"error in opening file\n";
		return;
	}
	infl.seekg(0,ios::end);
	int count=infl.tellg()/sizeof(*this);
	cout<<"\n there are "<<count<<" record in the file";
	cout<<"\n enter record number to delete: ";
	cin>>n;
	fstream tmpfl;
	tmpfl.open("tmpfile.doc",ios::out|ios::binary);
	infl.seekg(0);
	for(int i=0;i<count;i++)
	{
		infl.read(reinterpret_cast<char*>(this),sizeof(*this));
		if(i==(n-1))
		{
			continue;
	    }
		    tmpfl.write(reinterpret_cast<char*>(this),sizeof(*this));
	    
	}
	infl.close();
	tmpfl.close();
	remove("record.doc");
	rename("tmpfile.doc","record.doc");
}
int main()
{
	account_query A;
	int choice;
	cout<<"*** Account Information System ***"<<endl;
	while(true)
	{
		cout<<"select one option below";
		cout<<"\n\t1--> Add record to a file";
		cout<<"\n\t2--> show record from a file";
		cout<<"\n\t3--> search record from a file";
		cout<<"\n\t4--> update record";
		cout<<"\n\t5--> delete record";
		cout<<"\n\t6--> quit";
		cout<<"\n enter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
		    system("cls");
			A.write_rec();
			break;
			case 2:
			system("cls");
			A.read_rec();
			break;
			case 3:
			system("cls");
			A.search_rec();
			break;
			case 4:
			system("cls");
			A.edit_rec();
			break;
			case 5:
			system("cls");
			A.delete_rec();
			break;
			case 6:
			system("cls");
			exit(0);
			break;
			default:
				cout<<"\n enter correct choice";
				exit(0);
		}
			
	}
	system("pause");
	return 0;
	
}
