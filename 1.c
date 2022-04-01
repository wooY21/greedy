#include <stdio.h>
int main()
{
		int firstNum, secondNum, thirdNum;
		printf("두 수를 입력 : ");
		scanf("%d %d", &firstNum, &secondNum);
		thirdNum = firstNum++ && secondNum++;

		printf("출력전 예상 결과\n firstnum = %d  , secondNum = %d , thirdNum = %d\n",firstNum,secondNum,firstNum && secondNum);
		printf(" 결과 = \n firstnum = %d , secondNum = %d, thirdNum = %d", firstNum, secondNum, thirdNum);
		return 0;
}