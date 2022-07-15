#include<dos.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
class customer
{
	private:
	long ano;
	char cname[30];
	char phone[15];
	char address[100];
	long balance;
	char status;  //I->inactive, A->active
	public:
	void menu();
	void create();
	void modify();
	void closeaccount();
	void search();
	void displayall();
	int validate(long x);
	void update(long x, long y);
	long getano();
	char* getcname();
	char* getphone();
	char* getaddress();
	long getbalance();
	char getstatus();
};

void customer::menu()
{
	clrscr();
	int ch;
	do
	{       clrscr();
		cout<<"1.Create account"<<endl;
		cout<<"2.Modify details"<<endl;
		cout<<"3.Close existing account"<<endl;
		cout<<"4.Search for an account"<<endl;
		cout<<"5.display all account details"<<endl;
		cout<<"6.Back to main menu"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>ch;
		if(ch==1)
		{
			create();
		}
		else if(ch==2)
		{
			modify();
		}
		else if(ch==3)
		{
			 closeaccount();
		}
		else if(ch==4)
		{
			search();
		}
		else if(ch==5)
		{
			displayall();
		}
		else
		{
			return;
		}
	}while(ch!=6);
	getch();
}

void customer::create()
{
	clrscr();
	fstream f;
	f.open("cust.dat",ios::app|ios::binary);
	cout<<"Enter account number"<<endl;
	cin>>ano;
	cout<<"Enter customer name"<<endl;
	gets(cname);
	cout<<"Enter phone number"<<endl;
	gets(phone);
	cout<<"Enter address"<<endl;
	gets(address);
	cout<<"Balance= Rs. 1000"<<endl; // an initial amount of Rs. 1000 is to be deposited
	balance=1000;
	status='A';
	f.write((char*)this,sizeof(*this));
	cout<<"Account has been created"<<endl;
	getch();
}

