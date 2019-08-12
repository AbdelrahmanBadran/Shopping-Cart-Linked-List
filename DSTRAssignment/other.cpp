//SAMPLE ANSWER for Week 10.

#include <iostream>
#include <string>

using namespace std;

struct employee
{
	string Name;
	int emp_id, age;
	string title_job, address;

	employee * next;
	employee * back;
}*head, *tail, *newhead, *newtail;

void insertintobeginning(string Name, string emp_id, string title_job, string address, string age);
void insertfromtheend(string Name, string emp_id, string title_job, string address, string age);
void createnewnode(string Name, string emp_id, string title_job, string address, string age);
void createsortnode();
void insertintosortedlist(employee * newnode);
void displaylistfrombeginning(int i);
void displaylistfromtheend();
void menu();
string LoginValidation();
int calculatenodes();
string * question();

//int main()
{
	head = NULL;
	tail = NULL; 
	int choice = 1; 
	string username;
	string Name, emp_id, title_job, address, age; 
	string * reademp;
	
	string employeelist[5][5] =
	{
	{"Ali Ahmad", "123445", "Manager", "14, Jalan Setia, Puchong", "23"},
	{"Joker Ahmed", "334333", "CS Executive", "234, Jalan UPM, Seri Kembangan", "45"},
	{"Louis Mok", "245533", "IT Executive", "9, Taman Danai, Alor Setar", "33"},
	{"Jesicca Wong", "545533", "IT Executive", "11, Taman Desa, Sri Petaling", "32"},
	{"Joon Ching", "245544", "Admin", "16, Taman Desa, Kuala Lumpur", "27"}
	};
	for (int i = 0; i < 5; i++)
	{
		createnewnode(employeelist[i][0], employeelist[i][1], employeelist[i][2], employeelist[i][3], employeelist[i][4]);
	}
	username = LoginValidation();
	while (choice != 0)
	{
		menu();
		cout << "\nEnter your choice: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1: displaylistfrombeginning(0); break;
		case 2: displaylistfromtheend();break;
		case 3:
			reademp = question();
			insertintobeginning(reademp[0], reademp[1], reademp[2], reademp[3], reademp[4]); break;
		case 4: createsortnode();break;
		case 5:
			reademp = question();
			insertfromtheend(reademp[0], reademp[1], reademp[2], reademp[3], reademp[4]); break;
		}
	}
	system("CLS");
	cout << "\nGoob Bye!!!" << endl;
}
string * question()
{
	string *emp_info = new string[5];
	cout << "Enter employee name: ";
	cin.ignore();
	getline(cin, emp_info[0]);
	cout << "\nEnter employee id: ";
	cin >> emp_info[1];
	cin.ignore();
	cout << "Enter employee job_title: ";
	getline(cin, emp_info[2]);
	cout << "Enter employee home address: ";
	getline(cin, emp_info[3]);
	cout << "Enter employee age: ";
	cin >> emp_info[4];
	return emp_info;
}
void createnewnode(string Name, string emp_id, string title_job, string address, string age)
{
	employee * newnode = new employee();
	newnode->Name = Name;
	newnode->emp_id = stoi(emp_id);
	newnode->title_job = title_job;
	newnode->address = address;
	newnode->age = stoi(age);
	newnode->back = NULL;
	newnode->next = NULL;
	insertintosortedlist(newnode);
}
void createsortnode()
{
	employee * temp = head;
	newhead = head;
	head = NULL;
	newtail = tail;
	tail = NULL;
	while (temp != NULL)
	{
		employee * newnode = new employee();
		newnode->Name = temp->Name;
		newnode->emp_id = temp->emp_id;
		newnode->title_job = temp->title_job;
		newnode->address = temp->address;
		newnode->age = temp->age;
		newnode->back = NULL;
		newnode->next = NULL;
		insertintosortedlist(newnode);
		temp = temp->next;
	}
	temp = newhead;
	newhead = head;
	head = temp;
	temp = newtail;
	newtail = tail;
	tail = temp;
	displaylistfrombeginning(1);
}

