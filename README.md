# 项目说明
## 功能说明

1. **显示图书信息**  
   - 显示图书的 ID、书名、作者、库存数量（总量和可借数量）、借阅状态。

2. **查找图书**  
   - 支持通过 ID 或书名查找图书，可进行模糊匹配。

3. **JSON 数据管理**  
   - 图书信息存储在 `data/books.json`，通过 `JsonUtils` 进行读写操作。

4. **CMake 构建**  
   - 使用 `CMakeLists.txt` 进行跨平台构建，生成可执行文件在 `build/` 目录。

# 快速使用指南

## 1. 构建项目（Windows / Linux）

```bash
mkdir build
cd build

cmake ..

cmake --build .
````

可执行文件将在 `build/LibrarySystem.exe`（Windows）或 `build/LibrarySystem`（Linux）生成。

---

## 2. 运行项目

```bash
./LibrarySystem      # Linux
LibrarySystem.exe    # Windows
```

---

## 3. GitHub 同步流程

### 3.1 初始化本地 Git 仓库

```bash
git init
git add .
git commit -m "Initial commit"
```

### 3.2 添加远程仓库

```bash
git remote add origin https://github.com/Atnagnohil/LibrarySystem
git remote -v
```



