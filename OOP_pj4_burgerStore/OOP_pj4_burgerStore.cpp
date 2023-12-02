﻿#include <bangtal.h>
#include <string>
#include <vector>
#include <time.h>
#include<map>
using namespace std;

// 전역 변수
int day = 0; // 몇 번째 날인지
int customer_order = 1; // 몇 번째 손님인지

SceneID StartScene, TutorialScene, MarketScene, BurgerScene, EndScene;
ObjectID tutorialButton, startButton; // StartScene
ObjectID closeButton; // TutorialScene
ObjectID completeButton; // MarketScene
ObjectID checkButton; // BurgerScene
ObjectID endButton; // EndScene

// 함수 목록
void mouseCallback(ObjectID, int, int, MouseAction);
ObjectID createObject(const char*, const char*, SceneID, int, int);
void setIngredients();

// 클래스
class Ingredient {
private:
    string name;
    int price;
    string imageName;
public:
    ObjectID obj_Ingredient;
    void setIngredientInfo(string name, int price, string imageName) {
        this->name = name;
        this->price = price;
        this->imageName = imageName;
    }

     string getName() {
        return name;
    }

    int getPrice() {
        return price;
    }
    string getImageName() {
        return imageName;
    }
};
Ingredient ingredient[13];

class Menu {
private:
    string name;
    int price;
    vector<Ingredient> ingredients;
public:
    Menu() { name = "NULL"; price = 0; }
    Menu(string _name, int _price, vector<Ingredient> _ingredients) :price(_price) {
        name = _name;   //shallow copy
        for (int i = 0; i < _ingredients.size(); i++) {
            ingredients.push_back(_ingredients[i]);
        }
    }
    ObjectID obj;
    int getPrice() { return price; }
    bool checkIngredient(vector<Ingredient> choosenIngredients);
};

bool Menu::checkIngredient(vector<Ingredient> choosenIngredients) {
    int checkIng = 0;
    for (int i = 0; i < ingredients.size(); i++) {  //내거에서 있는지 비교 -> 있으면 바로 break -> 고른 수량상관없이 확인가능 -> 개수이용
        for (int j = 0; j < choosenIngredients.size(); j++) {
            if (ingredients[i].getName() == choosenIngredients[j].getName()) {  //내거랑 고른거랑 같은게 존재한다면
                checkIng++;
                break;
            }
        }
    }
    if (checkIng == ingredients.size()) {   //메뉴재료랑 같은 고른 재료의 개수가 메뉴재료의 개수와 같다면 
        return true;
    }
    else {
        return false;
    }
}


class Burger :public Menu {
public:
    Burger() {}
    Burger(string _name, int _price, vector<Ingredient> _ingredients) :Menu(_name, _price, _ingredients) {/*생성자*/ };
};

class Side :public Menu {
public:
    Side() {}
    Side(string _name, int _price, vector<Ingredient> _ingredients) :Menu(_name, _price, _ingredients) {/*생성자*/ };
};

class Drink :public Menu {
public:
    Drink() {}
    Drink(string _name, int _price, vector<Ingredient> _ingredients) :Menu(_name, _price, _ingredients) {/*생성자*/ };
};


