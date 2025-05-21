#include <iostream>

#define NUMBER_OF_TABLE_ENTRIES 100     // event-action table의 현재 entry 갯수
#define MAX_NUMBER_OF_ACTIONS   3       // transition 시 실행되는 최대 action 갯수

using namespace std;


// State 열거형 정의
typedef enum {
    STATE_READY,
    STATE_100_INSERTED,
    STATE_200_INSERTED,
    STATE_END
} State;


// Event 열거형 정의
typedef enum {
    EVENT_INSERT_100,               //100원넣음
    EVENT_REFUND_BUTTON_PRESSED,    //반환ㅓ튼
    EVENT_BEVERAGE_BUTTON_PRESSED,  //음료버튼
    EVENT_QUIT                      
} Event;


// 음료 자동판매기를 위한 StateMachine 클래스 정의
class StateMachine
{
private:
    State curState;     // 현재 상태

    // event-action table structure 정의
    typedef struct {
        State curState;             // 현재 상태
        Event event;                // 사용자로부터 발생된 이벤트
        int number_of_actions;                                      // 해당 transition에 실행되는 action 함수의 갯수
        void (StateMachine::*action[MAX_NUMBER_OF_ACTIONS])(int);   // action 함수 포인터(type pointer)의 배열      //주소값을 몇개까지 저장할수있게할건지
       int action_parameter[MAX_NUMBER_OF_ACTIONS];                 // action 함수의 매개변수 배열                  //같은수로 파라미터 할당하도록
        State nextState;            // transition 후에 변경될 다음 상태
    } EventActionTable;
       
    // vending machine에서 사용할 event-action table 초기화
    EventActionTable table[NUMBER_OF_TABLE_ENTRIES] {
        {STATE_READY,	        EVENT_INSERT_100,	           1,  {&StateMachine::displayInsertedMoney},	                                                        {100},       STATE_100_INSERTED},
        {STATE_100_INSERTED,	EVENT_INSERT_100,	           2,  {&StateMachine::displayInsertedMoney, &StateMachine::turnLight},	                                {200, 1},    STATE_200_INSERTED},
        {STATE_100_INSERTED,	EVENT_REFUND_BUTTON_PRESSED,   2,  {&StateMachine::displayInsertedMoney, &StateMachine::refundCoins},	                            {0, 100},    STATE_READY},
        {STATE_200_INSERTED,	EVENT_INSERT_100,	           1,  {&StateMachine::refundCoins},	                                                                {100},       STATE_200_INSERTED},
        {STATE_200_INSERTED,	EVENT_REFUND_BUTTON_PRESSED,   3,  {&StateMachine::displayInsertedMoney, &StateMachine::refundCoins, &StateMachine::turnLight},	    {0, 200, 0}, STATE_READY},
        {STATE_200_INSERTED,	EVENT_BEVERAGE_BUTTON_PRESSED, 3,  {&StateMachine::displayInsertedMoney, &StateMachine::turnLight, &StateMachine::releaseBeverage}, {0, 0, 0},   STATE_READY} 
    };

    void displayInsertedMoney(int displayedMoneyAmount); // LED 화면에 현재 투입된 금액을 표시함
    void refundCoins(int refundedMoneyAmount);           // 반환 버튼을 눌렀을 때 투입된 금액을 반환함
    void turnLight(int lightOn);                         // 음료 버튼에 조명을 켜거나 끄는 동작 수행함.  ->  on = 1,  off = 0;
    void releaseBeverage(int dummy);                     // 선택한 음료를 외부로 내보냄 -> dummy parameter 파라미터가 필요없어서 더미 넣음

    Event getNextEvent();       // 사용자로부터 다음 이벤트를 입력받음

    string getCurrentStateString();     // 현재 상태에 해당하는 문자열을 생성해서 반환함


public:
    void run();               // state machine 실행 
};






