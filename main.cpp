//
// Created by Cooper Diego on 1/26/26.
//

#include "website.h"
#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

void showMenu(){
  cout << "---Finance/Client Tracker Menu---"<< endl;
  cout << "1. Add New Client" << endl;
  cout << "2. List All Clients" << endl;
  cout << "3. Add Transaction" << endl;
  cout << "4. Check Client Balance" << endl;
  cout << "5. Create Invoice" << endl;
  cout << "6. Exit" << endl;

  cout << "Enter your choice (1-6): ";
}

int main(){
  FinanceTracker tracker;
  string choice;

  while(true){
    showMenu();
    getline(cin,choice);

    // Menu #1 adds new clients to csv file
    if(choice == "1"){
      string name;
      cout << "Enter Client Name: ";
      getline(cin, name);

      if (name.empty()){
        cout << "You did not input a client name." << endl;
        continue;
      }
      cout << "Confirm Client's Name is: " << name << endl;
      string confirm;
      cout << "Type 'Y' for yes and 'N' for no: " << endl;
      getline(cin, confirm);

      for (char &c : confirm){
        c = toupper(c);
      }
      if (confirm == "Y" || confirm == "YES" ){
        tracker.addClient(name);
        cout << "Client name confirmed, and has been added!" << endl;
        name = name;


      }
      else if (confirm == "N" || confirm == "NO"){
        cout << "Client name not confirmed. Input again." << endl;
        continue;
      }
      else {
        cout << "Invalid Input. Please try again." << endl;
      }
    }
    // Menu #2 lists all clients from CSV file
    else if (choice == "2"){
      tracker.listClients();
    }

    // Menu #3 adds transactions to clients
    else if (choice == "3"){
      int id;
      string date;
      string work;
      double amount;
      while (true) {
        cout << "Enter Client ID: ";
        if (cin >> id) {
          cin.ignore(1000, '\n');
          break;
        }
        else {
          cout << "Invalid ID! Please enter a whole number." << endl;
          cin.clear();
          cin.ignore(1000, '\n');
        }
      }
      cout << "Enter Client Date(MM/DD/YYYY): ";
      cin >> date;
      cin.ignore(1000, '\n');

      cout << "Enter Work Type/ Description: ";
      getline(cin, work);

      while (true) {
        cout << "Enter Amount to add: ";
        if (cin >> amount) {
          // Input is a valid double
          cin.ignore(1000, '\n');
          break;
        } else {
          // Input was NOT a number
          cout << "Invalid Input! Please enter a numeric value (e.g., 50.00)." << endl;
          cin.clear(); // Clear the error flag
          cin.ignore(1000, '\n'); // Discard the bad input
        }
      }

      Transaction t(date, amount, work, false);
      if (tracker.addTransaction(id, t)) {
        cout << "Transaction added successfully!" << endl;
      } else {
        cout << "Error: Client ID not found." << endl;
      }
    }

    //Menu #4 checks clients balance based upon user input of and id #
    else if (choice == "4") {
      int id;
      while (true) {
        cout << "Enter Client ID: ";
        if (cin >> id) {
          cin.ignore(1000, '\n');
          break;
        }
        else {
          cout << "Invalid ID! Please enter a whole number." << endl;
          cin.clear();
          cin.ignore(1000, '\n');
        }
      }


      tracker.checkBalance(id);
    }
    else if (choice == "5") {
      int id;

      while (true) {
        cout << "Enter Client ID for Invoice: ";
        if (cin >> id) {
          cin.ignore(1000, '\n');
          break;
        } else {
          cout << "Invalid ID! Please enter a whole number." << endl;
          cin.clear();
          cin.ignore(1000, '\n');
        }
      }

      // Call Python script
      string command = "python3 ~/CLionProjects/M3OEP-cldiego/create_invoice.py " + to_string(id);
      system(command.c_str());
    }

    else if (choice == "6") {
      cout << "Exiting..." << endl;
      break;
    }
    else {
      cout << "Invalid Input." << endl;
    }
  }
  return 0;
}