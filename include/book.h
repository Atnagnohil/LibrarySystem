#ifndef BOOK_H
#define BOOK_H
/*
    用来添加书籍信息的头文件
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 书本结构体
struct Book {
    int id;
    string title;
    string author;
    int totalStock; // 总库存
    int availableStock; // 可借阅数量
    int version; // 版本号
};
class BookManager {
    public:
        void addBook();
        void deleteBook();
        Book* searchById();
        vector<Book*> searchByTitle();
        void displayBooks();
        void saveToFile(); 
        void loadFromFile();
        int getBookSize();
        void sortBooksById();
    private:
        vector<Book> books; // 存储书本信息的容器
};


#endif // BOOK_H