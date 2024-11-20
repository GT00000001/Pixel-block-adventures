#include <graphics.h> // ʹ��EasyXͼ�ο�
#include <windows.h>
#include <mmsystem.h> // ���ڲ�������
#include <string>
#include <vector>
#include <fstream> 
#include <sstream>
#include <iostream>
#pragma comment(lib, "winmm.lib") // ���� winmm ��

// ���ڳߴ�
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;

// ����ҳ������
enum MenuPage {
    MENU1, MENU2, LEVEL_SELECT, SETTINGS, DIFFICULTY,
    HOW_TO_PLAY, LEADERBOARD, SHOP, ABOUT_TEAM,
    CROSSING_STORY, LEVEL1_STORY, LEVEL1_MAP,
    LEVEL2_STORY, LEVEL2_MAP, LEVEL3_STORY, LEVEL3_MAP,
    VICTORY_SCREEN, // ��� VICTORY_SCREEN
    FAIL
};

// ��������Ľṹ��
struct GroundBlock {
    int left, top, right, bottom; // �������ĸ��߽�����
};

// ����ؿ�1�ĵ����
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
    // ���Լ���������������
};

// ����ؿ�2�ĵ���飨δ��ɣ�
std::vector<GroundBlock> level2GroundBlocks = {
    {50, 740, 328, 740},
    {368, 660, 486, 660},
    // ���Լ���������������
};

// ����ؿ�3�ĵ���飨δ��ɣ�
std::vector<GroundBlock> level3GroundBlocks = {
    {50, 740, 328, 740},
    {368, 660, 486, 660},
    // ���Լ���������������
};

// ����ǽ�ڿ�Ľṹ��
struct WallBlock {
    int left, top, right, bottom; // ǽ�ڵ����ұ߽�����±߽�
};

// ����ؿ�1��ǽ�ڿ�
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
};

// ����ؿ�2��ǽ�ڿ飨δ��ɣ�
std::vector<WallBlock> level2WallBlocks = {
    {400, 420, 580, 740},
    {650, 670, 620, 740},
    // ���Լ����������ǽ�ڿ�
};

// ����ؿ�3��ǽ�ڿ飨δ��ɣ�
std::vector<WallBlock> level3WallBlocks = {
    {400, 420, 580, 740},
    {650, 670, 620, 740},
    // ���Լ����������ǽ�ڿ�
};

// �����컨���Ľṹ��
struct CeilingBlock {
    int left, top, right, bottom; // �컨������ұ߽�����±߽�
};

// ����ؿ�1���컨���
std::vector<CeilingBlock> level1CeilingBlocks = {
    {931, 580, 1050, 580},
    {1091, 498, 1249, 498},
    {51, 419, 1048, 419},
    {229, 278, 269, 278},
    {269, 160, 467, 160},
    {51, 20, 1249, 20},
};


// ����ؿ�2���컨��飨δ��ɣ�
std::vector<CeilingBlock> level2CeilingBlocks = {
    {300, 500, 100, 120},
    {600, 700, 200, 220},
    // ���Լ�����������컨���
};

// ����ؿ�3���컨��飨δ��ɣ�
std::vector<CeilingBlock> level3CeilingBlocks = {
    {300, 500, 100, 120},
    {600, 700, 200, 220},
    // ���Լ�����������컨���
};


// ��������Ľṹ��
struct TrapBlock {
    int left, top, right, bottom; // �컨������ұ߽�����±߽�
};

// ����ؿ�1�ĵش�
std::vector<TrapBlock> level1TrapBlocks = {
    {486,700,526,740},
    {526,700,566,740},
    {566,700,606,740},
    {730,700,770,740},
};

// ����ؿ�2�ĵش̣�δ��ɣ�
std::vector<TrapBlock> level2TrapBlocks = {

};

// ����ؿ�3�ĵش̣�δ��ɣ�
std::vector<TrapBlock> level3TrapBlocks = {

};

// ����ͨ�ط���Ľṹ��
struct VictoryDoor {
    int left, top, right, bottom; // ͨ�ط�������ұ߽�����±߽�
};

VictoryDoor level1VictoryDoor = { 310, 22, 385, 121 };
VictoryDoor level2VictoryDoor = { 310, 121, 385, 22 };
VictoryDoor level3VictoryDoor = { 310, 121, 385, 22 };

class Player {
private:
    IMAGE rightImage; // �������ͼƬ
    IMAGE leftImage; // �������ͼƬ
    int HP = 100;//�������ֵ
    int x, y; // ���λ������A
    bool facingRight; // ��ҷ���trueΪ�ң�falseΪ��
    bool isJumping = false; // �Ƿ�����Ծ��
    bool doubleJumpAvailable = true; // �Ƿ���Խ��ж�����
    int vy = 0; // ��ֱ�ٶ�
    const int jumpPower = -15; // ��Ծ�ĳ�ʼ�ٶ�
    const int gravity = 1; // �������ٶ�
    int jumpCooldown = 0; // ��Ծ��ȴ��ʱ��
    int trapdamage = 10; //������˺�
    std::vector<int> clearancetimelevel{ 0,0,0 };

public:
    // ���캯������ʼ�����λ�úͷ���
    Player(int startX, int startY) : x(startX), y(startY), facingRight(true) {}


