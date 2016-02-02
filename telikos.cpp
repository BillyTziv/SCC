/********************************************************************************************
 *      Compilers 2015
 *      Computer Science and Engineering Department - University of Ioannina
 * 
 *      Tzivaras Panagioths 1931 and Tzivaras Vasilis 1770
 * 
 *      Contact email: vtzivaras@gmail.com
 *      Language: C++
 * 
 *      Compile this file: g++ <file>.cpp
 *      Run as ./a.out <input_file>
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>


#define WHITE_SPACE 0
#define LETTERS 1
#define DIGITS 2
#define PLUS 3
#define MINUS 4
#define MULTIPLY 5
#define DIVIDE 6
#define LESS 7
#define GREATER 8
#define EQUAL 9
#define COLON 10
#define LEFTPARENTHESIS 11
#define RIGHTPARENTHESIS 12
#define LEFTSQUAREPARENTHESIS 13
#define RIGHTSQUAREPARENTHESIS 14
#define LEFTBRACKETS 15
#define RIGHTBRACKETS 16
#define SEMICOLON 17
#define COMMA 18
#define ENDFILE 19
#define WHATEVER 20

#define STATE0 0
#define STATE1 1
#define STATE2 2
#define STATE3 3
#define STATE4 4
#define STATE5 5 
#define STATE6 6
#define STATE7 7
#define STATE8 8

#define IDTK 20
#define NUMBERTK 21
#define PLUSTK 30
#define MINUSTK 40
#define MULTIPLYTK 50
#define DIVIDETK 60
#define LESSTK 70
#define LESSEQUALTK 71
#define NOT_EQUALTK 72
#define GREATERTK 80
#define GREATEREQUALTK 81
#define EQUALTK 90
#define ASSIGNMENTTK 100
#define LEFTPARENTHESISTK 110
#define RIGHTPARENTHESISTK 120
#define LEFTSQUAREPARENTHESISTK 130
#define RIGHTSQUAREPARENTHESISTK 140
#define LEFTBRACKETSTK 150
#define RIGHTBRACKETSTK 160
#define SEMICOLONTK 170
#define COMMATK 180
#define ENDFILETK 190
#define ERROR_WHATEVERTK 200
#define ERROR_ENDFILETK 201
#define ERROR_COLONTK 202

#define ANDTK 210
#define EXITTK 211
#define IFTK 212
#define PROGRAMTK 213
#define WHENTK 214
#define DECLARETK 215
#define PROCEDURETK 216
#define INTK 217
#define ORTK 218
#define CALLTK 219
#define DOTK 220
#define FUNCTIONTK 221
#define INOUTTK 222
#define RETURNTK 223
#define ELSETK 224
#define PRINTTK 225
#define NOTTK 226
#define WHILETK 227
#define ENDDECLARETK 228
#define INCASETK 229
#define FORCASETK 230
#define COPYTK 231

#define VAR 0
#define FUNC 1
#define PAR 2

using namespace std;
ofstream output;
ofstream outputTelikos;

class Argument {
private:
	int parmode;
	int type;
	Argument *next;
public:
	Argument(int parmode, int type);
	Argument *getNext();
	void setNext(Argument *next);
};

class Variable{
private:
	int offset;
public:
	Variable(int offset);
	int getOffset();
	void setOffset(int offset);
};

class Function{
private:
	int startQuad;
	Argument *listArg;
	int framelength;
	int type;
public:
	Function(int type);
	int getStartQuad();
	void setStartQuad(int startQuad);
	int getFramelength();
	void setFramelength(int framelength);
	int getType();
};


class Parameter{
private:
	int parmode;
	int offset;
public:
	Parameter(int parmode, int offset);
	int getParmode();
	int getOffset();
};


class Entity{
private:
	char name[30];
	int type;
	Variable *var;
	Function *func;
	Parameter *par;
	Entity *next;
public:
	Entity(char name[30],int type,Variable *var);
	Entity(char name[30],int type,Function *func);
	Entity(char name[30],int type,Parameter *par);
	
	Variable *getVar();
	Function *getFunc();
	Parameter *getPar();
	Entity *getNext();
	void setNext(Entity *next);
	void print();
	char *getName(){ return(name);}
	int getType(){return(type);}
	
};

class Scope{
private:
	Entity *listEntity;
	int nestingLevel;
	Scope *next;
 	int counter;
public:
	Scope(int nestingLevel);
	int getNestingLevel();
	void setNext(Scope *next);
	Scope *getNext();
	void addEntity(Entity *ent);
	int getCounter();
	void print();
	void incCounter();
	Entity *findEntity(char *name);
	Entity *findEntityAll(char *name, int *x);
	
	void setFramelength(int framelength);
	void setStartQuad(int startQuad);
};


class Analyzer{
	private:
		fstream input;
		int state_transition[9][21];
		int lastWordId;
		char word[30];
		char place[30];
	public:
		Analyzer(char *filename);
		void initialize_state_transition();
		int map(char ch);
		int nextWord();
		int check(char *word);
		int getLastWordId();
		char *getPlace();
		void setPlace(char *place);
		char *getWord(){ return word;}
};

Analyzer* lex;

class Quads{
private:
	int address;
	char *op,*x,*y,*z;
	Quads *next;
public:
	Quads(int address,char *op,char *x,char *y,char *z);
	Quads(int address,char *op);
	Quads(int address,char *op,char *x);
	Quads(int address,char *op,char *x,char *y);
	
	void setNext(Quads *next);
	void setz(char z[30]);
	Quads *getNext();
	void print();//ofstream f);
	int getAddress() {
	    return address;
	}
	char *getOp(){ return op;}
	char *getX(){ return x;}
	char *getY(){ return y;}
	char *getZ(){ return z;}
	
};

class List {
private:
	int address;
	List *next;
public:
	List(int x);
	List *getNext();
	void setNext(List *next);
	int getAddress() {
	    return this->address;
	}
};

class Syntax {
private:
	Quads *first;
	int address;
	int tempCounter;
	Scope *head;
	
public:
	Syntax();
	
	void genquad(char *op);
	void genquad(char *op,char *x);
	void genquad(char *op,char *x,char *y);
	void genquad(char *op,char *x,char *y,char *z);
	
	void insert(Quads *newQuads);
	
	void addScope();
	void printHead();
	void deleteScope();
	
	int nextquad();
	char *newtemp();
	
	List *makelist(int x);
	List *merge(List *l1,List *l2);
	void backpatch(List *list, int x);
	void print(char fname[30]);
	void setz(char temp[30], int addr);
	
	void error(int code);
	void program();
	
	void block(char name[30],int flag);
	void declarations();
	
	void varlist();
	
	void subprograms();
	void func();
	void funcbody(char name[30]);
	void formalpars();
	void formalparlist();
	void formalparitem();
	void sequence();
	void bracketseq();
	void statement();
	void assignmentstat();
	void expression();
	void optionalsign();
	void term();
	void factor();
	void idtail(char name[30]);
	void actualparitem();
	void actualparlist();
	int actualpars();
	void addoper();
	void condition(List **T, List **F);
	void condition(){};
	void boolterm(List **T, List **F);
	void boolfactor(List **T, List **F);
	void relationaloper();
	void ifstat();
	void bracket_seq();
	void brackorstat();
	void elsepart();
	void dowhilestat();
	void printstat();
	void returnstat();
	void exitstat();
	void whilestat();
	void callstat();
	void incasestat();
	void forcasestat();
};

class Telikos{
private:
	Quads *first;
	Scope *head;
	int parCounter;
public:
	Telikos(Quads *first, char *fname, Scope *head);
	void loadvr(char *v, int r);
	void storerv(int r, char *v);
	
	void convert();
	
};

Telikos::Telikos(Quads *first, char *fname, Scope *head){
	this->first=first;
	this->head=head;
	outputTelikos.open(fname,ios::app);
	parCounter=0;
}

void Telikos::loadvr(char *v, int r){
	Entity *temp;
	int nestingLevel;
	
	temp=head->findEntityAll(v,&nestingLevel);
	if(isdigit(v[0])){
		char str[100];
		sprintf(str,"movi R[%d],%s",r,v);
		outputTelikos<<str<<endl;
	}
	else if(nestingLevel==0){//global
		int offset;
		if(temp->getType()==VAR){
			offset=temp->getVar()->getOffset();
		}
		char str[100];
		sprintf(str,"movi R[%d],M[600+%d]",r,offset);
		outputTelikos<<str<<endl;
	}
	else if(nestingLevel==head->getNestingLevel()){//vathos iso me to trexwn
		if(temp->getType()==VAR || (temp->getType()==PAR && temp->getPar()->getParmode()==INTK)){
			int offset;
			char str[100];
			if(temp->getType()==VAR){
				offset=temp->getVar()->getOffset();
			}
			else{
				offset=temp->getPar()->getOffset();
			}
			sprintf(str,"movi R[%d],M[600+%d]",r,offset);
			outputTelikos<<str<<endl;
		}
		else if(temp->getType()==PAR && temp->getPar()->getParmode()==INOUTTK){
			int offset=temp->getPar()->getOffset();
			char str[100];
			
			sprintf(str,"movi R[255],M[R[0]+%d]\n",offset);
			outputTelikos<<str<<endl;
			
			sprintf(str,"movi R[%d],M[R[255]]",r);
			outputTelikos<<str<<endl;
			
		}
	}
	else{
		if(temp->getType()==VAR || (temp->getType()==PAR && temp->getPar()->getParmode()==INTK)){
			int offset;
			int steps=head->getNestingLevel() - nestingLevel;
			
			char str[100];
			sprintf(str,"movi R[255],M[4+R[0]]\n");
			outputTelikos<<str;
			while(steps>1){
				steps--;
				sprintf(str,"movi R[255],M[4+R[255]]\n");
				outputTelikos<<str;
				
				 
			}
			
			if(temp->getType()==VAR){
				offset=temp->getVar()->getOffset();
			}
			else{
				offset=temp->getPar()->getOffset();
			}
			sprintf(str,"movi R[254],%d]\n",offset);
			outputTelikos<<str;
			sprintf(str,"addi R[255],R[254],R[255]\n");
			
			
			sprintf(str,"movi R[%d],M[R[255]]",r);
			outputTelikos<<str<<endl;
		}
		else if(temp->getType()==PAR && temp->getPar()->getParmode()==INOUTTK){
			int offset;
			int steps=head->getNestingLevel() - nestingLevel;
			
			char str[100];
			sprintf(str,"movi R[255],M[4+R[0]]\n");
			outputTelikos<<str;
			while(steps>1){
				steps--;
				sprintf(str,"movi R[255],M[4+R[255]]\n");
				outputTelikos<<str;
				
				
			}
			
			if(temp->getType()==VAR){
				offset=temp->getVar()->getOffset();
			}
			else{
				offset=temp->getPar()->getOffset();
			}
			sprintf(str,"movi R[254],%d]\n",offset);
			outputTelikos<<str;
			sprintf(str,"addi R[255],R[254],R[255]\n");
			outputTelikos<<str;
			
			sprintf(str,"movi R[255],M[R[255]]\n");
			outputTelikos<<str;
			
			sprintf(str,"movi R[%d],M[R[255]]",r);
			outputTelikos<<str<<endl;
			
		}
	}
}


void Telikos::storerv(int r, char *v){
	Entity *temp;
	int nestingLevel;
	
	temp=head->findEntityAll(v,&nestingLevel);
	if(nestingLevel==0){//global
		int offset;
		if(temp->getType()==VAR){
			offset=temp->getVar()->getOffset();
		}
		char str[100];
		sprintf(str,"movi M[600+%d],R[%d]",offset,r);
		outputTelikos<<str<<endl;
	}
	else if(nestingLevel==head->getNestingLevel()){//vathos iso me to trexwn
		if(temp->getType()==VAR || (temp->getType()==PAR && temp->getPar()->getParmode()==INTK)){
			int offset;
			char str[100];
			if(temp->getType()==VAR){
				offset=temp->getVar()->getOffset();
			}
			else{
				offset=temp->getPar()->getOffset();
			}
			sprintf(str,"movi M[600+%d],R[%d]",offset,r);
			outputTelikos<<str<<endl;
		}
		else if(temp->getType()==PAR && temp->getPar()->getParmode()==INOUTTK){
			int offset=temp->getPar()->getOffset();
			char str[100];
			
			sprintf(str,"movi M[R[0]+%d],R[255]\n",offset);
			outputTelikos<<str<<endl;
			
			sprintf(str,"movi M[R[255]],R[%d]",r);
			outputTelikos<<str<<endl;
			
		}
	}
	else{
		if(temp->getType()==VAR || (temp->getType()==PAR && temp->getPar()->getParmode()==INTK)){
			int offset;
			int steps=head->getNestingLevel() - nestingLevel;
			
			char str[100];
			sprintf(str,"movi M[4+R[0]],R[255]\n");
			outputTelikos<<str;
			while(steps>1){
				steps--;
				sprintf(str,"movi M[4+R[255]],R[255]\n");
				outputTelikos<<str;
				
				
			}
			
			if(temp->getType()==VAR){
				offset=temp->getVar()->getOffset();
			}
			else{
				offset=temp->getPar()->getOffset();
			}
			sprintf(str,"movi R[254],%d]\n",offset);
			outputTelikos<<str;
			sprintf(str,"addi R[255],R[254],R[255]\n");
			
			
			sprintf(str,"movi M[R[255]],R[%d]",r);
			outputTelikos<<str<<endl;
		}
		else if(temp->getType()==PAR && temp->getPar()->getParmode()==INOUTTK){
			int offset;
			int steps=head->getNestingLevel() - nestingLevel;
			
			char str[100];
			sprintf(str,"movi M[4+R[0]],R[255]\n");
			outputTelikos<<str;
			while(steps>1){
				steps--;
				sprintf(str,"movi M[4+R[255]],R[255]\n");
				outputTelikos<<str;
				
				
			}
			
			if(temp->getType()==VAR){
				offset=temp->getVar()->getOffset();
			}
			else{
				offset=temp->getPar()->getOffset();
			}
			sprintf(str,"movi R[254],%d]\n",offset);
			outputTelikos<<str;
			sprintf(str,"addi R[255],R[254],R[255]\n");
			outputTelikos<<str;
			
			sprintf(str,"movi M[R[255]],R[255]\n");
			outputTelikos<<str;
			
			sprintf(str,"movi M[R[255]],R[%d]",r);
			outputTelikos<<str<<endl;
			
		}
	}
}
void Telikos::convert(){
	Quads *temp=first;
	int nestingLevel;
	
	while(temp!=NULL){
		outputTelikos<<"L"<<temp->getAddress()<<":"<<endl;
		char *op=temp->getOp();
		if(strcmp(op,"par")!=0)
			parCounter=0;
		
		if(strcmp(op,"jump")==0){
			outputTelikos<<"jmp L"<<temp->getZ();
		}
		else if(strcmp(op,"=")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"cmpi R[1],R[2]"<<endl;
			outputTelikos<<"je L"<<temp->getZ()<<endl;
		}
		
		else if(strcmp(op,"<>")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"cmpi R[1],R[2]"<<endl;
			outputTelikos<<"jne L"<<temp->getZ()<<endl;
		}
		
		else if(strcmp(op,">")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"cmpi R[1],R[2]"<<endl;
			outputTelikos<<"jb L"<<temp->getZ()<<endl;
		}
		else if(strcmp(op,">=")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"cmpi R[1],R[2]"<<endl;
			outputTelikos<<"jbe L"<<temp->getZ()<<endl;
		}
		
		else if(strcmp(op,"<")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"cmpi R[1],R[2]"<<endl;
			outputTelikos<<"ja L"<<temp->getZ()<<endl;
		}
		else if(strcmp(op,"<=")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"cmpi R[1],R[2]"<<endl;
			outputTelikos<<"ja L"<<temp->getZ()<<endl;
		}
		else if(strcmp(op,":=")==0){
			loadvr(temp->getX(),1);
			storerv(1,temp->getZ());
		}
		else if(strcmp(op,"+")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"addi R[3],R[1],R[2]"<<endl;
			storerv(3,temp->getZ());	
		}
		else if(strcmp(op,"-")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"subi R[3],R[1],R[2]"<<endl;
			storerv(3,temp->getZ());	
		}
		else if(strcmp(op,"*")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"muli R[3],R[1],R[2]"<<endl;
			storerv(3,temp->getZ());	
		}
		else if(strcmp(op,"/")==0){
			loadvr(temp->getX(),1);
			loadvr(temp->getY(),2);
			outputTelikos<<"divi R[3],R[1],R[2]"<<endl;
			storerv(3,temp->getZ());	
		}
		else if(strcmp(op,"out")==0){
			loadvr(temp->getX(),1);
			outputTelikos<<"outi R[1]"<<endl;
		}
		else if(strcmp(op,"in")==0){
			outputTelikos<<"ini R[1]"<<endl;
			storerv(1,temp->getX());	
		}
		else if(strcmp(op,"retv")==0){
			loadvr(temp->getX(),1);
			outputTelikos<<"movi R[255],M[8+R[0]]"<<endl;
			outputTelikos<<"movi M[R[255]],R[1]"<<endl;			
		}
		else if(strcmp(op,"halt")==0){
			outputTelikos<<"halt"<<endl;
		}
		else if(strcmp(op,"endblock")==0){
			outputTelikos<<"jmp M[R[0]]"<<endl;
		}
		else if(strcmp(op,"par")==0){
			char *y=temp->getY();
			char *funcName;
			Quads *tmp=temp->getNext();
			while(tmp!=NULL && strcmp(tmp->getOp(),"call")!=0){
				tmp=tmp->getNext();
			}
			funcName=tmp->getY();
			
			Entity *ent=head->findEntityAll(funcName,&nestingLevel);
			
			if(strcmp(y,"cv")==0){
				loadvr(temp->getX(),255);
				int d=ent->getFunc()->getFramelength()+12+4*parCounter;
				parCounter++;
				outputTelikos<<"movi M["<<d<<"+R[0]],R[255]"<<endl;
				
			}
			else if(strcmp(y,"ref")==0){
				Entity *ent2=head->findEntityAll(temp->getX(),&nestingLevel);
				if(nestingLevel==head->getNestingLevel()){//vathos iso me to trexwn
					if(ent->getType()==VAR || (ent->getType()==PAR && ent->getPar()->getParmode()==INTK)){
						outputTelikos<<"movi R[255],R[0]"<<endl;
						int offset;
						if(ent2->getType()==VAR){
							offset=ent2->getVar()->getOffset();
						}
						else{
							offset=ent2->getPar()->getOffset();
						}
						outputTelikos<<"movi R[254],"<<offset<<endl;
						outputTelikos<<"addi R[255],R[254],R[255]"<<offset<<endl;
						
						int d=ent->getFunc()->getFramelength()+12+4*parCounter;
						parCounter++;
						outputTelikos<<"movi M["<<d<<"+R[0]],R[255]"<<endl;
					}
					else if(ent->getType()==PAR && ent->getPar()->getParmode()==INOUTTK){
						outputTelikos<<"movi R[255],R[0]"<<endl;
						int offset=9999;
						
						if(ent2->getType()==VAR){
							offset=ent2->getVar()->getOffset();
						}
						else{
							offset=ent2->getPar()->getOffset();
						}
						outputTelikos<<"movi R[254],"<<offset<<endl;
						outputTelikos<<"addi R[255],R[254],R[255]"<<endl;
						
						int d=ent->getFunc()->getFramelength()+12+4*parCounter;
						parCounter++;
						outputTelikos<<"movi R[1],M[R[255]]"<<endl;
						outputTelikos<<"movi M["<<d<<"+R[0]],R[1]"<<endl;
					}
				}
				else{
					if(ent->getType()==VAR || (ent->getType()==PAR && ent->getPar()->getParmode()==INTK)){
						int steps=head->getNestingLevel() - nestingLevel;
						char str[100];
						sprintf(str,"movi R[255],M[4+R[0]]\n");
						outputTelikos<<str;
						while(steps>1){
							steps--;
							sprintf(str,"movi R[255],M[4+R[255]]\n");
							outputTelikos<<str;
						}
						int offset;
						
						if(ent->getType()==VAR){
							offset=ent->getVar()->getOffset();
						}
						else{
							offset=ent->getPar()->getOffset();
						}
						sprintf(str,"movi R[254],%d]\n",offset);
						outputTelikos<<str;
						sprintf(str,"addi R[255],R[254],R[255]\n");
						
						int d=ent->getFunc()->getFramelength()+12+4*parCounter;
						parCounter++;
						outputTelikos<<"movi M["<<d<<"+R[0]],R[255]"<<endl;
					}
					else if(ent->getType()==PAR && ent->getPar()->getParmode()==INOUTTK){
						int steps=head->getNestingLevel() - nestingLevel;
						char str[100];
						sprintf(str,"movi R[255],M[4+R[0]]\n");
						outputTelikos<<str;
						while(steps>1){
							steps--;
							sprintf(str,"movi R[255],M[4+R[255]]\n");
							outputTelikos<<str;
						}
						int offset;
						
						if(ent->getType()==VAR){
							offset=ent->getVar()->getOffset();
						}
						else{
							offset=ent->getPar()->getOffset();
						}
						sprintf(str,"movi R[254],%d]\n",offset);
						outputTelikos<<str;
						sprintf(str,"addi R[255],R[254],R[255]\n");
						
						int d=ent->getFunc()->getFramelength()+12+4*parCounter;
						parCounter++;
						outputTelikos<<"movi R[1],M[R[255]]"<<endl;
						outputTelikos<<"movi M["<<d<<"+R[0]],R[1]"<<endl;
					}
				}
			}
			else if(strcmp(y,"ret")==0){
				int offset=999,framelength=9999;
				Entity *ent2=head->findEntityAll(temp->getX(),&nestingLevel);
				
				if(ent2->getType()==VAR){
					offset=ent2->getVar()->getOffset();
				}
				else{
					offset=ent2->getPar()->getOffset();
				}
				framelength=ent->getFunc()->getFramelength();
				outputTelikos<<"movi R[255],R[0]"<<endl;
				outputTelikos<<"movi R[254]"<<offset<<endl;
				outputTelikos<<"addi R[255],R[254],R[255]"<<endl;
				outputTelikos<<"movi M["<<framelength<<"+8+R[0],R[255]"<<endl;			
			}
		}
		else if(strcmp(op,"call")==0){
			Entity *ent=head->findEntityAll(temp->getX(),&nestingLevel);
			
			int framelength=ent->getFunc()->getFramelength();
			Entity *ent2=head->findEntityAll(temp->getX(),&nestingLevel);
			
			if(nestingLevel==head->getNestingLevel()-1){
				outputTelikos<<"movi R[255],R[0]"<<endl;
				outputTelikos<<"movi M["<<framelength<<"+4+R[0]],R[255]"<<endl;			
			}
			else{
				outputTelikos<<"movi M["<<framelength<<"+4+R[0]],R[0]"<<endl;			
				
			}
			
			outputTelikos<<"movi R[255],"<<framelength<<endl;
			outputTelikos<<"addi R[0],R[255],R[0]"<<endl;
			outputTelikos<<"movi R[255],$"<<endl;
			outputTelikos<<"movi R[254],15"<<endl;
			outputTelikos<<"addi R[255],R[254],R[255]"<<endl;
			outputTelikos<<"movi M[R[0]],R[255]"<<endl;			
			outputTelikos<<"jmp L"<<ent->getFunc()->getStartQuad()<<endl;
			outputTelikos<<"movi R[255],"<<framelength<<endl;
			outputTelikos<<"addi R[0],R[0],R[255]"<<endl;		
		}
		

		
		
		temp=temp->getNext();
	}
	outputTelikos.close();
}
/*
 * Constructor
*/
Analyzer::Analyzer(char *filename){
	this->input.open(filename);
	this->initialize_state_transition();
}

