#define _CRT_SECURE_NO_WARNINGS

#include <bangtal.h>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include <algorithm>
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
ObjectID dayObject;
ObjectID successObj;
ObjectID failObj;
ObjectID obj_chosenIngredient[7];

// 함수 목록
void mouseCallback(ObjectID, int, int, MouseAction);
ObjectID createObject(const char*, const char*, SceneID, int, int);
void setStock(SceneID);
void showChosenIngredient(string, int, int);

// 클래스
class Ingredient {
private:
    string name;
    int price;
public:
    ObjectID obj_marketIngredient;
    ObjectID obj_userIngredient;
    void setIngredientInfo(string name, int price) {
        this->name = name;
        this->price = price;
    }

    string getName() {
        return name;
    }

    int getPrice() {
        return price;
    }
};
Ingredient ingredient[13];

void setIngredients() {
    ingredient[0].setIngredientInfo("bread", 500);
    ingredient[1].setIngredientInfo("bulgogiPatty", 1000);
    ingredient[2].setIngredientInfo("chicken", 1000);
    ingredient[3].setIngredientInfo("crabMeat", 2000);
    ingredient[4].setIngredientInfo("cow", 10000);
    ingredient[5].setIngredientInfo("tomato", 500);
    ingredient[6].setIngredientInfo("cabbage", 500);
    ingredient[7].setIngredientInfo("slicedCheese", 500);
    ingredient[8].setIngredientInfo("potato", 500);
    ingredient[9].setIngredientInfo("oil", 500);
    ingredient[10].setIngredientInfo("stringCheese", 500);
    ingredient[11].setIngredientInfo("coke", 1000);
    ingredient[12].setIngredientInfo("soda", 1000);
}

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
    string getName() { return name; }
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
    void updateCustomer() {
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
    bool allCheckIngredient(vector<Ingredient> chosenIngredient) {///choosenIngredient 클릭함수에서 구현 후 해야함
        if (myBurger.checkIngredient(chosenIngredient) && mySide.checkIngredient(chosenIngredient) && myDrink.checkIngredient(chosenIngredient)) {
            return true;
        }
        else
            return false;
        if (customer_order % 2 == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    //손님 랜덤 이미지
    void chooseCustomer() {
        int random = rand() % 21;
        char buff[30];
        sprintf(buff, "Images/customer/%d.png", random);
        char id = (char)random;
        obj_Customer = createObject(&id, buff, BurgerScene, 860, 305);
        scaleObject(obj_Customer, 0.50f);
    }

    //손님 옆에 메뉴 띄우기
    void showCustomerMenu() {
        string imagePath;

        //버거
        imagePath = "Images/menu/" + myBurger.getName() + ".png";
        myBurger.obj = createObject("burger", imagePath.c_str(), BurgerScene, 460, 530);
        scaleObject(myBurger.obj, 0.3f);

        //사이드
        imagePath = "";
        imagePath = "Images/menu/" + mySide.getName() + ".png";
        mySide.obj = createObject("side", imagePath.c_str(), BurgerScene, 620, 530);
        scaleObject(mySide.obj, 0.3f);

        //음료
        imagePath = "";
        imagePath = "Images/menu/" + myDrink.getName() + ".png";
        myDrink.obj = createObject("drink", imagePath.c_str(), BurgerScene, 760, 530);
        scaleObject(myDrink.obj, 0.3f);
    }

    void hideCustomerMenu() {
        hideObject(myBurger.obj);
        hideObject(mySide.obj);
        hideObject(myDrink.obj);
    }

    void hideCustomer() {
        hideObject(obj_Customer);
    }
    ObjectID obj_Customer;
};

class User {
private:
    map<string, int> ingredientSet;
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

    // 재료 개수 감소 -------확인 필요
    void useIngredient(Ingredient& ingredient) {
        string ingredientName = ingredient.getName();
        ingredientSet[ingredientName]--;
    }

    // 마켓에서 산 재료를 재료 목록에 추가
    void updateIngredients(Ingredient& ingredient) {
        string ingredientName = ingredient.getName();
        ingredientSet[ingredientName]++;
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

    int getMoney() {
        return myMoney;
    }

    //재고 수량 반환하기
    int getIngredientAmount(Ingredient& ingredient) {
        return ingredientSet.at(ingredient.getName());
    }
    ObjectID obj_ingredientStock[13];
};
User user;


class Market {
public:
    Market() {
    }

    bool chooseIngredients(ObjectID object) {
        for (int i = 0; i < 13; i++) {
            if (object == ingredient[i].obj_marketIngredient) { // market scene에서 구매할 물품을 선택했을 떄
                if (user.getMoney() >= ingredient[i].getPrice()) { // 유저가 해당 ingredient를 살 돈이 충분한 경우
                    user.useMoney(ingredient[i].getPrice());
                    user.updateIngredients(ingredient[i]);
                    return true;
                }
                else {
                    // 유저가 해당 ingredient를 살 돈이 충분하지 않은 경우
                    // 살 수 없음
                    return false;
                }
            }
        }
    }
};


// 이부분 전역변수 
Customer customer[4]; // 5일마다 각 4명, 날 바뀔 때마다 초기화해서 재사용
Market market;
vector<ObjectID> moneyNum;

void showMoney(int myMoney, SceneID sceneName) {
    string money = to_string(myMoney); //int형의 myMoney를 string형으로 변환
    reverse(money.begin(), money.end()); //money를 뒤집기

    moneyNum.resize(money.length());

    //MarketScene과 BurgerScene에서
    if (sceneName == MarketScene || sceneName == BurgerScene) {
        /*moneyNum[0] = createObject("0", "Images/money/0.png", sceneName, 300, 30);
        scaleObject(moneyNum[0], 0.05f);
        moneyNum[1] = createObject("0", "Images/money/0.png", sceneName, 270, 30);
        scaleObject(moneyNum[1], 0.05f);*/

        for (int i = 0; i < money.length(); i++) {
            switch (money[i]) {
            case '0':
                moneyNum[i] = createObject("0", "Images/money/0.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '1':
                moneyNum[i] = createObject("1", "Images/money/1.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '2':
                moneyNum[i] = createObject("2", "Images/money/2.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '3':
                moneyNum[i] = createObject("3", "Images/money/3.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '4':
                moneyNum[i] = createObject("4", "Images/money/4.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '5':
                moneyNum[i] = createObject("5", "Images/money/5.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '6':
                moneyNum[i] = createObject("6", "Images/money/6.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '7':
                moneyNum[i] = createObject("7", "Images/money/7.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '8':
                moneyNum[i] = createObject("8", "Images/money/8.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            case '9':
                moneyNum[i] = createObject("9", "Images/money/9.png", sceneName, 270 - 30 * (i - 1), 30);
                scaleObject(moneyNum[i], 0.05f);
                break;
            default:
                break;
            }
        }
    }
    //EndScene에서 최종 돈 띄우기
    else if (sceneName == EndScene) {
        for (int i = 0; i < money.length(); i++) {
            switch (money[i]) {
            case '0':
                moneyNum[i] = createObject("0", "Images/money/0.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '1':
                moneyNum[i] = createObject("1", "Images/money/1.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '2':
                moneyNum[i] = createObject("2", "Images/money/2.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '3':
                moneyNum[i] = createObject("3", "Images/money/3.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '4':
                moneyNum[i] = createObject("4", "Images/money/4.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '5':
                moneyNum[i] = createObject("5", "Images/money/5.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '6':
                moneyNum[i] = createObject("6", "Images/money/6.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '7':
                moneyNum[i] = createObject("7", "Images/money/7.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '8':
                moneyNum[i] = createObject("8", "Images/money/8.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            case '9':
                moneyNum[i] = createObject("9", "Images/money/9.png", sceneName, 695 - 55 * (i - 1), 378);
                scaleObject(moneyNum[i], 0.08f);
                break;
            default:
                break;
            }
        }
    }
}


void showDay(int day, SceneID sceneName) {
    string imagePath;
    imagePath = "Images/day/day" + to_string(day) + ".png";
    dayObject = createObject("day", imagePath.c_str(), sceneName, 132, 601);
    scaleObject(dayObject, 0.13f);
}

vector<Ingredient> chosenIngredient; //선택한 재료들의 이름을 넣는 벡터
int ingredientNum[3]; //선택한 ingredient의 개수

// 함수 구현
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

    scaleObject(successObj, 0.10f); hideObject(successObj);
    scaleObject(failObj, 0.10f);    hideObject(failObj);

    if (object == tutorialButton) { // 튜토리얼 버튼을 누르면
        enterScene(TutorialScene); // 튜토리얼 scene으로 이동
    }
    if (object == startButton) { // 시작 버튼을 누르면
        enterScene(MarketScene); // 구매 scene으로 이동
        showMoney(user.getMoney(), MarketScene);
        showDay(day, MarketScene);
        setStock(MarketScene);
    }
    if (object == closeButton) { // 튜토리얼을 다 읽고 닫기 버튼을 누르면
        enterScene(StartScene); // 시작 scene으로 이동
    }
    if (object == completeButton) { // 구매를 마친 후 완료 버튼을 누르면

        //new day        
        for (int i = 0; i < moneyNum.size(); i++)  hideObject(moneyNum[i]);
        customer[customer_order - 1].chooseCustomer();  //고객 obj+이미지 생성
        scaleObject(customer[customer_order - 1].obj_Customer, 0.45f);

        customer[customer_order - 1].updateCustomer(); //랜덤으로 손님 메뉴 설정
        customer[customer_order - 1].showCustomerMenu(); //손님 옆에 메뉴 사진 띄우기

        enterScene(BurgerScene); // 판매 scene으로 이동
        showMoney(user.getMoney(), BurgerScene);
        if (day == 0) day++;
        hideObject(dayObject);
        showDay(day, BurgerScene);
        for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
        setStock(BurgerScene);
    }

    /*
    //버거씬에서 내 재료 누를 때
    for (int i = 0; i < 13; i++) {
        if (object == ingredient[i].obj_userIngredient) {
            if (user.getIngredientAmount(ingredient[i]) > 0) {  //재료의 개수가 0보다 클 때만
                chosenIngredient.push_back(ingredient[i]);
                showChosenIngredient(ingredient[i].getName());
                user.useIngredient(ingredient[i]);  //user에 있는 map에서 재료 개수 감소
                for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
                showMoney(user.getMoney(), BurgerScene);
                for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
                setStock(BurgerScene);
            }
        }
    }
    */

    if (object == successObj || object == failObj) {
        hideObject(object);
        if (object == successObj) {

            for (int i = 0; i < moneyNum.size(); i++)  hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
        }

    }
    if (object == checkButton) { // 각 손님에게 메뉴를 제공하기 위해 체크 버튼을 누르면
        chosenIngredient.clear(); //선택한 ingredient를 저장하는 벡터 초기화
        ingredientNum[0] = 0; //선택한 ingredient의 개수를 저장하는 배열 초기화
        ingredientNum[1] = 0;
        ingredientNum[2] = 0;

        //재고 바에서 선택한 객체들을 모아서 벡터로 만들고 그걸 보내야 해
        if (customer[customer_order - 1].allCheckIngredient(chosenIngredient)) {    //제작 성공-> success 띄우고 money update
            user.earnMoney(customer[customer_order - 1].getTotalPrice());
            showObject(successObj);
            //이거 누르면 없어지고, 돈 올라감

        }
        else {
            showObject(failObj);
            //이 obj 누르면 없어지는걸로
        }
        if (customer_order < 4) {
            customer[customer_order - 1].hideCustomerMenu();  //이전 손님 메뉴 삭제
            customer[customer_order - 1].hideCustomer(); //이전 손님 삭제
            customer_order += 1;                                    // 손님배열 증가 -> 굳이 왜 배열로?
            customer[customer_order - 1].chooseCustomer();  //다음 고객 obj+이미지 생성
            scaleObject(customer[customer_order - 1].obj_Customer, 0.45f);

            for (int i = 0; i < 7; i++)  hideObject(obj_chosenIngredient[i]);

            customer[customer_order - 1].updateCustomer(); //랜덤으로 손님 메뉴 설정
            customer[customer_order - 1].showCustomerMenu(); //손님 옆에 메뉴 사진 띄우기

        }

        else if (customer_order == 4) { // 마지막 손님이면
            customer[customer_order - 1].hideCustomerMenu();//이전 손님 메뉴 삭제
            customer[customer_order - 1].hideCustomer(); //이전 손님 삭제
            hideObject(dayObject);
            if (day < 5) { // 마지막 날이 아니면
                customer_order = 1;
                day++; // 해당 날이 끝나고 다음 날로 바꿈
                enterScene(MarketScene); // 구매 scene으로 이동
                for (int i = 0; i < moneyNum.size(); i++)  hideObject(moneyNum[i]);
                showMoney(user.getMoney(), MarketScene);
                showDay(day, MarketScene);
                for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
                setStock(MarketScene);
            }
            else { // 마지막 날이면
                enterScene(EndScene);
                showMoney(user.getMoney(), EndScene); //최종 돈 띄우기
            }
        }
    }

    if (object == endButton) { // 종료 버튼을 누르면
        endGame(); // 게임 종료
    }
    if (market.chooseIngredients(object) == true) {
        // 마켓의 ingredients를 클릭한 경우
        for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
        showMoney(user.getMoney(), MarketScene);
        for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
        setStock(MarketScene);
    }

    //ingredient를 선택한 경우
    if (object == ingredient[0].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[0]) > 0) {
            chosenIngredient.push_back(ingredient[0]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[0].getName(), 0, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[1].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[1]) > 0) {
            chosenIngredient.push_back(ingredient[1]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[1].getName(), 1, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[2].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[2]) > 0) {
            chosenIngredient.push_back(ingredient[2]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[2].getName(), 2, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[3].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[3]) > 0) {
            chosenIngredient.push_back(ingredient[3]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[3].getName(), 3, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[4].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[4]) > 0) {
            chosenIngredient.push_back(ingredient[4]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[4].getName(), 4, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[5].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[5]) > 0) {
            chosenIngredient.push_back(ingredient[0]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[5].getName(), 5, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[6].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[6]) > 0) {
            chosenIngredient.push_back(ingredient[6]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[6].getName(), 6, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[7].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[7]) > 0) {
            chosenIngredient.push_back(ingredient[7]);
            ingredientNum[0]++;
            showChosenIngredient(ingredient[7].getName(), 7, ingredientNum[0]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[8].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[8]) > 0) {
            chosenIngredient.push_back(ingredient[8]);
            ingredientNum[1]++;
            showChosenIngredient(ingredient[8].getName(), 8, ingredientNum[1]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[9].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[9]) > 0) {
            chosenIngredient.push_back(ingredient[9]);
            ingredientNum[1]++;
            showChosenIngredient(ingredient[9].getName(), 9, ingredientNum[1]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[10].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[10]) > 0) {
            chosenIngredient.push_back(ingredient[10]);
            ingredientNum[1]++;
            showChosenIngredient(ingredient[10].getName(), 10, ingredientNum[1]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[11].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[11]) > 0) {
            chosenIngredient.push_back(ingredient[11]);
            ingredientNum[2]++;
            showChosenIngredient(ingredient[11].getName(), 11, ingredientNum[2]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
    if (object == ingredient[12].obj_userIngredient) {
        if (user.getIngredientAmount(ingredient[12]) > 0) {
            chosenIngredient.push_back(ingredient[12]);
            ingredientNum[2]++;
            showChosenIngredient(ingredient[12].getName(), 12, ingredientNum[2]);
            for (int i = 0; i < moneyNum.size(); i++) hideObject(moneyNum[i]);
            showMoney(user.getMoney(), BurgerScene);
            for (int i = 0; i < 13; i++) hideObject(user.obj_ingredientStock[i]);
            setStock(BurgerScene);
        }
    }
}

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y) {
    // object 선언 함수
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y); // 해당 위치에 object를 위치시킴
    showObject(object); // object를 보이게 함

    return object;
}

void setMarketIngredients() {
    //가격띄우기
    ingredient[0].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 550, 560);
    scaleObject(ingredient[0].obj_marketIngredient, 0.15f);
    ingredient[1].obj_marketIngredient = createObject("1000", "Images/price/1000.png", MarketScene, 555, 425);
    scaleObject(ingredient[1].obj_marketIngredient, 0.15f);
    ingredient[2].obj_marketIngredient = createObject("1000", "Images/price/1000.png", MarketScene, 555, 285);
    scaleObject(ingredient[2].obj_marketIngredient, 0.15f);
    ingredient[3].obj_marketIngredient = createObject("2000", "Images/price/2000.png", MarketScene, 558, 145);
    scaleObject(ingredient[3].obj_marketIngredient, 0.15f);
    ingredient[4].obj_marketIngredient = createObject("10000", "Images/price/10000.png", MarketScene, 570, 6);
    scaleObject(ingredient[4].obj_marketIngredient, 0.15f);
    ingredient[5].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 830, 560);
    scaleObject(ingredient[5].obj_marketIngredient, 0.15f);
    ingredient[6].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 830, 425);
    scaleObject(ingredient[6].obj_marketIngredient, 0.15f);
    ingredient[7].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 830, 285);
    scaleObject(ingredient[7].obj_marketIngredient, 0.15f);
    ingredient[8].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 830, 145);
    scaleObject(ingredient[8].obj_marketIngredient, 0.15f);
    ingredient[9].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 1110, 560);
    scaleObject(ingredient[9].obj_marketIngredient, 0.15f);
    ingredient[10].obj_marketIngredient = createObject("500", "Images/price/500.png", MarketScene, 1110, 425);
    scaleObject(ingredient[10].obj_marketIngredient, 0.15f);
    ingredient[11].obj_marketIngredient = createObject("1000", "Images/price/1000.png", MarketScene, 1115, 285);
    scaleObject(ingredient[11].obj_marketIngredient, 0.15f);
    ingredient[12].obj_marketIngredient = createObject("1000", "Images/price/1000.png", MarketScene, 1118, 145);
    scaleObject(ingredient[12].obj_marketIngredient, 0.15f);

    //재료 띄우기
    ingredient[0].obj_marketIngredient = createObject("bread", "Images/ingredient/bread.png", MarketScene, 440, 580);
    scaleObject(ingredient[0].obj_marketIngredient, 0.28f);
    ingredient[1].obj_marketIngredient = createObject("bulgogiPatty", "Images/ingredient/bulgogiPatty.png", MarketScene, 440, 440);
    scaleObject(ingredient[1].obj_marketIngredient, 0.28f);
    ingredient[2].obj_marketIngredient = createObject("chicken", "Images/ingredient/chicken.png", MarketScene, 435, 295);
    scaleObject(ingredient[2].obj_marketIngredient, 0.28f);
    ingredient[3].obj_marketIngredient = createObject("crabMeat", "Images/ingredient/crabMeat.png", MarketScene, 440, 165);
    scaleObject(ingredient[3].obj_marketIngredient, 0.28f);
    ingredient[4].obj_marketIngredient = createObject("cow", "Images/ingredient/cow.png", MarketScene, 440, 20);
    scaleObject(ingredient[4].obj_marketIngredient, 0.28f);
    ingredient[5].obj_marketIngredient = createObject("tomato", "Images/ingredient/tomato.png", MarketScene, 720, 573);
    scaleObject(ingredient[5].obj_marketIngredient, 0.28f);
    ingredient[6].obj_marketIngredient = createObject("cabbage", "Images/ingredient/cabbage.png", MarketScene, 720, 440);
    scaleObject(ingredient[6].obj_marketIngredient, 0.28f);
    ingredient[7].obj_marketIngredient = createObject("slicedCheese", "Images/ingredient/slicedCheese.png", MarketScene, 720, 295);
    scaleObject(ingredient[7].obj_marketIngredient, 0.28f);
    ingredient[8].obj_marketIngredient = createObject("potato", "Images/ingredient/potato.png", MarketScene, 720, 165);
    scaleObject(ingredient[8].obj_marketIngredient, 0.28f);
    ingredient[9].obj_marketIngredient = createObject("oil", "Images/ingredient/oil.png", MarketScene, 1000, 580);
    scaleObject(ingredient[9].obj_marketIngredient, 0.28f);
    ingredient[10].obj_marketIngredient = createObject("stringCheese", "Images/ingredient/stringCheese.png", MarketScene, 1000, 440);
    scaleObject(ingredient[10].obj_marketIngredient, 0.28f);
    ingredient[11].obj_marketIngredient = createObject("coke", "Images/ingredient/coke.png", MarketScene, 1000, 295);
    scaleObject(ingredient[11].obj_marketIngredient, 0.28f);
    ingredient[12].obj_marketIngredient = createObject("soda", "Images/ingredient/soda.png", MarketScene, 1000, 165);
    scaleObject(ingredient[12].obj_marketIngredient, 0.28f);
}

void setUserIngredientsAt(SceneID scene) {
    ingredient[0].obj_userIngredient = createObject("bread", "Images/ingredient/bread.png", scene, 40, 530);
    scaleObject(ingredient[0].obj_userIngredient, 0.18f);
    ingredient[1].obj_userIngredient = createObject("bulgogiPatty", "Images/ingredient/bulgogiPatty.png", scene, 40, 440);
    scaleObject(ingredient[1].obj_userIngredient, 0.18f);
    ingredient[2].obj_userIngredient = createObject("chicken", "Images/ingredient/chicken.png", scene, 40, 345);
    scaleObject(ingredient[2].obj_userIngredient, 0.18f);
    ingredient[3].obj_userIngredient = createObject("crabMeat", "Images/ingredient/crabMeat.png", scene, 40, 275);
    scaleObject(ingredient[3].obj_userIngredient, 0.18f);
    ingredient[4].obj_userIngredient = createObject("cow", "Images/ingredient/cow.png", scene, 40, 195);
    scaleObject(ingredient[4].obj_userIngredient, 0.18f);
    ingredient[5].obj_userIngredient = createObject("tomato", "Images/ingredient/tomato.png", scene, 40, 105);
    scaleObject(ingredient[5].obj_userIngredient, 0.18f);
    ingredient[6].obj_userIngredient = createObject("cabbage", "Images/ingredient/cabbage.png", scene, 210, 530);
    scaleObject(ingredient[6].obj_userIngredient, 0.18f);
    ingredient[7].obj_userIngredient = createObject("slicedCheese", "Images/ingredient/slicedCheese.png", scene, 215, 440);
    scaleObject(ingredient[7].obj_userIngredient, 0.18f);
    ingredient[8].obj_userIngredient = createObject("potato", "Images/ingredient/potato.png", scene, 220, 345);
    scaleObject(ingredient[8].obj_userIngredient, 0.18f);
    ingredient[9].obj_userIngredient = createObject("oil", "Images/ingredient/oil.png", scene, 210, 275);
    scaleObject(ingredient[9].obj_userIngredient, 0.18f);
    ingredient[10].obj_userIngredient = createObject("stringCheese", "Images/ingredient/stringCheese.png", scene, 210, 195);
    scaleObject(ingredient[10].obj_userIngredient, 0.18f);
    ingredient[11].obj_userIngredient = createObject("coke", "Images/ingredient/coke.png", scene, 175, 110);
    scaleObject(ingredient[11].obj_userIngredient, 0.18f);
    ingredient[12].obj_userIngredient = createObject("soda", "Images/ingredient/soda.png", scene, 270, 110);
    scaleObject(ingredient[12].obj_userIngredient, 0.18f);
}

//사이드바에 stock 띄우기
void setStock(SceneID scene) {
    int pos[13][2] = { {135,540}, {135,453}, {135,363},
        {135,285}, {130,198}, {125,115}, {300,540}, {300,455},
        {300,370}, {300,290}, {300,205}, {230,125}, {325,125} };

    for (int i = 0; i < 13; i++) {
        switch (user.getIngredientAmount(ingredient[i])) {
        case 0:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/0.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 1:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/1.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 2:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/2.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 3:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/3.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 4:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/4.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 5:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/5.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 6:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/6.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 7:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/7.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 8:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/8.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        case 9:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/9.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        default:
            user.obj_ingredientStock[i] = createObject("stock", "Images/stock/many.png", scene, pos[i][0], pos[i][1]);
            scaleObject(user.obj_ingredientStock[i], 0.05f);
            break;
        }
    }
}

void showChosenIngredient(string ingredientName, int index, int num) {
    string imagePath;
    imagePath = "Images/ingredient/" + ingredientName + ".png";
    if (index >= 0 && index <= 7) { //햄버거 재료를 선택할 경우
        switch (num) {
        case 1:
            obj_chosenIngredient[0] = createObject("choose", imagePath.c_str(), BurgerScene, 680, 180);
            scaleObject(obj_chosenIngredient[0], 0.22f);
            user.useIngredient(ingredient[index]);  //user에 있는 map에서 재료 개수 감소
            break;
        case 2:
            obj_chosenIngredient[1] = createObject("choose", imagePath.c_str(), BurgerScene, 900, 180);
            scaleObject(obj_chosenIngredient[1], 0.22f);
            user.useIngredient(ingredient[index]);
            break;
        case 3:
            obj_chosenIngredient[2] = createObject("choose", imagePath.c_str(), BurgerScene, 680, 53);
            scaleObject(obj_chosenIngredient[2], 0.22f);
            user.useIngredient(ingredient[index]);
            break;
        case 4:
            obj_chosenIngredient[3] = createObject("choose", imagePath.c_str(), BurgerScene, 900, 53);
            scaleObject(obj_chosenIngredient[3], 0.22f);
            user.useIngredient(ingredient[index]);
            break;
        default:
            chosenIngredient.pop_back();
            break;
        }
    }
    else if (8 <= index && index <= 10) { //사이드 재료를 선택할 경우
        switch (num) {
        case 1:
            obj_chosenIngredient[4] = createObject("choose", imagePath.c_str(), BurgerScene, 463, 178);
            scaleObject(obj_chosenIngredient[4], 0.22f);
            user.useIngredient(ingredient[index]);
            break;
        case 2:
            obj_chosenIngredient[5] = createObject("choose", imagePath.c_str(), BurgerScene, 463, 55);
            scaleObject(obj_chosenIngredient[5], 0.22f);
            user.useIngredient(ingredient[index]);
            break;
        default:
            chosenIngredient.pop_back();
            break;
        }
    }
    else if (11 <= index && index <= 12) { //음료를 선택할 경우
        switch (num) {
        case 1:
            obj_chosenIngredient[6] = createObject("choose", imagePath.c_str(), BurgerScene, 1130, 115);
            scaleObject(obj_chosenIngredient[6], 0.22f);
            user.useIngredient(ingredient[index]);
            break;
        default:
            chosenIngredient.pop_back();
            break;
        }
    }
}

void setUserIngredients() {
    setUserIngredientsAt(MarketScene);
    //setStock(MarketScene);
    setUserIngredientsAt(BurgerScene);
    //setStock(BurgerScene);
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
    checkButton = createObject("checkButton", "Images/button/checkButton.png", BurgerScene, 1100, 300);
    scaleObject(checkButton, 0.5f);
    endButton = createObject("endButton", "Images/button/endButton.png", EndScene, 0, 0);

    successObj = createObject("successObj", "Images/result/success.png", BurgerScene, 1100, 550);
    failObj = createObject("failObj", "Images/result/fail.png", BurgerScene, 1100, 550);

    setIngredients();
    setMarketIngredients();
    setUserIngredients();

    user.setMoney(20000);

    startGame(StartScene);
}