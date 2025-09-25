#include "user.h"
#include <iostream>
#include <cstring>
#include <cJSON.h>
#include <fstream>
#define filename "data/user.json"

using namespace std;

User curUser; // 当前登录用户


void UserManager::showLogMenu() {
    // 选择登录高或者注册
    int choice;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cin >> choice;
    if (choice == 1) {
        signIn();
    } else if (choice == 2) {
        signOn();
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}


// 注册
void UserManager::signOn() {
    // 注册逻辑
    string username, password;    
    cout << "Enter username: ";
    cin >> username;    

    // 验证用户名是否存在
    for (const auto& user : users) {
        if (user.username == username) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }
    }
    
    cout << "Enter password: (at least 8 characters with numbers, uppercase and lowercase letters) ";
    cin >> password;
    // 首先验证密码格式是否正确
    if (!verifyPasswordFormat(password.c_str())) {
        cout << "Invalid password format. Registration failed." << endl;
        return;
    }
    // 给密码加盐
    password =  saltPassword(password);
    // 是否注册为管理员
    cout << "Register as admin? (y/n): ";
    char isAdminChoice;
    cin >> isAdminChoice;
    bool isAdmin = (isAdminChoice == 'y' || isAdminChoice == 'Y');
    if (isAdmin) {
        int adminKey;
        cout << "Enter admin key: ";
        cin >> adminKey;
        if (adminKey != ADMIN_KEY) {
            cout << "Invalid admin key. Registering as regular user." << endl;
            isAdmin = false;
        }
    }

    User user;
    user.isAdmin = isAdmin;
    user.username = username;
    user.password = password;

    // 将新用户添加到容器
    users.push_back(user);
    cout << "Registration successful!" << endl;
}

// 登录
void UserManager::signIn() {
    // 登录逻辑
    // 选择admin或者普通用户登录
    int choice;
    cout << "Login as: 1. Admin  2. User" << endl;
    cin >> choice;
    if (choice == 1) {
        // 管理员登录逻辑
        string username, password;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;
        // 首先验证密码格式是否正确
        if (!verifyPasswordFormat(password.c_str())) {
            cout << "Invalid password format. Registration failed." << endl;
            return;
        }
        // 给密码加盐
        password =  saltPassword(password);
        // 输入密钥
        int adminKey;
        cout << "Enter admin key: ";
        cin >> adminKey;
        if (adminKey != ADMIN_KEY) {
            cout << "Invalid admin key. Login failed." << endl;
            return; 
        }
        
        User user;
        user.isAdmin = true;
        user.username = username;
        user.password = password;
        // 这里可以添加验证逻辑
        if (!verifyUserInfoFromJson(user)) {
            cout << "Admin credentials not found or incorrect. Login failed." << endl;
            return;
        }
        // 登录成功，设置当前用户
        curUser = user;
        cout << "Admin login successful!" << endl;
    } else if (choice == 2) {
        // 普通用户登录逻辑
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // 首先验证密码格式是否正确
        if (!verifyPasswordFormat(password.c_str())) {
            cout << "Invalid password format. Registration failed." << endl;
            return;
        }
        // 给密码加盐
        password =  saltPassword(password);

        User user;
        user.isAdmin = false;
        user.username = username;
        user.password = password;
        // 这里可以添加验证逻辑
        if (!verifyUserInfoFromJson(user)) {
            cout << "User credentials not found or incorrect. Login failed." << endl;
            return;
        }
        // 登录成功，设置当前用户
        curUser = user;
        cout << "User login successful!" << endl;
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

bool UserManager::verifyPasswordFormat(const char* password) {
    int length = strlen(password);
    if (length < 8) return false;

    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (int i = 0; i < length; ++i) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}


string UserManager::saltPassword(const string& password) {
    return password + "S@ltStr1ng";
}



void UserManager::saveUserInfoToJson() {
    cJSON* root = cJSON_CreateObject();
    cJSON* usersArray = cJSON_CreateArray();
    cJSON_AddItemToObject(root, "users", usersArray);

    for ( auto& user : users) {
        cJSON* userJson = cJSON_CreateObject();
        cJSON_AddStringToObject(userJson, "username", user.username.c_str());
        cJSON_AddStringToObject(userJson, "password", user.password.c_str());
        cJSON_AddBoolToObject(userJson, "isAdmin", user.isAdmin);
        cJSON_AddItemToArray(usersArray, userJson);
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

bool UserManager::verifyUserInfoFromJson(User& usr) {
    // 传入当前数据, 验证JSON文件中的用户信息
   // 遍历用户容器
   for (const auto& user : users) {
        if (user.username == usr.username && user.password == usr.password && user.isAdmin == usr.isAdmin) {
            return true; // 找到匹配的用户
        }
   }
   return false; // 未找到匹配的用户
}


// 从 JSON 文件加载用户到容器
void UserManager::loadFromFile() {
    // 清空现有 users 容器
    users.clear();

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

    // 获取 users 数组
    cJSON* usersArray = cJSON_GetObjectItem(root, "users");
    if (!usersArray || !cJSON_IsArray(usersArray)) {
        std::cout << "Error: Invalid or missing 'users' array in JSON!" << std::endl;
        cJSON_Delete(root);
        return;
    }

    // 遍历 users 数组
    for (int i = 0; i < cJSON_GetArraySize(usersArray); ++i) {
        cJSON* userJson = cJSON_GetArrayItem(usersArray, i);
        if (!cJSON_IsObject(userJson)) {
            std::cout << "Error: Invalid user object at index " << i << std::endl;
            continue;
        }

        User user;
        // 获取字段
        cJSON* username = cJSON_GetObjectItem(userJson, "username");
        cJSON* password = cJSON_GetObjectItem(userJson, "password");
        cJSON* isAdmin = cJSON_GetObjectItem(userJson, "isAdmin");
        // 验证字段是否存在且类型正确
        if (!username || !cJSON_IsString(username) ||
            !password || !cJSON_IsString(password) ||
            !isAdmin || !cJSON_IsBool(isAdmin)) {
            std::cout << "Error: Missing or invalid fields in user object at index " << i << std::endl;
            continue;
        }

        // 填充 User 结构体
        user.username = username->valuestring;
        user.password = password->valuestring;
        user.isAdmin = isAdmin->valueint;

        // 添加到 users 容器
        users.push_back(user);
    }
}


bool UserManager::getUserStatus() {
    return curUser.isAdmin;
}
