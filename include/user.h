// 用户信息结构体及登录的相关函数
#ifndef USER_H
#define USER_H
// 定义管理员密钥: 
#define ADMIN_KEY 123456
#include <vector>
#include <string>
using namespace std;
struct User
{
    string username;
    string password;
    bool isAdmin; // 是否为管理员
};

class UserManager {
    public:
        void showLogMenu(); // 显示登录菜单
        void signOn();  // 注册新用户
        void signIn();  // 用户登录
        string saltPassword(const string& password); // 给密码加盐
        bool verifyPasswordFormat(const char* password); // 验证密码是否为8位含数字，大小写字母
        void saveUserInfoToJson();   // 存储用户容器信息到JSON
        bool verifyUserInfoFromJson(User& usr);       // 验证JSON文件中的用户信息
        void loadFromFile(); // 从文件加载用户信息
        bool getUserStatus();
   private:
        vector<User> users; /// 存储用户信息的容器
};


#endif // USER_H