char extchar(struct DIGIT x)
{
	if(x.operand==0)
	{
		return x.value+'0'; 
	}
	else if(x.operand ==1)
	{
		return 't';
	}
	else if(x.operand ==2)
	{
		return 'r';
	}
	else if(x.operand ==3)
	{
		return 'R';
	}
	else if(x.operand ==4)
	{
		return 'c';
	}
	return '!';	
}


double extval(struct DIGIT x)
{
	if(x.operand==0)
	{
		return x.value;
	}
	else if(x.operand ==1)
	{
		return turns;
	}
	else if(x.operand ==2)
	{
		return rand()%2;
	}
	else if(x.operand ==3)
	{
		return	(rand()%21)-10;
	}
	else if(x.operand == 4)
	{
		return	x.value;
	}
	return 0;	
	
}

int oper_cost(int operator,int number)
{
	/* gets operator id return cost */
	return number*oper[operator].cost_factor[1]+number*oper[operator].cost_factor[0];
	
}

int intvar(char c){
	int i;
	for(i=0;i<maxvar;i++)
	{
		if(var[i].symbol==c)
		{
			return i+1;
		}
	}
	return i+1;
	
}
	
int intopr(char c){
	int i;
	for(i=0;i<maxoper;i++)
	{
		if(oper[i].symbol==c)
		{
			return i;
		}
	}
	return i;
}

double fsolver(int p,int f)
{
	int i;
	double S;
	S=extval(player[p].fun[f][0]);
	
	
	for(i=1;i<player[p].fpoint[f];i++)
	{
		
		switch (player[p].fun[f][i].operator)
		{
			case 0:
			S+=extval(player[p].fun[f][i])	;	
			break;		
			case 1:
			S-=extval(player[p].fun[f][i]);
			break;
			case 2:
			S*=extval(player[p].fun[f][i]);
			break;
			case 3:
			S/=extval(player[p].fun[f][i]);
			break;
			case 4:
			S=pow(S,extval(player[p].fun[f][i]));
			break;
			default:
			exit(1);
		}		
			
	}
	return S;
}

void add_digit(int play_num,int fun,struct DIGIT new){
	/*
	 * 
	 * */
	player[play_num].load_point=fun;
	
	if(!new.operand)
	{
		player[play_num].load=oper_cost(new.operator,new.value);
	}
	else
	{
		player[play_num].load=oper[new.operator].cost_var ;
	}
	player[play_num].new_fun=new;
	
  return;
}