class Customer {
private:
    Burger myBurger;
    Side mySide;
    Drink myDrink;
    int totalPrice;
    //이미지는 맨 밑에서 createObject할 때 지정
public:
    Customer() {
        srand(time(0));
        int num;
        //햄버거 설정
        vector <Ingredient> burgerIng;
        num = rand() % 9;
        if (num == 1 || num == 8) {
            burgerIng.push_back(ingredient[0]);
            burgerIng.push_back(ingredient[1]);
            burgerIng.push_back(ingredient[6]);
            myBurger = Burger("bulgogiBurger", 3000, burgerIng);
        }
        else if (num == 2 || num == 7) {
            burgerIng.push_back(ingredient[0]);
            burgerIng.push_back(ingredient[1]);
            burgerIng.push_back(ingredient[6]);
            burgerIng.push_back(ingredient[7]);
            myBurger = Burger("cheeseBurger", 3500, burgerIng);
        }
        else if (num == 3 || num == 6) {
            burgerIng.push_back(ingredient[0]);
            burgerIng.push_back(ingredient[2]);
            burgerIng.push_back(ingredient[6]);
            myBurger = Burger("chickenBurger", 3500, burgerIng);
        }
        else if (num == 4 || num == 5) {
            burgerIng.push_back(ingredient[0]);
            burgerIng.push_back(ingredient[3]);
            burgerIng.push_back(ingredient[5]);
            myBurger = Burger("crabBurger", 4500, burgerIng);
        }
        else {
            burgerIng.push_back(ingredient[0]);
            burgerIng.push_back(ingredient[4]);
            burgerIng.push_back(ingredient[5]);
            burgerIng.push_back(ingredient[6]);
            myBurger = Burger("cauBurger", 20000, burgerIng);
        }
        //사이드메뉴 설정
        vector <Ingredient> sideIng;
        num = rand() % 4;
        if (num == 1) {
            sideIng.push_back(ingredient[8]);
            sideIng.push_back(ingredient[9]);
            mySide = Side("chips", 2000, sideIng);
        }
        else if (num == 2) {
            sideIng.push_back(ingredient[7]);
            sideIng.push_back(ingredient[9]);
            mySide = Side("nugget", 2000, sideIng);
        }
        else if (num == 3) {
            sideIng.push_back(ingredient[10]);
            sideIng.push_back(ingredient[9]);
            mySide = Side("cheeseStick", 2000, sideIng);
        }
        else {
            //null인데 기본생성자가 null이라 뭐 안해줘도 됨 !
        }

        //음료 설정
        vector <Ingredient> drinkIng;
        num = rand() % 3;
        if (num == 1) {
            drinkIng.push_back(ingredient[11]);
            myDrink = Drink("coke", 2000, drinkIng);
        }
        else if (num == 2) {
            drinkIng.push_back(ingredient[12]);
            myDrink = Drink("soda", 2000, drinkIng);
        }
        else {
            //null인데 기본생성자가 null이라 뭐 안해줘도 됨 !
        }

        // 총 가격 설정
        totalPrice = myBurger.getPrice() + mySide.getPrice() + myDrink.getPrice();
    }
    
    int getTotalPrice() {
        return totalPrice;
    }
    bool allCheckIngredient() {/* choosenIngredient 클릭함수에서 구현 후 해야함
        if (myBurger.checkIngredient() && mySide.checkIngredient() && myDrink.checkIngredient()) {
            return true;
        }else
            return false;*/
    }
    ObjectID obj_Customer;
};

class User {
private:
    map< string, int> ingredientSet;
    int myMoney; //내가 가지고 있는 돈


public:
    User() {
        ingredientSet = {
            { "bread", 0 },
            { "bulgogiPatty", 0 },
            { "chicken", 0 },
            { "crabMeat", 0 },
            { "cow", 0 },
            { "tomato", 0 },
            { "cabbage", 0 },
            { "slicedCheese", 0 },
            { "potato", 0 },
            { "oil", 0 },
            { "stringCheese", 0 },
            { "coke", 0 },
            { "soda", 0 }
        };
    }

    void setMoney(int initialMoney) {
        myMoney = initialMoney;
    }

    // 마켓에서 산 재료를 재료 목록에 추가
    void updateIngredients( Ingredient& ingredient) {
        int amount;
        amount = ingredientSet[ingredient.getName()];
        amount++;
        
    }
    // 마켓에서 구매할 때 돈을 차감
    void useMoney(int totalPrice) {
        if (myMoney >= totalPrice) {
            myMoney -= totalPrice;
        }
        else {
            //돈없는데 사려고함 --> 안된다고 띄워~~~~
        }
    }

    // 손님에게 판매하여 돈 벌기
    void earnMoney(int earnTotalPrice) {
        myMoney += earnTotalPrice;
    }

    // 재료를 사용하여 햄버거 만들기
    void makeBurgerIngredients( Ingredient& ingredient) {
        if (ingredientSet.find(ingredient.getName()) != ingredientSet.end() && ingredientSet[ingredient.getName()] > 0) {
            ingredientSet[ingredient.getName()]--;
        }
        else {
        }
    }

    ObjectID obj_User;
};


class Market {
private:
     // 13개
public:
    Market() {
    }

    bool chooseIngredients(ObjectID object) {
        for (int i = 0; i < 13; i++) {
            if (object == ingredient[i].obj_Ingredient) { // market scene에서 구매할 물품을 선택했을 떄
                // ******** 돈이 부족하면 불가능하다고 말해야함 ********
                
                // ******** 돈이 부족하지 않으면 내가 가지고 있는 돈은 줄이고 가지고 있는 물품에 추가
            }return true;
        }
    }
};

// 이부분 전역변수 
Burger burger[5]; // 5개
Side side[4]; // NULL 포함 4개
Drink drink[3]; // NULL 포함 3개
Customer customer[4]; // 5일마다 각 4명, 날 바뀔 때마다 초기화해서 재사용
User user;
Market market;