void insertintosortedlist(employee * newnode)
{
	if (head == NULL)
	{
		head = tail = newnode;
	}
	else if (head->emp_id > newnode->emp_id)
	{
		newnode->next = head;
		head->back = newnode;
		head = newnode;
	}
	else
	{
		employee * temp = head;
		employee * previous = temp;
		while (temp != NULL)
		{
			if (temp->emp_id < newnode->emp_id)
			{
				previous = temp;
			}
			else
			{
				break;
			}
			temp = temp->next;
		}
		if (temp != NULL) //in the middle
		{
			previous->next->back = newnode;
			newnode->next = previous->next;
			newnode->back = previous;
			previous->next = newnode;
		}
		else // at the end
		{
			newnode->back = tail;
			tail->next = newnode;
			tail = newnode;
		}
	}
}
void insertintobeginning(string Name, string emp_id, string title_job, string address, string age)
{
	employee * temp = head;
	employee * newnode = new employee();
	newnode->Name = Name;
	newnode->emp_id = stoi(emp_id);
	newnode->title_job = title_job;
	newnode->address = address;
	newnode->age = stoi(age);
	newnode->back = NULL;
	newnode->next = NULL;
	if (head == NULL)
	{
		head = tail = newnode;
	}
	else
	{
		newnode->next = head;
		head->back = newnode;
		head = newnode;
	}
	cout << "Data inserted at the front!" << endl << endl;
	_sleep(2500);
	system("CLS");
}
void insertfromtheend(string Name, string emp_id, string title_job, string address, string age)
{
	employee * temp = tail;
	employee * newnode = new employee();
	newnode->Name = Name;
	newnode->emp_id = stoi(emp_id);
	newnode->title_job = title_job;
	newnode->address = address;
	newnode->age = stoi(age);
	newnode->back = NULL;
	newnode->next = NULL;
	if (head == NULL)
	{
		head = tail = newnode;
	}
	else
	{
		newnode->back = tail;
		tail->next = newnode;
		tail = newnode;
	}
	cout << "Data inserted at the end!" << endl << endl;
	_sleep(2500);
	system("CLS");
}
void displaylistfrombeginning(int num)
{
	system("CLS");
	employee * temp;
	if (num == 0)
	{
		temp = head;
	}
	else
	{
		temp = newhead;
	}
	int i = 1;
	cout << "Employee list read from beginning to the end\n-------------------------------------\n";
	while (temp != NULL)
	{
		cout << i << ". " << temp->emp_id << "\t" << temp->Name << "\t" << temp->title_job << "\t" << temp->address << "\t" << temp->age;
		cout << endl;
		temp = temp->next;
		i++;
	}
	cout << endl << endl;
}
void displaylistfromtheend()
{
	system("CLS");
	employee * temp = tail;
	int i = calculatenodes();
	cout << "Employee list read from end to the beginning\n-------------------------------------\n";
	while (temp != NULL)
	{
		cout << (i) << ". " << temp->emp_id << "\t" << temp->Name << "\t" << temp->title_job << "\t" << temp->address << "\t" << temp->age;
		cout << endl;
		temp = temp->back;
		i--;
	}
	cout << endl << endl;
}
int calculatenodes()
{
	employee * temp = head;
	int i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return i;
}
void menu()
{
	cout << "Choose the below options: \n";
	cout << "1. Display employee list from 1 to N\n";
	cout << "2. Display employee list from N to 1\n";
	cout << "3. Insert employee info from the beginning\n";
	cout << "4. Sort list based on Emp_ID\n";
	cout << "0. Exit Program\n";
}
string LoginValidation()
{
	string username, password; bool notvalid = true;
	cout << "Welcome to APU Employee List System!\n------------------------------------------\n";
	while (notvalid == true)
	{
		cout << "Login Username: ";
		cin >> username;
		cout << "Login Password: ";
		cin >> password;
		if (username == "abc" && password == "1123")
		{
			notvalid = false;
			system("CLS");
			cout << "Hi, " << username << "\n\nWelcome to APU Employee List System!\n------------------------------------------\n";
		}
		else
		{
			cout << "Wrong username / password ! Please try again!";
			cout << endl << endl;
		}
	}
	return username;
}