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
    ObjectID obj_Customer;
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
int day = 0; // 몇 번째 날인지
int customer_order = 1; // 몇 번째 손님인지

SceneID StartScene, TutorialScene, MarketScene, BurgerScene, EndScene;
ObjectID TutorialButton, startButton; // StartScene
ObjectID closeButton; // TutorialScene
ObjectID completeButton; // MarketScene
ObjectID checkButton; // BurgerScene
ObjectID endButton; // EndScene

vector<Ingredient> ingredient; // 13개
vector<Burger> burger; // 5개
vector<Side> side; // NULL 포함 4개
vector<Drink> drink; // NULL 포함 3개
vector<Customer> customer[4]; // 5일마다 각 4명, 날 바뀔 때마다 초기화해서 재사용
User user;
Market market;

// 함수 목록
void mouseCallback(ObjectID, int, int, MouseAction);
ObjectID createObject(const char*, const char*, SceneID, int, int);

// 함수 구현
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == TutorialButton) { // 튜토리얼 버튼을 누르면
        enterScene(TutorialScene); // 튜토리얼 scene으로 이동
    }
    else if (object == startButton) { // 시작 버튼을 누르면
        enterScene(MarketScene); // 구매 scene으로 이동
    }
    else if (object == closeButton) { // 튜토리얼을 다 읽고 닫기 버튼을 누르면
        enterScene(StartScene); // 시작 scene으로 이동
    }
    else if (object == completeButton) { // 구매를 마친 후 완료 버튼을 누르면
        // ********** 구매자 초기화 ********** -> 이때 object 선언

        enterScene(BurgerScene); // 판매 scene으로 이동
    }
    else if (object == checkButton) { // 각 손님에게 메뉴를 제공하기 위해 체크 버튼을 누르면
        // ********* 결과 보여주기 ************

        if (customer_order < 5) { // 마지막 손님이 아니면
            customer_order += 1; // 다음 손님을 봐야 함
        }
        else if (customer_order == 5) { // 마지막 손님이면
            if (day < 5) { // 마지막 날이 아니면
                customer_order = 1; // 손님 순서 초기화
                day += 1; // 해당 날이 끝나고 다음 날로 바꿈
                enterScene(MarketScene); // 구매 scene으로 이동
            }
            else { // 마지막 날이면
                enterScene(EndScene);
            }
        }
    }
    else if (object == endButton) {
        endGame();
    }
}
ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y) {
    // object 선언 함수
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y); // 해당 위치에 object를 위치시킴
    showObject(object); // object를 보이게 함

    return object;
}

int main()
{
    // 안 보여야 될 것들 가림
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

    setMouseCallback(mouseCallback);

    // scene 생성
    // 각 사진도 입력해야 함
    StartScene = createScene("StartScene", "");
    TutorialScene = createScene("TutorialScene", "");
    MarketScene = createScene("MarketScene", "");
    BurgerScene = createScene("BurgerScene", "");
    EndScene = createScene("EndScene", "");

    // object 생성
    // 아직 이미지, 위치 지정 안함
    TutorialButton = createObject("TutorialButton", "", StartScene, 0, 0);
    startButton = createObject("startButton", "", StartScene, 0, 0);
    closeButton = createObject("closeButton", "", TutorialScene, 0, 0);
    completeButton = createObject("completeButton", "", MarketScene, 0, 0);
    checkButton = createObject("checkButton", "", BurgerScene, 0, 0);
    endButton = createObject("endButton", "", EndScene, 0, 0);

    // 각 재료들마다 구현해야 함. 아직 안함 임시임
    for (int i = 0; i < 13; i++) ingredient[i].obj_Ingredient = createObject("", "", MarketScene, 0, 0);

    startGame(StartScene);
}