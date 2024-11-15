#include <graphics.h> // 使用EasyX图形库
#include <windows.h>
#include <mmsystem.h> // 用于播放声音
#include <string>
#include <vector>

#pragma comment(lib, "winmm.lib") // 链接 winmm 库

// 窗口尺寸
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;

// 定义页面类型
enum MenuPage {
    MENU1, MENU2, LEVEL_SELECT, SETTINGS, DIFFICULTY,
    HOW_TO_PLAY, LEADERBOARD, SHOP, ABOUT_TEAM,
    CROSSING_STORY, LEVEL1_STORY, LEVEL1_MAP,
    LEVEL2_STORY, LEVEL2_MAP, LEVEL3_STORY, LEVEL3_MAP,
    VICTORY_SCREEN // 添加 VICTORY_SCREEN
};

// 定义地面块的结构体
struct GroundBlock {
    int left, top, right, bottom; // 地面块的四个边界坐标
};

// 定义关卡1的地面块（示例）
std::vector<GroundBlock> level1GroundBlocks = {
    {50, 740, 367, 740},
    {368, 660, 486, 660},
    {488, 740, 608, 740},
    {610, 619, 728, 619},
    {729, 740, 929, 740},
    {930, 660, 1088, 660},
    {1089, 621, 1249, 621},
    {930, 540, 1047, 540},
    {1089, 462, 1249, 462},
    {1010, 380, 1048, 380},
    {130, 340, 1009, 340},
    {229, 120, 387, 120},
    // 可以继续添加其他地面块
};

// 定义关卡2的地面块（示例）
std::vector<GroundBlock> level2GroundBlocks = {
    {50, 740, 328, 740},
    {368, 660, 486, 660},
    // 可以继续添加其他地面块
};

// 定义关卡3的地面块（示例）
std::vector<GroundBlock> level3GroundBlocks = {
    {50, 740, 328, 740},
    {368, 660, 486, 660},
    // 可以继续添加其他地面块
};

// 定义墙壁块的结构体
struct WallBlock {
    int left, top, right, bottom; // 墙壁的左右边界和上下边界
};

// 定义关卡1的墙壁块（示例）
std::vector<WallBlock> level1WallBlocks = {
    {50, 419, 50, 740},
    {369, 660, 369, 740},
    {486, 660, 486, 740},
    {610, 620, 610, 740},
    {729, 620, 729, 740},
    {930, 661, 930, 740},
    {1090, 625, 1090, 660},
    {930, 540, 930, 580},
    {1050, 540, 1050, 580},
    {1090, 463, 1090, 499},
    {1250, 21, 1250, 779},
    {1050, 381, 1050, 419},
    {1009, 340, 1009, 381},
    {130, 20, 130, 340},
    {230, 120, 230, 277},
    {270, 160, 270, 280},
    {388, 21, 388, 120},
    {468, 21, 468, 159},
    // 可以继续添加其他墙壁块
};

// 定义关卡2的墙壁块（示例）
std::vector<WallBlock> level2WallBlocks = {
    {400, 420, 580, 740},
    {650, 670, 620, 740},
    // 可以继续添加其他墙壁块
};

// 定义关卡3的墙壁块（示例）
std::vector<WallBlock> level3WallBlocks = {
    {400, 420, 580, 740},
    {650, 670, 620, 740},
    // 可以继续添加其他墙壁块
};

// 定义天花板块的结构体
struct CeilingBlock {
    int left, top, right, bottom; // 天花板的左右边界和上下边界
};

// 定义关卡1的天花板块（示例）
std::vector<CeilingBlock> level1CeilingBlocks = {
    {931, 580, 1050, 580},
    {1091, 498, 1249, 498},
    {51, 419, 1048, 419},
    {229, 278, 269, 278},
    {269, 160, 467, 160},
    {51, 20, 1249, 20},
    // 可以继续添加其他天花板块
};


