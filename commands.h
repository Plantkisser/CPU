CMD_DEF(PUSH, 40, 
{
	i++;
	switch (str[i])
	{
		case 'R':
			i++;
			mas->posl[mas->sizem] = CMD_PUSH_RA + str[i] - 'A';
			mas->sizem++;
			return 0;
		default:
			mas->posl[mas->sizem] = CMD_PUSH;
			mas->sizem++;
			int k = mas->sizem;
			mas->sizem++;
			int numb = 0;
			int fl = 0;
			int mul = 0;
			if (str[i] == '-')
				{
					mul = 1;
					i++;
				}
			while (str[i] != '\n')
			{
				numb = (str[i] - '0') + numb * 10;
				i++;
			}
			mas->posl[k] = rev256(numb, mas) + (BZERO * mul);
			return 0;
	}
},
{
	i++;
	int kol = code[i];
	int mul = 1;
	if (kol > BZERO)
	{ 
		kol -=BZERO;
		mul = -1;
	}
	int numb = 0;
	for (int j = 1; j <= kol; j++)
	{
		i++;
		numb = numb * 256 + code[i];
	}
	numb = numb * mul;
	push_back(&test, numb);
	break;
}) 
CMD_DEF(POP, 41, 
{
	i++;
	switch (str[i])
	{
		case 'R':
			i++;
			mas->posl[mas->sizem] = CMD_POP_RA + str[i] - 'A';
			mas->sizem++;
			return 0;
		default:
			mas->posl[mas->sizem] = CMD_POP;
			mas->sizem++;
			return 0;
	}
},
{
	pop(&test);
	break;
})
CMD_DEF (OUT, 42, 
{ 
	mas->posl[mas->sizem] = CMD_OUT;
	mas->sizem++;
	return 0;
},
{
	printf("%5lf\n", test.data[test.size]); //нужно поменять тип при смене типа стэка
	break;
})
CMD_DEF (ADD, 43, 
{
	mas->posl[mas->sizem] = CMD_ADD;
	mas->sizem++;
	return 0;
},
{
	ap = pop(&test);
	bp = pop(&test);
	push_back(&test, ap + bp);
	break;
}) 
CMD_DEF (MUL, 44,
{
	mas->posl[mas->sizem] = CMD_MUL;
	mas->sizem++;
	return 0;
},
{
	ap = pop(&test);
	bp = pop(&test);
	ap = ap*bp;
	push_back(&test, ap);
	break;
})
CMD_DEF (DIV, 45,
{
	mas->posl[mas->sizem] = CMD_DIV;
	mas->sizem++;
	return 0;
},
{
	ap = pop(&test);
	bp = pop(&test);
	ap = bp/ap;
	push_back(&test, ap);
	break;
})

CMD_DEF (SQRT, 46,
{
	mas->posl[mas->sizem] = CMD_SQRT;
	mas->sizem++;
	return 0;
},
{
	ap = pop(&test);
	ap = sqrt(ap);
	push_back(&test, ap);
	break;
})
CMD_DEF (MINUS, 47,
{
	mas->posl[mas->sizem] = CMD_MINUS;
		mas->sizem++;
		return 0;
},
{
	ap = pop(&test);
	push_back(&test, -1 * ap);
	break;
})
CMD_DEF (POP_RA, 48,
{

},
{
	test.ra = pop(&test);
	break;
})
CMD_DEF (POP_RB, 49,
{
	
},
{
	test.rb = pop(&test);
	break;
})
CMD_DEF (POP_RC, 50,
{
	
},
{
	test.rc = pop(&test);
	break;
})
CMD_DEF (POP_RD, 51,
{
	
},
{
	test.rd = pop(&test);
	break;
})
CMD_DEF (PUSH_RA, 52,
{
	
},
{
	push_back (&test, test.ra);
	break;
})
CMD_DEF (PUSH_RB, 53,
{
	
},
{
	push_back (&test, test.rb);
	break;
})
CMD_DEF (PUSH_RC, 54,
{
	
},
{
	push_back (&test, test.rc);
	break;
})
CMD_DEF (PUSH_RD, 55,
{
	
},
{
	push_back (&test, test.rd);
	break;
})
CMD_DEF (END, 56,
{
	mas->posl[mas->sizem] = CMD_END;
	mas->sizem++;
	return 0;
},
{
	
})
CMD_DEF (JA, 57,
{
	CMD_JUMP(JA)
},
{
	CMD_JUMP(<)
})
CMD_DEF (JB, 58,
{
	CMD_JUMP(JB)
},
{
	CMD_JUMP(>)
})
CMD_DEF (JE, 59,
{
	CMD_JUMP(JE)
},
{
	CMD_JUMP(==)
})
CMD_DEF (JAE, 60,
{
	CMD_JUMP(JAE)
},
{
	CMD_JUMP(<=)
})
CMD_DEF (JBE, 61,
{
	CMD_JUMP(JBE)
},
{
	CMD_JUMP(>=)
})
CMD_DEF (JNE, 62,
{
	CMD_JUMP(JNE)
},
{
	CMD_JUMP(!=)
})

CMD_DEF (CALL, 63,
{
	CMD_JUMP(CALL)
},
{
	i++;
	num = 0;
	j = 1;
	while (j <= code[i])
	{
		num = num * 256 + code[i + j];
		j++;
	}
	push_back(&recur, i);
	i = num - 1;
	break;
})

CMD_DEF (RET, 64,
{
	mas->posl[mas->sizem] = CMD_RET;
	mas->sizem++;
	return 0;
},
{
	i = pop(&recur);
	break;
})
