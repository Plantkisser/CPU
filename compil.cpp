#include <stdio.h>
#include <stdlib.h>
#include <cstring>
# define STR 15
# define PROC 1000
# define MARKS 15
# define BZERO 64

# define CANNOTCREATE(name, file)\
{\
	fprintf(file, "Cannot create "#name"\n");\
	return 0;\
}
# define CREATELOG(name);\
{\
	name = fopen(#name"log.txt", "a");\
}


# define ERROR 78
		
struct mark
{
	char* name;
	int pt;
};
		
struct process
{
	char* posl;
	int sizem;
};
FILE* comp;

enum commands
{
	#define CMD_DEF(name, num, codec, codep)\
		CMD_##name = num, 
	#include "commands.h"
	#undef CMD_DEF	
};

int clean_str(char* str, int kol)
{
	if (str == NULL)
	{
		fprintf(comp, "Null ptr in clean_str\n");
		return ERROR;
	}
	for (int i = 0; i < kol; i++)
		str[i] = 0;
	return 0;
}

int read_str (char* str, FILE* fin)
{
	if ((str == NULL)||(fin == NULL))
	{
		fprintf(comp, "Nullptr in read_str\n");
		return ERROR;
	}
	int i = 0;
	int k = 1;
	
	return k;
}

int search_num(char* buf, mark* arr)
{
	int i = 0;
	for(i = 0; i < MARKS; i++)
		if (!strcmp(buf, arr[i].name))
			return i;
	return -1;
}

int create_mark(char* buf, mark* arr)
{
	int i = 0;
	for(i = 0; i < MARKS; i++)
		if (arr[i].pt == -1)
		{
			strcpy(arr[i].name, buf);
			return i;
		}
	fprintf(comp, "Number of marks is out of range\n");
	return ERROR;
}

int rev256 (int numb, process* mas)
{
	if (mas == NULL)
	{
		fprintf(comp, "in rev256 ptr is NULL\n");
		return ERROR;
	}
	int l = 0;
	int del = 0;
	int rez = 0;
	int i = mas->sizem;
	while(numb > 0)
	{
		l++;
		del = 1;
		while (del <= numb)
			del = del * 256;
		del = del / 256;
		rez = numb / del;
		mas->posl[i] = rez;
		numb = numb % del;
		i++;
	}
	if (l == 0)
		l = 1;
	mas->sizem+= l;
	return l;
}



int getcode(char* str, process* mas, char* buf, mark* arr, char* buf2)
{
	
	if ((str == NULL) || (mas == NULL) || (buf == NULL))
	{
		fprintf(comp, "Nullptr in search_code\n");
		return ERROR;
	}
	int i = 0;
	
	while ((str[i] != ' ') && (str[i] != '\n'))
	{
		buf[i] = str[i];
		i++;
	}
	
	#define CMD_DEF(name, num, codec, codep)\
	if (!strcmp(buf, #name)) codec
	
	
	#define CMD_JUMP(letter)\
	i++;\
	int j = 0;\
	while ((str[i] != ' ') && (str[i] != '\n'))\
	{\
		buf2[j] = str[i];\
		j++;\
		i++;\
	}\
	mas->posl[mas->sizem] = CMD_##letter;\
	mas->sizem++;\
	int  k = mas->sizem;\
	mas->sizem++;\
	mas->posl[k] = rev256(arr[search_num(buf2, arr)].pt, mas);\
	clean_str(buf2, STR);\
	return 0;
	
	#include "commands.h"
	
	#undef CMD_JUMP
	#undef CMD_DEF
	int num = -1;
	int numb = 0;
	if (buf[0] == ':')
		{
			num = search_num(buf, arr);
			if (num == -1) 
			{
				num = create_mark(buf, arr);
				if (num == ERROR) 
					return ERROR;
			}
			arr[num].pt = mas->sizem;
			return 0;
		}
	return 0;
}

int print_code(process* mas)
{
	
	int i = 0;
	if (mas == NULL)
	{
		fprintf(comp, "Nullptr in search_code\n");
		return ERROR;
	}
	for (i = 0; i < mas->sizem; i++)
		printf("%d ",mas->posl[i]);
	printf("\n");
	return 0; 
}

int fprint_code(process* mas)
{
	FILE* fout = fopen("code", "wb");
	for (int i = 0; i < mas->sizem; i++)
	{
		fprintf(fout, "%c", mas->posl[i]);
	}
	fclose(fout);
	return 0;
}


int compil(char* str, process* mas, mark* arr, char* buf, char* buf2)
{
	FILE* fin = fopen("input.txt", "r");
	if (fin == NULL)
	{
		fprintf(comp, "Cannot open input.txt\n");
		return 0;
	};
	int rez = 0;
	while (fgets(str, 16, fin) != NULL)
	{	
		getcode(str, mas, buf, arr, buf2);
		rez = clean_str(str, STR);
		if (rez == ERROR) 
			break;
		rez = clean_str(buf, STR);
		if (rez == ERROR) 
			break;	
	}
	
	print_code(mas);
	fprint_code(mas);
	fclose(fin);
}

int main()
{
	CREATELOG(comp);
	char* str = (char*) calloc (STR, sizeof(char));
	if (str == NULL)
		CANNOTCREATE(str, comp);
	
	mark* arr = (mark*) calloc (MARKS, sizeof(mark));
	if (arr == NULL)
		CANNOTCREATE(arr, comp);
	
	
	int i = 0;
	for (i = 0; i < MARKS; i++)
	{
		arr[i].pt = -1;
		arr[i].name = (char*) calloc (STR, sizeof(char));
		if (arr[i].name == NULL)
			CANNOTCREATE(arr[i].name, comp);
	}

	char* buf2 = (char*) calloc (STR, sizeof(char));
	if (buf2 == NULL)
		CANNOTCREATE(buf2, comp);	
	
	char* buf = (char*) calloc (STR, sizeof(char));
	if (buf == NULL)
		CANNOTCREATE(buf, comp);
	
	process mas;
	mas.sizem = 0;
	mas.posl = (char*) calloc (PROC, sizeof(char));
	if (mas.posl == NULL)
		CANNOTCREATE(mas, comp);
		
	int rez = compil (str, &mas, arr, buf, buf2);
	if (rez != 0)
	{
		printf("Something went wrong in first use compil int main rez != 0\n");
		return 0;
	}
	mas.sizem = 0;
	rez = compil (str, &mas, arr, buf, buf2);
	if (rez != 0)
	{
		printf("Something went wrong in second use compil int main rez != 0\n");
		return 0;
	}
	free(str);
	free(buf);
	free(buf2);
	free(arr);
	free(mas.posl);
	return 0;
}
