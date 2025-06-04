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

// Derived class for seller
class Seller : public User {
  public:
    Seller(const string& user, const string& pass)
        : User(user, pass){}

    void menu(){
        int choice;
        do {
        cout << "\nWelcome to the Seller Menu \n";
        cout << "1. Add Product" << endl;
        cout << "2. View Products" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Edit Product" << endl;
        cout << "5. View Transaction" << endl;
        cout << "6. Logout" << endl;

        cout << "Please enter option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                editProduct();
                break;
            case 5:
                viewTransaction();
                break;
            case 6:
                cout << "Exiting Seller Menu." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                menu();
        }
        }
        while (choice != 6);
        
    };

    void addProduct(){
        char addProductChoice;
        do{
        cout << "Product added by seller: " << getUsername() << endl;
        cout << "Name of the product: ";
        string productName;
        getline(cin >> ws, productName);

        cout << "Quantity: ";
        int quantity;
        cin >> quantity;

        cout << "Price: ";
        double price;
        cin >> price;

        ofstream productFile("products.txt", ios::app);
        productFile << "Seller: " << getUsername() << "\tProduct: " << productName << "\tQuantity: "<< quantity << "\tPrice: " << price << endl;
        productFile.close();

        cout<< "\nProduct added successfully!\n" << endl;
        cout << "Do you want to add another product? (Yy/Nn): ";
        cin >> addProductChoice;
        }
        while(addProductChoice == 'Y' || addProductChoice == 'y');
        menu();

    };

    void viewProducts(){
    
        ifstream productFile("products.txt");
        string line;
        cout << "\nAvailable Products:\n";
        while (getline(productFile, line)) {
            cout << line << endl;
        }
        productFile.close();

        menu();
    }

    void deleteProduct() {
        
            ifstream productFile("products.txt");
            string line;
            vector<string> products;
            cout << "\nChoose Product to Delete:\n";
            int ptroductIndex = 1;
            while (getline(productFile, line)) {
                products.push_back(line);
                cout << ptroductIndex++ << ". " << line << endl;
            }
            
            productFile.close();
            
            if (products.empty()) {
                cout << "No products available to delete." << endl;
                return;
            }
            cout << "\nEnter 0 to cancel deletion.\n";
            cout <<"\nEnter the product number to delete: ";
            int productNumber;
            cin >> productNumber;

            if (productNumber < 1 || productNumber > products.size()) {
                cout << "Invalid product number. Please try again." << endl;
                return;
            }
            else if (productNumber == 0) {
                cout << "Deletion cancelled." << endl;
                return;
            }


            products.erase(products.begin() + productNumber - 1);
            ofstream outFile("products.txt");
            for (const auto& product : products) {
                outFile << product << endl;
            }
            outFile.close();

            cout << "\nProduct deleted successfully!\n" << endl;
        
        menu();
    }

    void editProduct() {
        char editProductChoice;
        do {
            ifstream productFile("products.txt");
            string line;

            vector<string> products;
            int ptroductIndex = 1;

            cout << "\nChoose Product to Edit:\n";
            while (getline(productFile, line)) {
                products.push_back(line);
                cout << ptroductIndex++ << ". " << line << endl;
            }
            productFile.close();
            cout << "\nEnter the product number to edit (1-" << products.size() << "): ";
            int productNumber;
            cin >> productNumber;

            if (productNumber < 1 || productNumber > products.size()) {
                cout << "Invalid product number. Please try again." << endl;
                continue;
            }

            int newQuantity;
            cout << "Enter the new quantity: ";
            cin >> newQuantity;

            string& selectedProduct = products[productNumber - 1];
            size_t quantityPos = selectedProduct.find("Quantity:");
            if (quantityPos != string::npos) {
            size_t qtyValueStart = quantityPos + 9;
            size_t qtyValueEnd = selectedProduct.find('\t', qtyValueStart);
            selectedProduct.replace(qtyValueStart, qtyValueEnd - qtyValueStart, to_string(newQuantity));
            }
            else {
            cout << "Error: Quantity field not found.\n";
            continue;
           }

            ofstream outFile("products.txt");
            for (const auto& product : products) {
                outFile << product << endl;
            }
            outFile.close();

            cout << "\nProduct Restocked Successfully!\n" << endl;

            cout << "Do you want to restock another product? (Yy/Nn): ";
            cin >> editProductChoice;
        } 
        while (editProductChoice == 'Y' || editProductChoice == 'y');
        menu();
    }

    void viewTransaction() {
        ifstream transactionFile("cart.txt");
        if (!transactionFile.is_open()) {
            cout << "No transactions file found.\n";
            return;
        }
    
        string line;
        bool hasTransaction = false;
    
        cout << "\n=== Transaction History ===\n";
        while (getline(transactionFile, line)) {
            if (!line.empty()) {
                cout << line << endl;
                hasTransaction = true;
            }
        }
        transactionFile.close();
    
        if (!hasTransaction) {
            cout << "No transactions available.\n";
        }
        cout << "===========================\n\n";
    }
};  