// 定义关卡2的天花板块（示例）
std::vector<CeilingBlock> level2CeilingBlocks = {
    {300, 500, 100, 120},
    {600, 700, 200, 220},
    // 可以继续添加其他天花板块
};

// 定义关卡3的天花板块（示例）
std::vector<CeilingBlock> level3CeilingBlocks = {
    {300, 500, 100, 120},
    {600, 700, 200, 220},
    // 可以继续添加其他天花板块
};


// 定义陷阱的结构体
struct TrapBlock {
    int left, top, right, bottom; // 天花板的左右边界和上下边界
};

// 定义关卡1的地刺（示例）
std::vector<TrapBlock> level1TrapBlocks = {
    {486,700,526,740},
    {526,700,566,740},
    {566,700,606,740},
    {730,700,770,740},
    
};

// 定义关卡2的地刺（示例）
std::vector<TrapBlock> level2TrapBlocks = {
    
};

// 定义关卡3的地刺（示例）
std::vector<TrapBlock> level3TrapBlocks = {
    
};

// 定义通关方块的结构体
struct VictoryDoor {
    int left, top, right, bottom; // 通关方块的左右边界和上下边界
};

VictoryDoor level1VictoryDoor = { 310, 22, 385, 121 };
VictoryDoor level2VictoryDoor = { 310, 121, 385, 22 };
VictoryDoor level3VictoryDoor = { 310, 121, 385, 22 };

class Player {
private:
    IMAGE rightImage; // 玩家右移图片
    IMAGE leftImage; // 玩家左移图片
    int HP=100;//玩家生命值
    int x, y; // 玩家位置坐标A
    bool facingRight; // 玩家方向（true为右，false为左）
    bool isJumping = false; // 是否在跳跃中
    bool doubleJumpAvailable = true; // 是否可以进行二段跳
    int vy = 0; // 垂直速度
    const int jumpPower = -15; // 跳跃的初始速度
    const int gravity = 1; // 重力加速度
    int jumpCooldown = 0; // 跳跃冷却计时器
    int trapdamage = 10; //陷阱的伤害

public:
    // 构造函数，初始化玩家位置和方向
    Player(int startX, int startY) : x(startX), y(startY), facingRight(true) {}

    // 加载玩家图片资源
    void loadResources() {
        loadimage(&rightImage, L"图片资源/右移.png"); // 加载“右移”图片
        loadimage(&leftImage, L"图片资源/左移.png"); // 加载“左移”图片
    }

    // 绘制玩家
    void draw() {
        if (facingRight) {
            putimage(x, y, &rightImage); // 绘制右移图片
        }
        else {
            putimage(x, y, &leftImage); // 绘制左移图片
        }
        if (HP >= 0)
        {
            setfillcolor(RED);
            fillrectangle(850, 40, 850 + 2 * HP, 80);
        }
    }

    //重置位置的函数
    void resetPosition() {
        HP = 100;
        x = 80; // 默认的 x 坐标
        y = 700 - 51; // 默认的 y 坐标
        isJumping = false; // 重置跳跃状态
        doubleJumpAvailable = true; // 重置二段跳
        vy = 0; // 重置垂直速度
    }

    // 检查玩家是否触碰到通关门
    bool checkVictory(const VictoryDoor& door) {
        return x + rightImage.getwidth() > door.left &&
            x < door.right &&
            y + rightImage.getheight() > door.top &&
            y < door.bottom;
    }

