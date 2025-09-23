/*
    用来添加书籍的信息的源代码
*/
#include <algorithm>
#include "book.h"
#include <cJSON.h>
#include <fstream>
#define filename "data/books.json"
// 添加书本
void BookManager::addBook() {
    Book newBook;
    Book* existingBook = nullptr;  // 检查的是否存在书
    cout << "Enter book ID: ";
    cin >> newBook.id;
    
    int flag = 0;  // 标注是否是新书
    // 首先检查id是否存在
    for (const auto& book : books) {
        if (book.id == newBook.id) {
            flag = 1; // 不是新书
            existingBook = const_cast<Book*>(&book);  // 记录已存在的书  // 使用 const_cast 去掉 const 限定符
            break;
        }
    }

    cout << "Enter book title: ";
    cin.ignore(); // 清除输入缓冲区
    getline(cin, newBook.title);

    if (flag && existingBook->title != newBook.title) {
        cout << "Warning: The ID already exists with a different title (" 
             << existingBook->title << ")." << endl;
             return;
    }

    cout << "Enter book author: ";
    getline(cin, newBook.author);

    if (flag && existingBook->author != newBook.author) {
        cout << "Warning: The ID already exists with a different author (" 
             << existingBook->author << ")." << endl;
             return;
    }

    // 输入版本号
    cout << "Enter book version: ";
    cin >> newBook.version;
    if (flag && existingBook->version != newBook.version) {
        cout << "Warning: The ID already exists with a different version (" 
             << existingBook->version << ")." << endl;
             return;
    }

    // 根据id更新库存和可借阅库存
    for (auto& book : books) {
        if (book.id == newBook.id) {
            book.totalStock += 1;
            book.availableStock += 1;
            break;
        }
    }

    if (flag == 0) {
        // 新书，库存和可借阅数量均为1
        newBook.totalStock = 1;
        newBook.availableStock = 1;
        books.push_back(newBook); // 将新书添加到容器中
    }

    cout << "Book added successfully!" << endl;
}

