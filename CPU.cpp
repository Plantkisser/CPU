#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
# define ERROR 535
# define CPCTY 1
# define STR 10
# define BREAK 134
# define PROC 1000
# define TEST 7
# define BZERO 64

typedef  double stktype;


# define CREATELOG(name);\
{\
	name = fopen(#name"log.txt", "a");\
}
# define UNITTEST(what, op, ref, type) \
{\
	type result = what;\
	type refcpy = ref;\
	if (result op refcpy)\
		printf (#what" [passed]\n");\
	else\
	{\
		printf (#what "is ");\
		print_##type(result);\
		printf ("but %s be ", result);\
		print_##type(refcpy);\
		printf("\n");\
	}\
}

	

#define CREATESTK( name ) \
	stack name;\
	name.kan1 = KAN;\
	name.kan2 = KAN;\
	name.size = 0;\
	name.capacity = CPCTY;\
	name.data = (stktype*) calloc (name.capacity + 2, sizeof(int));\
	name.data[0] = KAN;\
	name.data[name.capacity+1] = KAN;\
	if (name.data == NULL)\
	{\
		fprintf(stk, "Buy new processor\n");\
		return 0;\
	}
	

FILE* stk, *assemble;

struct stack
{
	int kan1;
	stktype *data;
	int size;
	int capacity;
	stktype ra;
	stktype rb;
	stktype rc;
	stktype rd;
	int kan2;
};

struct process
{
	char* posl;
	int sizem;
};


void print_int(int a)
{
	printf("%d ", a);
	return; 
}
void print_double(double a)
{
	printf("%lf ", a);
	return; 
}

#include "stack.cpp"


#define CMD_DEF(name, num, codec, codep)\
		CMD_##name = num,
		
		
enum commands
{ 
	
	#include "commands.h"	
};

#undef CMD_DEF

int create_code(int* code)
{
	int i = 0;
	FILE* f = fopen("code", "rb");
	if (f == NULL)
	{
		fprintf(assemble, "Cannot open file code\n");
		return ERROR;
	}
	
	fscanf(f, "%c", &code[i]);
	while (!feof(f))
	{
		i++;
		fscanf(f, "%c", &code[i]);
	}
	fclose(f);
	return 0;
}


int main()
{
	CREATELOG(assemble);
	CREATELOG(stk);
	CREATESTK(test)
	CREATESTK(recur)
	
	
	int* code = (int*) calloc(PROC, sizeof(int));
	int rez = create_code(code);
	if (rez == ERROR) 
	{
		fprintf(assemble, "Cannot create code arr\n");
		return 0;
	}
	
	
	int i = 0;
	stktype ap = 0;
	stktype bp = 0;
	int num = -1;
	int j = 0;
	int prov = 0;
	
	while (code[i] != CMD_END)
	{
		switch (code[i])
		{
		#define CMD_DEF(name, num, codec, codep)\
			case CMD_##name: codep
		#define CMD_JUMP(op)\
		ap = pop(&test);\
		bp = pop(&test);\
		i++;\
		num = 0;\
		j = 1;	\
		while (j <= code[i])\
		{\
			num = num * 256 + code[i + j];\
			j++;\
		}\
		if (ap op bp)\
		{\
			i = num - 1;\
		}\
		else\
			i += j - 1;\
		push_back(&test, bp);\
		push_back(&test, ap);\
		break;	
			
		#include "commands.h"
		#undef CMD_DEF
		}
		i++;
	}
	fclose(stk);
	fclose(assemble);
	free(code);
	return 0;
}