    // �����������ֵ
    void setHP(int hp) {
        HP = hp;
    }

    // ��ȡ�������ֵ��������ʾ��
    int getHP() const {
        return HP;
    }

    // �������ͼƬ��Դ
    void loadResources() {
        loadimage(&rightImage, L"ͼƬ��Դ/����.png"); // ���ء����ơ�ͼƬ
        loadimage(&leftImage, L"ͼƬ��Դ/����.png"); // ���ء����ơ�ͼƬ
    }

    // �������
    void draw() {
        if (facingRight) {
            putimage(x, y, &rightImage); // ��������ͼƬ
        }
        else {
            putimage(x, y, &leftImage); // ��������ͼƬ
        }
        // ���ƻ�ɫ�� HP ��������Ļ���Ͻ�
        if (HP >= 0) {
            settextcolor(YELLOW); // ����������ɫΪ��ɫ
            setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
            settextstyle(50, 0, L"΢���ź�"); // ��������Ϊ΢���źڣ���СΪ50

            wchar_t hpText[20];
            swprintf(hpText, 20, L"HP: %d", HP); // ת�� HP ��ֵΪ�ı�
            outtextxy(850, 40, hpText); // ����Ļ���Ͻ���ʾ HP ����
        }
    }

    //����λ�õĺ���
    void resetPosition() {
        HP = 100;
        x = 80; // Ĭ�ϵ� x ����
        y = 700 - 51; // Ĭ�ϵ� y ����
        isJumping = false; // ������Ծ״̬
        doubleJumpAvailable = true; // ���ö�����
        vy = 0; // ���ô�ֱ�ٶ�
    }

    // �������Ƿ�����ͨ����
    bool checkVictory(const VictoryDoor& door) {
        return x + rightImage.getwidth() > door.left &&
            x < door.right &&
            y + rightImage.getheight() > door.top &&
            y < door.bottom;
    }

    // �������λ�ã�����ǽ�ں��컨���⣩
    void update(const std::vector<GroundBlock>& groundBlocks, const std::vector<WallBlock>& wallBlocks, const std::vector<CeilingBlock>& ceilingBlocks, const std::vector<TrapBlock>& trapBlocks) {
        int originalX = x; // ��¼����ǰ��X����

        // �����ƶ�
        if (GetAsyncKeyState('A') & 0x8000) {
            x -= 5; // ����
            facingRight = false; // �ı䷽��Ϊ��
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            x += 5; // ����
            facingRight = true; // �ı䷽��Ϊ��
        }

        // ���ǽ����ײ
        for (const auto& wall : wallBlocks) {
            if (x + rightImage.getwidth() > wall.left && x < wall.right &&
                y + rightImage.getheight() > wall.top && y < wall.bottom) {
                // ���������ײ���ָ���֮ǰ��λ��
                x = originalX;
                doubleJumpAvailable = true; // ����ǽ��ʱ���ö�����
                break;
            }
        }

        // ����컨����ײ��������ҽӴ����컨���ײ�����ʱ
        for (const auto& ceiling : ceilingBlocks) {
            // ����һЩ΢С���룬����ֱ���赲����
            int ceilingCollisionBuffer = 5; // ���Ե����Ļ���߶�
            if (vy < 0 && x + rightImage.getwidth() > ceiling.left && x < ceiling.right &&
                y < ceiling.bottom && y + rightImage.getheight() >= ceiling.bottom - ceilingCollisionBuffer) {
                // ���ڿ����컨��ײ�һ����Χʱ����
                y = ceiling.bottom; // �����ͣ���컨���·�
                vy = 0; // ֹͣ�����ƶ�
                break;
            }
        }

        // ���ش���ײ
        static int timecount = 0;//��������˺���CD
        bool iscontactTrap = false;//��¼�Ƿ�������Ӵ�
        for (const auto& trap : trapBlocks) {
            if (x + rightImage.getwidth() > trap.left && x < trap.right &&
                y + rightImage.getheight() > trap.top && y < trap.bottom) {
                //������������壬���п�Ѫ
                if (timecount == 0)//���CDΪ�����Ѫ������CD
                {
                    HP -= trapdamage;
                    timecount = 10;
                }
                else
                    timecount--;
                iscontactTrap = true;
                break;
            }
        }
        //���û�к�����Ӵ�����ô��������˺���CD����
        if (!iscontactTrap)
            timecount = 0;

        // ��Ծ�Ͷ�����
        if (GetAsyncKeyState('W') & 0x8000) {
            jump();
        }

        // Ӧ����������Ծ
        applyGravity(groundBlocks);

        // ������Ծ��ȴ
        if (jumpCooldown > 0) {
            jumpCooldown--; // ��ȴʱ��ݼ�
        }
    }

private:
    // ������Ծ
    void jump() {
        if (!isJumping) { // ������Ծ
            isJumping = true;
            vy = jumpPower; // ������Ծ��
            doubleJumpAvailable = true; // ���ö�����
            jumpCooldown = 20; // ������Ծ��ȴʱ�䣨����20֡��
        }
        else if (doubleJumpAvailable && jumpCooldown == 0) { // ����������û����ȴ
            vy = jumpPower; // ������Ծ��
            doubleJumpAvailable = false; // ���ö�����
        }
    }

