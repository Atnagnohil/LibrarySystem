#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include <iostream>
#include <vector>
#include "book.h"
using namespace std;


class LibrarySystem {
     // 展示菜单
    public:
        LibrarySystem();
        void showMenu();
        void exitSystem();
        void clearScreen();
        void addBook();
 };

#endif 
