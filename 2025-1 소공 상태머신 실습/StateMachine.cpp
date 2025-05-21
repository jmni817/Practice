/*
계산기 state machine 프로그램 작성하기

주어진 자동판매기 state machine 코드를 이용해서 수업 시간에 연습한 계산기 state machine 프로그램을 C++ 언어로 작성하시오. 
단, 각 transition에 action 함수는 하나만 있고 파라미터는 없도록 코드를 수정함.
•각 action 함수가 다음과 같이 출력하도록 작성함.

A) displayInputValue)
> 입력된 값이 출력되었습니다.

B) overwriteOperator)
> 입력된 연산자가 이전 연산자를 대체했습니다.

C) displayResult)
> 연산결과가 출력되었습니다.

D) eraseAllDisplayDigit)
> 이전 연산결과를 지우고 입력된 값이 출력되었습니다.


계산기 state machine

﻿﻿계산기 동작 조건
﻿﻿- 사칙 연산만 지원함
﻿﻿- 피연산자는 2개이며 0과 자연수만 입력된다고 가정함
﻿﻿- 초기 값은 0이며 이미 첫번째 피연산자에 해당된다고 가정함
﻿﻿- 연산자가 입력된 상태에서 다른 연산자가 입력되면 기존 입력된 연산자를 덮어쓴다고 가정함
- 연산결과가 출력된 화면에서 숫자를 입력하면 새로운 연산이 시작된다고 가정함
﻿﻿- 1에서 9까지의 숫자가 나오기 전의 모든 ‘0' 값은 무시됨 
   예) 000234는 234로 간주됨. 단, 0만 반복된 경우는 0으로 간주됨.
 */
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
	int i;
	Event curEvent;		// 현재 이벤트

	curState = STATE_OPERAND1;				// 상태 초기화	
    while (true)		// 반복 수행함
	{ 
		curEvent = getNextEvent();		// 다음 이벤트를 입력받음
		
        for (i = 0; i < NUMBER_OF_TABLE_ENTRIES; i++)   // 테이블에 정의된 전각체 행(transition 내용)에 대해 비교함
		{ 
			if (curState == table[i].curState)			// 현재 상태와 일치하는지 검사
			{ 
				if (curEvent == table[i].event)			// 입력된 현재 이벤트와 일치하는지 검사
				{
					// 해당 transition이 발생할 때 수행해야 할 action 함수 실행시킴			
					(this->*table[i].action)();
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
	cout << "1. Input operand" << endl;
	cout << "2. Input operator" << endl;
	cout << "3. Input '=' " << endl;
	cout << "Select an event # : ";

	// 사용자로부터 이벤트 입력받음
	cin >> inputEvent;

	// 입력 값에 따라 반환할 이벤트 값을 결정함
	switch (inputEvent)
	{
	case 1:
		selectedEvent = EVENT_INPUT_OPERAND;
		break;
	case 2:
		selectedEvent = EVENT_INPUT_OPERATOR;
		break;
	case 3:
		selectedEvent = EVENT_INPUT_EQUAL;
	}

	return selectedEvent;
}



/*
	
	기능	  : LED 화면에 현재 입력된 숫자를 표시함
	반환값    : 없음
*/
void StateMachine::displayInputValue()
{
	cout << "A) displayInputValue)\n> 입력된 값이 출력되었습니다.";
}



/*
	
	기능	  : 연산자 덮어쓰기
	반환값    : 없음
*/
void StateMachine::overwriteOperator()
{
	cout << "B) overwriteOperator)\n> 입력된 연산자가 이전 연산자를 대체했습니다.";
}



/*
	
	기능	  : 연산 결과 출력
	반환값    : 없음
*/
void StateMachine::displayResult()
{
	cout << "C) displayResult)\n> 연산결과가 출력되었습니다.";
}



/*
	
	기능	  : 모든 연산 내용을 삭제.  
	반환값    : 없음
*/
void StateMachine::eraseAllDisplayDigit()
{
	cout << "D) eraseAllDisplayDigit)\n> 이전 결과를 지우고 새로운 입력을 받습니다.";
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
	case STATE_OPERAND1:
		returnedString = "STATE_OPERAND1";
		break;
	case STATE_OPERATOR:
		returnedString = "STATE_OPERATOR";
		break;
	case STATE_OPERAND2:
		returnedString = "STATE_OPERAND2";
		break;
	case STATE_RESULT:
		returnedString = "STATE_RESULT"; 
	}

	return returnedString;
}
