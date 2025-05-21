#include <string>
#include "StateMachine.h"


/*
	함수 이름 : StateMachine::run()
	기능	  : STATE_END 상태가 될 때까지 event-action 테이블에 정의된 규칙과 사용자에 의해 발생되는 이벤트에 따라 state machine을 동작시킴
	전달 인자 : 없음
	반환값    : 없음
*/
void StateMachine::run()
{
	int i, j;
	Event curEvent;		// 현재 이벤트

	curState = STATE_READY;				// 상태 초기화	//초기 상태는 ready
    while (curState != STATE_END)		// EVENT_QUIT이 입력될 때까지 반복 수행함
	{ 
		curEvent = getNextEvent();		// 다음 이벤트를 입력받음
		
        for (i = 0; i < NUMBER_OF_TABLE_ENTRIES; i++)   // 테이블에 정의된 전각체 행(transition 내용)에 대해 비교함
		{ 
			if (curState == table[i].curState)			// 현재 상태와 일치하는지 검사
			{ 
				if (curEvent == table[i].event)			// 입력된 현재 이벤트와 일치하는지 검사
				{
					// 해당 transition이 발생할 때 수행해야 할 action 함수들을 실행시킴
					for (j = 0; j < table[i].number_of_actions; j++)				
						(this->*table[i].action[j])(table[i].action_parameter[j]);

					curState = table[i].nextState;		// 테이블에 정의된 다음 상태로 현재 상태를 변경함
					break;
				}
			} 
		} 
		cout << endl << endl;
	}
}



/*
	함수 이름 : StateMachine::getNextEvent()
	기능	  : 사용자로부터 다음 이벤트를 입력받음
	전달 인자 : 없음
	반환값    : Event -> 입력받은 이벤트 값
*/
Event StateMachine::getNextEvent()
{
	Event selectedEvent;       // 반환할 이벤트
	int inputEvent;				// 사용자로부터 입력받은 이벤트

	// 입력 안내 메세지 출력
	cout << "[현재 상태 : " << getCurrentStateString() << "]" << endl;
	cout << "1. Deposit a 100 won coin" << endl;
	cout << "2. Press the refund button" << endl;
	cout << "3. Press the beverage button you want" << endl;
	cout << "4. Quit" << endl;
	cout << "Select an event # : ";

	// 사용자로부터 이벤트 입력받음
	cin >> inputEvent;

	// 입력 값에 따라 반환할 이벤트 값을 결정함
	switch (inputEvent)
	{
	case 1:
		selectedEvent = EVENT_INSERT_100;
		break;
	case 2:
		selectedEvent = EVENT_REFUND_BUTTON_PRESSED;
		break;
	case 3:
		selectedEvent = EVENT_BEVERAGE_BUTTON_PRESSED;
		break;
	case 4:		
	default : 
		selectedEvent = EVENT_QUIT;
		curState = STATE_END;
	}

	return selectedEvent;
}



/*
	함수 이름 : StateMachine::displayInsertedMoney()
	기능	  : LED 화면에 현재 투입된 금액을 표시함
	전달 인자 : displayedMoneyAmount -> 화면에 출력될 금액
	반환값    : 없음
*/
void StateMachine::displayInsertedMoney(int displayedMoneyAmount)
{
	cout << "현재 투입된 금액은 " << displayedMoneyAmount << "원입니다." << endl;
}



/*
	함수 이름 : StateMachine::refundCoins()
	기능	  : 반환 버튼을 눌렀을 때 투입된 금액을 반환함
	전달 인자 : refundedMoneyAmount -> 반환될 금액
	반환값    : 없음
*/
void StateMachine::refundCoins(int refundedMoneyAmount)
{
	cout << "반환되는 금액은 " << refundedMoneyAmount << "원입니다." << endl;
}



/*
	함수 이름 : StateMachine::turnLight()
	기능	  : 음료 버튼에 조명을 켜거나 끄는 동작 수행함.  
	전달 인자 : lightOn -> 1: on, 0: off
	반환값    : 없음
*/
void StateMachine::turnLight(int lightOn)
{
	if(lightOn == 1)
		cout << "음료 버튼의 조명이 켜졌습니다." << endl;
	else
		cout << "음료 버튼의 조명이 꺼졌습니다." << endl;
}



/*
	함수 이름 : StateMachine::releaseBeverage()
	기능	  : 선택한 음료를 외부로 내보냄.  
	전달 인자 : 매개변수는 필요 없지만 다른 함수와 매개변수를 맞추기 위해 동일하게 정의됨(dummy parameter)
	반환값    : 없음
*/
void StateMachine::releaseBeverage(int dummy)
{
	cout << "음료가 나왔습니다." << endl;
}


/*
	함수 이름 : StateMachine::getCurrentStateString()
	기능	  : 현재 상태에 해당하는 출력용 문자열을 생성해서 반환함
	전달 인자 : 없음
	반환값    : string -> 출력용 상태 문자열
*/
string StateMachine::getCurrentStateString()
{
	string returnedString;

	switch (curState)
	{
	case STATE_READY:
		returnedString = "STATE_READY";
		break;
	case STATE_100_INSERTED:
		returnedString = "STATE_100_INSERTED";
		break;
	case STATE_200_INSERTED:
		returnedString = "STATE_200_INSERTED";
	}

	return returnedString;
}
