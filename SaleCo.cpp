#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "sqlite3.h"

using namespace std;

void printMainMenu();
void viewInvoice(sqlite3 *);
void viewCustomer(sqlite3 *);
void createInvoice(sqlite3 *);
int mainMenu();

struct LineItem {
	string product_code;
	int quantity;
	double price;
};

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
			case 3: createInvoice(mydb); break;
			case -1: sqlite3_close(mydb); return 0;
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
	cout << "3. Create Invoice" << endl;
	cout << "Enter Choice: ";
}

int mainMenu()
{
	int choice = 0;
	
	printMainMenu();
	cin >> choice;
	while ((!cin || choice < 1 || choice > 4) && choice  != -1)
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
void createInvoice(sqlite3 * db)
{
    string query = "SELECT CUS_CODE, CUS_FNAME, CUS_LNAME FROM CUSTOMER;";
    sqlite3_stmt *pRes;
    string m_strLastError;
    int choice;
    int rc;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(pRes);
        cout << "There was an error: " << m_strLastError << endl;
        return;
    }
    else
    {
        cout << "Please choose a customer for the invoice:" << endl;
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

        int cus_code = sqlite3_column_int(pRes, 0); // Ensure cus_code is an integer
        sqlite3_finalize(pRes);

        vector<LineItem> lineItems;
        string product_code;
        int quantity;
        double price;
        char addMore;

        do {
            cout << "Please choose a product:" << endl;
            query = "SELECT P_CODE, P_DESCRIPT, P_PRICE FROM PRODUCT;";
            if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
            {
                m_strLastError = sqlite3_errmsg(db);
                sqlite3_finalize(pRes);
                cout << "There was an error: " << m_strLastError << endl;
                return;
            }
            else
            {
                int i = 1;
                while (sqlite3_step(pRes) == SQLITE_ROW)
                {
                    cout << i << ". " << sqlite3_column_text(pRes, 0) << " - " 
                         << sqlite3_column_text(pRes, 1) << " ($" 
                         << fixed << setprecision(2) << sqlite3_column_double(pRes, 2) << ")" << endl;
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

                product_code = reinterpret_cast<const char*>(sqlite3_column_text(pRes, 0));
                price = sqlite3_column_double(pRes, 2);
                sqlite3_finalize(pRes);

                cout << "Enter quantity: ";
                cin >> quantity;

                lineItems.push_back({product_code, quantity, price});

                cout << "Add more products? (y/n): ";
                cin >> addMore;
            }
        } while (addMore == 'y' || addMore == 'Y');

        // Start transaction
        char *errMsg = 0;
        rc = sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
            return;
        }

        // Generate a unique 4-digit invoice number
        int inv_number;
        bool unique = false;
        while (!unique) {
            inv_number = 1000 + rand() % 9000;
            string checkInvoice = "SELECT COUNT(*) FROM INVOICE WHERE INV_NUMBER = " + to_string(inv_number) + ";";
            if (sqlite3_prepare_v2(db, checkInvoice.c_str(), -1, &pRes, NULL) != SQLITE_OK) {
                m_strLastError = sqlite3_errmsg(db);
                sqlite3_finalize(pRes);
                cout << "There was an error: " << m_strLastError << endl;
                return;
            }
            if (sqlite3_step(pRes) == SQLITE_ROW && sqlite3_column_int(pRes, 0) == 0) {
                unique = true;
            }
            sqlite3_finalize(pRes);
        }

        string insertInvoice = "INSERT INTO INVOICE (INV_NUMBER, CUS_CODE, INV_DATE) VALUES (" + to_string(inv_number) + ", " + to_string(cus_code) + ", CURRENT_TIMESTAMP);";
        rc = sqlite3_exec(db, insertInvoice.c_str(), NULL, NULL, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
            sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &errMsg);
            return;
        }

        // Insert line records and update product quantity
        int line_number = 1;
        for (const auto& item : lineItems) {
            string insertLine = "INSERT INTO LINE (LINE_NUMBER, INV_NUMBER, P_CODE, LINE_UNITS, LINE_PRICE) VALUES (" + to_string(line_number++) + ", " + to_string(inv_number) + ", '" + item.product_code + "', " + to_string(item.quantity) + ", " + to_string(item.price) + ");";
            rc = sqlite3_exec(db, insertLine.c_str(), NULL, NULL, &errMsg);
            if (rc != SQLITE_OK) {
                cerr << "SQL error: " << errMsg << endl;
                sqlite3_free(errMsg);
                sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &errMsg);
                return;
            }

            string updateProduct = "UPDATE PRODUCT SET P_QOH = P_QOH - " + to_string(item.quantity) + " WHERE P_CODE = '" + item.product_code + "';";
            rc = sqlite3_exec(db, updateProduct.c_str(), NULL, NULL, &errMsg);
            if (rc != SQLITE_OK) {
                cerr << "SQL error: " << errMsg << endl;
                sqlite3_free(errMsg);
                sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &errMsg);
                return;
            }
        }

        // Update customer balance
        double totalAmount = 0;
        for (const auto& item : lineItems) {
            totalAmount += item.quantity * item.price;
        }
        string updateCustomer = "UPDATE CUSTOMER SET CUS_BALANCE = CUS_BALANCE + " + to_string(totalAmount) + " WHERE CUS_CODE = " + to_string(cus_code) + ";";
        rc = sqlite3_exec(db, updateCustomer.c_str(), NULL, NULL, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
            sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &errMsg);
            return;
        }

        // Commit transaction
        rc = sqlite3_exec(db, "COMMIT;", NULL, NULL, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
            return;
        }

        cout << "Invoice created successfully!" << endl;
    }
}