// 함수 구현
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    
    if (object == tutorialButton) { // 튜토리얼 버튼을 누르면
        showMessage("hellekejel");
        enterScene(TutorialScene); // 튜토리얼 scene으로 이동

    }
    if (object == startButton) { // 시작 버튼을 누르면
        enterScene(MarketScene); // 구매 scene으로 이동
    }
    if (object == closeButton) { // 튜토리얼을 다 읽고 닫기 버튼을 누르면
        enterScene(StartScene); // 시작 scene으로 이동
    }
    if (object == completeButton) { // 구매를 마친 후 완료 버튼을 누르면
        
        // ********** 손님 초기화 ********** -> 이때 object 선언
        customer_order = 1;
        customer[customer_order - 1].obj_Customer = createObject("bread", "Images/ingredient/bread.png", BurgerScene, 0, 0);
        scaleObject(customer[customer_order - 1].obj_Customer, 0.045f);
        enterScene(BurgerScene); // 판매 scene으로 이동
        //손님만들기
        
    }
    if (object == checkButton) { // 각 손님에게 메뉴를 제공하기 위해 체크 버튼을 누르면
        // ********* 결과 보여주기 ************
       /* if (customer[customer_order - 1].allCheckIngredient()) {
            //전부 재료 확인 함 -> 성공 -> success 띄우고 money update
            user.earnMoney(customer[customer_order - 1].getTotalPrice());   //돈 업데이트
        }
        else {
            //틀렸다고 말해주기 --튜토리얼에서 하나라도 틀리면 틀린거라고 설명~~~~~~~~~~
        }*/
        //손님 띄워주기
        if (customer_order < 4) { // 마지막 손님이 아니면
            //이전손님삭제~~~~
            
            //시간 지연 해보기~~~
            customer_order += 1; // 다음 손님을 봐야 함
            customer[customer_order - 1].obj_Customer = createObject("불고기패티", "Images/ingredient/불고기패티.png", BurgerScene, 0, 0);
            scaleObject(customer[customer_order - 1].obj_Customer, 0.045f);
            
        }
        else if (customer_order == 4) { // 마지막 손님이면
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
    if (object == endButton) { // 종료 버튼을 누르면
        endGame(); // 게임 종료
    }
    if ( market.chooseIngredients(object) == true) {
        // 마켓의 ingredients를 클릭한 경우
        for (int i = 0; i < 13; i++) {
            if (object == ingredient[i].obj_Ingredient) {
                user.updateIngredients(ingredient[i]);
                //바뀐 해당 재료의 amount를 show message
                //위치설정은 어캄?????????
            }
        }
        
        
    }
    //if (/*여기서 판매대에서 재료 클릭했을때*/) {
        //customer[customer_order - 1].allCheckIngredients(object);
    //}
}

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y) {
    // object 선언 함수
    ObjectID object = createObject(image);
    //해당 obj가 어떤 객체인지 모륵ㅁ
    locateObject(object, scene, x, y); // 해당 위치에 object를 위치시킴
    showObject(object); // object를 보이게 함

    return object;
}


void setMarketIngredients() {
    ingredient[0].obj_Ingredient = createObject("bread", "Images/ingredient/bread.png", MarketScene, 440, 580);
    scaleObject(ingredient[0].obj_Ingredient, 0.045f);
    ingredient[1].obj_Ingredient = createObject("불고기패티", "Images/ingredient/불고기패티.png", MarketScene, 440, 440);
    scaleObject(ingredient[1].obj_Ingredient, 0.065f);
    ingredient[2].obj_Ingredient = createObject("치킨", "Images/ingredient/생닭.png", MarketScene, 420, 290);
    scaleObject(ingredient[2].obj_Ingredient, 0.06f);
    ingredient[3].obj_Ingredient = createObject("게살", "Images/ingredient/게살.png", MarketScene, 440, 160);
    scaleObject(ingredient[3].obj_Ingredient, 0.2f);
    ingredient[4].obj_Ingredient = createObject("소한마리", "Images/ingredient/소한마리.png", MarketScene, 440, 20);
    scaleObject(ingredient[4].obj_Ingredient, 0.07f);
    ingredient[5].obj_Ingredient = createObject("토마토", "Images/ingredient/토마토.png", MarketScene, 710, 570);
    scaleObject(ingredient[5].obj_Ingredient, 0.065f);
    ingredient[6].obj_Ingredient = createObject("양상추", "Images/ingredient/양상추.png", MarketScene, 705, 420);
    scaleObject(ingredient[6].obj_Ingredient, 0.04f);
    ingredient[7].obj_Ingredient = createObject("체다치즈", "Images/ingredient/체다치즈.png", MarketScene, 710, 290);
    scaleObject(ingredient[7].obj_Ingredient, 0.065f);
    ingredient[8].obj_Ingredient = createObject("감자", "Images/ingredient/감자.png", MarketScene, 720, 165);
    scaleObject(ingredient[8].obj_Ingredient, 0.1f);
    ingredient[9].obj_Ingredient = createObject("식용유", "Images/ingredient/식용유.png", MarketScene, 1000, 570);
    scaleObject(ingredient[9].obj_Ingredient, 0.1f);
    ingredient[10].obj_Ingredient = createObject("스트링치즈", "Images/ingredient/스트링치즈.png", MarketScene, 1000, 440);
    scaleObject(ingredient[10].obj_Ingredient, 0.2f);
    ingredient[11].obj_Ingredient = createObject("콜라1캔", "Images/ingredient/콜라.png", MarketScene, 1000, 300);
    scaleObject(ingredient[11].obj_Ingredient, 0.15f);
    ingredient[12].obj_Ingredient = createObject("사이다1캔", "Images/ingredient/사이다.png", MarketScene, 1000, 165);
    scaleObject(ingredient[12].obj_Ingredient, 0.185f);
}

