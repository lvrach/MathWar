//      mathwar.symbol
//      
//      Copyright 2011 <xalgra@titanix>
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
	printf(" %s give name :" ,player[1].name);
	scanf("%s",player[1].name);	
	printf(" %s give name :" ,player[2].name);
	scanf("%s",player[2].name);		

}

int local_multi(){
	int f,go,opn;
	int i,p;
	char tempa;
	
	//initalization
	loadsettings();
	
	strcpy(player[1].name,"player 1");
	
	strcpy(player[2].name,"player 2");
	player[1].lvl=1;
	player[2].lvl=1;
	player[1].res=10;
	player[2].res=10;
	player[1].ul_fuct=0;
	player[2].ul_fuct=0;
	player[1].value=0;
	player[2].value=0;
	player[1].area=0;
	player[2].area=0;
	player[1].load_f=-1;
	player[2].load_f=-1;
	player[1].load=0;
	player[2].load=0;
	
	printf("select your first variable(0-%i):\n",maxvar-1);
	for(i=0;i<maxvar;i++){
		printf("%c \t %s \n",var[i].symbol,var[i].desc);
	}
	for(p=1;p<=2;p++){
		do{
			printf("%s select>",player[p].name);
			scanf(" %c",&tempa);
			
			opn=intvar(tempa);		
		}while(!(opn<maxvar));
		
		player[p].fuct[0][0].operant=opn;
		player[p].fuct[0][0].operator=0;
		player[p].fuct[0][0].value=0;
		player[p].ul_fuct=1;
		player[p].fcount[0]=1;
	}
	
	
	
	while(winner==0 && turns<=maxturns){
     /*pre battle 
      * start */
	turn_engine();	
	solver();      
	//finish
	/*battle resolts
	 *start */	
		clean();
		getchar();				
		playerbar();		
		getchar();
		
		clean();
	//end
	
	/*players fuction setup
	 *start                 */	
	 for(p=1;p<=2;p++){//player loop
	 printf("%s are you ready?(just press enter)",player[p].name);
	 getchar();
	 clean();
	 startturn:
		printf("|%s is your turn\n",player[p].name);
		printf("|press enter to skip\n");
		printf("|press h for help or o for options\n");
		printf("|choose number of a fuction to edit\n");
	    /* * * * * * * * * * * * *
		 *select function ::start
	     */	
		select_fun: //label 
		for(i=0;i<player[p].ul_fuct;i++){
			printf("%i. f%i(t)=",i,i);
			fviewer(p,i);	
			printf("\n");
			do{	
				printf("select>");	
				scanf("%c",&tempa);
				if(tempa=='\n'){
					goto endturn;
				}else if(tempa=='h'){
					help();
					clean();
					goto startturn;
				}else if(tempa=='o'){
					help();
					options();
					goto startturn;
				}			
				f=tempa-'0';
			}while(!(f<player[p].ul_fuct));
			
			go=editor_menu(p,f);
			if(go>0){
				goto endturn;
			}else if(go < 0){
				goto select_fun;
			}
		}		
		
		endturn: //end turn with out edit functions
		getchar();
		clean();
		
	}
	//end
	
	/*turn commands 
	 *start */	
		turns++;
		
	//end	
	}
	if(player[1].area>player[2].area){
		printf("%s Wins",player[1].name);
	}else if(player[2].area>player[1].area){
		printf("%s Wins",player[2].name);
	}else{
		printf("Draw");
	}
	return 0;
	
}

int main(int argc, char **argv)
{

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
		local_multi();
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
