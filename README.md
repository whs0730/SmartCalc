# SmartCalc

SmartCalc 是一个使用 C++17、CMake 和 Qt Widgets 编写的科学计算器课程项目。项目把计算逻辑、数学算法、历史记录、工具函数和图形界面分成独立模块，便于分工开发和后续扩展。

目前程序已经能够完成基础表达式计算、科学函数计算、矩阵运算、单位转换、函数绘图和历史记录展示。核心计算逻辑主要放在 `core`、`math`、`storage`、`utils` 中，Qt 界面只负责接收输入和显示结果。

## 当前状态

| 模块             | 状态      | 主要内容                               |
| -------------- | ------- | ---------------------------------- |
| `src/core`     | 已补全     | 表达式词法分析、语法分析、表达式树、求值和异常处理          |
| `src/math`     | 已补全     | 复数、矩阵、矩阵求解、科学函数、函数采样和单位转换          |
| `src/storage`  | 已实现基础功能 | 历史记录、设置读写和简单文件存储                   |
| `src/utils`    | 已补全     | 字符串处理、数字格式化、时间格式化                  |
| `src/gui`      | 已串联     | 基础计算、矩阵、函数绘图、单位转换、历史记录和设置窗口        |
| `src/main.cpp` | 已实现     | 创建 `QApplication`，显示主窗口并启动 Qt 事件循环 |
| `tests`        | 已补充     | 覆盖表达式、异常、数学、矩阵、存储和工具函数             |

## 功能说明

- 基础表达式：支持 `+`、`-`、`*`、`/`、`^`、括号、正负号和阶乘。
- 科学函数：支持 `sin`、`cos`、`tan`、`ln`、`log`、`sqrt`、`abs`、`exp`、`squa`、`pow`、`fact`。
- 常量与变量：支持 `pi`、`e`，函数绘图时支持变量 `x`。
- 矩阵运算：支持矩阵创建、加法、减法、乘法、转置、行列式、逆矩阵和线性方程组求解。
- 单位转换：支持长度、温度、角度之间的常用换算。
- 函数绘图：使用表达式求值器对 `x` 取样，并通过 Qt Charts 绘制曲线。
- 历史记录：基础计算、矩阵计算、单位转换和绘图操作会写入历史页面，并保存到本地文件。

注意：当前三角函数计算使用 C++ 标准库的弧度制，表达式里的 `sin(pi/2)` 等写法是推荐用法。角度/弧度模式设置界面已有入口，但还没有完全接入表达式求值流程。

## 项目结构

```text
SmartCalc/
|-- src/
|   |-- core/       表达式解析、表达式树和求值
|   |-- math/       复数、矩阵、科学函数、单位转换等数学能力
|   |-- storage/    历史记录和设置管理
|   |-- utils/      字符串、数字格式、时间等通用工具
|   |-- gui/        Qt Widgets 图形界面
|   `-- main.cpp    程序入口
|-- tests/          模块测试
|-- docs/           项目资料或补充文档
|-- CMakeLists.txt  CMake 构建配置
|-- .gitignore      Git 忽略规则
`-- README.md       项目说明
```

## 模块关系

```text
main.cpp
   |
   v
MainWindow
   |
   |-- BasicCalcPage  -> core::Evaluator
   |-- PlotPage       -> core::Evaluator + Qt Charts
   |-- MatrixPage     -> math::Matrix / MatrixSolver
   |-- UnitPage       -> math::UnitConverter
   |-- HistoryPage    -> storage::HistoryManager
   `-- SettingsDialog -> storage::SettingsManager / QSettings