/*
 * If we read a word that must be retured back this function
 * just returns that word that is saved at the struct
 * 
*/
int Analyzer::getLastWordId(){
	return(lastWordId);
}

char *Analyzer::getPlace(){
	return(this->place);
}
void Analyzer::setPlace(char *place){
	strcpy(this->place,place);
}
/*
 * According to a state and the next character state chagnes to a new one
 * 
*/
void Analyzer::initialize_state_transition(){
	state_transition[STATE0][WHITE_SPACE]=STATE0;
	state_transition[STATE0][LETTERS]=STATE1;
	state_transition[STATE0][DIGITS]=STATE2;
	state_transition[STATE0][PLUS]=PLUSTK;
	state_transition[STATE0][MINUS]=MINUSTK;
	state_transition[STATE0][MULTIPLY]=MULTIPLYTK;
	state_transition[STATE0][DIVIDE]=STATE3;
	state_transition[STATE0][LESS]=STATE6;
	state_transition[STATE0][GREATER]=STATE7;
	state_transition[STATE0][EQUAL]=EQUALTK;
	state_transition[STATE0][COLON]=STATE8;
	state_transition[STATE0][LEFTPARENTHESIS]=LEFTPARENTHESISTK;
	state_transition[STATE0][RIGHTPARENTHESIS]=RIGHTPARENTHESISTK;
	state_transition[STATE0][LEFTSQUAREPARENTHESIS]=LEFTSQUAREPARENTHESISTK;
	state_transition[STATE0][RIGHTSQUAREPARENTHESIS]=RIGHTSQUAREPARENTHESISTK;
	state_transition[STATE0][LEFTBRACKETS]=LEFTBRACKETSTK;
	state_transition[STATE0][RIGHTBRACKETS]=RIGHTBRACKETSTK;
	state_transition[STATE0][SEMICOLON]=SEMICOLONTK;
	state_transition[STATE0][COMMA]=COMMATK;
	state_transition[STATE0][ENDFILE]=ENDFILETK;
	state_transition[STATE0][WHATEVER]=ERROR_WHATEVERTK;
	
	
	state_transition[STATE1][WHITE_SPACE]=IDTK;
	state_transition[STATE1][LETTERS]=STATE1;
	state_transition[STATE1][DIGITS]=STATE1;
	state_transition[STATE1][PLUS]=IDTK;
	state_transition[STATE1][MINUS]=IDTK;
	state_transition[STATE1][MULTIPLY]=IDTK;
	state_transition[STATE1][DIVIDE]=IDTK;
	state_transition[STATE1][LESS]=IDTK;
	state_transition[STATE1][GREATER]=IDTK;
	state_transition[STATE1][EQUAL]=IDTK;
	state_transition[STATE1][COLON]=IDTK;
	state_transition[STATE1][LEFTPARENTHESIS]=IDTK;
	state_transition[STATE1][RIGHTPARENTHESIS]=IDTK;
	state_transition[STATE1][LEFTSQUAREPARENTHESIS]=IDTK;
	state_transition[STATE1][RIGHTSQUAREPARENTHESIS]=IDTK;
	state_transition[STATE1][LEFTBRACKETS]=IDTK;
	state_transition[STATE1][RIGHTBRACKETS]=IDTK;
	state_transition[STATE1][SEMICOLON]=IDTK;
	state_transition[STATE1][COMMA]=IDTK;
	state_transition[STATE1][ENDFILE]=IDTK;
	state_transition[STATE1][WHATEVER]=IDTK;
	
	
	
	state_transition[STATE2][WHITE_SPACE]=NUMBERTK;
	state_transition[STATE2][LETTERS]=NUMBERTK;
	state_transition[STATE2][DIGITS]=STATE2;
	state_transition[STATE2][PLUS]=NUMBERTK;
	state_transition[STATE2][MINUS]=NUMBERTK;
	state_transition[STATE2][MULTIPLY]=NUMBERTK;
	state_transition[STATE2][DIVIDE]=NUMBERTK;
	state_transition[STATE2][LESS]=NUMBERTK;
	state_transition[STATE2][GREATER]=NUMBERTK;
	state_transition[STATE2][EQUAL]=NUMBERTK;
	state_transition[STATE2][COLON]=NUMBERTK;
	state_transition[STATE2][LEFTPARENTHESIS]=NUMBERTK;
	state_transition[STATE2][RIGHTPARENTHESIS]=NUMBERTK;
	state_transition[STATE2][LEFTSQUAREPARENTHESIS]=NUMBERTK;
	state_transition[STATE2][RIGHTSQUAREPARENTHESIS]=NUMBERTK;
	state_transition[STATE2][LEFTBRACKETS]=NUMBERTK;
	state_transition[STATE2][RIGHTBRACKETS]=NUMBERTK;
	state_transition[STATE2][SEMICOLON]=NUMBERTK;
	state_transition[STATE2][COMMA]=NUMBERTK;
	state_transition[STATE2][ENDFILE]=NUMBERTK;
	state_transition[STATE2][WHATEVER]=NUMBERTK;
	
	
	state_transition[STATE3][WHITE_SPACE]=DIVIDETK;
	state_transition[STATE3][LETTERS]=DIVIDETK;
	state_transition[STATE3][DIGITS]=DIVIDETK;
	state_transition[STATE3][PLUS]=DIVIDETK;
	state_transition[STATE3][MINUS]=DIVIDETK;
	state_transition[STATE3][MULTIPLY]=STATE4;
	state_transition[STATE3][DIVIDE]=DIVIDETK;
	state_transition[STATE3][LESS]=DIVIDETK;
	state_transition[STATE3][GREATER]=DIVIDETK;
	state_transition[STATE3][EQUAL]=DIVIDETK;
	state_transition[STATE3][COLON]=DIVIDETK;
	state_transition[STATE3][LEFTPARENTHESIS]=DIVIDETK;
	state_transition[STATE3][RIGHTPARENTHESIS]=DIVIDETK;
	state_transition[STATE3][LEFTSQUAREPARENTHESIS]=DIVIDETK;
	state_transition[STATE3][RIGHTSQUAREPARENTHESIS]=DIVIDETK;
	state_transition[STATE3][LEFTBRACKETS]=DIVIDETK;
	state_transition[STATE3][RIGHTBRACKETS]=DIVIDETK;
	state_transition[STATE3][SEMICOLON]=DIVIDETK;
	state_transition[STATE3][COMMA]=DIVIDETK;
	state_transition[STATE3][ENDFILE]=DIVIDETK;
	state_transition[STATE3][WHATEVER]=DIVIDETK;
	
	
	state_transition[STATE4][WHITE_SPACE]=STATE4;
	state_transition[STATE4][LETTERS]=STATE4;
	state_transition[STATE4][DIGITS]=STATE4;
	state_transition[STATE4][PLUS]=STATE4;
	state_transition[STATE4][MINUS]=STATE4;
	state_transition[STATE4][MULTIPLY]=STATE5;
	state_transition[STATE4][DIVIDE]=STATE4;
	state_transition[STATE4][LESS]=STATE4;
	state_transition[STATE4][GREATER]=STATE4;
	state_transition[STATE4][EQUAL]=STATE4;
	state_transition[STATE4][COLON]=STATE4;
	state_transition[STATE4][LEFTPARENTHESIS]=STATE4;
	state_transition[STATE4][RIGHTPARENTHESIS]=STATE4;
	state_transition[STATE4][LEFTSQUAREPARENTHESIS]=STATE4;
	state_transition[STATE4][RIGHTSQUAREPARENTHESIS]=STATE4;
	state_transition[STATE4][LEFTBRACKETS]=STATE4;
	state_transition[STATE4][RIGHTBRACKETS]=STATE4;
	state_transition[STATE4][SEMICOLON]=STATE4;
	state_transition[STATE4][COMMA]=STATE4;
	state_transition[STATE4][ENDFILE]=ERROR_ENDFILETK;
	state_transition[STATE4][WHATEVER]=STATE4;
	
	
	state_transition[STATE5][WHITE_SPACE]=STATE4;
	state_transition[STATE5][LETTERS]=STATE4;
	state_transition[STATE5][DIGITS]=STATE4;
	state_transition[STATE5][PLUS]=STATE4;
	state_transition[STATE5][MINUS]=STATE4;
	state_transition[STATE5][MULTIPLY]=STATE4;
	state_transition[STATE5][DIVIDE]=STATE0;
	state_transition[STATE5][LESS]=STATE4;
	state_transition[STATE5][GREATER]=STATE4;
	state_transition[STATE5][EQUAL]=STATE4;
	state_transition[STATE5][COLON]=STATE4;
	state_transition[STATE5][LEFTPARENTHESIS]=STATE4;
	state_transition[STATE5][RIGHTPARENTHESIS]=STATE4;
	state_transition[STATE5][LEFTSQUAREPARENTHESIS]=STATE4;
	state_transition[STATE5][RIGHTSQUAREPARENTHESIS]=STATE4;
	state_transition[STATE5][LEFTBRACKETS]=STATE4;
	state_transition[STATE5][RIGHTBRACKETS]=STATE4;
	state_transition[STATE5][SEMICOLON]=STATE4;
	state_transition[STATE5][COMMA]=STATE4;
	state_transition[STATE5][ENDFILE]=ERROR_ENDFILETK;
	state_transition[STATE5][WHATEVER]=STATE4;
	
	
	state_transition[STATE6][WHITE_SPACE]=LESSTK;
	state_transition[STATE6][LETTERS]=LESSTK;
	state_transition[STATE6][DIGITS]=LESSTK;
	state_transition[STATE6][PLUS]=LESSTK;
	state_transition[STATE6][MINUS]=LESSTK;
	state_transition[STATE6][MULTIPLY]=LESSTK;
	state_transition[STATE6][DIVIDE]=LESSTK;
	state_transition[STATE6][LESS]=LESSTK;
	state_transition[STATE6][GREATER]=NOT_EQUALTK;
	state_transition[STATE6][EQUAL]=LESSEQUALTK;
	state_transition[STATE6][COLON]=LESSTK;
	state_transition[STATE6][LEFTPARENTHESIS]=LESSTK;
	state_transition[STATE6][RIGHTPARENTHESIS]=LESSTK;
	state_transition[STATE6][LEFTSQUAREPARENTHESIS]=LESSTK;
	state_transition[STATE6][RIGHTSQUAREPARENTHESIS]=LESSTK;
	state_transition[STATE6][LEFTBRACKETS]=LESSTK;
	state_transition[STATE6][RIGHTBRACKETS]=LESSTK;
	state_transition[STATE6][SEMICOLON]=LESSTK;
	state_transition[STATE6][COMMA]=LESSTK;
	state_transition[STATE6][ENDFILE]=LESSTK;
	state_transition[STATE6][WHATEVER]=LESSTK;
	
	
	state_transition[STATE7][WHITE_SPACE]=GREATERTK;
	state_transition[STATE7][LETTERS]=GREATERTK;
	state_transition[STATE7][DIGITS]=GREATERTK;
	state_transition[STATE7][PLUS]=GREATERTK;
	state_transition[STATE7][MINUS]=GREATERTK;
	state_transition[STATE7][MULTIPLY]=GREATERTK;
	state_transition[STATE7][DIVIDE]=GREATERTK;
	state_transition[STATE7][LESS]=GREATERTK;
	state_transition[STATE7][GREATER]=GREATERTK;
	state_transition[STATE7][EQUAL]=GREATEREQUALTK;
	state_transition[STATE7][COLON]=GREATERTK;
	state_transition[STATE7][LEFTPARENTHESIS]=GREATERTK;
	state_transition[STATE7][RIGHTPARENTHESIS]=GREATERTK;
	state_transition[STATE7][LEFTSQUAREPARENTHESIS]=GREATERTK;
	state_transition[STATE7][RIGHTSQUAREPARENTHESIS]=GREATERTK;
	state_transition[STATE7][LEFTBRACKETS]=GREATERTK;
	state_transition[STATE7][RIGHTBRACKETS]=GREATERTK;
	state_transition[STATE7][SEMICOLON]=GREATERTK;
	state_transition[STATE7][COMMA]=GREATERTK;
	state_transition[STATE7][ENDFILE]=GREATERTK;
	state_transition[STATE7][WHATEVER]=GREATERTK;
	
	
	state_transition[STATE8][WHITE_SPACE]=ERROR_COLONTK;
	state_transition[STATE8][LETTERS]=ERROR_COLONTK;
	state_transition[STATE8][DIGITS]=ERROR_COLONTK;
	state_transition[STATE8][PLUS]=ERROR_COLONTK;
	state_transition[STATE8][MINUS]=ERROR_COLONTK;
	state_transition[STATE8][MULTIPLY]=ERROR_COLONTK;
	state_transition[STATE8][DIVIDE]=ERROR_COLONTK;
	state_transition[STATE8][LESS]=ERROR_COLONTK;
	state_transition[STATE8][GREATER]=ERROR_COLONTK;
	state_transition[STATE8][EQUAL]=ASSIGNMENTTK;
	state_transition[STATE8][COLON]=ERROR_COLONTK;
	state_transition[STATE8][LEFTPARENTHESIS]=ERROR_COLONTK;
	state_transition[STATE8][RIGHTPARENTHESIS]=ERROR_COLONTK;
	state_transition[STATE8][LEFTSQUAREPARENTHESIS]=ERROR_COLONTK;
	state_transition[STATE8][RIGHTSQUAREPARENTHESIS]=ERROR_COLONTK;
	state_transition[STATE8][LEFTBRACKETS]=ERROR_COLONTK;
	state_transition[STATE8][RIGHTBRACKETS]=ERROR_COLONTK;
	state_transition[STATE8][SEMICOLON]=ERROR_COLONTK;
	state_transition[STATE8][COMMA]=ERROR_COLONTK;
	state_transition[STATE8][ENDFILE]=ERROR_COLONTK;
	state_transition[STATE8][WHATEVER]=ERROR_COLONTK;
	
}

