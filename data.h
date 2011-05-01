char winner=0;
 int maxturns=20,turns=1,maxoper,maxvar;
 
 
 struct VARIABLE {
	char symbol;
	char desc[40];		
}*var;

struct OPERATOR {
	char symbol;
	char name[20];		
	int cost_base;
	int cost_factor[2];
	int cost_var;
}*oper;

struct DIGIT {
	int operator;
	int operand;
	double value;
};

 struct PLAYER {
		char name[20];
		struct DIGIT fun[4][200];
		int fcount[4];
		int res;
		double value;
		char lvl;
		double area;
		int ul_fun;
		int load; 
		int load_f;
		struct DIGIT new_fun;	
	} player[3];

