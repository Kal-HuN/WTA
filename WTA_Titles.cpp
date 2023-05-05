#include <cstdlib>
#include <iostream>
#include <forward_list>
#include <fstream>
#include "WTAParse.h"

using namespace std;


const string finalsfile="finals.csv";
const string resultfile="wta_matches_2023.csv";

int main ()
{
	forward_list<Parse> finals;
	auto end=finals.before_begin();
	string line, header;
	
	ifstream filein(finalsfile);
	while (getline(filein, line)){
		end=finals.emplace_after(end, line);
	}
	filein.close();
	
	filein.open(resultfile);
	getline(filein, header);
	while (getline(filein, line)){
		Parse match(line);
		if (!match.fed() && match.final()){
			auto f=finals.before_begin();
			for (auto i=finals.begin();i!=finals.end();i++){
				if (i->winner()>match.winner())
					break;
				f=i;
			}
			finals.insert_after(f, match);
		}
	}
	filein.close();
	
	string pname="";
	int numt;
	ofstream fileout("titles.csv");
	fileout<<"titles," <<header <<endl;
	for (auto i=finals.begin();i!=finals.end();i++){
		if (i->winner()==pname){
			numt++;
		}
		else{
			pname=i->winner();
			numt=1;
		}
		fileout<<numt <<',';
		for (int j=0;j<49;j++){
			fileout<<i->get_string(j) <<',';
		}
		fileout<<endl;
	}
}