/*
 * Maps the +, -, *, / and some more symbols with numbers
 * 
*/
int Analyzer::map(char ch){
	char chars[19]={'+','-','*','/','<','>','=',':','(',')','[',']','{','}',';',','};
	int i;
	
	if(ch==EOF){
		return(ENDFILE);
	}
	else if((ch>='a'&&ch<='z') ||(ch>='A'&&ch<='Z')){
		return(LETTERS);
	}
	else if(ch==' ' || ch=='\t' || ch=='\n'){
			return(WHITE_SPACE);
	}
	else if(ch>='0'&&ch<='9'){
		return(DIGITS);
	}

	for(i=0;i<16;i++){
		if(chars[i]==ch)
			return(i+3);
	}

	return(WHATEVER);
}

/*
 * Checks if the word is one of the predefined words and returns the approperate ID
 * 
*/
int Analyzer::check(char *word){
	char defined_words[22][30]={"and","exit","if","program","when","declare","procedure","in","or","call","do","function","inout","return","else","print","not","while","enddeclare","incase","forcase","copy"};

	int i;
	for(i=0;i<22;i++){
		if(strcmp(defined_words[i],word)==0)
			return(i+ANDTK);
	}
	return(IDTK);
}

/*
 * While we are jumping in safe states that are acceptable my the syntax analyzer
 * we read a new word and save it at the stuct. This function is being called as many
 * times as needed from the part of code that implements the syntax analyzer
 *
*/
int Analyzer::nextWord(){
	int work_state = STATE0;
	int new_state;
//	char word[31];
	
	char ch;
	int m,len = 0;
	
	while(work_state <= STATE8){
		// Get a character
		ch = this->input.get();
		
		// Get the ID of this character according to the mapping table
		m = this->map(ch);
		
		// Get the new state according to the state table
		new_state = state_transition[work_state][m];
		
		
		if( (new_state != STATE4) && (new_state != STATE5) ){
			if(len < 30){
				word[len] = ch;
				len++;
			}
		}
		
		if(new_state == STATE0) {
		  len = 0;
		}
		
		work_state = new_state;
	}
	
	word[len] = '\0';
	
	// Check if the state is not one of the error states
	if(work_state == ERROR_COLONTK){
		cout << "Error: Expected = after the :\nWill not exit." << endl;
		exit(0);
	}
	
	if(work_state == ERROR_ENDFILETK){
		cout<<"EOF inside comments.\nWill now exit."<<endl;
		exit(0);
	}
	
	if(work_state == ERROR_WHATEVERTK){
		cout<<"Unexpected character.\nWill now exit."<<endl;
		exit(0);
	}
	
	// In some cases we need to return the character we read
	if(work_state == IDTK || work_state == NUMBERTK || work_state == DIVIDETK || work_state == LESSTK || work_state == GREATERTK){
		word[len-1] = '\0';
		this->input.putback(ch);
	}
	
	// If we finally get here we must check if the word is one of the pre defined words
	if(work_state == IDTK){
		work_state = check(word);
	}
	
	//cout << "Word found: " << word << endl;
	
	strcpy(this->place,word);
	this->lastWordId=work_state;
	return(work_state);
}


