void clean()
{
	printf("\033[2J\n");
	if (system("cls")) system("clear");
	printf("==============================\\\\\n");
	printf("= |\\  /|    \\    /     = = = = \\\\ \n");
	printf("= | \\/ |ath  \\/\\/ ar   = = = = =\\\\\n");
	printf("=================================\\\\   \n");
	return;
}
void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
void player_info(int play){
	clean();
	printf("name :%s\n",player[play].name);
	printf("level :%i\n",player[play].level);
	printf("work per turn :%i\n",player[play].work);
	printf("current function value: %lf\n",player[play].value);
	printf("number of function :%i\n",player[play].fun_num);
	printf("load : %i \n",player[play].load);
	printf("loading at %i function\n",player[play].load_point);
	getchar();
}
void intro(){	
		//printf("\033[2J");
		/*if (system("cls"))*/ system("clear");
		printf("\topen source presents:");
		wait(2);

		printf("\n\n\n\n\n");
		printf("\t\t||\\\\    //||\n");
		printf("\t\t|| \\\\  // || \n");
		printf("\t\t||  \\\\//  \\|     // \n");
		printf("\t\t||        |\\    //  \n");
		printf("\t\t            \\/\\//   \n");		
		printf("\n\n \t Math-War");
		printf("\n");
		wait(4);		
		clean();	
		wait(1);
}
		
		
		
	
	
	


void fviewer(int p,int f)
{
	int i;
	
		for(i=1;i<player[p].fpoint[f];i++)
		{
			if(player[p].fun[f][i].operator>1)
			{
				printf("(");
			}
		}
	printf("%c",extchar(player[p].fun[f][0]));	
		for(i=1;i<player[p].fpoint[f];i++)
		{
			if(player[p].fun[f][i].operator>1)
			{			
				printf(")");
			}
			printf("%c",oper[player[p].fun[f][i].operator].symbol);
			printf("%c",extchar(player[p].fun[f][i]));
		}
}


void playerbar(){
	int i;
	printf("\t \t<==[turn%i/%i]==>  \n",turns,maxturns);
	
	printf("name[level]\t area\t loading function changes \n");
	for(i=0;i<2;i++)
	{
		printf("%s [%i]\t %.2f ",player[i].name,player[i].level,player[i].area);
			if(player[i].load_point>=0)
			{
				printf("%i turns to insert %c",(player[i].load%player[i].work)?(player[i].load/player[i].work)+1:player[i].load/player[i].work
				,oper[player[i].new_fun.operator].symbol);
				if(player[i].new_fun.operand)
				{
					printf("%c",extchar(player[i].new_fun));	
				}
				else
				{
					printf("%0.2f",player[i].new_fun.value);	
				}
			}
			else
			{
				printf("no changes");
			}
		printf("\n");
	}
	printf("\n \t");
	fviewer(0,0);
	
	for(i=1;i<player[0].fun_num;i++)
	{
		fviewer(0,i);
	}	
	printf("\t ");	
	if(player[0].value==player[1].value)
	{
		printf("=");
	}
	else if(player[0].value>player[1].value){	
		printf(">");
	}
	else
	{
		printf("<");
	}
	printf("\t ");	
	fviewer(1,0);
	for(i=1;i<player[1].fun_num;i++)
	{
		fviewer(1,i);
	}	
	printf("\t=>\n\t");
	printf("%.2f",player[0].value);
	printf("\t ");
	if(player[0].value==player[1].value)
	{
		printf("=");
	}
	else if(player[0].value>player[1].value)
	{
		printf(">");
	}
	else
	{
		printf("<");
	}
	printf("\t ");
	printf("%.2f \n",player[1].value);
	return ;	
}
