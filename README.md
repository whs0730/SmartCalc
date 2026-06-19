# SmartCalc

SmartCalc 是一个使用 C++17、CMake 和 Qt Widgets 规划开发的智能科学计算器课程项目。
项目计划支持普通表达式计算、科学计算、复数、矩阵、函数绘图、单位转换、
历史记录和设置管理。

## 当前状态

| 模块         | 状态          |
| ---------- | ----------- |
| `math`     | 已实现并有测试     |
| `core`     | 文件已创建，内容待实现 |
| `storage`  | 文件已创建，内容待实现 |
| `utils`    | 文件已创建，内容待实现 |
| `gui`      | 文件已创建，内容待实现 |
| `main.cpp` | 待实现         |

当前只有数学模块具有实际功能。其他模块仍是项目骨架，完整程序暂时没有界面和交互入口。

## 项目结构

```text
SmartCalc/
|-- src/
|   |-- core/       表达式解析与求值
|   |-- math/       数学数据结构与算法
|   |-- storage/    历史记录和设置存储
|   |-- utils/      通用辅助工具
|   |-- gui/        Qt 图形界面
|   `-- main.cpp    程序入口
|-- tests/          测试代码
|-- CMakeLists.txt  CMake 构建配置
|-- .gitignore      Git 忽略规则
`-- README.md       项目开发说明
```

## 文件说明

### src/math

数学模块已经实现，可以独立使用。

| 文件                       | 意义                           |
| ------------------------ | ---------------------------- |
| `ComplexNumber.h`        | 声明复数类，保存实部和虚部，提供四则运算、模长和共轭功能 |
| `ComplexNumber.cpp`      | 实现复数类中的计算逻辑和除零检查             |
| `Matrix.h`               | 声明矩阵类，保存矩阵数据并提供基本矩阵操作        |
| `Matrix.cpp`             | 实现矩阵创建、元素访问、加减、乘法、数乘和转置      |
| `MatrixSolver.h`         | 声明矩阵高级计算类                    |
| `MatrixSolver.cpp`       | 实现行列式、逆矩阵、高斯消元和线性方程组求解       |
| `ScientificFunction.h`   | 声明三角函数、对数、开方、乘方和阶乘等科学计算接口    |
| `ScientificFunction.cpp` | 实现科学计算及参数范围检查                |
| `FunctionSampler.h`      | 声明采样点结构和函数采样类                |
| `FunctionSampler.cpp`    | 在指定区间等距计算函数值，为曲线绘图生成坐标点      |
| `UnitConverter.h`        | 声明角度、长度和温度单位及转换接口            |
| `UnitConverter.cpp`      | 实现角度、长度和温度之间的换算              |

### src/core

表达式核心模块目前为空，计划负责把用户输入的表达式转换为计算结果。

| 文件                     | 意义                    |
| ---------------------- | --------------------- |
| `Token.h/.cpp`         | 表示数字、运算符、括号和函数名等      |
| `Lexer.h/.cpp`         | 将表达式字符串拆分成 Token 序列   |
| `Parser.h/.cpp`        | 检查表达式语法和运算符优先级，生成表达式树 |
| `ASTNode.h/.cpp`       | 定义抽象语法树节点，保存表达式结构     |
| `Evaluator.h/.cpp`     | 遍历表达式树并计算最终结果         |
| `OperatorTable.h/.cpp` | 统一保存运算符优先级、结合方向等规则    |
| `CalcException.h/.cpp` | 定义非法字符、语法错误和除零等计算异常   |

计划中的调用过程：

```text
表达式字符串 -> Lexer -> Token -> Parser -> ASTNode -> Evaluator -> 结果
```

### src/storage

存储模块目前为空，计划负责历史记录和程序设置的持久化。