/******************************************************************************************/

Quads::Quads(int address,char *op,char *x,char *y,char *z){
	this->address=address;
	
	this->op = new char[strlen(op)+1];
	this->x = new char[strlen(x)+1];
	this->y = new char[strlen(y)+1];
	this->z = new char[strlen(z)+1];
	
	strcpy(this->op,op);
	strcpy(this->x,x);
	strcpy(this->y,y);
	strcpy(this->z,z);
}

Quads::Quads(int address,char *op){
	this->address=address;
	
	this->op = new char[strlen(op)+1];
	this->x= new char[2];
	this->y= new char[2];
	this->z= new char[20];
	
	strcpy(this->op,op);
	strcpy(this->x,"_");
	strcpy(this->y,"_");
	strcpy(this->z,"_");
	
}

Quads::Quads(int address,char *op,char *x){
	this->address=address;
	this->op = new char[strlen(op)+1];
	this->x = new char[strlen(x)+1];

	this->y= new char[2];
	this->z= new char[20];
	
	strcpy(this->y,"_");
	strcpy(this->z,"_");
	
	strcpy(this->op,op);
	strcpy(this->x,x);
}
Quads::Quads(int address,char *op,char *x,char *y){
	this->address=address;
	
	this->op = new char[strlen(op)+1];
	this->x = new char[strlen(x)+1];
	this->y = new char[strlen(y)+1];
	this->z= new char[20];
	
	strcpy(this->op,op);
	strcpy(this->x,x);
	strcpy(this->y,y);
	strcpy(this->z,"_");
}
void Quads::setNext(Quads *next) {
	this->next=next;
}

