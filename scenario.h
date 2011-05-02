void solver(){
	int i,l,p;
	double S;
	//for every sub function for each player
	for(p=0;p<2;p++){
		S=0;
		for(i=0;i< player[p].fun_num;i++){//sub function loop
			for(l=0;l<player[p].fpoint[i];l++){//digit lopp
				if(!player[p].fun[i][l].operand){
					
		if(player[p].fun[i][l].operand==4){ //4=c
						player[p].fun[i][l].value=rand()%10;	
					}
				}
			}
			
			S+=fsolver(p,i);
			}
			player[p].value=S;			
	}	
	

}
void loadsettings(char filename[])
{
	// load operators
	int i,j,k,N,id;
	char temp;
	char data_type[10];
	FILE *finput=fopen(filename,"r");


		for(;;)
		{
			temp=getc(finput);
				if(temp=='$')
				{
					
					fscanf(finput,"%s %i",data_type,&N);
					printf("loading %s",data_type);
						if(!strcmp(data_type,"oper"))
						{	
						
						oper=malloc(N*sizeof(struct OPERATOR));
							for(i=0;i<N;i++)
							{
								fscanf(finput,"%i.",&id);
								fscanf(finput,"%c %s  %i %i %i\n",&oper[id].symbol,
																	oper[id].name,														
																	&oper[id].cost_factor[0],
																	&oper[id].cost_factor[1],
																	&oper[id].cost_var);
							}	
						maxoper=N;
						}
						else if(!strcmp(data_type,"var"))
						{						
			
						var=malloc(N*sizeof(struct VARIABLE));
							for(i=0;i<N;i++)
							{
								fscanf(finput,"%i.",&id);
								fscanf(finput,"%c %s\n",&var[id].symbol,var[id].desc);
				
							}
						maxvar=N;			
			
						}
						else if(!strcmp(data_type,"player"))
						{	
							printf("%i",N);
							maxplayer=N;					
							var=malloc(N*sizeof(struct PLAYER));
								for(i=0;i<N;i++)
								{
									fscanf(finput,"%i.",&id);
									fscanf(finput,"%i,%i,%lf,%lf\n",&player[id].level,&player[id].work,&player[id].value,&player[id].area);
									fscanf(finput,"%i:\n",&player[id].fun_num);
										for(j=0;j<player[id].fun_num;j++)
										{
										fscanf(finput,"%i=",&player[id].fpoint[j]);
											for(k=0;k<player[id].fpoint[j];j++)
											{
												fscanf(finput,"finput,%lf-%i-%i ",&player[id].fun[j][k].value,
																	&player[id].fun[j][k].operand,&player[id].fun[j][k].operator);
																	
																								
											}
										fscanf(finput,"\n");
										
										}
									strcpy(player[id].name,"player");
									player[i].name[6]=i+'0';	
								}
						maxvar=N;			
			
						}
		
				}
				else if(temp==EOF)
				{
				break;		
				} 
				else if(temp=='!'){
					printf("\ndebug echo:");
					printf("maxoper=%i,maxvar=%i,maxplayer=%i \n",maxoper,maxvar,maxplayer);
					
				}
		} 
fclose(finput);
return;

}





void turn_engine()
{
	int p,f;

	for(p=0;p<2;p++){
		f=player[p].load_point;
		if(f>=0){
			player[p].load-=player[p].work;
			if(player[p].load<=0)
			{
				player[p].load=0;
				player[p].load_point=-1;
			player[p].fun[f][player[p].fpoint[f]]=player[p].new_fun;
			player[p].fpoint[f]++;
			}
			
		}
	
	player[p].area+=player[p].value;
	if(player[p].area>=10+pow(5,player[p].level)){
		player[p].level++;
		player[p].work*=2;
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
		clean();
		printf("now select an operator:\n");
		for(i=0;i<maxoper;i++)
		{
			printf("%c \t %s \n",oper[i].symbol,oper[i].name);
			
		}
		for(;;)
		{	
			printf("select>");	
			scanf("%s",temps);
			printf("%i\n",temps[0]);
				if(temps[0]=='b')
				{
					return -1; // a step back (function selection)
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
			printf("(%i)\n",(oper_cost(new_digit.operator,j)/player[play_num].work)+((oper_cost(new_digit.operator,j)%player[play_num].work)?1:0));		
		}
		for(i=0;i<maxvar;i++)
		{
			printf("%c \t\t%i\n",var[i].symbol,100);//(oper[new_digit.operator].cost_var%player[player].res)?(oper[new_digit.operator].cost_var/player[player].res)+1:oper[new_digit.operator].cost_var/player[player].res);
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
					new_digit.operand=intvar(temps[0]);
					break;
				}
			}
			else 
			/*now we can extract any number we want and check it
			 */
			{	
				if(atoi(temps)<10){
					new_digit.operand=0;// 0 to say that is not a variable but a value 
					new_digit.value=atoi(temps);
					break;
				}
			}
		}
				      
		add_digit(play_num,fun,new_digit);//additor can now get a DIGIT insted of operator,operand 
		return 0;
	}

void load_safe()
	{
	/*use it when you wan't player to edit options about them
	 *recommended for multiplayer game mod
	 */ 
	 player=malloc(maxplayer*sizeof(struct PLAYER));
	
	 int i;
	 for(i=0;i<maxplayer;i++){
		 strcpy(player[i].name,"player");
		player[i].name[6]=i+'1';	
		player[i].fpoint[0]=0;
		 player[i].work=10;
		 player[i].value=0;
		 player[i].level=1;
		player[i]. area=0;
		 player[i].fun_num=1;
		player[i].load=0; 
		player[i].load_point=-1;
	
		}
		return ;
	}