    // 更新玩家位置（加入墙壁和天花板检测）
    void update(const std::vector<GroundBlock>& groundBlocks, const std::vector<WallBlock>& wallBlocks, const std::vector<CeilingBlock>& ceilingBlocks, const std::vector<TrapBlock>& trapBlocks) {
        int originalX = x; // 记录更新前的X坐标

        // 左右移动
        if (GetAsyncKeyState('A') & 0x8000) {
            x -= 5; // 左移
            facingRight = false; // 改变方向为左
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            x += 5; // 右移
            facingRight = true; // 改变方向为右
        }

        // 检查墙壁碰撞
        for (const auto& wall : wallBlocks) {
            if (x + rightImage.getwidth() > wall.left && x < wall.right &&
                y + rightImage.getheight() > wall.top && y < wall.bottom) {
                // 如果发生碰撞，恢复到之前的位置
                x = originalX;
                doubleJumpAvailable = true; // 碰到墙壁时重置二段跳
                break;
            }
        }

        // 检查天花板碰撞，仅在玩家接触到天花板块底部区域时
        for (const auto& ceiling : ceilingBlocks) {
            // 允许一些微小进入，避免直接阻挡上升
            int ceilingCollisionBuffer = 5; // 可以调整的缓冲高度
            if (vy < 0 && x + rightImage.getwidth() > ceiling.left && x < ceiling.right &&
                y < ceiling.bottom && y + rightImage.getheight() >= ceiling.bottom - ceilingCollisionBuffer) {
                // 仅在靠近天花板底部一定范围时触发
                y = ceiling.bottom; // 将玩家停在天花板下方
                vy = 0; // 停止向上移动
                break;
            }
        }

        // 检查地刺碰撞
        static int timecount = 0;//陷阱造成伤害的CD
        bool iscontactTrap = false;//记录是否与陷阱接触
        for (const auto& trap : trapBlocks) {
            if (x + rightImage.getwidth() > trap.left && x < trap.right &&
                y + rightImage.getheight() > trap.top && y < trap.bottom) {
                //如果触碰到陷阱，进行扣血
                if (timecount == 0)//如果CD为零则扣血并重置CD
                {
                    HP -= trapdamage;
                    timecount = 60;
                }
                else
                    timecount--;
                iscontactTrap = true;
                break;
            }
        }
        //如果没有和陷阱接触，那么陷阱造成伤害的CD归零
        if (!iscontactTrap)
            timecount = 0;

        // 跳跃和二段跳
        if (GetAsyncKeyState('W') & 0x8000) {
            jump();
        }

        // 应用重力和跳跃
        applyGravity(groundBlocks);

        // 处理跳跃冷却
        if (jumpCooldown > 0) {
            jumpCooldown--; // 冷却时间递减
        }
    }

private:
    // 处理跳跃
    void jump() {
        if (!isJumping) { // 初次跳跃
            isJumping = true;
            vy = jumpPower; // 设置跳跃力
            doubleJumpAvailable = true; // 启用二段跳
            jumpCooldown = 20; // 设置跳跃冷却时间（比如20帧）
        }
        else if (doubleJumpAvailable && jumpCooldown == 0) { // 二段跳，且没有冷却
            vy = jumpPower; // 设置跳跃力
            doubleJumpAvailable = false; // 禁用二段跳
        }
    }

    // 判断玩家是否接触地面
    bool isOnGround(const std::vector<GroundBlock>& groundBlocks) {
        for (const auto& block : groundBlocks) {
            // 检查玩家底部是否位于地面块的顶部
            if (x + rightImage.getwidth() > block.left && x < block.right &&
                y + rightImage.getheight() == block.top) {
                return true;
            }
        }
        return false;
    }

    // 应用重力
    void applyGravity(const std::vector<GroundBlock>& groundBlocks) {
        // 让玩家掉落
        y += vy;
        vy += gravity;

        // 检查是否与地面碰撞
        for (const auto& block : groundBlocks) {
            if (x + rightImage.getwidth() > block.left && x < block.right &&
                y + rightImage.getheight() >= block.top && y < block.bottom) {
                y = block.top - rightImage.getheight(); // 将玩家停在地面上
                vy = 0; // 重置垂直速度
                isJumping = false; // 重置跳跃状态
                doubleJumpAvailable = true; // 恢复二段跳
                break;
            }
        }
    }
};



// 按钮类，管理按钮的区域和点击检测
class Button {
private:
    RECT area; // 按钮区域，用矩形表示

public:
    // 构造函数，初始化按钮的位置和尺寸
    Button(int left, int top, int right, int bottom) {
        area = { left, top, right, bottom };
    }