// Derived class for buyer
class Buyer : public User {
  public:
    Buyer(const string& user, const string& pass)
        : User(user, pass){}

    void menu() {
        int choice;
        do{
        cout << "\nWelcome to the Buyer Menu\n";
        cout << "1. Add to Cart" << endl;
        cout << "2. View Cart" << endl;
        cout << "3. Remove from Cart" << endl;
        cout << "4. Update Cart" << endl;
        cout << "5. Logout" << endl;

        cout << "Please enter option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addToCart();
                break;
            case 2:
                viewCart();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                cout << "Exiting Buyer Menu." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                menu();
                break;
        }
        }
        while (choice != 5);
    };

    void addToCart() {
    char addToCartChoice;
    do {
        ifstream productFile("products.txt");
        vector<string> products;
        string line;

        cout << "\nAvailable Products:\n";
        int productIndex = 1;
        while (getline(productFile, line)) {
            products.push_back(line);
            cout << productIndex++ << ". " << line << endl;
        }
        productFile.close();

        if (products.empty()) {
            cout << "No products found.\n";
            return;
        }

        cout << "\nEnter the product ID (1 to " << products.size() << "): ";
        int productId;
        cin >> productId;

        if (productId < 1 || productId > products.size()) {
            cout << "Invalid product ID. Please try again.\n";
            continue;
        }

        string selectedLine = products[productId - 1];

        string seller, productName;
        int quantity, price;

        size_t sellerPos = selectedLine.find("Seller:");
        size_t productPos = selectedLine.find("Product:");
        size_t quantityPos = selectedLine.find("Quantity:");
        size_t pricePos = selectedLine.find("Price:");

        if (sellerPos == string::npos || productPos == string::npos || quantityPos == string::npos || pricePos == string::npos) {
            cout << "Invalid product format.\n";
            continue;
        }

        seller = selectedLine.substr(sellerPos + 7, productPos - (sellerPos + 7));
        productName = selectedLine.substr(productPos + 8, quantityPos - (productPos + 8));
        string quantityStr = selectedLine.substr(quantityPos + 9, pricePos - (quantityPos + 9));
        string priceStr = selectedLine.substr(pricePos + 6);

        // Convert to int
        try {
            quantity = stoi(quantityStr);
            price = stoi(priceStr);
        } catch (...) {
            cout << "Invalid number format in product data.\n";
            continue;
        }

        int buyQty;
        cout << "Enter quantity to buy (Available: " << quantity << "): ";
        cin >> buyQty;

        if (buyQty <= 0 || buyQty > quantity) {
            cout << "Invalid quantity.\n";
            continue;
        }

        // Deduct the quantity
        quantity -= buyQty;

        // Reconstruct updated line
        string updatedLine = "Seller:" + seller + "\tProduct:" + productName +
                             "\tQuantity:" + to_string(quantity) + "\tPrice:" + to_string(price);
        products[productId - 1] = updatedLine;

        // Write updated product list to temp file
        ofstream tempFile("temp.txt");
        for (const auto& prod : products) {
            tempFile << prod << endl;
        }
        tempFile.close();

        // Replace original file
        remove("products.txt");
        rename("temp.txt", "products.txt");

        // Add item to cart.txt
        ofstream cartFile("cart.txt", ios::app);
        if (cartFile.is_open()) {
            cartFile << "Buyer: " << getUsername()
                     << " | Product: " << productName
                     << " | Price: " << price
                     << " | Quantity: " << buyQty << endl;
            cartFile.close();
            cout << "\nProduct added to cart successfully!\n";
        } else {
            cout << "Error: Item not added to cart.\n";
            return;
        }

        cout << "Do you want to add another product to cart? (Y/y for yes): ";
        cin >> addToCartChoice;

    } while (addToCartChoice == 'Y' || addToCartChoice == 'y');

    menu();
}

    void viewCart() {
        char viewCartChoice;
        do {
            ifstream cartFile("cart.txt");
            string line;
            cout << "\nYour Cart:\n";
            while (getline(cartFile, line)) {
                cout << line << endl;
            }
            cartFile.close();

            cout << "\nPress X to exit viewing cart: ";
            cin >> viewCartChoice;
        } 
        
        while (viewCartChoice != 'X' && viewCartChoice != 'x');
        menu();
    };

    void removeToCart() {
        char removeFromCartChoice;
        do {
            ifstream cartFile("cart.txt");
            string line;
            
            vector<string> cartItems;
            cout << "\nYour Cart:\n";
            int itemIndex = 1;
            while (getline(cartFile, line)) {
                cartItems.push_back(line);
                cout << itemIndex++ << ". " << line << endl;
            }
            cartFile.close();
            if (cartItems.empty()) {
                cout << "Your cart is empty." << endl;
                return;
            }
            cout << "\nEnter the item number to remove (1-" << cartItems.size() << "): ";
            int itemNumber;
            cin >> itemNumber;
            cartItems.erase(cartItems.begin() + itemNumber - 1);
            ofstream outFile("cart.txt");
            for (const auto& item : cartItems) {
                outFile << item << endl;
            }
            outFile.close();
            cout << "\nItem removed from cart successfully!\n" << endl;
            cout << "Do you want to remove another item from cart? (Yy/Nn): ";
            cin >> removeFromCartChoice;
        }
        while (removeFromCartChoice == 'Y' || removeFromCartChoice == 'y');
        menu();
    }

};