void Quads::setz(char *z) {
	strcpy(this->z, z);
}

Quads *Quads::getNext() {
	return(this->next);
}
void Quads::print(){//ofstream output) {
	output<<address<<","<<op<<","<<x<<","<<y<<","<<z<<endl;
}
/*****************************************************************************************/
List::List(int x) {
	this->address=x;
	this->next=NULL;
}

List *List::getNext() {
	return(this->next);
}

void List::setNext(List *next) {
	this->next=next;
}

/*****************************************************************************************/
void Syntax::printHead(){
	Scope *temp=head;
	cout<<endl<<endl;
	while(temp!=NULL){
		cout<<temp->getNestingLevel()<<" ";
		temp->print();
		temp=temp->getNext();
		cout<<endl;
	}
}

void Syntax::deleteScope(){
	printHead();
	head=head->getNext();
}

void Syntax::addScope(){
	if(head==NULL){
		head = new Scope(0);
	}
	else{
		Scope *temp= new Scope(head->getNestingLevel()+1);
		temp->setNext(head);
		head=temp;
	}
}
Syntax::Syntax() {
	first=NULL;
	address=100;
	tempCounter=1;
	head=NULL;
	
}

void Syntax::print(char name[30]) {
	//ofstream output;
	output.open(name);
	
	Quads *temp=first;
	while(temp!=NULL){
		temp->print();//output);
		temp=temp->getNext();
	}
	output.close();
}

void Syntax::genquad(char *op) {
	int address = nextquad();
	Quads *newQuads = new Quads(address,op);
	this->address+=10;
	insert(newQuads);
	
	
}

void Syntax::genquad(char *op,char *x) {
	int address = nextquad();
	Quads *newQuads = new Quads(address,op,x);
	this->address+=10;
	insert(newQuads);
	
	
}

void Syntax::genquad(char *op,char *x,char *y) {
	int address = nextquad();
	Quads *newQuads = new Quads(address,op,x,y);
	this->address+=10;
	insert(newQuads);
	
	
}

void Syntax::genquad(char *op,char *x,char *y,char *z) {
	int address = nextquad();
	Quads *newQuads = new Quads(address,op,x,y,z);
	this->address+=10;
	insert(newQuads);
	
}

//eisagwgh tetradas sto telos
void Syntax::insert(Quads *newQuads) {
	if(first==NULL){
		first=newQuads;
	}
	else{
		Quads *temp=first;
		
		while(temp->getNext()!=NULL){
			temp=temp->getNext();
		}
		
		temp->setNext(newQuads);
	}
}

int Syntax::nextquad() {
	return(this->address);
}