```

## 主要文件说明

### `src/core`

| 文件                     | 作用                             |
| ---------------------- | ------------------------------ |
| `Token.h/.cpp`         | 定义表达式中的数字、运算符、括号、函数名、变量等 Token |
| `Lexer.h/.cpp`         | 将用户输入的字符串拆分成 Token 序列          |
| `Parser.h/.cpp`        | 按运算符优先级解析表达式，生成抽象语法树           |
| `ASTNode.h/.cpp`       | 保存表达式树节点，包括数字、变量、一元运算、二元运算和函数  |
| `Evaluator.h/.cpp`     | 遍历语法树并计算结果，也提供直接计算字符串表达式的接口    |
| `OperatorTable.h/.cpp` | 统一保存运算符优先级和结合方向                |
| `CalcException.h/.cpp` | 定义词法、语法、求值阶段使用的异常类型            |

表达式计算流程：

```text
输入字符串 -> Lexer -> Token 序列 -> Parser -> ASTNode 表达式树 -> Evaluator -> double 结果
```

### `src/math`

| 文件                          | 作用                       |
| --------------------------- | ------------------------ |
| `ComplexNumber.h/.cpp`      | 复数类，支持四则运算、模长和共轭         |
| `Matrix.h/.cpp`             | 矩阵类，支持创建、访问、加减、乘法、数乘和转置  |
| `MatrixSolver.h/.cpp`       | 矩阵高级运算，支持行列式、逆矩阵和线性方程组求解 |
| `ScientificFunction.h/.cpp` | 三角函数、对数、开方、幂运算、阶乘等科学计算   |
| `FunctionSampler.h/.cpp`    | 在区间内对函数进行等距采样            |
| `UnitConverter.h/.cpp`      | 长度、温度、角度单位转换             |

### `src/storage`

| 文件                       | 作用                    |
| ------------------------ | --------------------- |
| `HistoryRecord.h/.cpp`   | 表示一条历史记录，包括表达式、结果和时间  |
| `HistoryManager.h/.cpp`  | 管理历史记录的添加、删除、搜索、保存和加载 |
| `SettingsManager.h/.cpp` | 管理角度模式、精度、主题等设置       |
| `JsonStorage.h/.cpp`     | 负责历史记录的文件保存和读取        |

### `src/utils`

| 文件                    | 作用                              |
| --------------------- | ------------------------------- |
| `StringUtil.h/.cpp`   | 去空格、大小写转换、分割、拼接、替换和数字字符串判断      |
| `NumberFormat.h/.cpp` | 普通格式、定点格式、科学计数法、百分比格式和浮点近似比较    |
| `TimeUtil.h/.cpp`     | 当前日期时间、文件安全时间戳、Unix 时间戳和自定义时间格式 |

### `src/gui`

| 文件                      | 作用                                       |
| ----------------------- | ---------------------------------------- |
| `MainWindow.h/.cpp`     | 主窗口，负责菜单、页面切换、历史记录加载保存和页面信号连接            |
| `BasicCalcPage.h/.cpp`  | 基础计算器页面，调用 `Evaluator` 得到表达式结果           |
| `PlotPage.h/.cpp`       | 函数绘图页面，调用 `Evaluator` 对 `x` 取样并绘图        |
| `MatrixPage.h/.cpp`     | 矩阵页面，调用 `Matrix` 和 `MatrixSolver` 完成矩阵计算 |
| `UnitPage.h/.cpp`       | 单位转换页面，调用 `UnitConverter` 完成换算           |
| `HistoryPage.h/.cpp`    | 历史记录页面，显示、清空和双击复用历史输入                    |
| `SettingsDialog.h/.cpp` | 设置对话框，提供精度、角度模式、主题等设置入口                  |

### `tests`

| 文件                    | 作用                     |
| --------------------- | ---------------------- |
| `test_expression.cpp` | 测试表达式运算、函数、常量和变量 `x`   |
| `test_exception.cpp`  | 测试非法表达式、除零、非法函数参数等异常情况 |
| `test_math.cpp`       | 测试复数、科学函数、函数采样和单位转换    |
| `test_matrix.cpp`     | 测试矩阵基础运算、行列式、逆矩阵和线性方程组 |
| `test_storage.cpp`    | 测试历史记录和设置保存加载          |
| `test_utils.cpp`      | 测试字符串、数字格式和时间工具函数      |

## 构建与运行

### 只构建核心和测试

不需要 Qt 时，可以关闭 GUI，只验证核心模块：

```powershell
cmake -S . -B out/core-tests -DSMARTCALC_ENABLE_QT=OFF -DSMARTCALC_BUILD_TESTS=ON
cmake --build out/core-tests
ctest --test-dir out/core-tests --output-on-failure
```

### 构建 Qt 图形界面

GUI 需要安装 Qt Widgets 和 Qt Charts。Windows 上如果使用 `E:/Qt/6.11.1/msvc2022_64` 这一类 Qt Kit，编译器也要使用 MSVC，不要用 MinGW 去链接 MSVC 版 Qt。

```powershell
cmake -S . -B out/gui -DSMARTCALC_ENABLE_QT=ON -DSMARTCALC_BUILD_TESTS=OFF
cmake --build out/gui
```

CMake 已加入 `windeployqt` 的构建后步骤。正常情况下，GUI 编译完成后会自动复制 Qt 运行时 DLL。如果运行时仍提示缺少 `Qt6Chartsd.dll`，可以检查：

- Qt 安装目录中是否存在 `bin/Qt6Chartsd.dll`。
- 是否安装了 Qt Charts 组件。
- 是否重新运行过 CMake 配置并重新构建。
- 是否把 Qt 的 `bin` 目录加入了运行环境，或者手动执行 `windeployqt SmartCalc.exe`。

### 三角函数是角度还是弧度

当前表达式求值使用弧度制。例如：

```text
sin(pi/2) = 1
cos(0) = 1
```

如果要输入角度，可以先用单位转换页面把角度转成弧度，再放进表达式。

## AI 工具使用说明

本项目部分代码在编写和完善过程中使用了 AI 工具辅助生成或修改，主要涉及以下文件：

- `src/core/ASTNode.cpp`
- `src/core/CalcException.cpp`
- `src/core/Evaluator.cpp`
- `src/storage/SettingsManager.cpp`
- `src/storage/JsonStorage.cpp`
- CMakeLists.txt

AI 工具主要用于辅助补全基础逻辑、异常处理和文件读写流程以及cmake文件编写，最终代码已结合项目接口和课程要求进行人工检查与测试。
