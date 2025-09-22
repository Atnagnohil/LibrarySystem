#include <iostream>
#include <cstdlib>
#include "../include/LibrarySystem.h"
using namespace std;
/*
	图书管理系统主要功能：
		1，读取数据文件：从JSON读取图书信息，并按照 id/书名 排序
		2，显示图书信息：id, 书名，作者，库存数量（总数量和可借数量），借阅状态（是否已被借出）
		3，查找图书：通过 ID 或书名查找，支持简单模糊匹配。
		4，借阅/归还图书：支持借阅和归还，更新库存状态。
		5，添加图书：允许管理员添加新图书（简单输入 ID、书名、库存）。
		6，删除图书：支持通过 ID 删除图书。
		7，保存数据：操作后自动保存到文件。
		8，简单菜单：提供清晰的命令行菜单，方便用户选择操作。
		9，错误提示：对无效输入（如 ID 不存在、库存不足）提供简洁提示。
*/

int main()
{

    LibrarySystem libSys;
    libSys.showMenu();
	system("pause");
	return 0;
}


