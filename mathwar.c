//      mathwar.c
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


//global data 
char winner=0;
int maxturns=20,turns=1,maxoper,maxvar;
	
struct VARIABLE {
	char c;
	char disc[40];		
}*var;

struct OPERATOR {
	char c;
	char name[20];		
	int res;
	int factor[2];
	int sres;
}*oper;

struct DIGIT {
	int operator;
	int operant;
	double value;
};

struct PLAYER {
		char name[20];
		struct DIGIT fuct[4][200];
		int fcount[4];
		int res;
		double value;
		char lvl;
		double area;
		int ul_fuct;
		int load; 
		int load_f;
		struct DIGIT new_fuct;	
	} player[3];





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
	
void help()
{
	clean();
	printf("help is not ready yet");
	getchar();
	return;
}

double extval(struct DIGIT x){
	if(x.operant==0){
		return x.value;
	}else if(x.operant ==1){
		return turns;
	}else if(x.operant ==2){
		return rand()%2;
	}else if(x.operant ==3){
		return	(rand()%21)-10;
	}else if(x.operant == 4){
		return	x.value;
	}
	return 0;	
	
}

int intvar(char c){
	int i;
	for(i=0;i<maxvar;i++){
		if(var[i].c==c){
			return i+1;
		}
	}
	return i+1;
	
}
	
int intopr(char c){
	int i;
	for(i=0;i<maxoper;i++){
		if(oper[i].c==c){
			return i;
		}
	}
	return i;
}
char extchar(struct DIGIT x){
	if(x.operant==0){
		return x.value+'0'; 
	}else if(x.operant ==1){
		return 't';
	}else if(x.operant ==2){
		return 'r';
	}else if(x.operant ==3){
		return 'R';
	}else if(x.operant ==4){
		return 'c';
	}
	return '!';	
	
	
}

double fsolver(int p,int f){
	int i;
	double S;
	S=extval(player[p].fuct[f][0]);
	
	
	for(i=1;i<player[p].fcount[f];i++){
		
		switch (player[p].fuct[f][i].operator){
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
			//S=pow(S,extval(player[p].fuct[f][i]));
			break;
			default:
			exit(1);
		}		
			
	}
	return S;
}

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
			printf("%c",oper[player[p].fuct[f][i].operator].c);
			printf("%c",extchar(player[p].fuct[f][i]));
		}
}

void playerbar(){
	int i;
	printf("\t \t<==[turn%i/%i]==>  \n",turns,maxturns);
	
	printf("name[level]\t area\t loading function changes \n");
	for(i=1;i<=2;i++)
	{
		printf("%s [%i]\t %.2f\t ",player[i].name,player[i].lvl,player[i].area);
			if(player[i].load_f>=0)
			{
				printf("%i turns to insert %c",(player[i].load%player[i].res)?(player[i].load/player[i].res)+1:player[i].load/player[i].res
				,oper[player[i].new_fuct.operator].c);
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
	fviewer(1,0);
	for(i=1;i<player[1].ul_fuct;i++){
		fviewer(1,i);
	}	
	printf("\t ");	
	if(player[1].value==player[2].value){
		printf("=");
	}else if(player[1].value>player[2].value){
		printf(">");
	}else{
		printf("<");
	}
	printf("\t ");	
	fviewer(2,0);
	for(i=1;i<player[2].ul_fuct;i++){
		fviewer(2,i);
	}	
	printf("\t=>\n\t");
	printf("%.2f",player[1].value);
	printf("\t ");
	if(player[1].value==player[2].value){
		printf("=");
	}else if(player[1].value>player[2].value){
		printf(">");
	}else{
		printf("<");
	}
	printf("\t ");
	printf("%.2f \n",player[2].value);
	return ;	
}

void additor(int p,int f,int op,int opn){
	player[p].load_f=f;
	if(opn<10){
		player[p].load=(opn*oper[op].res*oper[op].factor[1])+(opn*oper[op].factor[0]);
	}else{
		player[p].load=oper[op].sres ;	
	}
	if(opn<10){
		player[p].new_fuct.value=opn;
		player[p].new_fuct.operant=0;
	}else{
		player[p].new_fuct.value=0;
		player[p].new_fuct.operant=opn-9;
	}
		player[p].new_fuct.operator=op;
	
  return;
}


void loadsettings(){
 // load operators
 int i;
 FILE *foperators=fopen("mathwar.oper","r");
	
 fscanf(foperators,"%i\n",&maxoper);
 if(!maxoper) exit(1);
 oper=malloc(maxoper*sizeof(struct OPERATOR));
 
 for(i=0;i<maxoper;i++){
	 fscanf(foperators,"%c %s %i %i %i %i \n",&oper[i].c,
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
	 fscanf(foperators,"%c %s \n",&var[i].c,var[i].disc);
	}
fclose(foperators);
return;
}

void options(){
	clean();
	printf(" %s give name :" ,player[1].name);
	scanf("%s",player[1].name);	
	printf(" %s give name :" ,player[2].name);
	scanf("%s",player[2].name);		

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
	if(player[p].area>=10*player[p].lvl){//must be replaced by pow (but it does not work)
		player[p].lvl++;
	}
	}	
	return;	
}
int local_multi(){
		int f,op,opn;
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
		printf("%c \t %s \n",var[i].c,var[i].disc);
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
			
		//select fuction ::start
		for(i=0;i<player[p].ul_fuct;i++){
			printf("%i. f%i(t)=",i,i);
			fviewer(p,i);	
			printf("\n");
		}		
		do{	
			printf("select>");	
			scanf("%c",&tempa);
			if(tempa=='\n'){
				goto endturn;
			}
			else if(tempa=='h'){
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
		//end fuction
		//operator selection		
		printf("now select an operator:\n");
		for(i=0;i<maxoper;i++){
			printf("%c \t %s \n",oper[i].c,oper[i].name);
			
			}
		do{	
			printf("select>");	
			scanf("%c",&tempa);
			op=intopr(tempa);
		}while(!(op<maxoper));	
		//end operator
		//operant selection
		printf("now select an operant number:\n");
		printf("number. operant \tturns to load\n");
		for(i=0;i<10;i++)
		{
			printf("%i. \t %i \t\t%i\n",i,i,
					((i*oper[op].factor[1]*oper[op].res+i*oper[op].factor[0])%player[p].res)?((i*oper[op].factor[1]*oper[op].res+i*oper[op].factor[0])/player[p].res)+1:(i*oper[op].factor[1]*oper[op].res+i*oper[op].factor[0])/player[p].res);
		}
		for(i=0;i<maxvar;i++)
		{
			printf("%i. \t %c \t\t%i\n",i+10,var[i].c,(oper[op].sres%player[p].res)?(oper[op].sres/player[p].res)+1:oper[op].sres/player[p].res);
		}
		
		do{	
			printf("select>");	
			scanf("%i",&opn);
		}while(!(opn<14));
		//end operant
		      
		additor(p,f,op,opn);//send selection
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
	menu:
	clean();
	printf("Wellcome to mathwar \n");
	printf("\t[main menu]\n");
	printf("(single player)\n  \n(multi player)\n l.local\n(other) \n h. help \n o. options\n q.quit \n");
	
	scanf("%c",&choice);
	if(choice=='h')
	{
		help();
		goto menu;
	}
	else if(choice=='o')
	{
		options();
		goto menu;		
	}
	else if(choice=='l')
	{
		clean();
		local_multi();
		goto menu;		
	}
	else if(choice=='q')
	{
		return 0;
	}
	else
	{
		goto menu;
	}
		
	return 0;
}
