/* Disable warning for scanf unsafe ONLY for visual studio */
/*#pragma warning(disable : 4996)
#pragma warning(disable : 6031)*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

typedef enum
{
	FALSE, TRUE
}BOOLEAN;

// **************** Implementation of Stack for the operators **************** //
typedef struct
{
	char item[SIZE];
	int top;
}OprStack;

void opr_push(OprStack* sp, char value)
{
	if (sp->top == SIZE - 1)
	{
		printf("Stack Overflow\n");
		return;
	}

	sp->item[++sp->top] = value;
}

char opr_pop(OprStack* sp)
{
	if (sp->top == -1)
	{
		printf("Stack Underflow\n");
		return '\0';
	}

	int value = sp->item[sp->top--];
	
	return value;
}
// **************** End of stack implementation for operators **************** //

/*
	prcd (op, '(' ) = FALSE
	prcd ('(', op ) = FALSE,
	prcd(op, ')') = TRUE,  except op = '('
	prcd('(', ')') = FALSE, we should push, however instead of PUSH we will pop
	prcd('/', '')

	READ $ == ^ (raised to power)
*/

BOOLEAN prcd(char left, char right)
{
	if (left == '(' || right == '(')
		return FALSE;
	if (right == ')')
		return TRUE;

	if (left == '*' || left == '/')
	{
		if (right == '*' || right == '/' || right == '+' || right == '-')
			return TRUE;
		else
			return FALSE;
	}

	if (left == '+' || left == '-')
	{
		if (right == '+' || right == '-')
			return TRUE;
		else
			return FALSE;
	}

	if (left == '$' && right == '$')
	{
		return FALSE;
	}
	else if (left == '$' && right != '$')
	{
		return TRUE;
	}
	else if (left != '$' && right == '$')
		return FALSE;
}

/*
   conversion: converts the supplied infix string to postfix string and assigns that
   postfix string to the postfix array supplied as parameter

*/
void convert(char infix[], char postfix[])
{
	OprStack stack;
	stack.top = -1;  // empty stack
	int i = 0, j = 0;
	
	while (infix[i] != '\0')
	{
		char next = infix[i];
		if (next >= '0' && next <= '9')
		{
			postfix[j++] = infix[i];
		}
		else if (next == '+' || next == '-' || next == '/' || next == '*' || next == '$' || next == '(' || next == ')')
		{
			/* While not empty stack and prcd. of stacktop is higher than next then pop and append */
			/* If while fails push otherwise pop */
			while (stack.top != -1 && prcd(stack.item[stack.top], next))
			{
				/* pop the stack and append the topsymbol to the postfix string */
				postfix[j++] = opr_pop(&stack);
			}
			
			if(next == '$')
				opr_push(&stack, next);
			
			if (next != ')')
				opr_push(&stack, next);
			else
				opr_pop(&stack);
		}
		else
		{
			printf("Invalid symbol %c encountered, terminating the program\n", next);
			exit(0);
		}

		++i;
	}

	while (stack.top != -1)
	{
		postfix[j++] = opr_pop(&stack);
	}
	
	postfix[j] = '\0';  // end of the string with null character
}

int main(int argc, char const* argv[])
{
	char postfix[SIZE], infix[SIZE];
	printf("Input infix string: ");

	scanf("%s", infix);
	convert(infix, postfix);
	printf("Postfix string: %s\n", postfix);
	
	return 0;
}