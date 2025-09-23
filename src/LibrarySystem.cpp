#include "../include/LibrarySystem.h"
#include "book.h"

BookManager bookManager; // 创建 BookManager 实例

// 构造函数
LibrarySystem::LibrarySystem() {
    bookManager.loadFromFile(); // 初始化时加载数据
    bookManager.sortBooksById(); // 按照ID排序书本
    isRunning = true; // 设置程序运行状态为 true
}

// 析构函数
LibrarySystem::~LibrarySystem() {
    bookManager.saveToFile(); // 退出时保存数据
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
    isRunning = false;
}

// 获取程序运行状态
bool LibrarySystem::getIsRunning() {
    return isRunning;
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
}

// 展示所有书本信息
void LibrarySystem::showBooks() {
    if (bookManager.getBookSize() > 0) { //  检查books容器的长度
        bookManager.displayBooks();
    } else {
        cout << "No books available." << endl;
    }
}

// 删除书本
void LibrarySystem::deleteBook() {
    bookManager.deleteBook();
}

// 搜索书本
void LibrarySystem::searchBook() {
    int choice;
    cout << "please search book by: 1. ID  2. Title" << endl;
    cin >> choice;
    if (choice == 1) {
        Book* book = bookManager.searchById();
        if (book) {
            cout << "Book found: ID: " << book->id 
                 << ", Title: " << book->title
                 << ", Author: " << book->author
                 << ", Total Stock: " << book->totalStock
                << ", Available Stock: " << book->availableStock
                << ", Version: " << book->version << endl;
        } else {
            cout << "No book found with the given ID." << endl;
        }
    } else if (choice == 2) {
        vector<Book*> results = bookManager.searchByTitle();
        if (!results.empty()) {
            cout << "Books found:" << endl;
            for (const auto& book : results) {
                cout << "Book found: ID: " << book->id 
                 << ", Title: " << book->title
                 << ", Author: " << book->author
                 << ", Total Stock: " << book->totalStock
                << ", Available Stock: " << book->availableStock 
                << ", Version: " << book->version << endl;
        }
    } else {
            cout << "No books found with the given title." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
                     
}


// 借阅书本
void LibrarySystem::borrowBook() {
    int choice;
    cout << "please borrow book by: 1. ID  2. Title" << endl;
    cin >> choice;
    if (choice == 1) {
        // 查找书本
        Book* book = bookManager.searchById();
        if (book) {
            // 找到书本
            if (book->availableStock > 0) {
                book->availableStock -= 1;
                cout << "You have successfully borrowed the book: " << book->title << endl;
            } else {
                cout << "Sorry, the book \"" << book->title << "\" is currently out of stock." << endl;
            }
        } else {
            cout << "No book found with the given ID." << endl;
        }
    } else if (choice == 2) {
        // 查找书本
        vector<Book*> book = bookManager.searchByTitle();  // 通过书名查找可能返回多个结果
        if (!book.empty()) {
            // 展示找到的书本列表
            cout << "Books found:" << endl;
            for (const auto& b : book) {
                cout << "Book found: ID: " << b->id 
                     << ", Title: " << b->title
                     << ", Author: " << b->author
                     << ", Total Stock: " << b->totalStock
                     << ", Available Stock: " << b->availableStock
                     << ", Version: " << b->version << endl;
            }
            // 让用户选择具体要借阅的书本id
            int borrowId;
            cout << "Enter the ID of the book you want to borrow: ";
            cin >> borrowId;
            Book* selectedBook = nullptr;
            for (const auto& b : book) {
                if (b->id == borrowId) {
                    selectedBook = b;
                    break;
                }
            }
            if (selectedBook) {
                if (selectedBook->availableStock > 0) {
                    selectedBook->availableStock -= 1;
                    cout << "You have successfully borrowed the book: " << selectedBook->title << endl;
                } else {
                    cout << "Sorry, the book \"" << selectedBook->title << "\" is currently out of stock." << endl;
                }
            } else {
                cout << "No book found with the given ID." << endl;
            }
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
    
}

// 还书
void LibrarySystem::returnBook() {
    // 还书的时候，只需要输入ID或者书名即可
    int choice;
    cout << "Please return book by: 1. ID  2. Title" << endl;
    cin >> choice;
    if (choice == 1) {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;
        Book* book = bookManager.searchById();
        if (book) {
            book->availableStock += 1;
            cout << "You have successfully returned the book: " << book->title << endl;
        } else {
            cout << "No book found with the given ID." << endl;
        }
    } else if (choice == 2) {
        string title;
        cout << "Enter book title to return: ";
        cin.ignore();
        getline(cin, title);
        vector<Book*> results = bookManager.searchByTitle();
        if (!results.empty()) {
            for (const auto& book : results) {
                if (book->title == title) {
                    book->availableStock += 1;
                    cout << "You have successfully returned the book: " << book->title << endl;
                    return;
                }
            }
        }
        cout << "No books found with the given title." << endl;
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

