#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include <iostream>
#include <vector>
#include "book.h"
#include "user.h"
using namespace std;


class LibrarySystem {
     // 展示菜单
    public:
        LibrarySystem();
        ~LibrarySystem();
        void showMenu();
        void exitSystem();
        void clearScreen();
        void addBook();
        void showBooks();
        bool getIsRunning();  // 获取程序运行状态
        void deleteBook();
        void searchBook();
        void borrowBook();
        void returnBook();
        void userLog(); // 用户登录
    private:
        bool isRunning;  // 程序运行状态标志位
 };

#endif 