int main () {

    int choice;
    
    do {
        cout << "\nWelcome to the E-commerce Platform\n";

        cout << "\n***** Customer *****:\n";
        cout << "1. Customer Login\n";
        cout << "2. Customer Signup\n";

        cout << "\n***** Seller *****:\n";
        cout << "3. Seller Login\n";
        cout << "4. Seller Signup\n";
        cout << "\n5. Exit\n";
        cout << "\nPlease enter your choice: ";
        cin >> choice;
        cin.ignore();

        Authen_Strategy* authStrategy = nullptr;
        string userType;

       switch (choice) {
            case 1:
                authStrategy = new CustomerAthen();
                userType = "Customer";
                break;
            case 2:
                authStrategy = new CustomerAthen();
                userType = "Customer";
                break;
            case 3:
                authStrategy = new SellerAuthen();
                userType = "Seller";
                break;
            case 4:
                authStrategy = new SellerAuthen();
                userType = "Seller";
                break;
            case 5:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }
        string username;
        if (choice == 1 || choice == 3) {
            username = authStrategy->login();
        } 
        else {
            username = authStrategy->signup();
        }

        if (!username.empty()) {
            if (userType == "Customer") {
                Buyer buyer(username, "");
                buyer.menu();
            } 
            else if (userType == "Seller") {
                Seller seller(username, "");
                seller.menu();
            }
        }

        delete authStrategy;
    }
    while (choice != 5);
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
// Pa add nunng mga functions sa mga class either one if kaya
// ako na bahala sa logic dun sa menu
// nag add na mee ng txt file fore cart


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