void setUserIngredients() {
    user.obj_User = createObject("bread", "Images/ingredient/bread.png", BurgerScene, 40, 530);
    scaleObject(user.obj_User, 0.028f);
    user.obj_User = createObject("불고기패티", "Images/ingredient/불고기패티.png", BurgerScene, 40, 445);
    scaleObject(user.obj_User, 0.036f);
    user.obj_User = createObject("치킨", "Images/ingredient/생닭.png", BurgerScene, 30, 340);
    scaleObject(user.obj_User, 0.04f);
    user.obj_User = createObject("게살", "Images/ingredient/게살.png", BurgerScene, 40, 275);
    scaleObject(user.obj_User, 0.12f);
    user.obj_User = createObject("소한마리", "Images/ingredient/소한마리.png", BurgerScene, 40, 195);
    scaleObject(user.obj_User, 0.034f);
    user.obj_User = createObject("토마토", "Images/ingredient/토마토.png", BurgerScene, 35, 105);
    scaleObject(user.obj_User, 0.038f);
    user.obj_User = createObject("양상추", "Images/ingredient/양상추.png", BurgerScene, 210, 530);
    scaleObject(user.obj_User, 0.024f);
    user.obj_User = createObject("체다치즈", "Images/ingredient/체다치즈.png", BurgerScene, 215, 450);
    scaleObject(user.obj_User, 0.035f);
    user.obj_User = createObject("감자", "Images/ingredient/감자.png", BurgerScene, 220, 370);
    scaleObject(user.obj_User, 0.055f);
    user.obj_User = createObject("식용유", "Images/ingredient/식용유.png", BurgerScene, 210, 290);
    scaleObject(user.obj_User, 0.065f);
    user.obj_User = createObject("스트링치즈", "Images/ingredient/스트링치즈.png", BurgerScene, 210, 200);
    scaleObject(user.obj_User, 0.12f);
    user.obj_User = createObject("콜라1캔", "Images/ingredient/콜라.png", BurgerScene, 180, 120);
    scaleObject(user.obj_User, 0.08f);
    user.obj_User = createObject("사이다1캔", "Images/ingredient/사이다.png", BurgerScene, 280, 120);
    scaleObject(user.obj_User, 0.095f);
}

void setStartScene() {
StartScene = createScene("StartScene", "Images/scene/StartScene.png");
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
    setStartScene();
    TutorialScene = createScene("TutorialScene", "Images/scene/TutorialScene.png");
    MarketScene = createScene("MarketScene", "Images/scene/MarketScene.png");
    BurgerScene = createScene("BurgerScene", "Images/scene/BurgerScene.png");
    EndScene = createScene("EndScene", "Images/scene/EndScene.png");

    // object 생성
    // 아직 이미지, 위치 지정 안함
    tutorialButton = createObject("tutorialButton", "Images/button/tutorialButton.png", StartScene, 150, 0);
    startButton = createObject("startButton", "Images/button/startButton.png", StartScene, 850, 0);
    closeButton = createObject("closeButton", "Images/button/closeButton.png", TutorialScene, 1000, 450);
    completeButton = createObject("completeButton", "Images/button/completeButton.png", MarketScene, 900, -80);
    checkButton = createObject("checkButton", "Images/button/checkButton.png", BurgerScene, 1000, 200);
    endButton = createObject("endButton", "Images/button/endButton.png", EndScene, 0, 0);


    setMarketIngredients();
    setUserIngredients();

    startGame(StartScene);
}