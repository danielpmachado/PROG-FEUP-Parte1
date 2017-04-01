#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <tchar.h>

#include "MainMenu.h"

using namespace std;

void layout()
{
	_tsetlocale(LC_ALL, _T("portuguese"));

	cout << "лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл\n\n";
	cout << "			        VENDE++\n\n";
	cout << "лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл\n";
}




int showMenu()
{
	int opcao = -1; 
	_tsetlocale(LC_ALL, _T("portuguese"));

	cout << "\n 		| MENU |\n\n";
	cout << "| 1 |	Gestao de clientes\n\n";
	cout << "| 2 |	Visualizar informacao de clientes\n\n";
	cout << "| 3 |	Visualizar informacao de transacoes\n\n";
	cout << "| 4 |	Efetuar compras\n\n";
	cout << "| 5 |	Sair\n";

	cout << "\nOpcao: ";
	cin >> opcao;
	return opcao;
}




void menuClientsManagement(vector<Client>&clientsRead, vector<Transaction>&transactionRead)
{
	int x;
	system("cls");
	layout();
	cout << "\n			| MENU DE CLIENTES |\n\n";
	cout << "| 1 |  Criar cliente\n\n";
	cout << "| 2 |  Alterar cliente\n\n";
	cout << "| 3 |  Remover cliente\n\n";
	cout << "| 4 |  Voltar ao menu principal\n\n";
	cout << "Opcao: ";
	cin >> x;

	switch (x)
	{
	case 1:
		system("cls");
		layout();
		cout << "\n    | CRIAR CLIENTE |\n\n";
		createClient(clientsRead);
	 // chamar menu principal
		break;
	case 2:
		system("cls");
		layout();
		cout << "\n    | MODIFICAR CLIENTE |\n\n";
		modifyClient(clientsRead);
		break;
	case 3:
		system("cls");
		layout();
		cout << "\n    | REMOVER CLIENTE |\n\n";
		removeClient(clientsRead);
		break;
	case 4:
		return;
	default:
		break;
	}
}

void menuClientsView (vector<Client>&clientsRead, vector<Transaction>&transactionRead)
{
	int x;
	system("cls");
	layout();
	cout << "\n			| MENU DE CLIENTES |\n\n";
	cout << "| 1 |  Ver informacao de um cliente\n\n";
	cout << "| 2 |  Ver informacao de todos os clientes\n\n";
	cout << "| 3 |  Voltar ao menu principal\n\n";
	cout << "Opcao: ";
	cin >> x;

	if (x == 1) 
	{
		system("cls");
		layout();
		cout << "\n    | INFORMACAO DE UM CLIENTE |\n\n";
		printOneClient(clientsRead);
		cin.get();
	}
	if (x == 2)
	{
		system("cls");
		layout();
		cout << "\n    | INFORMACAO DE TODOS OS CLIENTES |\n\n";
		printClients(clientsRead);
		cin.get();
	}
	if (x == 3)
		return;

	if (x < 1 || x > 2)
		cout << "\nInput invalido" << endl;
	//melhorar para voltar a mostrar menu

}

void menuTransactionsView (vector<Client>&clientsRead, vector<Transaction>&transactionRead)
{
	int x;
	system("cls");
	layout();
	cout << "\n 			| MENU DE TRANSACOES |\n\n";
	cout << "| 1 |  Visualizar as transacoes de um cliente\n\n";
	cout << "| 2 |  Visualizar as transacoes de um dia\n\n";
	cout << "| 3 |  Visualizar as transacoes entre 2 data especificadas\n\n";
	cout << "| 4 |  Visualizar todas as transacoes\n\n";
	cout << "| 5 |  Voltar ao menu principal\n\n";
	cout << "Opcao: ";
	cin >> x;

	if (x == 1)
	{
		system("cls");
		layout();
		cout << "\n    | TRANSACOES DE UM CLIENTE |\n\n";
		printClientTransactions(transactionRead);
		cin.get();
	}
	if (x==2)
	{
		system("cls");
		layout();
		cout << "\n    | TRANSACOES DE UM DIA |\n\n";
		printDayTransaction(transactionRead);
		cin.get();
	}
	if (x == 3)
	{
		system("cls");
		layout();
		cout << "\n    | TRANSACOES ENTRE 2 DATAS |\n\n";
		printTransactionsBetween(transactionRead);
		cin.get();
	}
	if (x == 4)
	{
		system("cls");
		layout();
		cout << "\n    | TODAS AS TRANSACOES |\n\n";
		printTransactions(transactionRead);
		cin.get();
	}
	if (x == 5)
		return;
		

	if (x < 1 || x > 5)
		cout << "\n\nInput invalido" << endl;
	// melhorar esta merda

}

void mainMenu(vector<Client>&clientsRead, vector<Transaction>&transactionRead)
{
	int opcao;

	while (true)
	{
		do
		{
			system("cls");
			layout();

			_tsetlocale(LC_ALL, _T("portuguese"));

			cout << "\n 		| MENU |\n\n";
			cout << "| 1 |	Gestao de clientes\n\n";
			cout << "| 2 |	Visualizar informacao de clientes\n\n";
			cout << "| 3 |	Visualizar informacao de transacoes\n\n";
			cout << "| 4 |	Efetuar compras\n\n";
			cout << "| 5 |	Sair\n";

			cout << "\nOpcao: ";
			cin >> opcao;

		} while (opcao > 6 || opcao < 0);


		switch (opcao)
		{
		case 1:
			menuClientsManagement(clientsRead, transactionRead);
			break;
		case 2:
			menuClientsView(clientsRead, transactionRead);
			break;
		case 3:
			menuTransactionsView(clientsRead, transactionRead);
			break;
		case 4:
			layout();
			system("cls");
			cout << "\n     | NOVA COMPRA |\n\n";
			addTransaction(transactionRead, clientsRead);
			break;
		case 5:
			return;
		default:
			break;
		}
	} // fecha while
}