void customer::modify()
{
	clrscr();
	int flag=0;
	fstream f1,f2;
	long n;
	cout<<"Enter account number of the customer to be modified"<<endl;
	cin>>n;
	f1.open("cust.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(ano!=n)
		{
			f2.write((char*)this,sizeof(*this));
		}
		else
		{
			flag=1;
			cout<<"Exixting details"<<endl;
			cout<<"Account number-"<<ano<<endl;
			cout<<"Account holder's name-"<<cname<<endl;
			cout<<"Registered phone number"<<phone<<endl;
			cout<<"Address-"<<address<<endl;
			cout<<"Balance-"<<balance<<endl;
			cout<<"Status-"<<status<<endl;
			cout<<"Enter new name"<<endl;
			gets(cname);
			cout<<"Enter new phone number"<<endl;
			gets(phone);
			cout<<"enter new address"<<endl;
			gets(address);
			f2.write((char*)this,sizeof(*this));
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	f2.close();
	remove("cust.dat");
	rename("temp.dat","cust.dat");
	if(flag==0)
	{
		cout<<"Account not found"<<endl;
	}
	getch();
}
void customer::closeaccount()
{
	clrscr();
	int flag=0;
	fstream f;
	f.open("cust.dat", ios::in|ios::out|ios::binary);
	long x;
	cout<<"Enter account number to be closed"<<endl;
	cin>>x;
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{	if(x==ano)
		{
			flag=1;
			status='I';
			f.seekp(f.tellg()-sizeof(*this),ios::beg);
			f.write((char*)this,sizeof(*this));
			break;
		}
		f.read((char*)this,sizeof(*this));
	}
	f.close();
	if(flag==0)
	{
		cout<<"account not found"<<endl;
	}
	getch();
}

void customer::search()
{       clrscr();
	int flag=0;
	fstream f;
	long x;
	cout<<"enter account number"<<endl;
	cin>>x;
	f.open("cust.dat",ios::in|ios::binary);
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{
		if(x==ano)
		{
		    flag=1;
		    cout<<"Account number-"<<ano<<endl;
		    cout<<"Account holder's name-"<<cname<<endl;
		    cout<<"Registered phone number"<<phone<<endl;
		    cout<<"Address-"<<address<<endl;
		    cout<<"Balance-"<<balance<<endl;
		    cout<<"Status-"<<status<<endl;
		}
		f.read((char*)this,sizeof(*this));
	}
	f.close();
	if(flag==0)
	{
		cout<<"Account not found"<<endl;
	}
	getch();
}

void customer::displayall()
{
	clrscr();
	fstream f;
	f.open("cust.dat",ios::in|ios::binary);
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{
		 cout<<"Account number-"<<ano<<endl;
		 cout<<"Account holder's name-"<<cname<<endl;
		 cout<<"Registered phone number"<<phone<<endl;
		 cout<<"Address-"<<address<<endl;
		 cout<<"Balance-"<<balance<<endl;
		 cout<<"Status-"<<status<<endl;
		 f.read((char*)this,sizeof(*this));
	}
	f.close();
	getch();
}
int customer::validate(long x)
{
	int flag=0;
	fstream f;
	f.open("cust.dat",ios::in|ios::binary);
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{
		if(x==ano)
		{
		    flag=1;
		    break;
		}
		f.read((char*)this,sizeof(*this));
	}
	f.close();
	return flag;
}

void customer::update(long x, long y)
{
	fstream f1,f2;
	f1.open("cust.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(ano!=x)
		{
			f2.write((char*)this,sizeof(*this));
		}
		else
		{
			balance=y;
			f2.write((char*)this,sizeof(*this));
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	f2.close();
	remove("cust.dat");
	rename("temp.dat","cust.dat");
}

long customer::getano()
{
	return ano;
}

char* customer::getcname()
{
	return cname;
}

char* customer::getphone()
{
	return phone;
}

char* customer::getaddress()
{
	return address;
}

long customer::getbalance()
{
	return balance;
}

char customer::getstatus()
{
	return status;
}

class transaction
{
	private:
	long ano;
	char ttype;
	long pbal;
	long tamt;
	long cbal;
	int dd;
	int mm;
	int yyyy;
	public:
	void menu();
	void deposit();
	void displayall();
	void withdrawl();
	int isgreaterdate(int d1,int m1,int y1,int d2,int m2,int y2);

	void passbook();
	void transondate();
};

void transaction::menu()
{
	clrscr();
	int ch;
	do
	{       clrscr();
		cout<<"1.Deposit"<<endl;
		cout<<"2.Withdrawl"<<endl;
		cout<<"3.Generate passbook"<<endl;
		cout<<"4.Transactions on a particular date"<<endl;
		cout<<"5.display all transactions"<<endl;
		cout<<"6.back to main menu"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>ch;
		if(ch==1)
		{
			deposit();
		}
		else if(ch==2)
		{
			withdrawl();
		}
		else if(ch==3)
		{
			 passbook();
		}
		else if(ch==4)
		{
			transondate();
		}
		else if(ch==5)
		{
			displayall();
		}
		else
		{
			return;
		}
	}while(ch!=6);
	getch();
}

void transaction::deposit()
{
	clrscr();
	fstream f1;
	f1.open("trans.dat", ios::app|ios::binary);
	long x;
	cout<<"enter account number"<<endl;
	cin>>x;
	cout<<endl;
	customer c;
	if(c.validate(x)==1)
	{
		cout<<c.getcname()<<" "<<c.getbalance()<<" "<<c.getphone()<<" "<<c.getaddress()<<" "<<c.getstatus()<<" "<<endl;
		ano=x;
		ttype='D';
		pbal=c.getbalance();
		cout<<"Enter amount ot be deposited"<<endl;
		cin>>tamt;
		cbal=pbal+tamt;
		struct date d;
		getdate(&d);
		dd=d.da_day;
		mm=d.da_mon;
		yyyy=d.da_year;
		f1.write((char*)this,sizeof(*this));
		cout<<"Amout has been deposited"<<endl;
		cout<<"Current balance ->"<<cbal<<endl;
		c.update(x,cbal);
		f1.close();
	}
	else

	{
		cout<<"No such account exists"<<endl;
	}
	getch();
}

void transaction::withdrawl()
{
	clrscr();
	fstream f1;
	f1.open("trans.dat", ios::app|ios::binary);
	long x;
	cout<<"enter account number"<<endl;
	cin>>x;
	customer c;
	if(c.validate(x)==1)
	{
		cout<<c.getcname()<<" "<<c.getbalance()<<" "<<c.getphone()<<" "<<c.getaddress()<<" "<<c.getstatus()<<" "<<endl;
		ano=x;
		ttype='W';
		pbal=c.getbalance();
		cout<<"Enter amount to be withdrawn"<<endl;
		cin>>tamt;
		if(tamt>pbal)
		{
			cout<<"insufficient balance";
		}
		else
		{
			struct date d;
			getdate(&d);
			dd=d.da_day;
			mm=d.da_mon;
			yyyy=d.da_year;
			cbal=pbal-tamt;
			f1.write((char*)this,sizeof(*this));
			cout<<"Amout has been withdrawn"<<endl;
			cout<<"Current balance ->"<<cbal<<endl;
			c.update(x,cbal);
			f1.close();
		}
	}
	else
	{
		cout<<"No such account exists"<<endl;
	}
	getch();
}

void transaction::displayall()
{
	clrscr();
	fstream f;
	f.open("trans.dat",ios::in|ios::binary);
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{
		 cout<<"Account number-"<<ano<<endl;
		 cout<<"transaction type"<<ttype<<endl;
		 cout<<"present balance-"<<pbal<<endl;
		 cout<<"transaction amount"<<tamt<<endl;
		 cout<<"current balance"<<cbal<<endl;
		 cout<<"date-"<<dd<<"-"<<mm<<"-"<<yyyy<<endl;
		 f.read((char*)this,sizeof(*this));
	}
	f.close();
	getch();


}

int transaction::isgreaterdate(int d1,int m1,int y1,int d2,int m2,int y2)
{
	if(y1>y2)
	{
	 return 1;
	}
	else if(y1==y2)
	{
		if(m1>m2)
		{
			return 1;
		}
		else if(m1==m2)
		{
			if(d1>d2)
			{
				return 1;
			 }
		}
	}
	return 0;
}

void transaction::passbook()
{
	fstream f1,f2;
	clrscr();
	long n;
	cout<<"Enter account number "<<endl;
	cin>>n;
	f1.open("trans.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(ano==n)
		{
			f2.write((char*)this,sizeof(*this));
		}
		else
		{
			;
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	f2.close();
	fstream f;
	f.open("temp.dat",ios::in|ios::binary);
	int b;
	f.seekg(0,ios::end);
	b=(f.tellg()+1)/sizeof(*this);
	while(b>0)
	{
		int i=0;
		while(i<b)
		{
			transaction t1,t2;
			f.seekg(i*sizeof(*this),ios::beg);
			f.read((char*)&t1,sizeof(t1));
			f.seekg((i+1)*sizeof(*this),ios::beg);
			f.read((char*)&t2,sizeof(t2));
			if(isgreaterdate(t1.dd,t1.mm,t1.yyyy,t2.dd,t2.mm,t2.yyyy)==1 )
			{
				f.seekp(i*sizeof(*this),ios::beg);
				f.write((char*)&t1,sizeof(t1));
				f.seekp((i+1)*sizeof(*this),ios::beg);
				f.write((char*)&t2,sizeof(t2));
			}
			i++;
		}
		b--;
	}
	f.close();
	clrscr();
	f.open("temp.dat",ios::in|ios::binary);
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{
	      cout<<ano<<" ";
	      if(ttype=='D')
		cout<<"Deposit  ";
	      else if(ttype=='W')
		cout<<"Withdrawl";
	      cout<<" "<<pbal<<" "<<tamt<<" "<<cbal<<" "<<dd<<"-"<<mm<<"-"<<yyyy<<endl;
	      f.read((char*)this,sizeof(*this));
	}
	f.close();
	getch();
}

void transaction::transondate()
{
	clrscr();
	int d,m,y;
	cout<<"enter date"<<endl;
	cin>>d;
	cout<<"enter month"<<endl;
	cin>>m;
	cout<<"enter year"<<endl;
	cin>>y;
	fstream f;
	f.open("trans.dat",ios::in|ios::binary);
	f.read((char*)this,sizeof(*this));
	while(!f.eof())
	{
		 if(d==dd && m==mm && y==yyyy)
		{	cout<<ano<<" ";
			if(ttype=='D')
			cout<<"Deposit  ";
			else if(ttype=='W')
			cout<<"Withdrawl";
			cout<<" "<<pbal<<" "<<tamt<<" "<<cbal<<" "<<dd<<"-"<<mm<<"-"<<yyyy<<endl;
		 }
		 f.read((char*)this,sizeof(*this));
	}
	f.close();
	getch();

}

void main()
{
	clrscr();
	customer c;
	transaction t;
	int ch;
	do
	{       clrscr();
		cout<<"1.Customer menu "<<endl;
		cout<<"2.Transaction menu"<<endl;
		cout<<"3.Exit"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>ch;
		if(ch==1)
		{
		       c.menu();
		}
		else if(ch==2)
		{
			t.menu();
		}
		else
		{
			return;
		}
	}while(ch!=3);
}


