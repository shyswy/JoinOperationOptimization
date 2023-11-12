#include <bits/stdc++.h>
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include<string.h>
#include<string>
int cnt=0;
using namespace std;
vector<vector<string>> first_Array;
class name_age {
	public:
		string name;
		string age;
		
		void set_name_age(string tuple)
		{
			stringstream tuplestr(tuple);
			string agestr;

			getline(tuplestr, name, ',');
			getline(tuplestr, age);
		}
};

class name_salary {
	public:
		string name;
		string salary;
		
		void set_name_salary(string tuple)
		{
			stringstream tuplestr(tuple);
			string salarystr;

			getline(tuplestr, name, ',');
			getline(tuplestr, salary);
		}
};

string make_tuple(string name, string age, string salary)
{
	return name+ ',' + age + ',' + salary + '\n';
}
string line_Array_f[100];

int main(){

	string buffer[2];
	name_age temp0;
	name_salary temp1;
	int current_block[2] = {};
	ifstream block[12];//input & output
	ofstream output;

	output.open("./output1.csv");

	if(output.fail())
	{
		cout << "output file opening fail.\n";
	}

	int  br=0,bs=0;
	int pr=0,ps=0;
	int i=0;
	temp0=name_age();
	temp1=name_salary();
	
	block[1].open("./name_salary/0.csv");
	getline(block[1],buffer[1]);
	temp1.set_name_salary(buffer[1]);
	//here, eval equality?
	int chk=1;
while(br!=1000&&bs!=1000){// ~10th block
	bool done1=false;
	
	while(br!=1000&&!done1){
	
		if(chk==1){//if need to open new, next block
			block[i].close();
      string line;
      char num='0';
      string f="./name_age/";
      string b=".csv";
      string ss;
      ss+=f;
      ss+=to_string(br);
      ss+=b;
      block[i].open(ss);
      chk=0;
      }

	
	
	if( block[i].is_open() ){
		if(!block[i].eof()) {		
		getline(block[i],buffer[0]);
		temp0.set_name_age(buffer[0]);
		 if(block[i].eof()){ //if next tuple does not exist, previously move to  next block
              br++;
              chk=1;
			 	continue; 
 
         }
		  if(temp0.name.compare(temp1.name)==0){//nat join two tuple
                    string test2 =make_tuple(temp0.name,temp0.age,temp1.salary);//add to join table and continue
					output<<test2;
					cnt++;
		  }
          else if(temp1.name.compare(temp0.name)==-1  ){
                       done1=true;

          }
		  else{
			  done1=true;
		  }


		}
		else{
			 br++;
             chk=1;

		}
	}

	}

	bool done=false;
	int j=1;
	int chk2=0;
	while(bs!=1000&&!done){
		if(chk2==1){
			block[1].close();
		//	cout<<"innter block change!"<<endl;
		 	string ff="./name_salary/";
 	     	string bb=".csv";
    	  	string ssss;
     	 	ssss+=ff;
     	 	ssss+=to_string(bs);
     	 	ssss+=bb;
      		block[j].open(ssss);
			chk2=0;
		}
      	if( block[j].is_open() ){
        	  if(!block[j].eof()){
            	  getline(block[j],buffer[1]);
				  if(block[j].eof()){//if next tuple does not exist,;
                         bs++; //if one block done, next block!
						 chk2=1;
						 continue;
                    }

  
          		 temp1.set_name_salary(buffer[1]);
				  if(temp0.name.compare(temp1.name)==0){//nat join two tuple
                  	string test1=make_tuple(temp0.name,temp0.age,temp1.salary);//add to join table and continue
					output<<test1;
					cnt++;
			      }
				  else if( temp0.name.compare(temp1.name)==-1){ 
					  done=true;
				  }
				  else{
						done=true;
				  }

 
          	}
			  else{
					bs++;
					chk2=1;
			  }
  
      }
			
	}//find unequal s tuple or done s tuple

}
	block[0].close();
    block[1].close();
	output.close();

}
