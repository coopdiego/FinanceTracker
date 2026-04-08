//
// Created by Cooper Diego on 1/26/26.
//

#ifndef WEBSITE_H
#define WEBSITE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Represents a single financial record
class Transaction{
  public:
    string date;
    double amount;
    string workType;
    bool invoiced;
    Transaction(const string& date, double amount, const string& workType, bool invoiced);

    string getWork() const;
    string getDate() const;
};

// Represents individual clients and their financial history w/ the company
class Client {
  private:
    int id;
    string name;
    vector<Transaction> transactions;
  public:
    Client(int id, const string& name);
    int getId() const;
    string getName() const;
    void addTransaction(const Transaction& t);
    double getBalance() const;

    const vector<Transaction>& getTransactions() const;

};

// Manages the clients and handles the CSV file
class FinanceTracker {
  private: vector<Client> clients;
    int nextId;

  public:
    FinanceTracker();
    void addClient(const string& name);
    void listClients() const;

    Client* findClientById(int id);

    bool addTransaction(int id, const Transaction& transactions);

    void checkBalance(int id) const;
    void saveAll() const;

  	bool saveToCSV(const string& filename) const;
  	bool loadFromCSV(const string& filename);

};

#endif //WEBSITE_H
