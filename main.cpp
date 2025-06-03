#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
using namespace std;

// Base class for authentication strategy
class Authen_Strategy {
public:
    virtual string login() = 0;
    virtual string signup() = 0;
};

// Customer authentication strategy
class CustomerAthen : public Authen_Strategy {
    private:
        string username;
        string password;
    public:
        string signup() override {
            cout << "\nCustomer Signup\n" << endl;
            cout << "Username: ";
            getline(cin >> ws, username);
            cout << "Password: ";
            getline(cin >> ws, password);
            ofstream customerFile("customers.txt", ios::app);
            customerFile << username << " " << password << endl;
            customerFile.close();
            cout << "\nCustomer signed up successfully!" << endl;
            return username;
        }
        string login() override {
            cout << "\nCustomer Login\n" << endl;
            cout << "Username: ";
            getline(cin >> ws, username);
            cout << "Password: ";
            getline(cin >> ws, password);
    
            ifstream customerFile("customers.txt");
            string user, pass;
            while (customerFile >> user >> pass) {
                if (user == username && pass == password) {
                    customerFile.close();
                    cout << "Customer logged in successfully!\n";
                    return username;
                }
            }
    
            customerFile.close();
            cout << "Invalid credentials!\n";
            return "";
        }
    
    };

// Seller authentication strategy    
class SellerAuthen : public Authen_Strategy {
        private:
            string username;
            string password;
        public:
            string signup() override {
                cout << "\nSeller Signup\n" << endl;
                cout << "Username: ";
                getline(cin >> ws, username);
                cout << "Password: ";
                getline(cin >> ws, password);
                ofstream sellerFile("sellers.txt", ios::app);
                sellerFile << username << " " << password << endl;
                sellerFile.close();
                cout << "\nSeller signed up successfully!" << endl;
                return username;
            }

            string login() override {
                cout << "\nSeller Login\n" << endl;
                cout << "Username: ";
                getline(cin >> ws, username);
                cout << "Password: ";
                getline(cin >> ws, password);
        
                ifstream sellerFile("sellers.txt");
                string user, pass;
                while (sellerFile >> user >> pass) {
                    if (user == username && pass == password) {
                        sellerFile.close();
                        cout << "Seller logged in successfully!\n";
                        return username;
                    }
                }
        
                sellerFile.close();
                cout << "Invalid credentials!\n";
                return "";
            }
        };       

class User{ //main class
  private:
    string username;
    string password;

  public:
    User(const string& user, const string& pass) : username(user), password(pass) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }
};

class Seller : public User {//derived class for seller
  public:
    Seller(const string& user, const string& pass)
        : User(user, pass){}
};  

class Buyer : public User {//derived class for buyer
  public:
    Buyer(const string& user, const string& pass)
        : User(user, pass){}
};

int main () {
 

    return 0;
   
}

/*
Kiel E. Biscocho
Kyle Gabriel M. Dones
IT2A
*/

/* Notes */
// Done na Strategy pattern tas flow nung system sa main
// Na try ko na test ko yung strat pattern


/*Things to do*/
// Class for User/Customer/Seller
// Then define functions for each user
// Last na yung main flow ng system

// Me na bahala sa file handling pm mo nlng

/*  Customer */
// Add to Cart
// View Cart
// Delete item from cart
// Edit Quantity in cart

/* Seller */
// Add product
// View products
// Delete product/item
// Edit product
// View transaction