    // 判断按钮是否被点击
    bool isClicked(int x, int y) const {
        return PtInRect(&area, POINT{ x, y });
    }
};

// 页面类，管理页面的加载、绘制和点击事件
class Page {
protected:
    IMAGE backgroundImage; // 背景图像
    std::vector<Button> buttons; // 存储页面上的按钮

public:
    // 加载页面资源
    virtual void loadResources(const std::wstring& imagePath) {
        loadimage(&backgroundImage, imagePath.c_str());
    }

    // 绘制页面
    virtual void draw() {
        putimage((WINDOW_WIDTH - backgroundImage.getwidth()) / 2, (WINDOW_HEIGHT - backgroundImage.getheight()) / 2, &backgroundImage);
    }

    // 处理点击事件，纯虚函数，需由子类实现
    virtual void handleClick(int x, int y, MenuPage& currentPage) = 0;
};

// 主菜单页面类
class MainMenuPage : public Page {
public:
    MainMenuPage() {
        // 初始化按钮区域
        buttons.push_back(Button(908, 565, 1127, 610)); // 翻页按钮
        buttons.push_back(Button(564, 274, 733, 318));  // 关卡选择按钮
        buttons.push_back(Button(564, 358, 733, 402));  // 设置按钮
        buttons.push_back(Button(564, 455, 733, 498));  // 难度选择按钮
        buttons.push_back(Button(564, 543, 733, 587));  // 退出游戏按钮
    }

    // 处理点击事件
    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // 切换到主菜单2
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = LEVEL_SELECT; // 切换到关卡选择界面
        }
        else if (buttons[2].isClicked(x, y)) {
            currentPage = SETTINGS; // 切换到设置界面
        }
        else if (buttons[3].isClicked(x, y)) {
            currentPage = DIFFICULTY; // 切换到难度界面
        }
        else if (buttons[4].isClicked(x, y)) {
            closegraph(); // 关闭图形窗口，退出游戏
            exit(0);
        }
    }
};

// 其他页面类，继承Page基类
class Menu2Page : public Page {
public:
    Menu2Page() {
        buttons.push_back(Button(920, 562, 1024, 624)); // 返回按钮
        buttons.push_back(Button(552, 244, 748, 301));  // 玩法按钮
        buttons.push_back(Button(552, 340, 748, 395));  // 排行榜按钮
        buttons.push_back(Button(552, 437, 748, 492));  // 商店按钮
        buttons.push_back(Button(552, 530, 748, 590));  // 开发团队按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // 返回到主菜单1
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = HOW_TO_PLAY; // 进入玩法界面
        }
        else if (buttons[2].isClicked(x, y)) {
            currentPage = LEADERBOARD; // 进入排行榜界面
        }
        else if (buttons[3].isClicked(x, y)) {
            currentPage = SHOP; // 进入商店界面
        }
        else if (buttons[4].isClicked(x, y)) {
            currentPage = ABOUT_TEAM; // 进入关于团队界面
        }
    }
};

// 关卡选择页面类
class LevelSelectPage : public Page {
public:
    LevelSelectPage() {
        buttons.push_back(Button(575, 146, 730, 187)); // 返回按钮
        buttons.push_back(Button(919, 405, 1073, 448)); // “命运的交织”按钮
        buttons.push_back(Button(919, 451, 1073, 495)); // “真理的试炼”按钮
        buttons.push_back(Button(919, 497, 1073, 541)); // “智慧的挑战”按钮（关卡3）
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // 返回到主菜单1
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = CROSSING_STORY; // 进入“穿越剧情”页面
        }
        else if (buttons[2].isClicked(x, y)) {
            currentPage = LEVEL2_STORY; // 进入关卡2剧情页面
        }
        else if (buttons[3].isClicked(x, y)) {
            currentPage = LEVEL3_STORY; // 进入关卡3剧情页面
        }
    }
};

