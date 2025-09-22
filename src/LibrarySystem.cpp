#include "../include/LibrarySystem.h"
#include "book.h"

BookManager bookManager; // 创建 BookManager 实例

// 构造函数
LibrarySystem::LibrarySystem() {
}

// 展示菜单
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

// 退出系统
void LibrarySystem::exitSystem() {
    cout << "Exiting the system. Goodbye!" << endl;
    exit(0);
}

// 清屏
void LibrarySystem::clearScreen() {
#ifdef _WIN32
    system("cls"); // Windows 清屏
#else
    system("clear"); // Unix-like 系统清屏
#endif
}


// 添加书本
void LibrarySystem::addBook() {
   bookManager.addBook();
   bookManager.saveToFile(); // 添加书本后保存数据
}