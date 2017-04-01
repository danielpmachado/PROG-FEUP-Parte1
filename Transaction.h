#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "Common.h"

using namespace std;

struct Date
{
	int day;
	int month;
	int year;
};

struct Transaction
{
	int identifier;
	Date date;
	vector<string>listProducts;
};

void readDate(string s, string &d_str, string &m_str, string  &y_str)
{
	if (s[1] != '/')
	{
		d_str = s.substr(0, 2);
		m_str = s.substr(3, 2);
		y_str = s.substr(6, 4);
	}
	else
	{
		d_str = s.substr(0, 1);
		m_str = s.substr(2, 2);
		y_str = s.substr(5, 4);
	}
}


Transaction readTransaction(string line)
{
	Transaction transaction;

	istringstream is;
	is.str(line);
	string x_str, s, v_str, d_str, m_str, y_str;

	getline(is, x_str, ';'); transaction.identifier = stoi(x_str);

	getline(is, s, ';'); trim(s); // transaction.date = s;
	readDate(s, d_str, m_str, y_str);
	Date d;
	d.day = stoi(d_str);
	d.month = stoi(m_str);
	d.year = stoi(y_str);
	transaction.date = d;

	getline(is, v_str, ';');

	stringstream prods(v_str); string prod;

	while (getline(prods, prod, ',')) {

		trim(prod);
		transaction.listProducts.push_back(prod);
	}

	return transaction;
}

void printListProducts(vector<string>&listProducts)
{
	for (unsigned int i = 0; i < listProducts.size(); i++) {

		if (i == listProducts.size() - 1)
			cout << listProducts[i] << endl;
		else cout << listProducts[i] << ',';
	}
}

void printTransaction(Transaction transaction)
{
	cout << "Identifier:" << transaction.identifier << "--\n";

	cout << "Date:" << transaction.date.day << "/";

	if (transaction.date.month < 10)
		cout << "0" << transaction.date.month;
	else cout << transaction.date.month;

	cout << "/" << transaction.date.year << "--\n";

	cout << "List of Products:"; printListProducts(transaction.listProducts); cout << '\n';
}

void printTransactions (vector<Transaction>&transactionRead)
{
	for (unsigned int i = 0; i < transactionRead.size(); i++)
	{
		cout << "ID: " << transactionRead[i].identifier << endl;

		cout << "Data: " << transactionRead[i].date.day << "/";

		if (transactionRead[i].date.month < 10)
			cout << "0" << transactionRead[i].date.month;
		else cout << transactionRead[i].date.month;

		cout << "/" << transactionRead[i].date.year << endl;

		cout << "Lista de produtos:"; printListProducts(transactionRead[i].listProducts); cout << '\n';	
	}

	cin.get();
}

void printClientTransactions(vector<Transaction>&transactionRead)
{
	int id;
	bool nexist = true;

	cout << "Qual e o ID do cliente? ";
	cin >> id;

	for (unsigned int i = 0; i < transactionRead.size(); i++)
	{
		if (id == transactionRead[i].identifier)
		{
			nexist = false;

			cout << "ID: " << transactionRead[i].identifier << endl;

			cout << "Data: " << transactionRead[i].date.day << "/";

			if (transactionRead[i].date.month < 10)
				cout << "0" << transactionRead[i].date.month;
			else cout << transactionRead[i].date.month;

			cout << "/" << transactionRead[i].date.year << endl;

			cout << "Lista de produtos:"; printListProducts(transactionRead[i].listProducts); cout << '\n';
		}
	}

	if (nexist)
		cout << "O cliente nao existe" << endl;

	cin.get();
}

void printDayTransaction(vector<Transaction>&transactionRead)
{
	int d, m, y;
	bool nexist = true;

	cout << "Introduzir data\n";
	cout << "Ano: ";
	cin >> y;
	cout << "Mes: ";
	cin >> m;
	cout << "Dia: ";
	cin >> d;

	for (unsigned int i = 0; i < transactionRead.size(); i++)
	{
		if (d == transactionRead[i].date.day && m == transactionRead[i].date.month && y == transactionRead[i].date.year)
		{
			nexist = false;

			cout << "ID: " << transactionRead[i].identifier << endl;

			cout << "Data: " << transactionRead[i].date.day << "/";

			if (transactionRead[i].date.month < 10)
				cout << "0" << transactionRead[i].date.month;
			else cout << transactionRead[i].date.month;

			cout << "/" << transactionRead[i].date.year << endl;

			cout << "Lista de produtos:"; printListProducts(transactionRead[i].listProducts); cout << '\n';
		}
	}

	if (nexist)
		cout << "Nao existem transacoes nessa data" << endl;

	cin.get();
}