// 设置选择页面类
class SettingsPage : public Page {
public:
    SettingsPage() {
        buttons.push_back(Button(534, 199, 711, 260)); // 返回按钮
        buttons.push_back(Button(813, 309, 1008, 378)); // 音乐开关按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // 返回到主菜单1
        }
    }
};

// 穿越剧情页面类
class CrossingStoryPage : public Page {
public:
    CrossingStoryPage() {
        buttons.push_back(Button(926, 593, 1038, 653)); // 下一页按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL1_STORY; // 进入“关卡1剧情”页面
        }
    }
};

// 关卡1剧情页面类
class Level1StoryPage : public Page {
public:
    Level1StoryPage() {
        buttons.push_back(Button(904, 582, 1018, 643)); // 下一页按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL1_MAP; // 进入“关卡1地图”页面
        }
    }
};

// 关卡1地图页面类（无返回按钮）
class Level1MapPage : public Page {
public:
    Level1MapPage() {
        // 此页面无返回按钮，关卡1地图的唯一入口是从关卡1剧情
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        // 此页面无点击事件响应，保持在关卡1地图
    }
};

// 关卡2剧情页面类
class Level2StoryPage : public Page {
public:
    Level2StoryPage() {
        buttons.push_back(Button(904, 582, 1018, 643)); // 下一页按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL2_MAP; // 进入“关卡2地图”页面
        }
    }
};

// 关卡3剧情页面类
class Level3StoryPage : public Page {
public:
    Level3StoryPage() {
        buttons.push_back(Button(904, 582, 1018, 643)); // 下一页按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL3_MAP; // 进入“关卡3地图”页面
        }
    }
};

// 关卡2地图页面类
class Level2MapPage : public Page {
public:
    Level2MapPage() {
        // 此页面无返回按钮，关卡2地图的唯一入口是从关卡2剧情
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        // 无点击事件响应，保持在关卡2地图
    }
};

// 关卡3地图页面类
class Level3MapPage : public Page {
public:
    Level3MapPage() {
        // 此页面无返回按钮，关卡3地图的唯一入口是从关卡3剧情
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        // 无点击事件响应，保持在关卡3地图
    }
};

// 通关界面类
class VictoryPage : public Page {
private:
    MenuPage lastMapPage;
public:
    void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }
    VictoryPage() {
        // 初始化按钮区域
        buttons.push_back(Button(245, 285, 414, 345)); // 主菜单按钮
        buttons.push_back(Button(245, 378, 414, 436)); // 章节选择按钮
        buttons.push_back(Button(245, 460, 414, 528)); // 下一关按钮
    }

    // 加载通关界面的资源
    void loadResources(const std::wstring& imagePath) override {
        Page::loadResources(imagePath); // 调用基类的加载方法
    }

    // 处理点击事件
    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // 返回主菜单


        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = LEVEL_SELECT; // 返回到章节选择
        }
        else if (buttons[2].isClicked(x, y)) {
            // 进入下一关逻辑
            if (lastMapPage == LEVEL1_MAP) currentPage = LEVEL2_STORY;
            else if (lastMapPage == LEVEL2_MAP) currentPage = LEVEL3_STORY;
            else if (lastMapPage == LEVEL3_MAP) currentPage = LEVEL3_STORY;
        }
    }
};


// 难度选择页面
class DifficultyPage : public Page {
public:
    DifficultyPage() {
        buttons.push_back(Button(529, 202, 711, 260)); // 返回按钮
        buttons.push_back(Button(545, 290, 750, 350));//萌新按钮
        buttons.push_back(Button(545, 381, 750, 445));//入门按钮
        buttons.push_back(Button(545, 473, 750, 535));//熟练按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // 返回到主菜单1
        }
        if (buttons[1].isClicked(x, y))
        {
            
        }
        if (buttons[2].isClicked(x, y))
        {

        }
        if (buttons[3].isClicked(x, y))
        {

        }
    }
};

