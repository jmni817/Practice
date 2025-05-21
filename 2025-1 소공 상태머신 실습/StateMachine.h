#include <iostream>

#define NUMBER_OF_TABLE_ENTRIES 100     // event-action table의 현재 entry 갯수

using namespace std;


// State 열거형 정의
typedef enum {
    STATE_OPERAND1,
    STATE_OPERATOR,
    STATE_OPERAND2,
    STATE_RESULT
} State;


// Event 열거형 정의
typedef enum {
    EVENT_INPUT_OPERAND,    
    EVENT_INPUT_OPERATOR,    
    EVENT_INPUT_EQUAL                     
} Event;


// 자판기를 위한 StateMachine 클래스 정의
class StateMachine
{
private:
    State curState;     // 현재 상태

    // event-action table structure 정의
    typedef struct {
        State curState;             // 현재 상태
        Event event;                // 사용자로부터 발생된 이벤트
        void (StateMachine::*action)();   // action 함수 포인터     
        State nextState;            // transition 후에 변경될 다음 상태
    } EventActionTable;
       
    // vending machine에서 사용할 event-action table 초기화
    EventActionTable table[NUMBER_OF_TABLE_ENTRIES] {
        {STATE_OPERAND1,	EVENT_INPUT_OPERAND,	  &StateMachine::displayInputValue,     STATE_OPERAND1},
        {STATE_OPERAND1,	EVENT_INPUT_OPERATOR,	  &StateMachine::displayInputValue,	    STATE_OPERATOR},
        {STATE_OPERATOR,	EVENT_INPUT_OPERATOR,     &StateMachine::overwriteOperator,	    STATE_OPERATOR},
        {STATE_OPERATOR,	EVENT_INPUT_OPERAND,	  &StateMachine::displayInputValue,	    STATE_OPERAND2},
        {STATE_OPERAND2,	EVENT_INPUT_OPERAND,      &StateMachine::displayInputValue,     STATE_OPERAND2},
        {STATE_OPERAND2,	EVENT_INPUT_EQUAL,        &StateMachine::displayResult,         STATE_RESULT},
        {STATE_RESULT,  	EVENT_INPUT_OPERAND,      &StateMachine::eraseAllDisplayDigit,  STATE_OPERAND1}
    };

    void displayInputValue(); 
    void overwriteOperator();          
    void displayResult();                         
    void eraseAllDisplayDigit();       

    Event getNextEvent();       // 사용자로부터 다음 이벤트를 입력받음

    string getCurrentStateString();     // 현재 상태에 해당하는 문자열을 생성해서 반환함


public:
    void run();               // state machine 실행 
};