void writeTransaction(vector<Transaction>&transactionRead, string filename)
{
	ofstream fout;
	fout.open(filename);

	if (!fout.is_open())
	{
		cerr << "Output file failed open.\n";
		exit(2);
	}

	for (unsigned int i = 0; i < transactionRead.size(); i++)
	{

		fout << transactionRead[i].identifier << " ; " << transactionRead[i].date.day << "/";

		if (transactionRead[i].date.month < 10)
			fout << "0" << transactionRead[i].date.month;
		else fout << transactionRead[i].date.month;

		fout << "/" << transactionRead[i].date.year << " ; ";


		for (unsigned int j = 0; j < transactionRead[i].listProducts.size(); j++)
		{
			if (j == transactionRead[i].listProducts.size() - 1)
				fout << transactionRead[i].listProducts[j] << endl;
			else fout << transactionRead[i].listProducts[j] << ", ";
		}

	}

	fout.close();

}

vector<Transaction> addTransaction(vector<Transaction>&transactionRead, vector<Client>&clientRead)
{
	Transaction newTransaction;

	int id;
	cout << "Qual é o ID do cliente? : ";
	cin >> id;

	newTransaction.identifier = id;

	int d, m, y;
	
	cout << "\nAno da transacao: ";
	cin >> y;
	cout << "Mes da transacao: ";
	cin >> m;
	cout << "Dia da transacao: ";
	cin >> d;

	newTransaction.date.day = d;
	newTransaction.date.month = m;
	newTransaction.date.year = y;
	
	bool again = false;
	string product;

	do
	{
		
		char x;
		bool invalid = false;

		cout << "\nProduto a adicionar: ";
		cin.clear();
		cin.ignore(1000, '\n');
		getline(cin, product);

		newTransaction.listProducts.push_back(product);
		
		cout << endl;

		do
		{
			cout << "Deseja adicionar outro produto? (S/N)  :  ";			
			cin >> x;
			x = tolower(x);

			if (x == 's')
			{
				invalid = false;
				again = true;
			}
			else
			{
				if (x == 'n')
				{
					again = false;
					invalid = false;
				}
				else
				{
					cout << "\nInput invalido!\n\n";
					invalid = true;
					cin.clear();
					cin.ignore(1000, '\n');
				}
			}

		} while (invalid);

	} while (again);

	transactionRead.push_back(newTransaction);

	return transactionRead;
}

/*
Coloca nas variaveis de 1 a data mais recente 
*/

void latestDate (int &d1, int &m1, int &y1, int &d2, int &m2, int &y2) 
{
	if (y2 <= y1)
		if (m2 <= m1)
			if (y1 <= y2)
				d1 = d1;
			else {
				swap(d1, d2);
				swap(m1, m2);
				swap(y1, y2);
			}
		else {
			swap(d1, d2);
			swap(m1, m2);
			swap(y1, y2);
		}
	else {
		swap(d1, d2);
		swap(m1, m2);
		swap(y1, y2);
	}
}

bool compareDates (int d1, int d2, int d3, int m1, int m2, int m3, int y1, int y2, int y3)
{
	latestDate(d1, m1, y1, d2, m2, y2);

	if (y2 <= y3 && y3 <= y1)
		if (m2 <= m3 && m3 <= m1)
			if (m2 <= m3 && m3 <= m1)
				return true;
			else return false;
		else return false;
	else return false;

}

void printTransactionsBetween(vector<Transaction>&transactionRead) 
{
	int d1, d2, m1, m2, y1, y2;
	bool nexist = true;

	cout << "Inserir data\nAno: ";
	cin >> y1;
	cout << "Mes: ";
	cin >> m1;
	cout << "Dia: ";
	cin >> d1;

	cout << "\nInserir outra data\nAno: ";
	cin >> y2;
	cout << "Mes: ";
	cin >> m2;
	cout << "Dia: ";
	cin >> d2;
	cout << endl;

	for (unsigned int i = 0; i < transactionRead.size(); i++)
	{

		if(compareDates(d1,d2,transactionRead[i].date.day,m1,m2,transactionRead[i].date.month,y1,y2, transactionRead[i].date.year))
		{
			nexist = false;

			cout << "ID: " << transactionRead[i].identifier << endl;

			cout << "Data: " << transactionRead[i].date.day << "/";

			if (transactionRead[i].date.month < 10)
				cout << "0" << transactionRead[i].date.month;
			else cout << transactionRead[i].date.month;

			cout << "/" << transactionRead[i].date.year << endl;

			cout << "Lista de produtos:"; printListProducts(transactionRead[i].listProducts); cout << '\n';
		}	
	}

	if (nexist)
		cout << "Nao existe nenhuma transacao entre as duas datas";

	cin.get();

}

void compara() 
{
	int d1, d2, d3, m1, m2, m3, y1, y2, y3;
	
	cout << "Data1\nAno: ";
	cin >> y1;
	cout << "\nMes: ";
	cin >> m1;
	cout << "\nDia :";
	cin >> d1;

	cout << "Data2\nAno: ";
	cin >> y2;
	cout << "\nMes: ";
	cin >> m2;
	cout << "\nDia :";
	cin >> d2;

	cout << "Data3\nAno: ";
	cin >> y3;
	cout << "\nMes: ";
	cin >> m3;
	cout << "\nDia :";
	cin >> d3;

	if (compareDates(d1,d2,d3,m1,m2,m3,y1,y2,y3))
		cout << "Esta entre as datas.";
	else cout << "Nao esta entre as datas.";

}












