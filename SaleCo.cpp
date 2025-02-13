#include <iostream>
#include <string>
#include <iomanip>
#include "sqlite3.h"

using namespace std;

void printMainMenu();
void viewInvoice(sqlite3 *);
void viewCustomer(sqlite3 *);
int mainMenu();

int main()
{
	int choice;

	sqlite3 *mydb;

	int rc; 

	// Open a connection to the database
    rc = sqlite3_open("saleCo.db", &mydb);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(mydb) << endl;
        return(1);
    } else {
        cout << "Opened database successfully" << endl;
    }

	cout << "Welcome to SaleCo" << endl;
	choice = mainMenu();
	while (true)
	{
		switch (choice) 
		{
			case 1: viewInvoice(mydb); break;
			case 2: viewCustomer(mydb); break;
			case -1: return 0;
			default: cout << "That is not a valid choice." << endl;
		}
		cout << "\n\n";
		choice = mainMenu();
	}
	
}

void printMainMenu() 
{
	cout << "Please choose an option (enter -1 to quit):  " << endl;
	cout << "1. View an invoice" << endl;
	cout << "2. View Customer Information" << endl;
	cout << "Enter Choice: ";
}

int mainMenu()
{
	int choice = 0;
	
	printMainMenu();
	cin >> choice;
	while ((!cin || choice < 1 || choice > 3) && choice  != -1)
	{		
		if (!cin)
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cout << "That is not a valid choice." << endl << endl;
		printMainMenu();
		cin >> choice;
	} 
	return choice;
}

void viewInvoice(sqlite3 * db)
{
	string query = "SELECT INVOICE.INV_NUMBER, INVOICE.INV_DATE, CUSTOMER.CUS_FNAME, CUSTOMER.CUS_LNAME ";
	query += "FROM INVOICE JOIN CUSTOMER ON INVOICE.CUS_CODE = CUSTOMER.CUS_CODE;";
	sqlite3_stmt *pRes;
	string m_strLastError;
	string query2;
	string inv_number;
	string inv_date;
	string cus_fname,cus_lname;
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
	{
		m_strLastError = sqlite3_errmsg(db);
		sqlite3_finalize(pRes);
		cout << "There was an error: " << m_strLastError << endl;
		return;
	}
	else
	{
		cout << "Please choose the invoice you want to see:" << endl;
		int columnCount = sqlite3_column_count(pRes);
		int i = 1, choice;
		sqlite3_stmt *pRes2;
		cout << left;
		while (sqlite3_step(pRes) == SQLITE_ROW)
		{
			cout << i << ". " << sqlite3_column_text(pRes, 0);
			cout << endl;
			i++;
		}
		do
		{
			if (!cin) 
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin >> choice;
			if (!cin || choice < 1 || choice > i)
				cout << "That is not a valid choice! Try Again!" << endl;
		} while (!cin);

		sqlite3_reset(pRes);
		for (int i = 0; i < choice; i++)
			sqlite3_step(pRes);
		inv_number = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 0));
		inv_date = reinterpret_cast<const char*>(sqlite3_column_text(pRes,1));
		cus_fname = reinterpret_cast<const char*>(sqlite3_column_text(pRes,2));
		cus_lname = reinterpret_cast<const char*>(sqlite3_column_text(pRes,3));
		sqlite3_finalize(pRes);
		//need to provide the query to select the customers with the chosen region from the database
		query2 = "SELECT PRODUCT.P_DESCRIPT as Product ,LINE.LINE_PRICE as Price, LINE.LINE_UNITS as Units ";
		query2 += "FROM LINE ";
		query2 += "JOIN PRODUCT on line.P_CODE = PRODUCT.P_CODE  ";
		query2 += "WHERE LINE.INV_NUMBER = '" + inv_number + "';";

		if (sqlite3_prepare_v2(db, query2.c_str(), -1, &pRes2, NULL) != SQLITE_OK)
		{
			m_strLastError = sqlite3_errmsg(db);
			sqlite3_finalize(pRes2);
			cout << "There was an error: " << m_strLastError << endl;
			return;
		}
		else
		{
			cout << "Invoice #: " << inv_number << endl;
			cout << "Invoice Date: " << inv_date << endl;
			cout << "Customer: " << cus_fname << " " << cus_lname << endl;
			columnCount = sqlite3_column_count(pRes2);
			cout << left;
			for (int i = 0; i < columnCount; i++)
			{
				cout << "|" << setw(25) << sqlite3_column_name(pRes2, i);
			}
			cout << "|" << endl;
			
			while (sqlite3_step(pRes2) == SQLITE_ROW)
			{
				for (int i = 0; i < columnCount; i++)
				{
					if (sqlite3_column_type(pRes2, i) != SQLITE_NULL)
						cout << "|" << setw(25) << sqlite3_column_text(pRes2, i);
					else
						cout << "|" << setw(25) << " ";
				}
				cout << "|" << endl;
			}
			sqlite3_finalize(pRes2);
		}

	}
}

void viewCustomer(sqlite3 * db)
{
    string query = "SELECT CUS_CODE, CUS_FNAME, CUS_LNAME FROM CUSTOMER;";
    sqlite3_stmt *pRes;
    string m_strLastError;
    int choice;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(pRes);
        cout << "There was an error: " << m_strLastError << endl;
        return;
    }
    else
    {
        cout << "Please choose a customer:" << endl;
        int i = 1;
        cout << left;
        while (sqlite3_step(pRes) == SQLITE_ROW)
        {
            cout << i << ". " << sqlite3_column_text(pRes, 0) << " - " 
                 << sqlite3_column_text(pRes, 1) << " " 
                 << sqlite3_column_text(pRes, 2) << endl;
            i++;
        }

        do
        {
            if (!cin) 
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin >> choice;
            if (!cin || choice < 1 || choice >= i)
                cout << "That is not a valid choice! Try Again!" << endl;
        } while (!cin || choice < 1 || choice >= i);

        sqlite3_reset(pRes);
        for (int j = 0; j < choice; j++)
            sqlite3_step(pRes);

        string cus_code = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 0));
        sqlite3_finalize(pRes);

        string query2 = "SELECT CUS_FNAME, CUS_LNAME, CUS_AREACODE, CUS_PHONE, CUS_BALANCE FROM CUSTOMER WHERE CUS_CODE = '" + cus_code + "';";
        if (sqlite3_prepare_v2(db, query2.c_str(), -1, &pRes, NULL) != SQLITE_OK)
        {
            m_strLastError = sqlite3_errmsg(db);
            sqlite3_finalize(pRes);
            cout << "There was an error: " << m_strLastError << endl;
            return;
        }
        else
        {
            if (sqlite3_step(pRes) == SQLITE_ROW)
            {
                cout << "Customer Name: " << sqlite3_column_text(pRes, 0) << " " << sqlite3_column_text(pRes, 1) << endl;
                cout << "Phone Number: (" << sqlite3_column_text(pRes, 2) << ") " << sqlite3_column_text(pRes, 3) << endl;
                cout << "Balance: $" << sqlite3_column_text(pRes, 4) << endl;
            }
            sqlite3_finalize(pRes);
        }
    }
}