// 玩法界面
class HowToPlayPage : public Page {
public:
    HowToPlayPage() {
        buttons.push_back(Button(515, 180, 790, 240)); // 返回按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // 返回主菜单2
        }
    }
};

// 排行榜界面
class LeaderboardPage : public Page {
public:
    LeaderboardPage() {
        buttons.push_back(Button(515, 180, 790, 240)); // 返回按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // 返回主菜单2
        }
    }
};

// 商店界面
class ShopPage : public Page {
public:
    ShopPage() {
        buttons.push_back(Button(246, 189, 468, 250)); // 返回按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // 返回主菜单2
        }
    }
};

// 关于团队界面
class AboutTeamPage : public Page {
public:
    AboutTeamPage() {
        buttons.push_back(Button(733, 564, 1008, 624)); // 返回按钮
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // 返回主菜单2
        }
    }
};

// 游戏主类
class Game {
private:
    MenuPage currentPage; // 当前页面
    MainMenuPage mainMenu; // 主菜单页面
    Menu2Page menu2; // 主菜单2
    LevelSelectPage levelSelect; // 关卡选择页面
    SettingsPage settings; // 设置页面
    DifficultyPage difficulty; // 难度选择页面
    HowToPlayPage howToPlay; // 玩法界面
    LeaderboardPage leaderboard; // 排行榜界面
    ShopPage shop; // 商店界面
    AboutTeamPage aboutTeam; // 关于团队界面
    CrossingStoryPage crossingStory; // 穿越剧情页面
    Level1StoryPage level1Story; // 关卡1剧情页面
    Level1MapPage level1Map; // 关卡1地图页面
    Level2StoryPage level2Story; // 关卡2剧情页面
    Level2MapPage level2Map;     // 关卡2地图页面
    Level3StoryPage level3Story; // 关卡3剧情页面
    Level3MapPage level3Map;     // 关卡3地图页面
    Player player;  // 玩家对象
    IMAGE backgroundImage; // 添加背景图像变量，用于胜利界面
    VictoryPage victoryPage;

public:
    Game() : currentPage(MENU1), player(80, 700 - 51) {} // 初始化当前页面为主菜单

    // 加载所有页面资源
    void loadResources() {
        mainMenu.loadResources(L"图片资源/主菜单1.png");
        menu2.loadResources(L"图片资源/主菜单2.png");
        levelSelect.loadResources(L"图片资源/关卡选择界面.png");
        settings.loadResources(L"图片资源/设置界面.png");
        difficulty.loadResources(L"图片资源/难度界面.png");
        howToPlay.loadResources(L"图片资源/玩法界面.png");
        leaderboard.loadResources(L"图片资源/排行榜界面.png");
        shop.loadResources(L"图片资源/商店界面.png");
        aboutTeam.loadResources(L"图片资源/开发团队界面.png");
        crossingStory.loadResources(L"图片资源/穿越剧情.png");
        level1Story.loadResources(L"图片资源/关卡1剧情.png");
        level1Map.loadResources(L"图片资源/关卡1地图.jpg");
        level2Story.loadResources(L"图片资源/关卡2剧情.png");
        level2Map.loadResources(L"图片资源/关卡2地图.jpg");
        level3Story.loadResources(L"图片资源/关卡3剧情.png");
        level3Map.loadResources(L"图片资源/关卡3地图.jpg");
        player.loadResources(); // 加载玩家资源
        victoryPage.loadResources(L"图片资源/胜利界面1.png"); // 加载胜利界面图片

    }

    bool isLevelMusicPlaying = false; // 标志位，判断是否在播放地图音乐
    bool isMusicOn = true; // 全局变量，记录音乐开关状态，初始状态为开启

