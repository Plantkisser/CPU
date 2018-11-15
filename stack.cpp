# define CPCTY 1
# define KAN 1987
# define WERROR 365




/** compare canary with constant KAN
*/

int check_stack(stack* test)
{
	int i = 0;
	fprintf(stk, "Stack text\n{\n\tsize=%d\n\tcount=%d\n\tdata[%d]\n\t{\n", test->capacity, test->size, test->capacity);
	for (i = 1; i <= test->capacity; i++)
		fprintf(stk, "\t\t[%d] : %d\n", i, test->data[i]);
	fprintf(stk, "\t}\n}\n");
	if (test->data[0] != KAN)
	{
		return ERROR;
	}
	if (test->data[test->capacity + 1] != KAN)
	{
		return ERROR;
	}
	if (test->capacity <= test->size)
	{
		fprintf(stk, "capacity less then data pointer\n");
		return ERROR;
	}	
	return 0;
}

/** compare pointer with NULL
*/

int checkptr (stack * ptr)
{
	if (ptr == NULL)
	{
		printf("Pointer test is NULL"); //log
		return ERROR;
	}
	return 0;
}

/** increase size of stack by multiplying on 2
*/

int incrcapacity(stack *test)
{
	
	if (checkptr(test) == ERROR) return ERROR;
	
	stktype *newdata =(stktype*) calloc(test->capacity * 2 + 2, sizeof(stktype));
	test->capacity = test->capacity * 2;
	int i = 0;
	for (i = 0; i <= test->size; i++)
	{
		newdata[i] = test->data[i];
	}
	newdata[test->capacity + 1] = KAN; 
	free(test->data);
	test->data = newdata;
	return 0;
}

/** add a number with type int
*/

int push_back(stack *test, stktype a)
{
	int rezch = check_stack(test);
	if (rezch == ERROR)
	{
		fprintf(stk, "Problem with check_stack\n");
		return WERROR;
	}
	
	
	
	if (checkptr(test) == ERROR) return ERROR;
	if (test->capacity <= test->size + 1)
	{
		int rez = incrcapacity(test); // log
		if (rez == ERROR) 
		{
			fprintf(stk, "Buy new processor\n");	
		}
	}
	test->size++;
	test->data[test->size] = a;
	
	rezch = check_stack(test);
	if (rezch == ERROR)
	{
		fprintf(stk, "Problem with check_stack\n");
		return WERROR;
	}
	
	return 0;
}

/** delete the last cell and return cells value
*/

int pop (stack *test)
{
	if (checkptr(test) == ERROR) return ERROR;
	int a = test->data[test->size];
	test->size--;
	return a;
}

/** print all cells value
*/

int print_data(stack* test)
{
	if (checkptr(test) == ERROR) return ERROR;
	int i = 0;
	for (i = 1; i <= test->size; i++)
	{
		printf("%d\n", test->data[i]);
	}
	return 0;
}

/** open file "input.txt" and read all values
WARNING value must be type double!!!
after reading print it on screen
all errors and values of stack will be written in log.txt 
*/



