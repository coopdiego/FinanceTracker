//
// Created by Cooper Diego on 1/26/26.
//

#include "website.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Constructors
Transaction::Transaction(const string& date, double amount, const string& workType, bool invoiced)
    : date(date), amount(amount), workType(workType), invoiced(invoiced)  {}

Client::Client(int id, const string& name) : id(id), name(name){}

// gets clients ID
int Client::getId() const {
  return id;
}

// Gets clients name
string Client::getName() const {
  return name;
}

string Transaction::getWork() const {
    return workType;
}

string Transaction::getDate() const {
    return date;
}

// Pushes transactions to vector
void Client::addTransaction(const Transaction& t){
  transactions.push_back(t);
}

const vector<Transaction>& Client::getTransactions() const {
    return transactions;
}

//gets client balance
double Client::getBalance() const{
  double balance = 0;
  for(const auto& t : transactions){
    balance += t.amount;
  }
  return balance;
}

//Opens csv file and reads it, as well as allowing to add to it
FinanceTracker::FinanceTracker() : nextId(1) {
    ifstream inFile("../data/clients.csv");
    if (!inFile.is_open()) return;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, dateStr, workTypeStr, amountStr, invoicedStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, dateStr, ',');
        getline(ss, workTypeStr, ',');
        getline(ss, amountStr, ',');
        getline(ss, invoicedStr, ',');

        int id = stoi(idStr);
        double amount = stod(amountStr);
        bool invoiced = (invoicedStr == "YES");

        // Find the client in memory (or create new one)
        Client* existing = findClientById(id);
        if (!existing) {
            clients.push_back(Client(id, name));
            existing = &clients.back();
        }

        // <-- THIS IS WHERE THE LINE GOES
        existing->addTransaction(Transaction(dateStr, amount, workTypeStr, invoiced));

        if (id >= nextId) {
            nextId = id + 1;
        }
    }

    inFile.close();
}

//Adds clients, uses saveAll to save to CSV file
void FinanceTracker::addClient(const string& clientName) {
        clients.push_back(Client(nextId, clientName));
        nextId++;
        saveAll();

        cout << "Added Client: " << clientName << endl;
    }



// Reads all clients from csv file and prints their ID #, Name and Balance
void FinanceTracker::listClients() const {
    for (const auto& client : clients) {
        cout << "ID: " << client.getId()
             << " | Name: " << client.getName()
             << " | Balance: $" << client.getBalance()
             << endl;
    }
}

// Finds clients by searching for ID #
Client* FinanceTracker::findClientById(int id) {
    for (auto &client : clients) {
        if (client.getId() == id)
            return &client;
    }
    return nullptr;
}

// Adds user balance to total amount
bool FinanceTracker::addTransaction(int id, const Transaction& t) {
    Client* client = findClientById(id);
    if (client) {
      client->addTransaction(t);
        saveAll();
        return true;
    }
    return false;
}

// Checks clients balance by taking the id # in, has input validation
void FinanceTracker::checkBalance(int id) const {
    for (const auto& client : clients) {
        if (client.getId() == id) {
            cout << "Client Name: " << client.getName() << " | Balance: " << client.getBalance() << endl;
            return;
        }
    }
    cout << "Client ID " << id << " not found." << endl;
}

// Saves all new information added to the csv file, has input validation
void FinanceTracker::saveAll() const {
    ofstream outFile("../data/clients.csv");

    if (!outFile.is_open()) {
        cout << "Error: Could not update database file." << endl;
        return;
    }

    for (const auto& client : clients) {
        for (const auto& t : client.getTransactions()) {
            outFile << client.getId() << ","
                    << client.getName() << ","
                    << t.getDate() << ","
                    << t.getWork() << ","
                    << t.amount << ","
                    << (t.invoiced ? "YES" : "NO")
                    << endl;
        }
    }

    outFile.close();
}
