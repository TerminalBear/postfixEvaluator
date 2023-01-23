#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "stack.h"

using namespace std;

bool isFunct(char& curr);
void add(stack<int>& s, string &output);
void sub(stack<int>& s, string &output);
void mult(stack<int>& s, string &output);
void div(stack<int>& s, string &output);
void exp(stack<int>& s, string &output);
void mod(stack<int>& s, string &output);
string parse(string in);

class DivisionByZero{};

int main()
{
bool loop = true;
do{			// choice != 'Y', ends program
	string output;
	stack <int> s(20);	
	string in;
	bool run = true;	// upon semicolon, run = false
	bool isNeg = false;
	cout<<"\t\t######################\n\t\tTHE POSTFIX EVALUATOR\n\t\t######################"<<endl;
	cout<<"\nInput a postfix mathematical expression: ";	
	while(run){
		getline(cin, in);
		in = parse(in);
		istringstream scan(in);	
		do{
			int num;
			string subs;	// word
			scan >> subs;
			istringstream ss(subs);
			
			if(isdigit(subs[0])){
				ss>>num;
				if(!isNeg)
					s.push(num);
				else{
					num *= -1;
					s.push(num);
					isNeg = false;
				}
			
				stringstream ss;
				ss << num;
				output += "Token = " + ss.str() + "\tPush "+ ss.str()+"\n";
			}
			else{
				for(int i = 0; i < subs.length(); i++){
					char curr = subs[i];
						if(curr == ';')
							run = false;
						else if(isFunct(curr)){		// if the char is a operator
								if(curr == '+'){
									add(s, output);
								}
								else if(curr == '-'){
									sub(s, output);
								}
								else if(curr == '*'){
									mult(s, output);
								}
								else if(curr == '/'){
									div(s, output);
								}
								else if(curr == '^'){
									exp(s, output);
								}
								else if(curr == '%'){
									mod(s, output);
								}
								else if(curr == '_'){
									isNeg = true;
								}
								else if(curr == ';'){
									run = false;
								}
						}
						else if(curr!=' '){
								cout<<"Exception -- You have entered an invalid expression. Now exiting."<<endl;
								return 0;					
						}
				}
			}
		}while(scan);	// end of while-space loop
	}	// end of run-while loop
		cout<<output;
		cout<<"Token = ;\tPop "<<s.top()<<endl;            s.pop();

	cout<<"\nAgain? (Y/N)"<<endl;
	char choice;	cin>>choice;
		if(choice == 'Y'){
			s.makeEmpty();
			output=="";
		}
		else
			loop = false;
}while(loop);
	
	system("clear");
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string parse(string in){
	string p;
	for(int i = 0; i < in.length(); i++){
		if(isdigit(in[i])){
			p+=in[i];
			if(!isdigit(in[i+1])){
				if(isFunct(in[i+1]))
					p+=' ';
				else if(in[i+1] == ' ')
					p+=' ';
			}	
		}else if(isFunct(in[i])){
			p+=in[i];
			if(isdigit(in[i+1])||isFunct(in[i+1])){
				p+=' ';
			}else if(in[i+1] == ' ')
				p+= ' ';
		}			
	}
	return p;
}

bool isFunct(char &curr){
	if(curr == '+'|| curr == '-' || curr == '*' || curr == '/' || curr == '^' || curr == '%' || curr == '_' || curr == ';')
		return true;
	else
		return false;
}
	
void add(stack<int>& s, string &output){
	int x = s.topAndPop();
	int y = s.topAndPop();
	int z =x+y;
	s.push(z);
		stringstream n, o, p;
               							n<<x;
                output += "Token = +\tPop " + n.str();		o<<y;
		output += "\t\tPop " + o.str();			p<<z;
		output += "\t\tPush "+ p.str()+"\n";
}

void sub(stack<int>& s, string &output){
	int x = s.topAndPop();
	int y = s.topAndPop();
	int z =y-x;
	s.push(z);
		stringstream n, o, p;
								n<<x;
                output += "Token = -\tPop " + n.str();		o<<y;
                output += "\t\tPop " + o.str();         	p<<z;
                output += "\t\tPush "+ p.str()+"\n";
}

void mult(stack<int>& s, string &output){
	int x = s.topAndPop();
	int y = s.topAndPop();
	int z=x*y;
	s.push(z);
		stringstream n, o, p;
                	                                        n<<x;
                output += "Token = *\tPop " + n.str();          o<<y;
                output += "\t\tPop " + o.str();                 p<<z;
                output += "\t\tPush "+ p.str()+"\n";

}

void div(stack<int>& s, string &output){
	int x = s.topAndPop();
	int y = s.topAndPop();
	try{
		if(x == 0)
			throw DivisionByZero();	
		int z=y/x;
		s.push(z);
			stringstream n, o, p;
									n<<x;
			output += "Token = /\tPop " + n.str();          o<<y;
			output += "\t\tPop " + o.str();                 p<<z;
			output += "\t\tPush "+ p.str()+"\n";
	
		} catch (DivisionByZero exc){
			cerr<<"Error: Division by zero is invalid. Stack is now empty.\nPlease re-enter input:"<<endl;
		s.makeEmpty();
	}
}

void exp(stack<int>& s, string &output){
	int x = s.topAndPop();
	int y = s.topAndPop();	
	int z = y;
	for(int j = 1; j<x; j++){
		z=z*y;
	}
	s.push(z);
                stringstream n, o, p;
                                                                n<<x;
                output += "Token = ^\tPop " + n.str();          o<<y;
                output += "\t\tPop " + o.str();                 p<<z;
                output += "\t\tPush "+ p.str()+"\n";

}

void mod(stack<int>& s, string &output){
	int x = s.topAndPop();
        int y = s.topAndPop();
	int z = y%x;
	s.push(z);
                stringstream n, o, p;
                                                                n<<x;
                output += "Token = %\tPop " + n.str();          o<<y;
                output += "\t\tPop " + o.str();                 p<<z;
                output += "\t\tPush "+ p.str()+"\n";
}


