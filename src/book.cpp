/*
    用来添加书籍的信息的源代码
*/
#include "book.h"
#include <cJSON.h>
#include <fstream>
#define filename "data/books.json"
// 添加书本
void BookManager::addBook() {
    Book newBook;
    cout << "Enter book ID: ";
    cin >> newBook.id;
    // 检查ID是否已存在
    for (const auto& book : books) {
        if (book.id == newBook.id) {
            cout << "Book ID already exists. Please try again." << endl;
            return;
        }
    }

    cout << "Enter book title: ";
    cin.ignore(); // 清除输入缓冲区
    getline(cin, newBook.title);

    cout << "Enter book author: ";
    getline(cin, newBook.author);

    // 根据书名更新库存和可借阅库存
    int flag = 0; // 标志库存是否有该书
    for (auto& book : books) {
        if (book.title == newBook.title) {
            // 跟新每本相同名字的书的库存信息
            book.totalStock += 1;
            book.availableStock += 1;
            // 更新新书的库存信息
            newBook.totalStock = book.totalStock;
            newBook.availableStock = book.availableStock;
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        // 新书，库存和可借阅数量均为1
        newBook.totalStock = 1;
        newBook.availableStock = 1;
    }

    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

// 删除书本
void BookManager::deleteBook() {
}

// 通过ID查找书本
// Book* BookManager::searchById() {

// }

// 通过书名查找书本
// vector<Book*> BookManager::searchByTitle() {

// }

// 展示所有书本信息
void BookManager::displayBooks() {

}

// 保存书本信息到文件
void BookManager::saveToFile() {
    cJSON* root = cJSON_CreateObject();
    cJSON* booksArray = cJSON_CreateArray();
    cJSON_AddItemToObject(root, "books", booksArray);

    for ( auto& book : books) {
        cJSON* bookJson = cJSON_CreateObject();
        cJSON_AddStringToObject(bookJson, "id", to_string(book.id).c_str());
        cJSON_AddStringToObject(bookJson, "title", book.title.c_str());
        cJSON_AddStringToObject(bookJson, "author", book.author.c_str());
        cJSON_AddNumberToObject(bookJson, "totalStock", book.totalStock);
        cJSON_AddNumberToObject(bookJson, "availableStock", book.availableStock);
        cJSON_AddItemToArray(booksArray, bookJson);
    }

    char* jsonString = cJSON_Print(root);
    if (!jsonString) {
        cout << "Error: JSON serialization failed!" << endl;
        cJSON_Delete(root);
        return;
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << " for writing!" << endl;
        cJSON_free(jsonString);
        cJSON_Delete(root);
        return;
    }
    file << jsonString;
    file.close();

    cJSON_free(jsonString);
    cJSON_Delete(root);
    cout << "Data has been saved to " << filename << endl;
}

// 从文件加载书本信息并且将其存储到 books 容器中
void BookManager::loadFromFile() {
    
}