    // �ж�����Ƿ�Ӵ�����
    bool isOnGround(const std::vector<GroundBlock>& groundBlocks) {
        const int groundCollisionBuffer = 5; // ����߶�
        for (const auto& block : groundBlocks) {
            // �����ҵײ��Ƿ�λ�ڵ����Ķ���������һЩ����
            if (x + rightImage.getwidth() > block.left && x < block.right &&
                y + rightImage.getheight() >= block.top - groundCollisionBuffer &&
                y + rightImage.getheight() <= block.top + groundCollisionBuffer) {
                return true;
            }
        }
        return false;
    }

    // Ӧ������
    void applyGravity(const std::vector<GroundBlock>& groundBlocks) {
        const int groundCollisionBuffer = 5; // ����߶�

        // ����ҵ���
        y += vy;
        vy += gravity;

        // ����Ƿ��������ײ������һЩ����
        for (const auto& block : groundBlocks) {
            if (x + rightImage.getwidth() > block.left && x < block.right &&
                y + rightImage.getheight() >= block.top - groundCollisionBuffer &&
                y < block.bottom) {
                y = block.top - rightImage.getheight(); // �����ͣ�ڵ�����
                vy = 0; // ���ô�ֱ�ٶ�
                isJumping = false; // ������Ծ״̬
                doubleJumpAvailable = true; // �ָ�������
                break;
            }
        }
    }
};



// ��ť�࣬����ť������͵�����
class Button {
private:
    RECT area; // ��ť�����þ��α�ʾ

public:
    // ���캯������ʼ����ť��λ�úͳߴ�
    Button(int left, int top, int right, int bottom) {
        area = { left, top, right, bottom };
    }

    // �жϰ�ť�Ƿ񱻵��
    bool isClicked(int x, int y) const {
        return PtInRect(&area, POINT{ x, y });
    }
};

// ҳ���࣬����ҳ��ļ��ء����ƺ͵���¼�
class Page {
protected:
    IMAGE backgroundImage; // ����ͼ��
    std::vector<Button> buttons; // �洢ҳ���ϵİ�ť

public:
    // ����ҳ����Դ
    virtual void loadResources(const std::wstring& imagePath) {
        loadimage(&backgroundImage, imagePath.c_str());
    }

    // ����ҳ��
    virtual void draw() {
        putimage((WINDOW_WIDTH - backgroundImage.getwidth()) / 2, (WINDOW_HEIGHT - backgroundImage.getheight()) / 2, &backgroundImage);
    }

    // �������¼������麯������������ʵ��
    virtual void handleClick(int x, int y, MenuPage& currentPage) = 0;
};

// ���˵�ҳ����
class MainMenuPage : public Page {
public:
    MainMenuPage() {
        // ��ʼ����ť����
        buttons.push_back(Button(908, 565, 1127, 610)); // ��ҳ��ť
        buttons.push_back(Button(564, 274, 733, 318));  // �ؿ�ѡ��ť
        buttons.push_back(Button(564, 358, 733, 402));  // ���ð�ť
        buttons.push_back(Button(564, 455, 733, 498));  // �Ѷ�ѡ��ť
        buttons.push_back(Button(564, 543, 733, 587));  // �˳���Ϸ��ť
    }

    // �������¼�
    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // �л������˵�2
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = LEVEL_SELECT; // �л����ؿ�ѡ�����
        }
        else if (buttons[2].isClicked(x, y)) {
            currentPage = SETTINGS; // �л������ý���
        }
        else if (buttons[3].isClicked(x, y)) {
            currentPage = DIFFICULTY; // �л����ѶȽ���
        }
        else if (buttons[4].isClicked(x, y)) {
            closegraph(); // �ر�ͼ�δ��ڣ��˳���Ϸ
            exit(0);
        }
    }
};

// ����ҳ���࣬�̳�Page����
class Menu2Page : public Page {
public:
    Menu2Page() {
        buttons.push_back(Button(920, 562, 1024, 624)); // ���ذ�ť
        buttons.push_back(Button(552, 244, 748, 301));  // �淨��ť
        buttons.push_back(Button(552, 340, 748, 395));  // ���а�ť
        buttons.push_back(Button(552, 437, 748, 492));  // �̵갴ť
        buttons.push_back(Button(552, 530, 748, 590));  // �����ŶӰ�ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // ���ص����˵�1
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = HOW_TO_PLAY; // �����淨����
        }
        else if (buttons[2].isClicked(x, y)) {
            currentPage = LEADERBOARD; // �������а����
        }
        else if (buttons[3].isClicked(x, y)) {
            currentPage = SHOP; // �����̵����
        }
        else if (buttons[4].isClicked(x, y)) {
            currentPage = ABOUT_TEAM; // ��������Ŷӽ���
        }
    }
};