// 删除书本
void BookManager::deleteBook() {
    int choice;
    cout << "please delete book by: 1. ID  2. Title" << endl;
    cin >> choice;
    if (choice == 1) {
        int id;
        cout << "Enter book ID to delete: ";
        cin >> id;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) { //  找到书本对应的ID
                // 找到书本，更新库存
                it->totalStock -= 1;
                it->availableStock -= 1;
                if (it->totalStock <= 0) {
                    // 库存为0，删除书本
                    books.erase(it);
                    cout << "Book with ID " << id << " has been deleted." << endl;
                } else {
                    cout << "Book with ID " << id << " stock decreased. Total Stock: " 
                         << it->totalStock << ", Available Stock: " << it->availableStock << endl;
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found." << endl;
    } else if (choice == 2) {
        string title;
        cout << "Enter book title to delete: ";
        cin.ignore(); // 清除输入缓冲区
        getline(cin, title);
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                // 找到书本，更新库存
                it->totalStock -= 1;
                it->availableStock -= 1;
                if (it->totalStock <= 0) {
                    // 库存为0，删除书本
                    books.erase(it);
                    cout << "Book with title \"" << title << "\" has been deleted." << endl;
                } else {
                    cout << "Book with title \"" << title << "\" stock decreased. Total Stock: " 
                         << it->totalStock << ", Available Stock: " << it->availableStock << endl;
                }
                return;
            }
        }
        cout << "Book with title \"" << title << "\" not found." << endl;
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

// 通过ID查找书本
Book* BookManager::searchById() {
    int id;
    cout << "Enter book ID to search: ";
    cin >> id;
    for (auto& book : books) {
        if (book.id == id) {
            return &book;
        }
    }
    return nullptr;
}

// 通过书名查找书本
vector<Book*> BookManager::searchByTitle() {
    string title;
    cout << "Enter book title to search: ";
    cin.ignore();  //  清除输入缓冲区
    getline(cin, title);
    vector<Book*> results;
    for (auto& book : books) {
        if (book.title.find(title) != string::npos) {
            // book.title 如果包含 title 子串，返回其首地址
            // != string::npos：检查是否找到了子字符串。如果 find 不返回 npos，说明 title 是 book.title 的子字符串
            results.push_back(&book);
        }
    }
    return results;
}



// 展示所有书本信息
void BookManager::displayBooks() {
    // 从books容器中读取书本信息并打印
    for (const auto& book : books) {
        cout << "ID: " << book.id 
             << ", Title: " << book.title
             << ", Author: " << book.author
             << ", Total Stock: " << book.totalStock
             << ", Available Stock: " << book.availableStock
             << ", Version: " << book.version << endl;
    }
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
        cJSON_AddNumberToObject(bookJson, "version", book.version);
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
    // 清空现有 books 容器
    books.clear();

    // 读取 JSON 文件
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file " << filename << " for reading!" << std::endl;
        return;
    }

    // 读取文件内容
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // 解析 JSON
    cJSON* root = cJSON_Parse(content.c_str());
    if (!root) {
        std::cout << "Error: JSON parsing failed!" << std::endl;
        return;
    }

    // 获取 books 数组
    cJSON* booksArray = cJSON_GetObjectItem(root, "books");
    if (!booksArray || !cJSON_IsArray(booksArray)) {
        std::cout << "Error: Invalid or missing 'books' array in JSON!" << std::endl;
        cJSON_Delete(root);
        return;
    }

    // 遍历 books 数组
    for (int i = 0; i < cJSON_GetArraySize(booksArray); ++i) {
        cJSON* bookJson = cJSON_GetArrayItem(booksArray, i);
        if (!cJSON_IsObject(bookJson)) {
            std::cout << "Error: Invalid book object at index " << i << std::endl;
            continue;
        }

        Book book;
        // 获取字段
        cJSON* id = cJSON_GetObjectItem(bookJson, "id");
        cJSON* title = cJSON_GetObjectItem(bookJson, "title");
        cJSON* author = cJSON_GetObjectItem(bookJson, "author");
        cJSON* totalStock = cJSON_GetObjectItem(bookJson, "totalStock");
        cJSON* availableStock = cJSON_GetObjectItem(bookJson, "availableStock");
        cJSON* version = cJSON_GetObjectItem(bookJson, "version");
        // 验证字段是否存在且类型正确
        if (!id || !cJSON_IsString(id) ||
            !title || !cJSON_IsString(title) ||
            !author || !cJSON_IsString(author) ||
            !totalStock || !cJSON_IsNumber(totalStock) ||
            !availableStock || !cJSON_IsNumber(availableStock) ||
            !version || !cJSON_IsNumber(version)) {
            std::cout << "Error: Missing or invalid fields in book object at index " << i << std::endl;
            continue;
        }

        // 填充 Book 结构体
        book.id = std::stoi(id->valuestring);
        book.title = title->valuestring;
        book.author = author->valuestring;
        book.totalStock = static_cast<int>(totalStock->valuedouble);
        book.availableStock = static_cast<int>(availableStock->valuedouble);
        book.version = static_cast<int>(version->valuedouble);

        // 添加到 books 容器
        books.push_back(book);
    }

    cJSON_Delete(root);
    std::cout << "Data has been loaded from " << filename << std::endl;

    // // 清空 JSON 文件，写入空的 JSON 结构
    // cJSON* emptyRoot = cJSON_CreateObject();
    // cJSON* emptyBooksArray = cJSON_CreateArray();
    // cJSON_AddItemToObject(emptyRoot, "books", emptyBooksArray);

    // char* jsonString = cJSON_Print(emptyRoot);
    // if (!jsonString) {
    //     std::cout << "Error: JSON serialization failed when clearing file!" << std::endl;
    //     cJSON_Delete(emptyRoot);
    //     return;
    // }

    // std::ofstream outFile(filename);
    // if (!outFile.is_open()) {
    //     std::cout << "Error: Unable to open file " << filename << " for writing!" << std::endl;
    //     cJSON_free(jsonString);
    //     cJSON_Delete(emptyRoot);
    //     return;
    // }
    // outFile << jsonString;
    // outFile.close();

    // cJSON_free(jsonString);
    // cJSON_Delete(emptyRoot);
    // std::cout << "File " << filename << " has been cleared!" << std::endl;
}


// 返回当前书本数量
int BookManager::getBookSize(){
    return (int)books.size();
}


// 按照ID排序书本
void BookManager::sortBooksById() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.id < b.id;
    });
}


