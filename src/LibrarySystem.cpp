#include "../include/LibrarySystem.h"
#include <iostream>

using namespace std;

LibrarySystem::LibrarySystem() {
}

void LibrarySystem::showMenu() {
    cout << "===== Library System Menu =====" << endl;
    cout << "1. Show book information" << endl;
    cout << "2. Search book" << endl;
    cout << "3. Borrow book" << endl;
    cout << "4. Return book" << endl;
    cout << "5. Add book" << endl;
    cout << "6. Delete book" << endl;
    cout << "7. Save data" << endl;
    cout << "0. Exit system" << endl;
    cout << "===============================" << endl;
}
