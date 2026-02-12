#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "product.h"
using namespace std;

class Inventory {
private:
    vector<Product> products;

public:
    void addProduct(Product product);
    void removeProduct(int id);
    Product* findProduct(int id);
    void updateProduct(int id, string name, string category, double price, int quantity);
    void printProduct() const;
    void saveInventoryToFile(const string& filename);
    void loadInventoryFromFile(const string& filename);
    void addStock(int id, int qty);
    void reduceStock(int id, int qty);
};

#endif