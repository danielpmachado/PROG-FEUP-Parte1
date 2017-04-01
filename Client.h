#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;



struct Client
{
	int identifier;
	string name;
	double money;
};




/*
Lê um Client a partir de uma linha no formato:
1 ; Rui Pereira ; 234.67
*/
Client readClient(string line) {
	
	Client client;

	istringstream is;
	is.str(line);         // a primeira linha fica em is
	string s, x_str, d_str;

	getline(is, x_str, ';'); client.identifier = stoi(x_str);
	getline(is, s, ';'); 
	client.name = s;
	getline(is, d_str, ';'); client.money = stod(d_str);

	return client;
}

void print2Client(Client client) {

	cout << "Identifier: " << client.identifier << endl;
	cout << "Name: " << client.name << endl;
	cout << "Money: " << client.money << endl;

}

void printClients(vector<Client>&clientRead)
{
	for (unsigned int i = 0; i < clientRead.size(); i++)
	{
		cout << "ID: " << clientRead[i].identifier << endl;
		cout << "Nome: " << clientRead[i].name << endl;
		cout << "Montante: " << clientRead[i].money << endl << endl;
	}

	cin.get();
}

void printOneClient(vector<Client>&clientRead)
{
	int id;
	bool nexist = true;

	cout << "Qual e o ID do cliente? :";
	cin >> id;

	for (unsigned int i = 0; i < clientRead.size(); i++)
	{
		if (id == clientRead[i].identifier)
		{
			nexist = false;
			cout << "\nID: " << clientRead[i].identifier << endl;
			cout << "Nome: " << clientRead[i].name << endl;
			cout << "Montante: " << clientRead[i].money;
		}	

	}

	if (nexist)
		cout << "O cliente que pretende imprimir nao existe." << endl;

	cin.get();
}


void writeClient(vector<Client>&clientRead, string filename) {

	ofstream fout;
	fout.open(filename);
	
	if (fout.fail())
	{
		cerr << "Erro a abrir o ficheiro de output.\n";
		exit(2);
	}

	for (unsigned int i = 0; i < clientRead.size(); i++) {

		fout << clientRead[i].identifier << " ; " << clientRead[i].name << " ; " << clientRead[i].money << '\n';

	}

	fout.close();
}

vector<Client> createClient(vector<Client>&clientRead)
{
	Client newclient;

	int id;
	id = clientRead[clientRead.size() - 1].identifier + 1;
	newclient.identifier = id;


	string str_client;
	cin.ignore();
	cout << "Introduza o nome do cliente: "; getline(cin, str_client); newclient.name = str_client;

	newclient.money = 0;

	clientRead.push_back(newclient);

	return clientRead;
}

vector<Client> modifyClient(vector<Client>&clientRead)
{
	int id;
	bool exist = false;
	cout << "\nIdentificador do cliente que deseja modificar: ";
	cin >> id;

	if (! (int) id)               // VERIFICAR INPUT INVALIDO !!!
		cout << "\nInput invalido" << endl;
	else {

		for (unsigned int i = 0; i < clientRead.size(); i++)
		{
			if (id == clientRead[i].identifier)
			{
				string name;

				cin.ignore();
				cout << "\nNome do cliente: ";
				getline(cin, name);
				//cin.ignore();

				clientRead[i].name = name;

				double cash;


				cout << "\nMontante total de compras: ";
				cin >> cash;
				//cin.ignore();

				clientRead[i].money = cash;

				exist = true;
			}
		}

		if (exist == false)
			cout << "\n	O cliente nao existe." << endl;
	}

	return clientRead;
}


vector<Client> removeClient(vector<Client>&clientRead)
{
	int id;
	int a;
	bool exist = false;

	cout << "\nIdentificador do cliente que deseja remover: ";
	cin >> id;

	for (unsigned int i = 0; i < clientRead.size(); i++) 
	{
		if (id == clientRead[i].identifier) 
		{
			a = i;
			exist = true;
		}
	}

	if (exist == true)
	{   
		char x;

		cout << "\nO cliente que pretende apagar: " << id << " ; " << clientRead[a].name << " ; " << clientRead[a].money << endl;
		cout << "\nTem a certeza que pretende apagar este cliente (S/N) : ";
		cin >> x;
		x = tolower(x);

		switch (x)
		{
		case 's':
			clientRead.erase(clientRead.begin() + (a));
			break;
		case 'n':
			cout << "Operacao cancelada\n";
		default:
			break;
		}
	}
	else 
	{
		cout << "O cliente nao existe." << endl;
	}

	return clientRead;
}