// �ؿ�ѡ��ҳ����
class LevelSelectPage : public Page {
public:
    LevelSelectPage() {
        buttons.push_back(Button(575, 146, 730, 187)); // ���ذ�ť
        buttons.push_back(Button(919, 405, 1073, 448)); // �����˵Ľ�֯����ť
        buttons.push_back(Button(919, 451, 1073, 495)); // ���������������ť
        buttons.push_back(Button(919, 497, 1073, 541)); // ���ǻ۵���ս����ť���ؿ�3��
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // ���ص����˵�1
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = CROSSING_STORY; // ���롰��Խ���顱ҳ��
        }
        else if (buttons[2].isClicked(x, y)) {
            currentPage = LEVEL2_STORY; // ����ؿ�2����ҳ��
        }
        else if (buttons[3].isClicked(x, y)) {
            currentPage = LEVEL3_STORY; // ����ؿ�3����ҳ��
        }
    }
};

// ����ѡ��ҳ����
class SettingsPage : public Page {
private:
    bool& isMusicOn;
public:
    SettingsPage(bool& musicOn) : isMusicOn(musicOn) {
        buttons.push_back(Button(534, 199, 711, 260)); // ���ذ�ť
        buttons.push_back(Button(813, 309, 1008, 378)); // ���ֿ��ذ�ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1;
        }
        else if (buttons[1].isClicked(x, y)) {
            isMusicOn = !isMusicOn; // �л�����״̬
            if (isMusicOn) {
                PlaySound(L"������Դ/�˼���.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            }
            else {
                PlaySound(NULL, NULL, 0);
            }
        }
    }
};

// ��Խ����ҳ����
class CrossingStoryPage : public Page {
public:
    CrossingStoryPage() {
        buttons.push_back(Button(926, 593, 1038, 653)); // ��һҳ��ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL1_STORY; // ���롰�ؿ�1���顱ҳ��
        }
    }
};

// �ؿ�1����ҳ����
class Level1StoryPage : public Page {
public:
    Level1StoryPage() {
        buttons.push_back(Button(904, 582, 1018, 643)); // ��һҳ��ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL1_MAP; // ���롰�ؿ�1��ͼ��ҳ��
        }
    }
};

// �ؿ�1��ͼҳ���ࣨ�޷��ذ�ť��
class Level1MapPage : public Page {
public:
    Level1MapPage() {
        // ��ҳ���޷��ذ�ť���ؿ�1��ͼ��Ψһ����Ǵӹؿ�1����
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        // ��ҳ���޵���¼���Ӧ�������ڹؿ�1��ͼ
    }
};

// �ؿ�2����ҳ����
class Level2StoryPage : public Page {
public:
    Level2StoryPage() {
        buttons.push_back(Button(904, 582, 1018, 643)); // ��һҳ��ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL2_MAP; // ���롰�ؿ�2��ͼ��ҳ��
        }
    }
};

// �ؿ�3����ҳ����
class Level3StoryPage : public Page {
public:
    Level3StoryPage() {
        buttons.push_back(Button(904, 582, 1018, 643)); // ��һҳ��ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = LEVEL3_MAP; // ���롰�ؿ�3��ͼ��ҳ��
        }
    }
};

// �ؿ�2��ͼҳ����
class Level2MapPage : public Page {
public:
    Level2MapPage() {
        // ��ҳ���޷��ذ�ť���ؿ�2��ͼ��Ψһ����Ǵӹؿ�2����
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        // �޵���¼���Ӧ�������ڹؿ�2��ͼ
    }
};

// �ؿ�3��ͼҳ����
class Level3MapPage : public Page {
public:
    Level3MapPage() {
        // ��ҳ���޷��ذ�ť���ؿ�3��ͼ��Ψһ����Ǵӹؿ�3����
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        // �޵���¼���Ӧ�������ڹؿ�3��ͼ
    }
};

// ͨ�ؽ�����
class VictoryPage : public Page {
private:
    MenuPage lastMapPage = MENU1; // ��ʼ��Ϊ MENU1������δ��ʼ���ľ���
    std::vector<IMAGE> imageV;

public:
    // ���������ͼҳ��ķ���
    void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

    VictoryPage() {
        // ��ʼ����ť����
        buttons.push_back(Button(245, 285, 414, 345)); // ���˵���ť
        buttons.push_back(Button(245, 378, 414, 436)); // �½�ѡ��ť
        buttons.push_back(Button(245, 460, 414, 528)); // ��һ�ذ�ť
    }

    // ����ͨ�ؽ������Դ
    void loadResourcesV(const std::wstring& imagePath){
        Page::loadResources(imagePath); // ���û���ļ��ط���
        imageV.push_back(backgroundImage);
    }

