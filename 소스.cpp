#include <bangtal.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
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
    map<string, int> ingredientSet;
    int myMoney; //내가 가지고 있는 돈


public:

    User(int initialMoney) : myMoney(initialMoney) {
        // Initialize the ingredientSet
        ingredientSet = {
            { "bread", 500 },
            { "bulgogiPatty", 1000 },
            { "chicken", 1000 },
            { "crabMeat", 2000 },
            { "cow", 10000 },
            { "tomato", 500 },
            { "cabbage", 500 },
            { "slicedCheese", 500 },
            { "potato", 500 },
            { "oil", 500 },
            { "stringCheese", 500 },
            { "coke", 1000 },
            { "soda", 1000 }
        };
    }

    void setMoney(int initialMoney) {
        myMoney = initialMoney;
    }

    // 마켓에서 산 재료를 재료 목록에 추가
    void updateIngredients(const string& ingredient, int quantity) {
        if (ingredientSet.find(ingredient) != ingredientSet.end()) {
            ingredientSet[ingredient] += quantity;
        }
        else {
            ingredientSet.insert({ ingredient, quantity });
        }
    }

    // 마켓에서 구매할 때 돈을 차감
    void useMoney(int totalPrice) {
        if (myMoney >= totalPrice) {
            myMoney -= totalPrice;
            cout << "Money used: " << totalPrice << endl;
        }
        else {
            cout << "Insufficient funds!" << endl;
        }
    }

    // 손님에게 판매하여 돈 벌기
    void earnMoney(int earnTotalPrice) {
        myMoney += earnTotalPrice;
        cout << "Money earned: " << earnTotalPrice << endl;
    }

    // 재료를 사용하여 햄버거 만들기
    void makeBurgerIngredients(const string& ingredient) {
        if (ingredientSet.find(ingredient) != ingredientSet.end() && ingredientSet[ingredient] > 0) {
            ingredientSet[ingredient]--;
        }
        else {
            cout << "Lack of ingredients!" << endl;
        }
    }

};



class Market {
private:
    Ingredient ingredient[13]; // 13개
public:
    Market() {
        ingredient[0].obj_Ingredient = createObject("bread", "Images/빵.png", MarketScene, 430, 570);
        scaleObject(ingredient[0].obj_Ingredient, 0.045f);
        ingredient[1].obj_Ingredient = createObject("불고기패티", "Images/불고기패티.png", MarketScene, 430, 430);
        scaleObject(ingredient[1].obj_Ingredient, 0.065f);
        ingredient[2].obj_Ingredient = createObject("치킨", "Images/생닭.png", MarketScene, 420, 290);
        scaleObject(ingredient[2].obj_Ingredient, 0.06f);
        ingredient[3].obj_Ingredient = createObject("게살", "Images/게살.png", MarketScene, 430, 185);
        scaleObject(ingredient[3].obj_Ingredient, 0.2f);
        ingredient[4].obj_Ingredient = createObject("소한마리", "Images/소한마리.png", MarketScene, 430, 40);
        scaleObject(ingredient[4].obj_Ingredient, 0.07f);
        ingredient[5].obj_Ingredient = createObject("토마토", "Images/토마토.png", MarketScene, 710, 570);
        scaleObject(ingredient[5].obj_Ingredient, 0.065f);
        ingredient[6].obj_Ingredient = createObject("양상추", "Images/양상추.png", MarketScene, 705, 420);
        scaleObject(ingredient[6].obj_Ingredient, 0.04f);
        ingredient[7].obj_Ingredient = createObject("체다치즈", "Images/체다치즈.png", MarketScene, 710, 290);
        scaleObject(ingredient[7].obj_Ingredient, 0.065f);
        ingredient[8].obj_Ingredient = createObject("감자", "Images/감자.png", MarketScene, 710, 165);
        scaleObject(ingredient[8].obj_Ingredient, 0.1f);
        ingredient[9].obj_Ingredient = createObject("식용유", "Images/식용유.png", MarketScene, 990, 570);
        scaleObject(ingredient[9].obj_Ingredient, 0.1f);
        ingredient[10].obj_Ingredient = createObject("스트링치즈", "Images/스트링치즈.png", MarketScene, 990, 440);
        scaleObject(ingredient[10].obj_Ingredient, 0.2f);
        ingredient[11].obj_Ingredient = createObject("콜라1캔", "Images/콜라.png", MarketScene, 990, 300);
        scaleObject(ingredient[11].obj_Ingredient, 0.15f);
        ingredient[12].obj_Ingredient = createObject("사이다1캔", "Images/사이다.png", MarketScene, 990, 165);
        scaleObject(ingredient[12].obj_Ingredient, 0.185f);
    }

    bool chooseIngredients(ObjectID object) {
        for (int i = 0; i < 13; i++) {
            if (object == ingredient[i].obj_Ingredient) { // market scene에서 구매할 물품을 선택했을 떄
                // ******** 돈이 부족하면 불가능하다고 말해야함 ********

                // ******** 돈이 부족하지 않으면 내가 가지고 있는 돈은 줄이고 가지고 있는 물품에 추가
            }
        }
    }
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

// 이부분 전역변수 신경 ㄴㄴ
Burger burger[5]; // 5개
Side side[4]; // NULL 포함 4개
Drink drink[3]; // NULL 포함 3개
Customer customer[4]; // 5일마다 각 4명, 날 바뀔 때마다 초기화해서 재사용
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
    else if (object == endButton) { // 종료 버튼을 누르면
        endGame(); // 게임 종료
    }
    else if (market.chooseIngredients(object) == true) {
        // 마켓의 ingredients를 클릭한 경우
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





    startGame(StartScene);
}