char *Syntax::newtemp() {
	char *temp = new char[12];
	
	sprintf(temp,"T_%d",tempCounter);
	int offset = head->getCounter()*4 + 12;
	
	Variable *var = new Variable(offset);
	Entity *ent = new Entity(temp,VAR,var);
	head->addEntity(ent);
	
	tempCounter++;
	return(temp);
}

List *Syntax::makelist(int x){
  List *temp = new List(x);
  return temp;
}

List *Syntax::merge(List *l1, List *l2){
  List *temp = l1;
    while(temp->getNext() != NULL) {
      temp = temp->getNext();
    }
    temp->setNext(l2);
    
    return l1;
}

void Syntax::backpatch(List *l1, int x) {
  char z[30];
  List *temp = l1;
  sprintf(z, "%d", x);
  while(temp != NULL) {
      this->setz(z, temp->getAddress());
      temp = temp->getNext();
    }
}

void Syntax::setz(char z[30], int address) {
    Quads *temp = first;
      while(temp != NULL) {
	if(temp->getAddress() == address) {
	  temp->setz(z);
	  
	  break;
	}
	temp = temp->getNext();
      }
}

/*
 * Error fucntion that prints a specific message according to the argument number.
*/
void Syntax::error(int code){

	switch(code){
		case 1:
			printf("Expected keyword program\n");
			break;
		case 2:
			printf("Expected program name\n");
			break;		
		case 3:
			printf("Expected {\n");
			break;
		case 4:
			printf("Expected variable name after ,\n");
			break;
		case 5:
			printf("Expected keyword enddeclare\n");
			break;		
		case 6:
			printf("Expected keyword in,inout or copy\n");
			break;
		case 7:
			printf("Expected (\n");
			break;
		case 8:
			printf("Expected function name\n");
			break;
		case 9:
			printf("Expected variable name\n");
			break;
		case 10:
			printf("Expected }\n");
			break;
		case 11:
			printf("Expected :=\n");
			break;
		case 12:
			printf("Expected variable name, constant or (\n");
			break;
		case 13:
			printf("Expected ]\n");
			break;
		case 14:
			printf("Expected )\n");
			break;
		case 15:
			printf("Expected <,>,<=,>=,<>, or =\n");
			break;
		case 16:
			printf("Duplicate variable name\n");
			break;
		case 17:
			printf("Duplicate argument name\n");
			break;
		case 18:
			printf("Variable name not found\n");
			break;
		case 19:
			printf("Name is function or procedure\n");
			break;
		default:
			printf("default\n");
	}
	exit(code);
}

/*
 * This is the first function that the syntax analyzer consists of.
 *
*/
void Syntax::program() {
	int wordID;
	wordID=lex->nextWord();
	if( wordID == PROGRAMTK) {
		addScope();
		wordID=lex->nextWord();
		if(wordID==IDTK){
			char name[30];
			strcpy(name,lex->getWord());
			wordID=lex->nextWord();
			block(name,1);
		}
		else{
			error(2);
		}
	}
	else{
		error(1);
	}
}

void Syntax::block(char name[30],int flag) {
	int wordID;
	char op[30];
	
	wordID=lex->getLastWordId();

	if(wordID==LEFTBRACKETSTK){
		wordID=lex->nextWord();
		if(wordID==DECLARETK){
			declarations();
		}
		subprograms();
		
		wordID=lex->getLastWordId();
		strcpy(op,"beginblock");
		if(flag!=1)
			head->getNext()->setStartQuad(nextquad());
		genquad(op,name);
		sequence();
		if(flag==1){
			strcpy(op,"halt");
			genquad(op);
		}else
			head->getNext()->setFramelength(head->getCounter());
		
		
		
		Quads *temp=first,*start=first;
		while(temp!=NULL){
			if(strcmp(temp->getOp(),"endblock")==0){
				start=temp;
			}
			temp=temp->getNext();
		}
		Telikos *fin = new Telikos(start,"finalFile",head);
		//fin->convert();
		
		strcpy(op,"endblock");
		genquad(op,name);
		deleteScope();
		

		
		wordID=lex->getLastWordId();
		if(wordID==RIGHTBRACKETSTK){
			wordID=lex->nextWord();
		}
		else{
			error(10);
		}
	}
	else{
		error(3);
	}
	
}
void Syntax::declarations() {
	int wordID;
	wordID=lex->nextWord();
	if(wordID==IDTK){
		varlist();
	}	
	wordID=lex->getLastWordId();
	
	if(wordID==ENDDECLARETK){
		wordID=lex->nextWord();	
	}
	else{
		error(5);
	}
	
	
}

void Syntax::varlist() {
	int wordID;
	int offset = head->getCounter()*4 + 12;
	
	if(head->findEntity(lex->getPlace())!=NULL){
		error(16);
	}
	Variable *var = new Variable(offset);
	Entity *ent = new Entity(lex->getPlace(),VAR,var);
	head->addEntity(ent);
	
	wordID=lex->nextWord();
	while(wordID==COMMATK){
		wordID=lex->nextWord();
		if(wordID==IDTK){
			offset = head->getCounter()*4 + 12;
			if(head->findEntity(lex->getPlace())!=NULL){
				error(16);
			}
			Variable *var = new Variable(offset);
			Entity *ent = new Entity(lex->getPlace(),VAR,var);
			head->addEntity(ent);
			wordID=lex->nextWord();
		}
		else{
			error(4);
		}
	}
}

void Syntax::subprograms() {
	int wordID=lex->getLastWordId();
	
	while(wordID==PROCEDURETK || wordID==FUNCTIONTK){
		func();
		wordID=lex->getLastWordId();
	}
}

void Syntax::func() {
	int wordID2=lex->getLastWordId();
	int wordID=lex->nextWord();
	char name[30];
	
	if(wordID==IDTK){
		//printf("func %s#%s\n",lex->getWord(),lex->getPlace());
		if(head->findEntity(lex->getPlace())!=NULL){
			error(17);
		}
		Function *var = new Function(wordID2);
		Entity *ent = new Entity(lex->getPlace(),FUNC,var);
		head->addEntity(ent);
		
		addScope();
		strcpy(name,lex->getWord());
		
		funcbody(name);
		//wordID=lex->nextWord();
	}
	else{
		error(8);
	}
}

void Syntax::funcbody(char name[30]) {
	formalpars();
	block(name,0);
}

void Syntax::formalpars() {
	int wordID=lex->nextWord();
	
	if(wordID==LEFTPARENTHESISTK){
		formalparlist();
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			wordID=lex->nextWord();
		}
		else{
			error(14);
		}
	}

}
void Syntax::formalparlist(){
	int wordID;
	do{
		formalparitem();
		wordID=lex->nextWord();
	}while(wordID==COMMATK);
}
void Syntax::formalparitem() {
	
	int wordID=lex->nextWord();
	int offset= head->getCounter()*4 + 12;;
	if(wordID==INTK || wordID==INOUTTK || wordID==COPYTK){
		int wordID2=wordID;
		
		wordID=lex->nextWord();
		
		if(head->findEntity(lex->getPlace())!=NULL){
			error(17);
		}
		Parameter *var = new Parameter(wordID2,offset);
		Entity *ent = new Entity(lex->getPlace(),PAR,var);
		head->addEntity(ent);
		
		if(wordID!=IDTK){
			error(9);
		}
	}
	else{
		error(6);
	}
}

void Syntax::sequence() {
	int wordID;
	
	statement();//diavazei to epomeno
	wordID=lex->getLastWordId();
	while(wordID==SEMICOLONTK){
		wordID=lex->nextWord();
		statement();
		wordID=lex->getLastWordId();
	}
}



void Syntax::statement() {
	int wordID=lex->getLastWordId();
	
	switch(wordID){
		case IDTK:
			
			assignmentstat();
			break;

		case IFTK:
			ifstat();
			break;
		case DOTK:
			dowhilestat();
			break;
		case PRINTTK:
			printstat();
			break;
		case RETURNTK:
			returnstat();
			break;
		case EXITTK:
			exitstat();
			break;
		case WHILETK:
			whilestat();
			break;
		case INCASETK:
			incasestat();
			break;
		case FORCASETK:
			forcasestat();
			break;
		case CALLTK:
			callstat();
			break;
	}
}

void Syntax::assignmentstat() {

	char op[30],x[30],y[30],z[30];
	int nestingLevel;
	
	Entity *temp=head->findEntityAll(lex->getPlace(),&nestingLevel);
	if(temp==NULL){
		error(18);
	}
	else if(temp->getType()==FUNC){
		error(19);
	}
	strcpy(z,lex->getPlace());
	int wordID=lex->nextWord();
	
	
	if(wordID==ASSIGNMENTTK){
		wordID=lex->nextWord();
		expression();
		strcpy(x,lex->getPlace());
		strcpy(op,":=");
		strcpy(y,"_");
		genquad(op,x,y,z);
		wordID=lex->getLastWordId();
	}
	else{
		error(11);
	}
}

void Syntax::optionalsign(){
	addoper();
}
void Syntax::addoper(){
	int wordID=lex->getLastWordId();
	if(wordID==PLUSTK || wordID==MINUSTK){
		wordID=lex->nextWord();
	}
}

