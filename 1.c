#include <stdio.h>
int main()
{
		int firstNum, secondNum, thirdNum;
		printf("�� ���� �Է� : ");
		scanf("%d %d", &firstNum, &secondNum);
		thirdNum = firstNum++ && secondNum++;

		printf("����� ���� ���\n firstnum = %d  , secondNum = %d , thirdNum = %d\n",firstNum,secondNum,firstNum && secondNum);
		printf(" ��� = \n firstnum = %d , secondNum = %d, thirdNum = %d", firstNum, secondNum, thirdNum);
		return 0;
}