    //����ͨ��ʱ��չʾ��ͬ��ͨ��ʤ������
    void drawV(int& seconds)
    {
        if (0 <= seconds && seconds <= 30)
        {
            putimage((WINDOW_WIDTH - imageV[0].getwidth()) / 2, (WINDOW_HEIGHT - imageV[0].getheight()) / 2, &imageV[0]);
        }
        else if (30 < seconds && seconds <= 60)
        {
            putimage((WINDOW_WIDTH - imageV[1].getwidth()) / 2, (WINDOW_HEIGHT - imageV[1].getheight()) / 2, &imageV[1]);
        }
        else if (60 < seconds)
        {
            putimage((WINDOW_WIDTH - imageV[2].getwidth()) / 2, (WINDOW_HEIGHT - imageV[2].getheight()) / 2, &imageV[2]);
        }
    }

    // �������¼�
    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // �������˵�
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = LEVEL_SELECT; // ���ص��½�ѡ��
        }
        else if (buttons[2].isClicked(x, y)) {
            // ������һ���߼�
            switch (lastMapPage) {
            case LEVEL1_MAP:
                currentPage = LEVEL2_STORY; // ����ؿ�2����ҳ��
                break;
            case LEVEL2_MAP:
                currentPage = LEVEL3_STORY; // ����ؿ�3����ҳ��
                break;
            case LEVEL3_MAP:
                // ����ǹؿ�3��Ĭ�Ͽ��Իص��ؿ�3����
                currentPage = LEVEL3_STORY;
                break;
            default:
                // �����Ա�̣���������ֵ���������˵�
                currentPage = MENU1;
                break;
            }
        }
    }
};

// ʧ��ҳ��
class FailPage : public Page {
private:
    MenuPage lastMapPage = MENU1; // ��ʼ��Ϊ MENU1������δ��ʼ���ľ���

public:
    // ���������ͼҳ��ķ���
    void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

    FailPage(){ // ���캯��������Ҷ�������
        // ��ʼ����ť����
        buttons.push_back(Button(245, 285, 414, 345)); // ���˵���ť
        buttons.push_back(Button(245, 378, 414, 436)); // �½�ѡ��ť
        buttons.push_back(Button(245, 460, 414, 528)); // ���¿�ʼ
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // �������˵�
        }
        else if (buttons[1].isClicked(x, y)) {
            currentPage = LEVEL_SELECT; // ���ص��½�ѡ��
        }
        else if (buttons[2].isClicked(x, y)) {
            // ������һ���߼�
            switch (lastMapPage) {
            case LEVEL1_MAP:
                currentPage = LEVEL1_MAP; // ����ؿ�2����ҳ��
                break;
            case LEVEL2_MAP:
                currentPage = LEVEL2_MAP; // ����ؿ�3����ҳ��
                break;
            case LEVEL3_MAP:
                // ����ǹؿ�3��Ĭ�Ͽ��Իص��ؿ�3����
                currentPage = LEVEL3_STORY;
                break;
            default:
                // �����Ա�̣���������ֵ���������˵�
                currentPage = MENU1;
                break;
            }
        }
    }
};

// �Ѷ�ѡ��ҳ��
class DifficultyPage : public Page {
private:
    Player& player; // ������Ҷ��������޸� HP ֵ

public:
    DifficultyPage(Player& p) : player(p) { // ���캯��������Ҷ�������
        buttons.push_back(Button(529, 202, 711, 260)); // ���ذ�ť
        buttons.push_back(Button(545, 290, 750, 350)); // ���°�ť
        buttons.push_back(Button(545, 381, 750, 445)); // ���Ű�ť
        buttons.push_back(Button(545, 473, 750, 535)); // ������ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU1; // ���ص����˵�1
        }
        if (buttons[1].isClicked(x, y)) { // �����Ѷ�
            player.setHP(100); // ������ҵ� HP Ϊ 100
        }
        if (buttons[2].isClicked(x, y)) { // �����Ѷ�
            player.setHP(50); // ������ҵ� HP Ϊ 50
        }
        if (buttons[3].isClicked(x, y)) { // �����Ѷ�
            player.setHP(20); // ������ҵ� HP Ϊ 20
        }
    }
};

// �淨����
class HowToPlayPage : public Page {
public:
    HowToPlayPage() {
        buttons.push_back(Button(515, 180, 790, 240)); // ���ذ�ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // �������˵�2
        }
    }
};

// ���а����  
class LeaderboardPage : public Page {
private:
    std::vector<int> clearancetime{ 0,0,0 };//��¼�����ؿ���ͨ��ʱ�䣬��λΪ��
public:

