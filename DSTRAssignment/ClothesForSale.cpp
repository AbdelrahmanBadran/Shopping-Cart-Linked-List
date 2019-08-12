#include <iostream>
#include <string>
#include <limits>
#include <conio.h>

using namespace std;
const int ORDER_ITEMS_MAX = 10;

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER_KEY 13

//clothes details & pointers
struct cloth {
	int item_id, item_quantity;
	float item_price;
	string item_category, item_color, item_size, item_description;
	cloth *back, *next;
}*head, *tail, *newhead, *newtail;

void close(void);
void smooth();
unsigned int yes_no(void);
int choice_input();

void navigate_cloths();
void search_cloths();
void user_functions();
int user_menu();

void clothes_output();
void admin_functions();
int admin_menu();

void login();
void initialize();
void main_menu();

int count_cloths();
void sort_item_list();
void insert_item_to_sorted_list(cloth * newnode);
void create_new_cloth(int item_id, string item_category, float item_price,
	int item_quantity, string item_color, string item_size, string item_description);
void create_cloth();
void display_items(int id);
void clothes_display(cloth *temp, int i);



/*
	(int item_id, string item_category,
	string item_name, float item_price, int item_quantity,
	string item_color, string item_size, string item_description)

	temp->item_id,
	temp->item_category,
	temp->item_price,
	temp->item_quantity,
	temp->item_color,
	temp->item_size,
	temp->item_description

	enum categories { jeans = 1, shirts, shorts, skirts, slacks};
*/


//struct order {	
//	/*order id should be auto generated*/
//	int order_id;
//	int item_list[ORDER_ITEMS_MAX][3]; //for item_id & item_quantity;  //foreach order item_list deduce the number of quantity with matching id
//	float total_cost, amount_recieved, balance_returned;
//	
//	bool delivery; //if true: total + RM 50
//	//buyer_name,buyer_address,buyer_contact_number
//	string buyer_details[1][3]; 
//	order *back, *next;
//}*head, *tail, *newhead, *newtail;


int main() {
	initialize();
	main_menu();
	return 0;
}

void initialize() {
	head = NULL;
	tail = NULL;

	string clothes[15][7] =
	{
	{"1", "jeans","500","13", "red", "S", "Slim Jeans"},
	{"2", "shirts","60","2", "yellow", "M", "Beach Shirt"},
	{"3", "shorts","49.9","4", "blue", "XS", "Casual Shorts"},
	{"4", "skirts","350","5", "green", "XL", "Long Skirt"},
	{"5", "slacks","65.5","4", "black", "L", "Suit Slacks"},
	{"6", "jeans", "150","6","grey", "S", "Outing Jeans"},
	{"7", "shirts","200","2", "white", "XXL", "Formal Shirt"},
	{"8", "shorts","340","4", "burgundy", "XS", "Casual Shorts"},
	{"9", "skirts", "25.3","23","orange", "L", "Short Skirt"},
	{"10", "slacks","75","53", "gry", "M", "Suit Slacks"},
	{"11", "jeans", "299","25", "black", "XS", "Boot Cut Jeans"},
	{"12", "shirts","89","11", "purple", "L", "Casual Shirt"},
	{"13", "shorts", "19.9","7","green", "XL", "Training Shorts"},
	{"14", "skirts", "300","5", "white", "XXS", "Foraml Skirt"},
	{"15", "slacks", "10.5","2","red", "XS", "Suit Slacks"},
	};

	for (int i = 0; i < 15; i++)
	{
		//conver string to int and to float
		int id = stoi(clothes[i][0]);
		float price = stof(clothes[i][2]);
		int quantity = stoi(clothes[i][3]);

		create_new_cloth(id, clothes[i][1], price, quantity,
			clothes[i][4], clothes[i][5], clothes[i][6]);
	}
}

void create_new_cloth(int item_id, string item_category, float item_price, 
	int item_quantity, string item_color, string item_size, string item_description){
	
	cloth * newnode = new cloth();
	newnode->item_id = item_id;
	newnode->item_category = item_category;
	newnode->item_price = item_price;
	newnode->item_quantity = item_quantity;
	newnode->item_color = item_color;
	newnode->item_size = item_size;
	newnode->item_description = item_description;
	newnode->back = NULL;
	newnode->next = NULL;
	insert_item_to_sorted_list(newnode);
}

//to insert a newnode intto a price sorted list
void insert_item_to_sorted_list(cloth * newnode){
	
	//Newnode be the head & tail if list is empty
	if (head == NULL)
	{
		head = tail = newnode;
	}

	//Newnode will be the head if its price is less than the head
	else if (newnode->item_price < head->item_price)
	{
		newnode->next = head;
		head->back = newnode;
		head = newnode;
	}

	else
	{
		cloth * temp = head;
		cloth * previous = temp;

		//while not end of the list
		while (temp != NULL)
		{
			//Go through the list: moving previous to be temp, then temp moves
			if (newnode->item_price > temp->item_price)
			{
				previous = temp;
			}
			else
			{
				break;
			}

			temp = temp->next;
		}

		/*if the pointer temp is pointing to something:condition of loop broken
		Insert newnode between two nodes: changing pointers first*/
		if (temp != NULL) //in the middle
		{
			previous->next->back = newnode;
			newnode->next = previous->next;

			newnode->back = previous;
			previous->next = newnode;
		}
		//Insert node at the end as it is with the highest price
		else // at the end
		{
			newnode->back = tail;
			tail->next = newnode;
			tail = newnode;
		}
	}
}