    // 播放背景音乐
    void playBackgroundMusic(const std::wstring& musicFile) {
        if (isMusicOn) { // 只有在音乐开关开启的情况下才播放音乐
            PlaySound(musicFile.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        else {
            PlaySound(NULL, NULL, 0); // 停止播放音乐
        }
    }

    // 根据页面播放不同的音乐
    void updateBackgroundMusic() {
        if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP) {
            if (!isLevelMusicPlaying) {
                // 进入地图界面且地图音乐未播放时，播放地图音乐
                playBackgroundMusic(L"音乐资源/传说之下.wav");
                isLevelMusicPlaying = true; // 标志位设为地图音乐正在播放
            }
        }
        else {
            if (isLevelMusicPlaying) {
                // 离开地图界面，切换回其他页面时播放默认音乐
                playBackgroundMusic(L"音乐资源/人间日.wav");
                isLevelMusicPlaying = false; // 标志位设为非地图音乐
            }
            // 如果在非地图界面，且已经播放人间日音乐，无需再次播放
        }
    }

    // 绘制当前页面
    void drawCurrentPage() {
        switch (currentPage) {
        case MENU1:
            mainMenu.draw();
            break;
        case MENU2:
            menu2.draw();
            break;
        case LEVEL_SELECT:
            levelSelect.draw();
            break;
        case SETTINGS:
            settings.draw();
            break;
        case DIFFICULTY:
            difficulty.draw();
            break;
        case HOW_TO_PLAY:
            howToPlay.draw();
            break;
        case LEADERBOARD:
            leaderboard.draw();
            break;
        case SHOP:
            shop.draw();
            break;
        case ABOUT_TEAM:
            aboutTeam.draw();
            break;
        case CROSSING_STORY:
            crossingStory.draw();
            break;
        case LEVEL1_STORY:
            level1Story.draw();
            break;
        case LEVEL1_MAP:
            level1Map.draw();
            player.draw(); // 在地图1绘制玩家
            break;
        case LEVEL2_STORY:
            level2Story.draw();
            break;
        case LEVEL2_MAP:
            level2Map.draw();
            player.draw(); // 在地图2绘制玩家
            break;
        case LEVEL3_STORY:
            level3Story.draw();
            break;
        case LEVEL3_MAP:
            level3Map.draw();
            player.draw(); // 在地图3绘制玩家
            break;
        case VICTORY_SCREEN: // 通关界面
            victoryPage.draw();
            break;
        }
    }

    // 处理鼠标点击事件
    void handleMouseClick(int x, int y) {
        MenuPage previousPage = currentPage; // 定义 previousPage 变量，存储当前页面

        switch (currentPage) {
        case MENU1:
            mainMenu.handleClick(x, y, currentPage);
            break;
        case MENU2:
            menu2.handleClick(x, y, currentPage);
            break;
        case LEVEL_SELECT:
            levelSelect.handleClick(x, y, currentPage);
            break;
        case SETTINGS:
            settings.handleClick(x, y, currentPage);
            break;
        case DIFFICULTY:
            difficulty.handleClick(x, y, currentPage);
            break;
        case HOW_TO_PLAY:
            howToPlay.handleClick(x, y, currentPage);
            break;
        case LEADERBOARD:
            leaderboard.handleClick(x, y, currentPage);
            break;
        case SHOP:
            shop.handleClick(x, y, currentPage);
            break;
        case ABOUT_TEAM:
            aboutTeam.handleClick(x, y, currentPage);
            break;
        case CROSSING_STORY:
            crossingStory.handleClick(x, y, currentPage);
            break;
        case LEVEL1_STORY:
            level1Story.handleClick(x, y, currentPage);
            break;
        case LEVEL1_MAP:
            level1Map.handleClick(x, y, currentPage);
            break;
        case LEVEL2_STORY:
            level2Story.handleClick(x, y, currentPage);
            break;
        case LEVEL2_MAP:
            level2Map.handleClick(x, y, currentPage);
            break;
        case LEVEL3_STORY:
            level3Story.handleClick(x, y, currentPage);
            break;
        case LEVEL3_MAP:
            level3Map.handleClick(x, y, currentPage);
            break;
        case VICTORY_SCREEN: // 胜利界面
            victoryPage.handleClick(x, y, currentPage);
            break;
        }
        if (currentPage != previousPage) {
            updateBackgroundMusic(); // 页面切换后更新背景音乐
        }
    }

    // 显示鼠标坐标
    void displayMouseCoordinates(int x, int y) {
        settextcolor(WHITE);
        std::wstring coords = L"X: " + std::to_wstring(x) + L", Y: " + std::to_wstring(y);
        outtextxy(10, 10, coords.c_str());
    }

    //游戏主循环
    void run() {
        initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口
        loadResources(); // 加载资源
        playBackgroundMusic(L"音乐资源/人间日.wav"); // 初始播放默认音乐

        std::vector<GroundBlock>* currentGroundBlocks = nullptr;
        std::vector<WallBlock>* currentWallBlocks = nullptr;
        std::vector<CeilingBlock>* currentCeilingBlocks = nullptr;
        std::vector<TrapBlock>* currentTrapBlocks = nullptr;
        VictoryDoor* currentVictoryDoor = nullptr; // 当前关卡的通关门

        while (true) {
            cleardevice(); // 清屏
            BeginBatchDraw();//双缓存
            drawCurrentPage(); // 绘制当前页面

            // 如果在胜利页面，跳过玩家位置更新，但保留鼠标事件处理
            if (currentPage == VICTORY_SCREEN) {
                victoryPage.draw(); // 绘制胜利界面
            }
            else {
                // 根据当前页面选择地图地面块、墙壁块、天花板块和通关门
                if (currentPage == LEVEL1_MAP) {
                    currentGroundBlocks = &level1GroundBlocks;
                    currentWallBlocks = &level1WallBlocks;
                    currentCeilingBlocks = &level1CeilingBlocks;
                    currentTrapBlocks = &level1TrapBlocks;
                    currentVictoryDoor = &level1VictoryDoor;
                }
                else if (currentPage == LEVEL2_MAP) {
                    currentGroundBlocks = &level2GroundBlocks;
                    currentWallBlocks = &level2WallBlocks;
                    currentCeilingBlocks = &level2CeilingBlocks;
                    currentTrapBlocks = &level2TrapBlocks;
                    currentVictoryDoor = &level2VictoryDoor;
                }
                else if (currentPage == LEVEL3_MAP) {
                    currentGroundBlocks = &level3GroundBlocks;
                    currentWallBlocks = &level3WallBlocks;
                    currentCeilingBlocks = &level3CeilingBlocks;
                    currentTrapBlocks = &level3TrapBlocks;
                    currentVictoryDoor = &level3VictoryDoor;
                }

                // 更新和绘制玩家
                if (currentGroundBlocks && currentWallBlocks && currentCeilingBlocks && currentTrapBlocks &&
                    (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)) {
                    player.update(*currentGroundBlocks, *currentWallBlocks, *currentCeilingBlocks, *currentTrapBlocks);
                    player.draw();

                    if (currentVictoryDoor && player.checkVictory(*currentVictoryDoor)) {
                        player.resetPosition(); // 通关时重置玩家位置
                        victoryPage.setLastMapPage(currentPage); // 设置当前地图页面
                        currentPage = VICTORY_SCREEN; // 切换到胜利界面
                        playBackgroundMusic(L"音乐资源/人间日.wav"); // 确保播放人间日音乐
                        currentVictoryDoor = nullptr; // 重置通关门对象
                        
                    }
                }
            }
            EndBatchDraw();

            // 检查是否有鼠标事件
            if (MouseHit()) {
                MOUSEMSG msg = GetMouseMsg();
                displayMouseCoordinates(msg.x, msg.y);

                if (msg.uMsg == WM_LBUTTONDOWN) {
                    handleMouseClick(msg.x, msg.y);
                }
            }

            Sleep(5); // 控制刷新频率
        }
        closegraph(); // 关闭图形窗口
        PlaySound(NULL, NULL, 0); // 停止播放音乐
    }
};

// 主函数
int main() {
    Game game;
    game.run();
    return 0;
}