| 文件                       | 意义                   |
| ------------------------ | -------------------- |
| `HistoryRecord.h/.cpp`   | 表示一条计算历史，例如表达式、结果和时间 |
| `HistoryManager.h/.cpp`  | 管理历史记录的添加、删除、查询和保存   |
| `SettingsManager.h/.cpp` | 管理精度、角度模式和界面主题等设置    |
| `JsonStorage.h/.cpp`     | 负责 JSON 文件的读取和写入     |

### src/utils

工具模块目前为空，用于存放多个模块都会使用的辅助功能。

| 文件                    | 意义                 |
| --------------------- | ------------------ |
| `StringUtil.h/.cpp`   | 字符串去空格、分割和大小写转换等操作 |
| `NumberFormat.h/.cpp` | 控制计算结果的小数位数和显示格式   |
| `TimeUtil.h/.cpp`     | 获取和格式化时间，主要供历史记录使用 |

### src/gui

GUI 已使用 Qt Widgets 实现。

| 文件                      | 意义                 |
| ----------------------- | ------------------ |
| `MainWindow.h/.cpp`     | 主窗口，负责菜单、导航和功能页面组织 |
| `BasicCalcPage.h/.cpp`  | 普通四则运算页面           |
| `UnitPage.h/.cpp` 	  | 单位转换页面        |
| `MatrixPage.h/.cpp`     | 矩阵输入、计算和结果显示页面     |
| `PlotPage.h/.cpp`       | 函数输入、采样和曲线绘制页面     |
| `HistoryPage.h/.cpp`    | 历史记录显示和管理页面        |
| `SettingsDialog.h/.cpp` | 程序设置对话框            |

GUI 只负责接收输入和显示结果，具体算法应放在 `core` 或 `math` 中。
##注意：
各接口在各实现文件的onXXX函数中，亟待完善

### src/main.cpp

程序入口。当前为空。

GUI 完成后，该文件负责创建 `QApplication`、显示 `MainWindow` 并启动 Qt 事件循环。
当前 CMake 会在它没有 `main()` 时生成一个临时入口，以便其他模块可以先编译。

### tests

| 文件                    | 意义                     |
| --------------------- | ---------------------- |
| `test_matrix.cpp`     | 测试矩阵基本运算、行列式、逆矩阵和线性方程组 |
| `test_math.cpp`       | 测试复数、科学函数、函数采样和单位转换    |
| `test_expression.cpp` | 预留给表达式解析与求值测试，目前为空     |
| `test_exception.cpp`  | 预留给异常处理测试，目前为空         |

### 根目录文件

| 文件               | 意义                          |
| ---------------- | --------------------------- |
| `CMakeLists.txt` | 定义项目、模块库、Qt 查找方式、可执行程序和测试目标 |
| `.gitignore`     | 忽略构建输出、IDE 配置和临时文件          |
| `README.md`      | 说明项目结构和每个文件的职责              |

## 模块关系

```text
main
  |
  v
gui
  |---- core       表达式解析与求值
  |---- math       数学计算
  |---- storage    历史记录和设置
  `---- utils      通用辅助工具
```

## 构建方法

不使用 Qt 构建当前项目：

```powershell
cmake -S . -B build -DSMARTCALC_ENABLE_QT=OFF
cmake --build build
```

构建现有测试：

```powershell
cmake -S . -B build `
  -DSMARTCALC_ENABLE_QT=OFF `
  -DSMARTCALC_BUILD_TESTS=ON

cmake --build build --target test_math test_matrix
ctest --test-dir build -R "^(math|matrix)$" --output-on-failure
```

`test_expression` 和 `test_exception` 目前为空，不需要构建。

## 开发约定

- 类声明放在 `.h`，实现放在同名 `.cpp`。
- 头文件引用统一从 `src` 开始，例如 `#include "math/Matrix.h"`。
- GUI 中不直接实现数学算法或文件存储。
- 新增文件后要加入 `CMakeLists.txt` 对应模块。
- 新增功能时同时补充测试和本 README 的文件说明。
- 浮点数测试应使用误差比较，不要直接判断完全相等。
- 参数非法时使用异常报告错误。
