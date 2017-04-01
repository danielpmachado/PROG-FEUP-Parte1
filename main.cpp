#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "Client.h"
#include "Transaction.h"
#include "Menu.h"
#include "Common.h"
#include "MainMenu.h"

using namespace std;

int main(void) 
{
	layout();

	string filename;                                   // string 
	cout << "\nIntroduza o nome do ficheiro de clientes: ";       // 
	cin >> filename;                                   // filename fica com o nome do ficheiro

	ifstream fin;         // include file stream -> nome da stream
	fin.open(filename);   // abrir o ficheiro na stream

	if (!fin.is_open())      // OR if (! infile.is_open())  OR if (! infile) 
	{
		cerr << "\nErro a abrir o ficheiro " << filename << "\n";
		return (1);
	}

	// em estudo
	                 // DESCOMENTAR
	string line;
	
	vector<Client>clientsRead;  // inicializa um vetor de clientes

	while (getline(fin,line)) 
	{
		Client client = readClient(line);
		//printClient(client);
		clientsRead.push_back(client);
	}
	

	// Ciclo do menu
	
	/*
	int opcao = -1;
	do {
		opcao = showMenu();
		cout << "opcao selecionada " << opcao;


	} while (opcao != 0);
	*/
	

	//createClient(clientsRead);

	//modifyClient(clientsRead);

	//printClients(clientsRead);
	
	//printOneClient(clientsRead);

	//removeClient(clientsRead);


	/*  ESTA PARTE ESTA COMENTADA!!! 
		FECHAR  O FICHEIRO VAI FICAR NO FINAL DO MAIN

	fin.close();

	string out_filename;
	out_filename = "out_" + filename;

	*/
	
	
	
	// writeClient(clientsRead,out_filename); //escrever num ficheiro
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	Lê a informação de um ficheiro de clientes
	Guarda informação num ficheiro com o nome "out_(nome do ficheiro de clientes)"
	*/

	

	string t_filename;
	cout << "\nPlease enter the transactions file name: ";
	cin >> t_filename;

	ifstream t_fin;
	t_fin.open(t_filename);

	if (! t_fin.is_open()) // if (t_fin.fail()) 
	{
		cerr << "\nError opening " << t_filename << "\n";
		exit(1);
	}

	string t_line;
	
	vector<Transaction>transactionRead;

	while (getline(t_fin, t_line))
	{
		Transaction transaction = readTransaction(t_line);
		//printTransaction(transaction);
		transactionRead.push_back(transaction);
	}

	//addTransaction(transactionRead,clientsRead);

	//printTransactions(transactionRead);

	//printClientTransactions(transactionRead);

	//printDayTransaction(transactionRead);

	//printTransactionsBetween(transactionRead);


	// A PARTIR DAQUI É PRECISO TER CUIDADO! 
	// O FICHEIRO DE CLIENTES APENAS É FECHADO AQUI
	// EXPERIENCIA

	mainMenu(clientsRead, transactionRead);


////////////////////////////////////////////
	fin.close();

	string out_filename;
	out_filename = "out_" + filename;

//////////////////////////////////////
	t_fin.close();

	string t_out_filename;
	t_out_filename = "out_" + t_filename;

	//writeTransaction(transactionRead, t_out_filename);
	
	
	return 0;
}