//Check this
void  sort_item_list() 
{
	cloth * temp = head;
	newhead = head;
	head = NULL;
	newtail = tail;
	tail = NULL;

	while (temp != NULL)
	{
		cloth * newnode = new cloth();
		newnode->item_id = temp->item_id;
		newnode->item_category = temp->item_category;
		newnode->item_price = temp->item_price;
		newnode->item_quantity = temp->item_quantity;
		newnode->item_color = temp->item_color;
		newnode->item_size = temp->item_size;
		newnode->item_description = temp->item_description;
		newnode->back = NULL;
		newnode->next = NULL;
		insert_item_to_sorted_list(newnode);
		temp = temp->next;
	}

	temp = newhead;
	newhead = head;
	head = temp;
	temp = newtail;
	newtail = tail;
	tail = temp;
	display_items(1);
}

void display_items( int id)
{
	cloth *temp;
	if (id == 0)
	{
		temp = head;
	}
	else
	{
		temp = newhead;
	}

	int i = 1;
	cout << "Clothes Items list of DRESSME Sorted by Price\n-------------------------------------\n";
	clothes_output();

	while (temp != NULL)
	{
		//printf("%-6s%-18s%-18s%-18s%-18s%-7s%10s\n", temp->item_id, temp->item_category, temp->item_price,
		//	temp->item_quantity, temp->item_color, temp->item_size, temp->item_description);
		clothes_display(temp, i);
		temp = temp->next;
		i++;
	}
	cout << endl << endl;
}

void main_menu() {
	smooth();
	int choice;
	cout << "----------------WELCOME TO DRESSME CLOTHING MARKETPLACE--------------------------\n(1)Login\n(0)Close System\n";
	choice = choice_input();
	if (choice == 0)
	{
		close();
	}
	else if(choice == 1){
		login();
	}
	else {
		cout << "Invalid choice!";		
		main_menu();
	}
}

void login() {
	smooth();
	string username, password;
	bool login = false;
	cout << "Login\n-------\n";
	while (login == false) {
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
		
		if (username == "admin" && password == "000")
		{
			system("CLS");
			cout << "Welcome, " << username << "\n-------------------------\n";
			login = true;
			admin_functions();
		}
		else if (username == "user" && password == "111")
		{
			system("CLS");
			cout << "Welcome, " << username << "\n-------------------------\n";
			login = true;
			user_functions();
		}
		else
		{
			cout << "Invalid username or password!";
			cout << endl << endl;
		}
	}
}

void admin_functions(){
	bool cor = true;
	int adm;
	do
	{
		switch (adm = admin_menu())
		{
		case 1: 
			//display_orders(0);
			break;
		case 2: 
			//navigate_orders();
			break;
		case 3:
			//modify_order();
			break;
		case 4: 
			//delete_order();
			//sort_item_list();
			break;
		case 5:
			create_cloth();
			break;
		default:
			cout << "Input is not a choice";
			cor = false;
			break;
		}
	} while (adm != 0);
	main_menu();
}

void user_functions(){
	bool cor = true;
	//cloth *new_item;
	int usc;
	do
	{
		switch (usc = user_menu())
		{
		case 1: 
			display_items(0); 
			break;
		case 2: 
			search_cloths();
			break;
		case 3:
			navigate_cloths();
			break;
		case 4:
			//select_item(); //can order by id
			break;
		case 5: 
			//check_out();
			break;
		default:
			cout << "Input is not a choice";
			cor = false;
			break;
		}
	} while (usc != 0);
	main_menu();
}


void create_cloth()
{
	smooth();
	int item_id = count_cloths() + 1;
	string item_category;
	float item_price;
	int item_quantity;
	string item_color, item_size, item_description;
	int choice;

	cout << "Please Input Item Details\n---------------------------\n";
	cout << "Please choose cloth item category:\n(1)Jeans\n(2)Shirts\n(3)Shorts\n(4)Skirts\n(5)Slacks\n";

	switch (choice = choice_input())
	{
	case 1:
		item_category = "jeans";
		break;
	case 2:
		item_category = "shirts";
		break;
	case 3:
		item_category = "shorts";
		break;
	case 4:
		item_category = "skirts";
		break;	
	case 5:
		item_category = "slacks";
		break;
	default:
		cout << "Input is not a choice";
		cin.ignore();
		create_cloth();
		break;
	}
	cout << "\nCategory Chosen: " << item_category;
	cout << "\nPrice: ";
	cin >> item_price;

	cout << "\nQuantity: ";
	cin >> item_quantity;
	cin.ignore();

	cout << "\nColor: ";
	getline(cin, item_color);

	cout << "\nSize: ";
	cin >> item_size;
	cin.ignore();

	cout << "\nDescription: ";
	cin >> item_description;

	create_new_cloth( item_id,  item_category,  item_price,  item_quantity, item_color,  item_size,  item_description);
	cout<<"Successfully added new item";

	_sleep(1000);
	system("CLS");
	display_items(0);

	return;
}