void Syntax::expression(){
	int wordID;
	char t1[30],t2[30],op[30];
	char *w;
	
	optionalsign();
	term();
	strcpy(t1,lex->getPlace());
	wordID=lex->getLastWordId();
	while(wordID==PLUSTK || wordID==MINUSTK){
		if(wordID==PLUSTK){
			addoper();
			term();
			strcpy(t2,lex->getPlace());
			w=newtemp();
			strcpy(op,"+");
			genquad(op,t1,t2,w);
			wordID=lex->getLastWordId();
			lex->setPlace(w);
		}
		else{
			addoper();
			term();
			strcpy(t2,lex->getPlace());
			w=newtemp();
			strcpy(op,"-");
			genquad(op,t1,t2,w);
			wordID=lex->getLastWordId();
			lex->setPlace(w);
		}
	}
	
}

void Syntax::term(){
	int wordID;
	char f1[30],f2[30],op[30];
	char *w;
	
	factor();
	strcpy(f1,lex->getPlace());
	wordID=lex->getLastWordId();
	while(wordID==MULTIPLYTK || wordID==DIVIDETK){
		if(wordID==MULTIPLYTK){
			wordID=lex->nextWord();
			factor();
			strcpy(f2,lex->getPlace());
			w=newtemp();
			strcpy(op,"*");
			genquad(op,f1,f2,w);
			wordID=lex->getLastWordId();
			lex->setPlace(w);
		}
		else{
			wordID=lex->nextWord();
			factor();
			strcpy(f2,lex->getPlace());
			w=newtemp();
			strcpy(op,"/");
			genquad(op,f1,f2,w);
			wordID=lex->getLastWordId();
			lex->setPlace(w);
		}
	}
	
}

void Syntax::factor(){
	int wordID=lex->getLastWordId();
	char place[30];
	strcpy(place,lex->getPlace());
	if(wordID==NUMBERTK){
		wordID=lex->nextWord();
		lex->setPlace(place);
	}else if(wordID==LEFTPARENTHESISTK){
		wordID=lex->nextWord();
		expression();
		strcpy(place,lex->getPlace());
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			wordID=lex->nextWord();
			lex->setPlace(place);
		}
		else{
			error(14);
		}
	}
	else if(wordID==IDTK){
		int x;
		Entity *temp=head->findEntityAll(lex->getPlace(),&x);
		if(temp==NULL){
			error(18);
		}
		
		
		idtail(place);
		lex->setPlace(place);
	}
	else{
		error(12);
	}
}

int Syntax::actualpars() {
	int wordID=lex->nextWord();
	
	if(wordID==LEFTPARENTHESISTK){
		actualparlist();
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			wordID=lex->nextWord();
		}
		else{
			error(14);
		}
		return(1);
	}
	return(0);//den exw parenthesi
}
void Syntax::idtail(char name[30]){
	
	int k=actualpars();
	char op[30],y[30];
	
	if(k==1){
		char *x=newtemp();
		strcpy(op,"par");
		strcpy(y,"ret");
		genquad(op,x,y);
		strcpy(op,"call");
		genquad(op,name);
		strcpy(name,x);//to name exei pleon to return ths klhshs
	}
}
void Syntax::actualparlist(){
	int wordID;
	do{
		actualparitem();
		wordID=lex->getLastWordId();
	}while(wordID==COMMATK);
}
void Syntax::actualparitem() {
	int wordID=lex->nextWord();
	char op[30],y[30];
	strcpy(op,"par");
	
	if(wordID==INTK){
		wordID=lex->nextWord();
		expression();
		
		
		strcpy(y,"cv");
		genquad(op,lex->getPlace(),y);
		
	}
	else if(wordID==INOUTTK){
		wordID=lex->nextWord();
		if(wordID!=IDTK){
			error(9);
		}
		strcpy(y,"ref");
		genquad(op,lex->getPlace(),y);
		wordID=lex->nextWord();
	}
	else if(wordID==COPYTK){
			wordID=lex->nextWord();
			if(wordID!=IDTK){
				
				error(9);
			}
			strcpy(y,"copy");
			genquad(op,lex->getPlace(),y);
			wordID=lex->nextWord();
		}
	else{
		error(6);
	}
}

void Syntax::condition(List **T, List **F){
	int wordID;
	List *T1;
	List *F1;
	List *T2;
	List *F2;
	
	boolterm(&T1, &F1);
	wordID=lex->getLastWordId();
	while(wordID==ORTK){
		wordID=lex->nextWord();
		backpatch(F1, nextquad());
		boolterm(&T2, &F2);
		wordID=lex->getLastWordId();
		T1 = merge(T1, T2);
		F1 = F2;
	}
	*T=T1;
	*F=F1;
}

void Syntax::boolterm(List **T,List **F){
	int wordID;
	List *T1;
	List *F1;
	List *T2;
	List *F2;
	
	boolfactor(&T1, &F1);
	wordID=lex->getLastWordId();
	while(wordID==ANDTK){
		wordID=lex->nextWord();
		backpatch(T1, nextquad());
		boolfactor(&T2, &F2);
		wordID=lex->getLastWordId();
		F1 = merge(F1, F2);
		T1 = T2;
	}
	*T=T1;
	*F=F1;
	
}

void Syntax::boolfactor(List **T,List **F){
	char e1[30], e2[30], relop[30];
	int wordID=lex->getLastWordId();
	List *t,*f;
	// true and false lsit
	if(wordID==NOTTK){
		wordID=lex->nextWord();
		if(wordID==LEFTSQUAREPARENTHESISTK){
			wordID=lex->nextWord();
			condition(F, T); // anapoda gt eimai sto not
			
			wordID=lex->getLastWordId();
			if(wordID==RIGHTSQUAREPARENTHESISTK){
				wordID=lex->nextWord();
			}
			else{
				error(13);
			}
		}
	}
	else if(wordID==LEFTSQUAREPARENTHESISTK){
		wordID=lex->nextWord();
		condition(T, F);
		
		wordID=lex->getLastWordId();
		if(wordID==RIGHTSQUAREPARENTHESISTK){
			wordID=lex->nextWord();
		}
		else{
			error(13);
		}
	}else {
		expression();
		strcpy(e1, lex->getPlace());
		strcpy(relop, lex->getWord());
		
		relationaloper();
		
		expression();
		strcpy(e2, lex->getPlace());
		t = makelist(nextquad());
		genquad(relop, e1, e2);
		f = makelist(nextquad());
		strcpy(e1, "jump");
		genquad(e1); 
		*T=t;
		*F=f;
	}
}

void Syntax::relationaloper(){
	int wordID=lex->getLastWordId();
	if(wordID==EQUALTK || wordID==GREATERTK || wordID==LESSTK || wordID==GREATEREQUALTK || wordID==LESSEQUALTK || wordID==NOT_EQUALTK){
		char place[30];
		strcpy(place,lex->getPlace());
		wordID=lex->nextWord();
		//lex->setPlace(place);
	}
	else{
		error(15);
	}
}

void Syntax::ifstat() {
	int wordID;
	List *T , *F, *J;
	char jump[30];
	strcpy(jump,"jump");
	wordID=lex->nextWord();
	if(wordID==LEFTPARENTHESISTK){
		wordID=lex->nextWord();
		condition(&T, &F);
		backpatch(T,nextquad());
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			brackorstat();
			
			J=makelist(nextquad());
			
			genquad(jump);
			
			wordID=lex->getLastWordId();
			backpatch(F,nextquad());
			
			elsepart();
			
			backpatch(J,nextquad());
		}
		else{
			error(14);
		}
	}
	else{
		error(7);
	}
}

void Syntax::brackorstat(){
	int wordID=lex->nextWord();
	
	if(wordID==LEFTBRACKETSTK){
		bracket_seq();
	}
	else{
		statement();
	}
}

void Syntax::bracket_seq(){
	int wordID=lex->nextWord();
	
	sequence();
	wordID=lex->getLastWordId();
	if(wordID==RIGHTBRACKETSTK){
		wordID=lex->nextWord();
	}
	else{
		error(10);
	}
}

void Syntax::elsepart() {
	int wordID;
	
	wordID=lex->getLastWordId();
	if(wordID==ELSETK){
		brackorstat();
	}
}

void Syntax::dowhilestat(){
	
	List *T, *F;
//	char op[30],x[30],y[30],z[30];
	
	int wordID;
	int doquad = nextquad();
	
	brackorstat();
	wordID=lex->getLastWordId();
	if(wordID==WHILETK){
		wordID=lex->nextWord();
		if(wordID==LEFTPARENTHESISTK){
			wordID=lex->nextWord();
			condition(&T, &F);
			backpatch(T,doquad);
			backpatch(F,nextquad());
			wordID=lex->getLastWordId();
			if(wordID==RIGHTPARENTHESISTK){
				
				wordID=lex->nextWord();
			}
			else{
				error(14);
			}
		}
		else{
			error(7);
		}
	}
}

