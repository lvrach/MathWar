char winner=0;
 int maxturns=20,turns=1,maxoper,maxvar;
 
 
 struct VARIABLE {
	char symbol;
	char desc[40];		
}*var;

struct OPERATOR {
	char symbol;
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

