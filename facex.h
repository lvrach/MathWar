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

void fviewer(int p,int f){
	int i;
	
		for(i=1;i<player[p].fcount[f];i++){
			if(player[p].fuct[f][i].operator>1){
				printf("(");
			}
		}
		printf("%c",extchar(player[p].fuct[f][0]));	
		for(i=1;i<player[p].fcount[f];i++){
			if(player[p].fuct[f][i].operator>1){
			printf(")");
			}
			printf("%c",oper[player[p].fuct[f][i].operator].symbol);
			printf("%c",extchar(player[p].fuct[f][i]));
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
				,oper[player[i].new_fuct.operator].symbol);
				if(player[i].new_fuct.operant)
				{
					printf("%c",extchar(player[i].new_fuct));	
				}
				else
				{
					printf("%0.2f",player[i].new_fuct.value);	
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
	
	for(i=1;i<player[1].ul_fuct;i++)
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
	for(i=1;i<player[2].ul_fuct;i++)
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