void Syntax::returnstat(){
	
	int wordID;
	char op[30];;
	wordID=lex->nextWord();
	if(wordID==LEFTPARENTHESISTK){
		wordID=lex->nextWord();
		expression();
		strcpy(op,"retv");
		genquad(op,lex->getPlace());
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			
			wordID=lex->nextWord();
		}
		else{
			error(14);
		}
	}
	else{
		error(7);
	}
}

void Syntax::printstat(){
	
	int wordID;
	char op[30];;
	
	wordID=lex->nextWord();
	if(wordID==LEFTPARENTHESISTK){
		wordID=lex->nextWord();
		expression();
		strcpy(op,"out");
		genquad(op,lex->getPlace());
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			
			wordID=lex->nextWord();
		}
		else{
			error(14);
		}
	}
	else{
		error(7);
	}
}

void Syntax::exitstat(){
	int wordID;
	wordID=lex->nextWord();
}

void Syntax::whilestat(){
	int wordID;
	List *T, *F;
	char op[30],x[30],y[30],z[30];
	
	wordID=lex->nextWord();
	if(wordID==LEFTPARENTHESISTK){
		wordID=lex->nextWord();
		int cond=nextquad();
		condition(&T, &F);
		backpatch(T, nextquad());
		wordID=lex->getLastWordId();
		if(wordID==RIGHTPARENTHESISTK){
			
			brackorstat();
			strcpy(op,"jump");
			strcpy(x,"_");
			strcpy(y,"_");
			sprintf(z,"%d",cond);
			genquad(op,x,y,z);
			backpatch(F,nextquad());
		}
		else{
			error(14);
		}
	}
	else{
		error(7);
	}	
}


void Syntax::forcasestat(){
	int wordID;
	List *T, *F;
	wordID=lex->nextWord();
	
	int start = nextquad();
	char x[30],op[30],y[30];

	
	
	while(wordID==WHENTK){
		wordID=lex->nextWord();
		if(wordID==LEFTPARENTHESISTK){
			wordID=lex->nextWord();
			condition(&T, &F);
			backpatch(T, nextquad());
			
			wordID=lex->getLastWordId();
			if(wordID==RIGHTPARENTHESISTK){
				
				brackorstat();
				strcpy(op,"jump");
				sprintf(x,"%d",start);
				strcpy(y,"_");
				genquad(op,y,y,x);
				
				backpatch(F, nextquad());
			}
			else{
				error(14);
			}
		}
		else{
			error(7);
		}
		wordID=lex->getLastWordId();
		
		backpatch(F, nextquad());
	}
}

void Syntax::incasestat(){
	int wordID;
	List *T, *F;
	
	int start = nextquad();
	
	char x[30],op[30],y[30];
	char *counter=newtemp();
	strcpy(op,":=");
	strcpy(x,"0");
	strcpy(y,"_");
	genquad(op,x,y,counter);
	
	wordID=lex->nextWord();
	
	while(wordID==WHENTK){
		wordID=lex->nextWord();
		if(wordID==LEFTPARENTHESISTK){
			wordID=lex->nextWord();
			condition(&T, &F);
			backpatch(T, nextquad());
			strcpy(op,"+");
			strcpy(x,"1");
			
			genquad(op,x,counter,counter);
			wordID=lex->getLastWordId();
			if(wordID==RIGHTPARENTHESISTK){
				
				brackorstat();
				backpatch(F, nextquad());
			}
			else{
				error(14);
			}
		}
		else{
			error(7);
		}
		wordID=lex->getLastWordId();
	}
	strcpy(op,">");
	sprintf(x,"%d",start);
	strcpy(y,"0");
	genquad(op,y,counter,x);
}

void Syntax::callstat(){
	int wordID;
	char name[30],op[30];
	
	wordID=lex->nextWord();
	if(wordID==IDTK){
		strcpy(name,lex->getWord());
		actualpars();
		strcpy(op,"call");
		genquad(op,name);
	}
	else{
		error(9);
	}
}
void try1(List **x) {
	*x = new List(2);
	
}


Argument::Argument(int parmode, int type){
	this->parmode=parmode;
	this->type=type;
}

Argument* Argument::getNext(){
	return(this->next);
}

void Argument::setNext(Argument *next){
	this->next=next;
}



Variable::Variable(int offset){
	this->offset=offset;
}
int Variable::getOffset(){
	return(offset);
}
void Variable::setOffset(int offset){
	this->offset=offset;
}

Function::Function(int type){
	this->type=type;
	this->listArg=NULL;
}
int Function::getStartQuad(){
	return(startQuad);
}

void Function::setStartQuad(int startQuad){
	this->startQuad=startQuad;
}
int Function::getFramelength(){
	return(framelength);
}
void Function::setFramelength(int framelength){
	this->framelength=framelength;
}

int Function::getType(){
	return(this->type);
}

Parameter::Parameter(int parmode, int offset){
	this->parmode=parmode;
	this->offset=offset;
}
int Parameter::getParmode(){
	return(parmode);
}
int Parameter::getOffset(){
	return(offset);
}


Entity::Entity(char name[30],int type,Variable *var){
	this->var=var;
	strcpy(this->name,name);
	this->type=type;
}

Entity::Entity(char name[30],int type,Function *func){
	this->func=func;
	strcpy(this->name,name);
	this->type=type;
}
Entity::Entity(char name[30],int type,Parameter *par){
	this->par=par;
	strcpy(this->name,name);
	this->type=type;
}

Variable *Entity::getVar(){
	return(var);
}

Function *Entity::getFunc(){
	return(func);
}

Parameter *Entity::getPar(){
	return(par);
}
Entity *Entity::getNext(){
	return(next);
}
void Entity::print(){
	if(type==VAR){
		cout<<name<<","<<var->getOffset()<<" ";
	}
	else if(type==PAR){
		cout<<name<<","<<par->getOffset()<<",";
		if(par->getParmode()==INTK)
			cout<<"cv ";
		else if(par->getParmode()==INOUTTK)
			cout<<"ref ";
		else 
			cout<<"copy ";
	}
	else if(type==FUNC){
		cout<<name<<",";
		if(func->getType()==PROCEDURETK){
			cout<<"PROCEDURE,";
		}
		else{
			cout<<"FUNCTION,";
		}
		cout<<func->getFramelength()<<","<<func->getStartQuad()<<" ";
	}
}
void Entity::setNext(Entity *next){
	this->next=next;
}
void Scope::setFramelength(int counter){
	Entity *temp=listEntity;
	
	while(temp->getNext()!=NULL){
		temp=temp->getNext();
	}
	temp->getFunc()->setFramelength(12+counter*4);
}

void Scope::setStartQuad(int startQuad){
	Entity *temp=listEntity;
	
	while(temp->getNext()!=NULL){
		temp=temp->getNext();
	}
	temp->getFunc()->setStartQuad(startQuad);
}
void Scope::incCounter(){
	counter++;
}
void Scope::print(){
	Entity *temp=listEntity;
	
	while(temp!=NULL){
		temp->print();
		temp=temp->getNext();
	}
}
Scope::Scope(int nestingLevel){
	this->nestingLevel=nestingLevel;
	this->next=NULL;
	this->listEntity=NULL;
	this->counter=0;
}
int Scope::getCounter(){
	return(counter);
}

int Scope::getNestingLevel(){
	return(this->nestingLevel);
}

void Scope::setNext(Scope *next){
	this->next=next;
}
Scope *Scope::getNext(){
	return(this->next);
}


Entity *Scope::findEntityAll(char *name,int *nestingLevel){
	Entity *temp=listEntity;
	Scope *temp1=this;
	do{
		*nestingLevel=temp1->nestingLevel;
		
		while(temp!=NULL){
			if(strcmp(temp->getName(),name)==0){
				return(temp);
			}
			temp=temp->getNext();
		}
		temp1=temp1->getNext();
	}while(temp1!=NULL);
	
	return(temp);
	
}
Entity *Scope::findEntity(char *name){
	Entity *temp=listEntity;
	Scope *temp1=this;

		
	while(temp!=NULL){
		if(strcmp(temp->getName(),name)==0){
			return(temp);
		}
		temp=temp->getNext();
	}

	return(temp);

}
void Scope::addEntity(Entity *ent){
	Entity *temp;
	
	if(listEntity==NULL){
		listEntity=ent;
	}
	else{
		temp=listEntity;
		while(temp->getNext()!=NULL){
			temp=temp->getNext();
		}
		
		temp->setNext(ent);
		
	}
	if(ent->getType()!=FUNC)
		incCounter();
}
/* 
 * Main function
 *
 * Gets input file as command line argument
 * and while we have not reasched the end of
 * the file it keeps returning words 
*/



int main(int argc,char *argv[]){
  int wordID = 0;
  Syntax *syntaxAnalyzer = new Syntax();
	
 	char filename[30];
	for(int i=1;i<=1;i++){
		outputTelikos.open("finalFile",ios::app);
		outputTelikos<<"movi R[0],600"<<endl;
		outputTelikos.close();
		
		sprintf(filename,"test%d.st",i);
		lex = new Analyzer(filename);
		syntaxAnalyzer->program();
		sprintf(filename,"1770_1931_test%d.st",i);
		syntaxAnalyzer->print(filename);
	}
  return 0;
}