int count_cloths()
{
	cloth * temp = head; 
	int i = 0;
	
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return i;
}

void search_cloths()
{
	smooth();
	struct cloth *temp;
	int i = 1, item, flag, cat_choice;
	string cat_search;

	temp = head;
	if (temp == NULL)
	{
		printf("\nSorry No cloths in store\n");
	}

	else
	{
		cout << "\nEnter item category to search:\n(1)Jeans\n(2)Shirts\n(3)Shorts\n(4)Skirts\n(5)Slacks\n";
		switch (cat_choice = choice_input())
		{
		case 1:
			cat_search = "jeans";
			break;
		case 2:
			cat_search = "shirts";
			break;
		case 3:
			cat_search = "shorts";
			break;
		case 4:
			cat_search = "skirts";
			break;
		case 5:
			cat_search = "slacks";
			break;
		default:
			cout << "Input is not a choice";
			cin.ignore();
			search_cloths();
			break;
		}
		
		clothes_output();
		while (temp != NULL)
		{
			if (temp->item_category == cat_search)
			{
				clothes_display(temp, i);
				flag = 0;
			}
			else
			{
				flag = 1;
			}
			i++;
			temp = temp->next;
		}

		if (flag == 1)
		{
			printf("\No Items in category\n");
		}
	}
}

void navigate_cloths() {
	
	smooth();
	struct cloth *temp;
	int i = 1, c = 0;;

	temp = head;	
	cout << "Please use Left and Right keyboard arrows <>\nItems are sorted by PRICE (low to high)\n(0)Exit\n";
	clothes_output();
	clothes_display(temp, i);

	do
	{		
		cout << "\n\nItems are sorted by PRICE (low to high)\n\nPlease use Left and Right keyboard arrows to Navigate <>\nPress Enter Key to go back\n";
		switch (c = getch()) {
		case KEY_LEFT:
			system("CLS");
			clothes_output();
			if (temp->back != NULL) {
				temp = temp->back;
				i--;
			}

			else {
				temp = tail;
				i = count_cloths();
			}
			clothes_display(temp, i);
			break;

		case KEY_RIGHT:
			system("CLS");
			clothes_output();
			if (temp->next != NULL) {
				temp = temp->next;
				i++;
			}
			else {
				temp = head;
				i = 1;
			}
			clothes_display(temp, i);
			break;

		case ENTER_KEY:
			return;
			break;

		default:
			cout << "Not Supported!" << endl;  // not an arrow key
			break;
		}

	}while (c != 0);
	return;
}

int user_menu() {
	puts ( "\nCustomer Menu\n-----------\n(1) View all clothes\n(2) Search by type\n"
		"(3) Navigate through clothes\n(4) Select clothes to order\n(5) Checkout order\n(0)Exit");
	return choice_input();
}

int admin_menu() {
	puts("\nAdmin Menu\n----------\n\n(1) View all orders\n"
		"(2) Navigate through orders\n(3) Modify an order\n(4) Delete an order\n(5) Add a new cloth\n(0)Exit");
	return choice_input();
}

void clothes_output()
{
	printf("\n\t %-18s%-18s%-18s%-18s%-18s%-7s%10s \n", "ItemID", "Category", "Price",
		"Quantity", "Color", "Size", "Description");
	cout << "-----------------------------------------------------------------------------------------------------------------";
}

void clothes_display(cloth *temp, int i) {
	/*cout << "\n" << i << ".\t" << temp->item_id << "\t\t" << temp->item_category
		<< "\t\t\t" << temp->item_price << "\t\t" << temp->item_quantity
		<< "\t\t" << temp->item_color << "\t" << temp->item_size
		<< "\t\t" << temp->item_description << endl;
*/
	cout << "\n" << i << ".\t" << temp->item_id << "\t\t   " << temp->item_category
		<< "\t\t" << temp->item_price << "\t\t" << temp->item_quantity
		<< "\t\t" << temp->item_color << "\t\t   " << temp->item_size
		<< "\t" << temp->item_description << endl;
}

int choice_input(){
	int input = -1;
	bool valid = false;
	do
	{
		cout << "Choice: " << flush;
		cin >> input;
		if (cin.good())
		{
			//input is integer as excpected; exit loop to return value
			valid = true;
		}
		else
		{
			//invalid input; clear the buffer and loop again
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input invalid! Please use numbers only" << endl;
		}
	} while (!valid);
	cin.ignore();

	return (input);
}

unsigned int yes_no(void)
{
	puts("\nAre You Sure You Want To Proceed?");
	puts("(1)Yes\n(0)No Return");
	return (choice_input());
}

void smooth()
{
	system("cls");
	printf("Loading...\n");
	_sleep(300);
	system("cls");
}

void close(void)
{
	system("cls");
	puts("Closing...");
	_sleep(300);
	exit(1);
}

//time_t now = time(NULL);
	//struct tm today = *(localtime(&now));
	//size_t str;