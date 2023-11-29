#include <bangtal.h>
#include <vector>
using namespace std;

// 클래스
class Ingredient {
private:
    
public:
    ObjectID obj_Ingredient;
};

class Burger {
private:

public:
    ObjectID obj_Burger;
};

class Side {
private:

public:
    ObjectID obj_Side;
};

class Drink {
private:

public:
    ObjectID obj_Drink;
};

class Customer {
private:

public:

};

class User {
private:

public:

};

class Market {
private:

public:

};

// 전역 변수
int day = 0;

SceneID StartScene, TutorialScene, MarketScene, BurgerScene, EndScene;
ObjectID TutorialButton, startButton; // StartScene
ObjectID closeButton; // TutorialScene

vector<Ingredient> ingredient; // 13개
vector<Burger> burger; // 5개
vector<Side> side; // NULL 포함 4개
vector<Drink> drink; // NULL 포함 3개
vector<Customer> customer[4]; // 5일마다 각 4명, 날 바뀔 때마다 초기화해서 재사용
User user;
Market market;

// 함수 목록
void mouseCallback(ObjectID, int, int, MouseAction);

// 함수 구현
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

}

int main()
{
    // 안 보여야 될 것들 가림
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

    setMouseCallback(mouseCallback);

    // scene 생성
    StartScene = createScene("StartScene", "");
    TutorialScene = createScene("TutorialScene", "");
    MarketScene = createScene("MarketScene", "");
    BurgerScene = createScene("BurgerScene", "");
    EndScene = createScene("EndScene", "");

    // object 생성


    startGame(StartScene);
}