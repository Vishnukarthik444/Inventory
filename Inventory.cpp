#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

static const string CSV_FILE = "inventory.csv";


// ---------------- ADD PRODUCT ----------------
void Inventory::addProduct(Product product) {
    for (const auto& p : products) {
        if (p.getId() == product.getId()) {
            cout << "\nId already exists.\n";
            cout << "-----------------------------------------------------------\n";
            return;
        }
    }

    products.push_back(product);

    cout << "\nProduct added successfully.\n";
    cout << "-----------------------------------------------------------\n";

    saveInventoryToFile(CSV_FILE);
}


// ---------------- REMOVE PRODUCT ----------------
void Inventory::removeProduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == id) {
            products.erase(it);

            cout << "\nProduct removed successfully.\n";
            cout << "-----------------------------------------------------------\n";

            saveInventoryToFile(CSV_FILE);
            return;
        }
    }

    cout << "\nId does not exist.\n";
    cout << "-----------------------------------------------------------\n";
}


// ---------------- FIND PRODUCT ----------------
Product* Inventory::findProduct(int id) {
    for (auto& p : products) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}


// ---------------- UPDATE PRODUCT ----------------
void Inventory::updateProduct(int id, string name, string category,
                              double price, int quantity) {

    Product* p = findProduct(id);   // ✅ find once

    if (!p) {
        cout << "\nID does not exist.\n";
        cout << "-----------------------------------------------------------\n";
        return;
    }

    // ✅ update fields
    p->setName(name);
    p->setCategory(category);
    p->setPrice(price);
    p->setQuantity(quantity);

    cout << "\nProduct updated successfully.\n";
    cout << "-----------------------------------------------------------\n";

    saveInventoryToFile(CSV_FILE);
}


// ---------------- PRINT PRODUCTS ----------------
void Inventory::printProduct() const {
    if (products.empty()) {
        cout << "\nNo products in inventory.\n";
        cout << "-----------------------------------------------------------\n";
        return;
    }

    for (const auto& p : products) {
        cout << "ID: " << p.getId() << endl;
        cout << "Name: " << p.getName() << endl;
        cout << "Category: " << p.getCategory() << endl;
        cout << "Price: Rs " << p.getPrice() << endl;
        cout << "Quantity: " << p.getQuantity() << endl;
        cout << "-----------------------------------------------------------\n";
    }
}


// ---------------- STOCK IN ----------------
void Inventory::addStock(int id, int qty) {
    Product* p = findProduct(id);

    if (!p) {
        cout << "Product not found\n";
        return;
    }

    p->setQuantity(p->getQuantity() + qty);

    cout << "Stock added.\n";

    saveInventoryToFile(CSV_FILE);
}


// ---------------- STOCK OUT ----------------
void Inventory::reduceStock(int id, int qty) {
    Product* p = findProduct(id);

    if (!p) {
        cout << "Product not found\n";
        return;
    }

    if (p->getQuantity() < qty) {
        cout << "Not enough stock\n";
        return;
    }

    p->setQuantity(p->getQuantity() - qty);

    cout << "Stock reduced.\n";

    saveInventoryToFile(CSV_FILE);
}


// ---------------- SAVE CSV ----------------
void Inventory::saveInventoryToFile(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }

    file << "id,name,category,price,quantity\n";

    for (const auto& p : products) {
        file << p.getId() << ","
             << "\"" << p.getName() << "\","
             << "\"" << p.getCategory() << "\","
             << p.getPrice() << ","
             << p.getQuantity() << "\n";
    }

    file.close();
}


// ---------------- LOAD CSV ----------------
void Inventory::loadInventoryFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "CSV not found. Starting empty inventory.\n";
        return;
    }

    products.clear();

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);

        string idStr, name, category, priceStr, quantityStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr);

        // remove quotes
        name.erase(remove(name.begin(), name.end(), '\"'), name.end());
        category.erase(remove(category.begin(), category.end(), '\"'), category.end());

        int id = stoi(idStr);
        double price = stod(priceStr);
        int quantity = stoi(quantityStr);

        products.emplace_back(id, name, category, price, quantity);
    }

    file.close();

    cout << "\nInventory loaded from CSV.\n";
    cout << "-----------------------------------------------------------\n";
}