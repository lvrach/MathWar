//      mathwar.c
//      
//      Copyright 2011 xal.gra@gmail.com
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "data.h"
#include "funtls.h"
#include "facex.h"
#include "scenario.h"
	
void help()
{
	clean();
	printf("help is not ready yet");
	getchar();
	return;
}

void options(){
	clean();
	printf(" %s give name :" ,player[0].name);
	scanf("%s",player[0].name);	
	printf(" %s give name :" ,player[1].name);
	scanf("%s",player[1].name);		

}

int local_multi(int players){
	/*local multi-player game mode
	 *multiple  players fight for defined turns
	 *Winner is the one whose area of his function is bigger
	 *return 0 for going to main menu
	 *return 1 to close the game
	 */
	maxplayer=players;
	int f,go;
	int i,p;
	char temps[10];
	loadsettings("mathwar.oper");//load settings from file with give name	
	load_safe();//load setting but not from file
	
	/*players must select the first variable to add to their function ,
	 * players wont wait to be added in function 
	 */ 
	first_var_select:
	clean();
	printf("select your first variable:\n");
		for(i=0;i<maxvar;i++)
		{	
			printf("%c \t %s \n",var[i].symbol,var[i].desc);
		}
		for(p=0;p<maxplayer;p++)
		{
		
			for(;;)
			{
			printf("%s select:",player[p].name);
			scanf("%s",temps);
				if(isalpha(temps[0]))
				{
					if(intvar(temps[0])<=maxvar)//use '<=' because variables start from 1 not from 0 ,because 0 defines number.
					{
						f=player[p].fun_num-1;
						player[p].fun[f][player[p].fpoint[f]].operand=intvar(temps[0]);
							if(intvar(temps[0])==4)
							{ 
								player[p].fun[f][player[p].fpoint[f]].value=rand()%10;	
							}
						player[p].fpoint[f]+=1;
						break;
					}
				}
				
				goto first_var_select;
				printf("go to error");
				
			}	
			
		
		}
	
	
	
	while(winner==0 && turns<=maxturns){
    
	turn_engine();	
	 
	p=0;//helps goto work     
	playerbar:	
		clean();						
		playerbar();		
		getchar();
		getchar();
		clean();
	
	 for(;p<2;p++){
	
	// clean();
	 
		
	   
		select_fun:
		clean();
		printf("%s is your turn\n",player[p].name);
		printf("s |to skip\n");
		printf("o |for options\n");
		printf("i |for info about you\n");
		printf("h |for help\n");
		printf("b |to go step back\n");
		printf("\tor choose number of a function to edit:\n");
		for(i=0;i<player[p].fun_num;i++){
			printf("%i |f%i=",i,i);
			
			fviewer(p,i);
			if(player[p].load_point==i){
				printf("\t (!)already adding(you will lose it)");
			}	
			printf("\n");
				
			for(;;)
			{	
				printf("select>");	
				scanf("%s",temps);
				if(temps[0]=='s')
				{
					goto endturn;
				}
				else if(temps[0]=='h')
				{
					help();
					getchar();
					clean();
					
				}
				else if(temps[0]=='o')
				{
					options();
					getchar();
					clean();
					
				}
				else if(temps[0]=='i')
				{
					player_info(p);	
					getchar();				
					clean();
								
				}
				else if(temps[0]=='b')
				{
					goto playerbar;
								
				}
				else if(isdigit(temps[0]))
				{
					
					f=temps[0]-'0';
					if(f<player[p].fun_num)	break;
				}			
				goto select_fun;	
			}
			
			go=editor_menu(p,f);
			if(go>0){
				goto endturn;
			}else if(go < 0){
				goto select_fun;
			}
		}		
		
		endturn: 
		
		clean();
		
	}
	
		turns++;
		
	
	}
	if(player[0].area>player[1].area){
		printf("%s Wins",player[0].name);
	}else if(player[1].area>player[0].area){
		printf("%s Wins",player[1].name);
	}else{
		printf("Draw");
	}
	return 0;
	
}

int main(int argc, char **argv)
{
	int go;
	intro();
	char choice;	
	mainmenu:
	clean();
	printf("Wellcome to mathwar \n");
	printf("\t[main menu]\n");
	printf("(single player)\n  \n(multi player)\n l.local\n(other) \n h. help \n o. options\n q.quit \n");
	
	scanf("%c",&choice);
	if(choice=='h')
	{
		help();
		goto mainmenu;
	}
	else if(choice=='o')
	{
		options();
		goto mainmenu;		
	}
	else if(choice=='l')
	{
		clean();
		go=local_multi(2);
		if(go>0){
			return 0;
		}
		goto mainmenu;		
	}
	else if(choice=='q')
	{
		return 0;
	}
	else
	{
		goto mainmenu;
	}
		
	return 0;
}