    LeaderboardPage() {
        buttons.push_back(Button(515, 180, 790, 240)); // ���ذ�ť  
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // �������˵�2  
        }
    }

    //��¼ͨ��ʱ��
    void recordclearancetime(int& seconds, MenuPage& LEVEL)
    {
        switch (LEVEL)
        {
        case LEVEL1_MAP:
            clearancetime[0] = seconds;
            break;
        case LEVEL2_MAP:
            clearancetime[1] = seconds;
            break;
        case LEVEL3_MAP:
            clearancetime[2] = seconds;
            break;
        }
    }

    //�����ļ��е����а���Ϣ
    void updateleaderboard()
    {
        std::vector<int>minimum = readleaderboard();
        for (int i = 0; i < minimum.size(); i++)
        {
            if (clearancetime[i] != 0 && minimum[i] != 0)
            {
                if (minimum[i] > clearancetime[i])
                    minimum[i] = clearancetime[i];
            }
            else if (minimum[i] == 0)
                minimum[i] = clearancetime[i];;
        }
        std::ofstream ofile{ "leaderboard.txt", std::ios::out };
        if (!ofile)
        {
            std::cerr << "�����а��ļ�ʧ��" << std::endl;
            exit(1);
        }
        for (int i = 0; i < minimum.size(); i++)
            ofile << minimum[i] << std::endl;
        ofile.close();
    }

    //��ȡ�ļ��е����а���Ϣ
    std::vector<int> readleaderboard()const
    {
        std::vector<int>minimum(3, 0);
        std::ifstream ifile{ "leaderboard.txt", std::ios::in };
        if (!ifile)
        {
            std::cerr << "�����а��ļ�ʧ��" << std::endl;
            exit(1);
        }
        for (int i = 0; i < minimum.size(); i++)
            ifile >> minimum[i];
        ifile.close();
        return minimum;
    }

    //�������а�ĳɼ�
    void drawleader()
    {
        clearancetime = readleaderboard();
        for (int i = 0; i < 3; i++)
        {
            wchar_t num[4];
            setcolor(YELLOW);
            settextstyle(40, 0, L"����");
            setbkmode(TRANSPARENT);
            swprintf(num, 4, L"%d", clearancetime[i]);
            outtextxy(800, 280 + i * 80, num);
            outtextxy(900, 280 + i * 80, L"��");
        }

    }
};

// �̵����
class ShopPage : public Page {
public:
    ShopPage() {
        buttons.push_back(Button(246, 189, 468, 250)); // ���ذ�ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // �������˵�2
        }
    }
};

// �����Ŷӽ���
class AboutTeamPage : public Page {
public:
    AboutTeamPage() {
        buttons.push_back(Button(733, 564, 1008, 624)); // ���ذ�ť
    }

    void handleClick(int x, int y, MenuPage& currentPage) override {
        if (buttons[0].isClicked(x, y)) {
            currentPage = MENU2; // �������˵�2
        }
    }
};

// ��Ϸ����
class Game {
private:
    MenuPage currentPage; // ��ǰҳ��
    MainMenuPage mainMenu; // ���˵�ҳ��
    Menu2Page menu2; // ���˵�2
    LevelSelectPage levelSelect; // �ؿ�ѡ��ҳ��
    SettingsPage settings; // ����ҳ��
    DifficultyPage difficulty; // �Ѷ�ѡ��ҳ��
    HowToPlayPage howToPlay; // �淨����
    LeaderboardPage leaderboard; // ���а����
    ShopPage shop; // �̵����
    AboutTeamPage aboutTeam; // �����Ŷӽ���
    CrossingStoryPage crossingStory; // ��Խ����ҳ��
    Level1StoryPage level1Story; // �ؿ�1����ҳ��
    Level1MapPage level1Map; // �ؿ�1��ͼҳ��
    Level2StoryPage level2Story; // �ؿ�2����ҳ��
    Level2MapPage level2Map;     // �ؿ�2��ͼҳ��
    Level3StoryPage level3Story; // �ؿ�3����ҳ��
    Level3MapPage level3Map;     // �ؿ�3��ͼҳ��
    Player player;  // ��Ҷ���
    IMAGE backgroundImage; // ��ӱ���ͼ�����������ʤ������
    VictoryPage victoryPage; // ʤ������
    FailPage failPage; //ʧ��ҳ��


public:
    Game() : currentPage(MENU1), player(80, 700 - 51), difficulty(player), settings(isMusicOn) {} // ��ʼ����ǰҳ��Ϊ���˵�

