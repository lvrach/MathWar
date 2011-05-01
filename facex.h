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
void intro(){	
	/*int i ,j ,k , l;
	char rand_char[]={'0','1','*','>','=','/','x','+','2','<'};
	
	
	for(i=0;i<10;i++)
	{
		
		for(l=0;l<25;l++)
		{
			printf("\033[2J");
			if (system("cls")) system("clear");		
		
				for(j=0;j<3;j++)
				{
					
					for(k=0;k<100;k++)
					{
						printf("%c",rand_char[((rand()*k)+j+1)%10]);
					}
					printf("\n");
				}
		}
		wait(1);
	}*/
		printf("\033[2J");
		if (system("cls")) system("clear");
		printf("\topen source presents:");
		wait(2);

		printf("\n\n\n\n\n");
		printf("\t\t||\\\\    //||\n");
		printf("\t\t|| \\\\  // || \n");
		printf("\t\t||  \\\\//  \\|     // \n");
		printf("\t\t||        |\\    //  \n");
		printf("\t\t            \\/\\//   \n");
		
		printf("\n\t MathWar");
		wait(4);		
		clean();	
		wait(1);
}
		
		
		
	
	
	


void fviewer(int p,int f)
{
	int i;
	
		for(i=1;i<player[p].fcount[f];i++)
		{
			if(player[p].fun[f][i].operator>1)
			{
				printf("(");
			}
		}
	printf("%c",extchar(player[p].fun[f][0]));	
		for(i=1;i<player[p].fcount[f];i++)
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
	for(i=1;i<=2;i++)
	{
		printf("%s [%i]\t %.2f ",player[i].name,player[i].lvl,player[i].area);
			if(player[i].load_f>=0)
			{
				printf("%i turns to insert %c",(player[i].load%player[i].res)?(player[i].load/player[i].res)+1:player[i].load/player[i].res
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
	fviewer(1,0);
	
	for(i=1;i<player[1].ul_fun;i++)
	{
		fviewer(1,i);
	}	
	printf("\t ");	
	if(player[1].value==player[2].value)
	{
		printf("=");
	}
	else if(player[1].value>player[2].value){	
		printf(">");
	}
	else
	{
		printf("<");
	}
	printf("\t ");	
	fviewer(2,0);
	for(i=1;i<player[2].ul_fun;i++)
	{
		fviewer(2,i);
	}	
	printf("\t=>\n\t");
	printf("%.2f",player[1].value);
	printf("\t ");
	if(player[1].value==player[2].value)
	{
		printf("=");
	}
	else if(player[1].value>player[2].value)
	{
		printf(">");
	}
	else
	{
		printf("<");
	}
	printf("\t ");
	printf("%.2f \n",player[2].value);
	return ;	
}
