/* program simplu de analiza a expresiilor cu variabile */
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>

#define DELIMITATOR 1
#define VARIABILA 2
#define NUMAR 3

extern char *prog; //indica spre expresia de analizat
char simb[80];
char tip_simb;
double vars[26]={ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
									0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

void eval_exp(double *rezultat),eval_exp2(double *rezultat);
void eval_exp1(double *rezultat);
void eval_exp3(double *rezultat),eval_exp4(double *rezultat);
void eval_exp5(double *rezultat);
void eval_exp6(double *rezultat),atom(double *rezultat);
void get_token(void),putback(void);
void serror(int eroare);
double find_var(char *s);
int isdelim(char c);

/* punct de intrare program */ 
void eval_exp(double *rezultat)
{
	get_token();
	if(!*simb)
	{
		serror(2);
		return;
	}
	eval_exp1(rezultat);
	if(*simb) serror(0); //ultimul simbol trebuie sa fie nul
}

/* procesarea unei atribuiri */
void eval_exp1(double *rezultat)
{
	int fanta;
	char temp_simb[80],sseg_tip;
	
	if(tip_simb==VARIABILA)
	{
		//salveaza vechiul simbol
		strcpy(temp_simb,simb);
		sseg_tip=tip_simb;
		
		//calculeaza indicele variabilei
		fanta=toupper(*simb)-'A';
		get_token();
		if(*simb!='=')
		{
			putback(); //returneaza segmenul curent
			//restabileste vechiul simbol - atribuire
			strcpy(simb,temp_simb);
			tip_simb=sseg_tip;
		}
		else
		{
			get_token();	//preia urmatoare parte din expresie
			eval_exp2(rezultat);
			vars[fanta]=*rezultat;
			return;
		}
	}
	eval_exp2(rezultat);
}
		
/* aduna sau scade doi termeni */
void eval_exp2(double *rezultat)
{
	char op;
	double temp;
	eval_exp3(rezultat);
	while((op=*simb)=='+' || op=='-')
	{
		get_token();
		eval_exp3(&temp);
		switch(op)
		{
			case '-':
				*rezultat=*rezultat-temp;
				break;
			case '+':
				*rezultat=*rezultat+temp;
				break;
		}
	}
}

/* inmulteste sau imparte doi factori */
void eval_exp3(double *rezultat)
{
	char op;
	double temp;
	eval_exp4(rezultat);
	while((op=*simb)=='*' || op=='/' || op=='%')
	{
		get_token();
		eval_exp4(&temp);
		switch(op)
		{
			case '*':
				*rezultat=*rezultat*temp;
				break;
			case '/':
				*rezultat=*rezultat/temp;
				break;
			case '%':
				*rezultat=(int)*rezultat%(int)temp;
				break;
		}
	}
}

/* proceseaza un exponent */
void eval_exp4(double *rezultat)
{
	double temp,ex;
	int t;
	
	eval_exp5(rezultat);
	if(*simb=='^')
	{
		get_token();
		eval_exp4(&temp);
		ex=*rezultat;
		if(temp==0.0)
		{
			*rezultat=1.0;
			return;
		}
		for(t=temp-1;t>0;--t) *rezultat=(*rezultat)*(double)ex;
	}
}

/* evalueaza un + sau - unar */
void eval_exp5(double *rezultat)
{
	char op;
	
	op=0;
	if((tip_simb==DELIMITATOR) && *simb=='+' || *simb=='-')
	{
		op=*simb;
		get_token();
	}
	eval_exp6(rezultat);
	if(op=='-') *rezultat=-(*rezultat);
}

/* proceseaza o expresie intre paranteze */
void eval_exp6(double *rezultat)
{
	if(*simb=='(')
	{
		get_token();
		eval_exp2(rezultat);
		if(*simb!=')') serror(1);
		get_token();
	}
	else atom(rezultat);
}

/* obtine valoarea unui numar */
void atom(double *rezultat)
{
	switch(tip_simb)
	{
		case VARIABILA:
			*rezultat=find_var(simb);
			get_token();
			return;
		case NUMAR:
			*rezultat=atof(simb);
			get_token();
			return;
		default:
			serror(0); //altfel eroare de sintaxa in expresie
	}
}

/* returneaza un simbol in fluxul de intrare */
void putback(void)
{
	char *t;
	
	t=simb;
	for(;*t;t++) prog--;
}

/* afiseaza o eroare de sintaxa */
void serror(int eroare)
{
	static char *e[]={
		"Eroare de sintaxa",
		"Paranteze neperechi",
		"Nici o expresie prezenta"
	};
	printf("%s\n",e[eroare]);
	fflush(stdout);
}

/* returneaza urmatorul simbol */
void get_token(void)
{
	char *temp;
	tip_simb=0;
	temp=simb;
	*temp='\0';
	if(!*prog) return; //la sfirsitul expresiei
	while(isspace(*prog)) ++prog; //omite spatiile albe
	if(strchr("+-*/%^=()",*prog))
	{
		tip_simb=DELIMITATOR;
		/* treci la urmatorul caracter */
		*temp++=*prog++;
	}
	else if(isalpha(*prog))
	{
		while(!isdelim(*prog)) *temp++=*prog++;
		tip_simb=VARIABILA;
	}
	else if(isdigit(*prog))
	{
		while(!isdelim(*prog)) *temp++=*prog++;
		tip_simb=NUMAR;
	}
	*temp='\0';
}
/* returneaza adevarat daca c este delimitator */
int isdelim(char c)
{
	if(strchr(" +-/*%^=()",c) || c==0 || c=='\r' || c==0) return 1;
	return 0;
}

/* Returneaza valoarea unei variabile */
double find_var(char *s)
{
	if(!isalpha(*s))
	{
		serror(1);
		return 0.0;
	}
	return vars[toupper(*simb)-'A'];
}
