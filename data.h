char winner=0;
 int maxturns=20,turns=1,maxoper,maxvar,maxplayer;
 
 
 struct VARIABLE {
	char symbol;
	char desc[40];		
}*var;

struct OPERATOR {
	char symbol;
	char name[20];	
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
		int fpoint[4];
		int work;
		double value;
		int level;
		double area;
		int fun_num;//unlock functions
		int load; 
		int load_point;
		struct DIGIT new_fun;	
	} *player;