    // ��������ҳ����Դ
    void loadResources() {
        mainMenu.loadResources(L"ͼƬ��Դ/���˵�1.png");
        menu2.loadResources(L"ͼƬ��Դ/���˵�2.png");
        levelSelect.loadResources(L"ͼƬ��Դ/�ؿ�ѡ�����.png");
        settings.loadResources(L"ͼƬ��Դ/���ý���.png");
        difficulty.loadResources(L"ͼƬ��Դ/�ѶȽ���.png");
        howToPlay.loadResources(L"ͼƬ��Դ/�淨����.png");
        leaderboard.loadResources(L"ͼƬ��Դ/���а����.png");
        shop.loadResources(L"ͼƬ��Դ/�̵����.png");
        aboutTeam.loadResources(L"ͼƬ��Դ/�����Ŷӽ���.png");
        crossingStory.loadResources(L"ͼƬ��Դ/��Խ����.png");
        level1Story.loadResources(L"ͼƬ��Դ/�ؿ�1����.png");
        level1Map.loadResources(L"ͼƬ��Դ/�ؿ�1��ͼ.jpg");
        level2Story.loadResources(L"ͼƬ��Դ/�ؿ�2����.png");
        level2Map.loadResources(L"ͼƬ��Դ/�ؿ�2��ͼ.png");
        level3Story.loadResources(L"ͼƬ��Դ/�ؿ�3����.png");
        level3Map.loadResources(L"ͼƬ��Դ/�ؿ�3��ͼ.jpg");
        player.loadResources(); // ���������Դ
        victoryPage.loadResourcesV(L"ͼƬ��Դ/ʤ������1.png"); // ����ʤ������ͼƬ
        victoryPage.loadResourcesV(L"ͼƬ��Դ/ʤ������2.png"); // ����ʤ������ͼƬ
        victoryPage.loadResourcesV(L"ͼƬ��Դ/ʤ������3.png"); // ����ʤ������ͼƬ
        failPage.loadResources(L"ͼƬ��Դ/ʧ�ܽ���1.png");

    }

    bool isLevelMusicPlaying = false; // ��־λ���ж��Ƿ��ڲ��ŵ�ͼ����
    bool isMusicOn = true; // ȫ�ֱ�������¼���ֿ���״̬����ʼ״̬Ϊ����

