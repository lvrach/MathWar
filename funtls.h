char extchar(struct DIGIT x)
{
	if(x.operant==0)
	{
		return x.value+'0'; 
	}
	else if(x.operant ==1)
	{
		return 't';
	}
	else if(x.operant ==2)
	{
		return 'r';
	}
	else if(x.operant ==3)
	{
		return 'R';
	}
	else if(x.operant ==4)
	{
		return 'c';
	}
	return '!';	
}


double extval(struct DIGIT x)
{
	if(x.operant==0)
	{
		return x.value;
	}
	else if(x.operant ==1)
	{
		return turns;
	}
	else if(x.operant ==2)
	{
		return rand()%2;
	}
	else if(x.operant ==3)
	{
		return	(rand()%21)-10;
	}
	else if(x.operant == 4)
	{
		return	x.value;
	}
	return 0;	
	
}

int oper_cost(int operator,int number)
{
	/* gets operator id return cost */
	return number*oper[operator].factor[1]*oper[operator].res+number*oper[operator].factor[0];
		
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
	S=extval(player[p].fuct[f][0]);
	
	
	for(i=1;i<player[p].fcount[f];i++)
	{
		
		switch (player[p].fuct[f][i].operator)
		{
			case 0:
			S+=extval(player[p].fuct[f][i])	;	
			break;		
			case 1:
			S-=extval(player[p].fuct[f][i]);
			break;
			case 2:
			S*=extval(player[p].fuct[f][i]);
			break;
			case 3:
			S/=extval(player[p].fuct[f][i]);
			break;
			case 4:
			S=pow(S,extval(player[p].fuct[f][i]));
			break;
			default:
			exit(1);
		}		
			
	}
	return S;
}

void additor(int play,int fun,struct DIGIT new){
	
	player[play].load_f=fun;
	
	if(!new.operant){
		player[play].load=oper_cost(new.operator,new.operant);
	}else{
		player[play].load=oper[new.operator].sres ;
	}
	player[play].new_fuct=new;
	
  return;
}
