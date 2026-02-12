#include <iostream>
#include <limits>
#include "Inventory.h"

using namespace std;

int main() {
    Inventory inventory;

    inventory.loadInventoryFromFile("inventory.csv");

    cout << "\n--------------- Inventory Management System ----------------\n\n";

    char choice;

    do {
        cout << "\nChoose an option:\n";
        cout << "1. Add product\n";
        cout << "2. Remove product\n";
        cout << "3. Find product\n";
        cout << "4. Update product\n";
        cout << "5. View all products\n";
        cout << "6. Add stock (IN)\n";
        cout << "7. Reduce stock (OUT)\n";
        cout << "8. Save to CSV\n";
        cout << "9. Load from CSV\n";
        cout << "Q. Quit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

        // ---------------- ADD PRODUCT ----------------
        case '1': {
            int id, quantity;
            double price;
            string name, category;

            cout << "Enter ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter product name: ";
            getline(cin, name);

            cout << "Enter category: ";
            getline(cin, category);

            cout << "Enter price (Rs): ";
            cin >> price;

            cout << "Enter quantity: ";
            cin >> quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inventory.addProduct(Product(id, name, category, price, quantity));
            break;
        }

        // ---------------- REMOVE ----------------
        case '2': {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inventory.removeProduct(id);
            break;
        }

        // ---------------- FIND ----------------
        case '3': {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Product* p = inventory.findProduct(id);

            if (p) {
                cout << "\nName: " << p->getName() << endl;
                cout << "Category: " << p->getCategory() << endl;
                cout << "Price: Rs " << p->getPrice() << endl;
                cout << "Quantity: " << p->getQuantity() << endl;
            } else {
                cout << "\nProduct not found.\n";
            }

            cout << "-----------------------------------------------------------\n";
            break;
        }

        // ---------------- UPDATE ----------------
        case '4': {
            int id, quantity;
            double price;
            string name, category;

            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new name: ";
            getline(cin, name);

            cout << "Enter new category: ";
            getline(cin, category);

            cout << "Enter new price (Rs): ";
            cin >> price;

            cout << "Enter new quantity: ";
            cin >> quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inventory.updateProduct(id, name, category, price, quantity);
            break;
        }

        // ---------------- VIEW ----------------
        case '5':
            inventory.printProduct();
            break;

        // ---------------- STOCK IN ----------------
        case '6': {
            int id, qty;
            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter quantity to add: ";
            cin >> qty;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inventory.addStock(id, qty);
            break;
        }

        // ---------------- STOCK OUT ----------------
        case '7': {
            int id, qty;
            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter quantity to reduce: ";
            cin >> qty;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inventory.reduceStock(id, qty);
            break;
        }

        // ---------------- SAVE ----------------
        case '8':
            inventory.saveInventoryToFile("inventory.csv");
            break;

        // ---------------- LOAD ----------------
        case '9':
            inventory.loadInventoryFromFile("inventory.csv");
            break;

        // ---------------- QUIT ----------------
        case 'q':
        case 'Q':
            cout << "\nSaving inventory before exit...\n";
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Goodbye!\n";
            return 0;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (true);
}