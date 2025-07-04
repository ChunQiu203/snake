# 贪吃蛇游戏项目说明文档
## 一、项目概述
本项目基于 C++ 语言，借助 EasyX 图形库开发贪吃蛇游戏，实现键盘与鼠标两种操控模式，包含蛇身移动、食物生成、碰撞检测、游戏结束判定等功能，为玩家带来经典贪吃蛇游戏体验，也可作为图形化编程、游戏逻辑开发的学习案例 。

## 二、文件结构说明
核心代码集中在单个 `.cpp` 文件中（因未拆分多个源文件，主要逻辑均在包含上述代码的文件内 ），依赖 EasyX 图形库运行，涉及以下关键功能实现：
- **图形绘制**：通过 `graphics.h` 相关函数（如 `fillrectangle`、`fillcircle` 等 ）完成蛇身、背景、食物、边界等视觉元素绘制。
- **逻辑处理**：涵盖蛇的移动（自动移动、根据输入调整方向 ）、食物生成、碰撞检测（边界碰撞、自身碰撞 ）、长度增长等游戏逻辑。 
- **输入交互**：利用 `_getch` 处理键盘输入，`peekmessage`、`getmessage` 等处理鼠标输入，实现两种操控模式切换。 

## 三、关键功能模块
### （一）图形绘制模块
1. **背景与边界绘制**：通过循环绘制线条和矩形，构建游戏区域边界与背景网格，使用 `line`、`fillrectangle` 函数，设置对应颜色（如 `line_color`、`bk_color` ）区分不同元素。 
2. **蛇身绘制**：`DrawSnake` 函数遍历蛇身坐标集合（`vector<Pair_lo>` ），调用 `DrawUnitBlock` 绘制每个蛇块，蛇头与蛇身通过不同颜色（`0x5057A4` 与 `snake_color` ）区分。 
3. **食物绘制**：`Product_food` 函数生成随机坐标，借助 `fillcircle` 绘制圆形食物，设置颜色 `0x845EC2` 。 

### （二）游戏逻辑模块
1. **蛇的移动**：
    - **自动移动**：`autoMove` 函数负责蛇的自动行进，包含蛇身跟随（后段坐标复制前段 ）、蛇头方向更新，以及根据长度控制（`c_power` 与 `num` ）决定是否删除尾部块。 
    - **方向控制**：`moveSnake`（键盘 ）、`m_moveSnake`（鼠标 ）函数依据输入（键盘按键、鼠标坐标 ）调整蛇头移动方向（`deraction_x`、`deraction_y` ）。 
2. **碰撞检测**：
    - **边界碰撞**：`Can_move_boundary` 函数判断蛇头坐标是否超出游戏区域边界（`origin_x`、`end_x` 等定义的范围 ）。 
    - **自身碰撞**：`Can_move_body` 函数遍历蛇身坐标，检查是否存在重复坐标，判断是否发生自身碰撞。 
3. **食物与成长**：
    - **食物生成**：`Product_food` 利用随机数引擎（`mt19937` ）生成随机坐标，添加食物位置到 `food_lo` 集合并绘制。 
    - **蛇身增长**：`lengthen` 函数检测蛇身与食物位置重叠，删除食物并统计数量，达到一定数量（`num / 10` ）时在蛇头前插入新块，实现长度增长。 

### （三）交互控制模块
1. **开始界面**：`main` 函数中绘制标题与两个模式选择按钮（键盘、鼠标 ），通过 `MouseHit`、`GetMouseMsg` 检测鼠标点击，确定游戏模式（`mode` ）。 
2. **键盘操控**：`key_move` 函数通过 `_kbhit`、`_getch` 监听按键，`q` 键触发游戏结束，其他方向键（`w`、`s`、`a`、`d` ）调整蛇移动方向，循环处理移动、碰撞、食物等逻辑。 
3. **鼠标操控**：`mouse_move` 函数借助 `peekmessage`、`getmessage` 获取鼠标坐标，调用 `m_moveSnake` 依据坐标差调整蛇移动方向，同样循环处理游戏核心逻辑。 

## 四、环境依赖与运行
### （一）环境依赖
需安装 **EasyX 图形库**，该库为 Windows 平台下简易的 C++ 图形编程库，可在其[官方网站](https://easyx.cn/)下载对应版本（适配编译器，如 Visual Studio、Dev - C++ 等 ）并安装配置 。

### （二）运行步骤
1. 确保已正确配置 EasyX 图形库到开发环境（如 Visual Studio 需添加库路径、包含头文件等 ）。 
2. 将项目代码（单个 `.cpp` 文件 ）导入开发环境，编译运行。编译时需链接 EasyX 相关库文件，不同编译器配置方式参考 EasyX 官方文档 。 
3. 程序启动后，在开始界面点击“键盘模式”或“鼠标模式”，进入游戏。按界面提示（键盘模式下 `w`/`s`/`a`/`d` 控制方向、`q` 结束；鼠标模式下鼠标移动控制蛇方向 ）进行游戏，蛇撞边界或自身则游戏结束。 

## 五、后续拓展方向
1. **功能优化**：
    - 完善游戏结束流程，如添加重新开始、返回主界面选项。 
    - 优化食物生成逻辑，避免食物出现在蛇身内；调整蛇移动速度控制（如动态变速 ），提升游戏体验。 
    - 丰富界面元素，如添加分数显示（基于蛇长度或食物获取数量 ）、游戏音效（吃食物、碰撞等音效 ）。 
2. **模式扩展**：
    - 增加双人对战模式，支持键盘分别控制两条蛇，或结合网络实现远程对战。 
    - 开发 AI 对战模式，利用算法（如简单寻路、强化学习 ）让 AI 控制蛇自动游戏，与玩家对抗。 
3. **跨平台适配**：因 EasyX 图形库依赖 Windows 环境，可尝试迁移到其他图形库（如 SFML、SDL ），实现 Linux、Mac 等平台运行，扩大使用范围 。 