    // ���ű�������
    void playBackgroundMusic(const std::wstring& musicFile) {
        if (isMusicOn) { // ֻ�������ֿ��ؿ���������²Ų�������
            PlaySound(musicFile.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        else {
            PlaySound(NULL, NULL, 0); // ֹͣ��������
        }
    }

    // ����ҳ�沥�Ų�ͬ������
    void updateBackgroundMusic() {
        if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP) {
            if (!isLevelMusicPlaying) {
                // �����ͼ�����ҵ�ͼ����δ����ʱ�����ŵ�ͼ����
                playBackgroundMusic(L"������Դ/��˵֮��.wav");
                isLevelMusicPlaying = true; // ��־λ��Ϊ��ͼ�������ڲ���
            }
        }
        else {
            if (isLevelMusicPlaying) {
                // �뿪��ͼ���棬�л�������ҳ��ʱ����Ĭ������
                playBackgroundMusic(L"������Դ/�˼���.wav");
                isLevelMusicPlaying = false; // ��־λ��Ϊ�ǵ�ͼ����
            }
            // ����ڷǵ�ͼ���棬���Ѿ������˼������֣������ٴβ���
        }
    }

    // ���Ƶ�ǰҳ��
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
            leaderboard.drawleader();
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
            player.draw(); // �ڵ�ͼ1�������
            break;
        case LEVEL2_STORY:
            level2Story.draw();
            break;
        case LEVEL2_MAP:
            level2Map.draw();
            player.draw(); // �ڵ�ͼ2�������
            break;
        case LEVEL3_STORY:
            level3Story.draw();
            break;
        case LEVEL3_MAP:
            level3Map.draw();
            player.draw(); // �ڵ�ͼ3�������
            break;
        case VICTORY_SCREEN: // ͨ�ؽ���
            victoryPage.drawV(seconds);
            break;
        case FAIL:
            failPage.draw();
            break;
        }
    }

    // ����������¼�
    void handleMouseClick(int x, int y) {
        MenuPage previousPage = currentPage; // ���� previousPage �������洢��ǰҳ��

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
        case VICTORY_SCREEN: // ʤ������
            victoryPage.handleClick(x, y, currentPage);
            break;
        case FAIL:
            failPage.handleClick(x, y, currentPage);
            break;
        }
        
        if (currentPage != previousPage) {
            updateBackgroundMusic(); // ҳ���л�����±�������
        }
    }


    //�ؿ���ʼʱ��¼��ʼʱ��
    void timeRecordStart(bool& levelStarted, DWORD& startTime, MenuPage& currentPage)
    {
        if (!levelStarted && (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)) {
            startTime = GetTickCount(); // ��¼��ʼʱ��  
            levelStarted = true; // ���ùؿ��ѿ�ʼ��־  
        }
    }

    void calculateTimeElapsed(int& seconds, DWORD& startTime, MenuPage& currentPage)
    {
        if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)
        {
            // ���㲢��ʾʱ��  
            DWORD elapsedTime = GetTickCount() - startTime; // ���㾭����ʱ��  
            seconds = elapsedTime / 1000; // ת��Ϊ��  
            // ����Ļ����ʾ������ʱ��  
            std::wstring timeText = L"ʱ��: " + std::to_wstring(seconds) + L"��";
            outtextxy(10, 10, timeText.c_str()); // ��ָ��λ�û���ʱ���ı�
        }
    }

    //���ؿ�ͨ����ʧ��ʱ��Ҫʵ���������λ�ú��л����ֵȹ��ܣ������������װ
    void levelFinish()
    {
        player.resetPosition(); // ͨ��ʱ�������λ��  
        playBackgroundMusic(L"������Դ/�˼���.wav"); // ȷ�������˼�������  
        levelStarted = false; // ���ùؿ���ʼ��־
        leaderboard.recordclearancetime(seconds, currentPage);
        leaderboard.updateleaderboard();
    }

    void inTheGame()
    {
        while (true)
        {
            BeginBatchDraw(); // ˫����  
            // �ؿ���ʼʱ��¼ʱ��  
            timeRecordStart(levelStarted, startTime, currentPage);
            // ���㵱ǰ�ؿ��Ѿ�����ʱ�䲢չʾ
            calculateTimeElapsed(seconds, startTime, currentPage);
            // ���ºͻ������  
            if (currentGroundBlocks && currentWallBlocks && currentCeilingBlocks && currentTrapBlocks &&
                (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)) {
                player.update(*currentGroundBlocks, *currentWallBlocks, *currentCeilingBlocks, *currentTrapBlocks);
                player.draw();

                //���������ֵС�ڵ���0ʱ���жϹؿ�ͨ��ʧ��
                if (player.getHP() <= 0)
                {
                    failPage.setLastMapPage(currentPage); // ���õ�ǰ��ͼҳ��   
                    currentVictoryDoor = nullptr; // ����ͨ���Ŷ���  
                    currentPage = FAIL; // �л���ʤ������ 
                    levelFinish();
                    break;
                }
                //�����ͨ��ʧ�ܵ��жϺ�����ͨ�ص��ж�Ψһ����������levelFinish()��λ�ò�ͬ��
                // levelFinish()��λ�ò�ͬ�ᵼ�����а��Ƿ���¼ʱ��
                // ���ʤ������  
                if (currentVictoryDoor && player.checkVictory(*currentVictoryDoor)) {
                    victoryPage.setLastMapPage(currentPage); // ���õ�ǰ��ͼҳ��   
                    currentVictoryDoor = nullptr; // ����ͨ���Ŷ���
                    levelFinish();
                    currentPage = VICTORY_SCREEN; // �л���ʤ������
                    break;
                }
            }

            EndBatchDraw();
            Sleep(5); // ����ˢ��Ƶ��  
        }
        
    }

    //��Ϸ��ѭ��
    void run() {
        initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���  
        loadResources(); // ������Դ  
        playBackgroundMusic(L"������Դ/�˼���.wav"); // ��ʼ����Ĭ������  

        while (true) {
            BeginBatchDraw(); // ˫����
            cleardevice(); // ����  
            drawCurrentPage(); // ���Ƶ�ǰҳ��  
            // ���ݵ�ǰҳ��ѡ���ͼ����顢ǽ�ڿ顢�컨����ͨ����  
            if (currentPage == LEVEL1_MAP) {
                currentGroundBlocks = &level1GroundBlocks;
                currentWallBlocks = &level1WallBlocks;
                currentCeilingBlocks = &level1CeilingBlocks;
                currentTrapBlocks = &level1TrapBlocks;
                currentVictoryDoor = &level1VictoryDoor;
                inTheGame();
            }
            else if (currentPage == LEVEL2_MAP) {
                currentGroundBlocks = &level2GroundBlocks;
                currentWallBlocks = &level2WallBlocks;
                currentCeilingBlocks = &level2CeilingBlocks;
                currentTrapBlocks = &level2TrapBlocks;
                currentVictoryDoor = &level2VictoryDoor;
                inTheGame();
            }
            else if (currentPage == LEVEL3_MAP) {
                currentGroundBlocks = &level3GroundBlocks;
                currentWallBlocks = &level3WallBlocks;
                currentCeilingBlocks = &level3CeilingBlocks;
                currentTrapBlocks = &level3TrapBlocks;
                currentVictoryDoor = &level3VictoryDoor;
                inTheGame();
            }
            EndBatchDraw();

            // ����Ƿ�������¼�  
            if (MouseHit()) {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    std::cout << msg.x << "," << msg.y << std::endl;
                }
            }

            Sleep(5); // ����ˢ��Ƶ��  
        }
        closegraph(); // �ر�ͼ�δ���  
        PlaySound(NULL, NULL, 0); // ֹͣ��������  
    }
private:
    // ��Ӽ�ʱ��صı���  
    DWORD startTime = 0; // �ؿ���ʼʱ��  
    int seconds = 0;//��¼�ؿ�ʱ��
    bool levelStarted = false; // ��ǹؿ��Ƿ��Ѿ���ʼ  
    std::vector<GroundBlock>* currentGroundBlocks = nullptr;
    std::vector<WallBlock>* currentWallBlocks = nullptr;
    std::vector<CeilingBlock>* currentCeilingBlocks = nullptr;
    std::vector<TrapBlock>* currentTrapBlocks = nullptr;
    VictoryDoor* currentVictoryDoor = nullptr; // ��ǰ�ؿ���ͨ����  
};

// ������
int main() {
    Game game;
    game.run();
    return 0;
}