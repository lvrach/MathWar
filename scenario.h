void solver(){
	int i,l,p;
	double S;
	//for every sub function for each player
	for(p=1;p <= 2;p++){
		S=0;
		for(i=0;i< player[p].ul_fuct;i++){//sub fuction loop
			for(l=0;l<player[p].fcount[i];l++){//digit lopp
				if(!player[p].fuct[i][l].operant){
					if(player[p].fuct[i][l].operant==4){ //4=c
						player[p].fuct[i][l].value=rand()%10;	
					}
				}
			}
			
			S+=fsolver(p,i);
			}
			player[p].value=S;			
	}	
	

}



void loadsettings(){
 // load operators
 int i;
 FILE *foperators=fopen("mathwar.oper","r");
	
 fscanf(foperators,"%i\n",&maxoper);
 if(!maxoper) exit(1);
 oper=malloc(maxoper*sizeof(struct OPERATOR));
 
 for(i=0;i<maxoper;i++){
	 fscanf(foperators,"%c %s %i %i %i %i \n",&oper[i].symbol,
												oper[i].name,												
												&oper[i].res,
												&oper[i].factor[0],
												&oper[i].factor[1],
												&oper[i].sres);
	}
fscanf(foperators,"%i\n",&maxvar);
 if(!maxvar) exit(1);	
 var=malloc(maxvar*sizeof(struct VARIABLE));
  for(i=0;i< maxvar;i++){
	 fscanf(foperators,"%c %s \n",&var[i].symbol,var[i].desc);
	}
fclose(foperators);
return;
}

void turn_engine(){
	int p,f;

	for(p=1;p<=2;p++){
		f=player[p].load_f;
		if(f>=0){
			player[p].load-=player[p].res;
			if(player[p].load<=0){
				player[p].load=0;
				player[p].load_f=-1;
			player[p].fuct[f][player[p].fcount[f]]=player[p].new_fuct;
			player[p].fcount[f]++;
			}
			
		}
	
	player[p].area+=player[p].value;
	if(player[p].area>=10+pow(5,player[p].lvl)){
		player[p].lvl++;
		player[p].res*=2;
	}
	}	
	return;	
}


int editor_menu(int play_num,int fun){
	/* this function gets player and FUNction player.
	 * It's got interface for helping the gamers to select 
	 * whatever they want to edit to their function
	*/
		
	/*if you want to go a step back in fun selection
	 *  (it is not included in this header)	
	 * return -1;
	 *if you want to skip ,and go to the next player
	 * (or next num if their is not anyone)
	 * return 1;
	 */
	char temps[10];//temp string
	int i,j; 
	struct DIGIT new_digit;
	
		operator_select:	
		printf("now select an operator:\n");
		for(i=0;i<maxoper;i++)
		{
			printf("%c \t %s \n",oper[i].symbol,oper[i].name);
			
		}
		for(;;)
		{	
			printf("select>");	
			scanf("%s",temps);
				if(temps[0]=='b')
				{
					return -1; // a step back
				}
				else if(temps[0]=='\n') //if press enter
				{
					return 1; // next player/turn
				}
			
				else{
					if(intopr(temps[0])<maxoper) // check if it is valid 
					{
						new_digit.operator=intopr(temps[0]);
						break;
					}
				
				}
			
		}
		clean();
		//operant selection
		printf("You have select %s operator \n",oper[new_digit.operator].name);
		printf("Now select an operant number:\n");
		printf("operant  ,cost(turns to load)\n");
		for(j=0;j<10;j++)
		{
			printf("%i \t, %i",j,oper_cost(new_digit.operator,j));
			printf("(%i)\n",(oper_cost(new_digit.operator,j)/player[play_num].res)+((oper_cost(new_digit.operator,j)%player[play_num].res)?0:1));		
		}
		for(i=0;i<maxvar;i++)
		{
			printf("%c \t\t%i\n",var[i].symbol,100);//(oper[new_digit.operator].sres%player[player].res)?(oper[new_digit.operator].sres/player[player].res)+1:oper[new_digit.operator].sres/player[player].res);
		}
		
			
		for(;;)
		{
			printf("select>");	
			scanf("%s",temps);
			if(temps[0]=='b')
			{
				goto operator_select;
			}
			else if(temps[0]=='\n')
			{
				return 1;
			}
			/*if looks if it is any other alphabetic  (also protect atoi)
			 * but looks just the first char ,as above ifs so it need extension 
			 */			 
			else if(isalpha(temps[0]))
			{
				if(intvar(temps[0])<=maxvar)//use <= because variables start from 1 not from 0 ,because 0 defines number.
				{
					new_digit.operant=intvar(temps[0]);
					break;
				}
			}
			else 
			/*now we can extract any number we want and check it
			 */
			{	
				if(atoi(temps)<10){
					new_digit.operant=0;// 0 to say that is not a variable but a value 
					new_digit.value=atoi(temps);
					break;
				}
			}
		}
				      
		additor(play_num,fun,new_digit);//additor can now get a DIGIT insted of operator,operand 
		return 0;
	}
