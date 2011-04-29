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
