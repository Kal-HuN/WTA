#include <cstdlib>
#include <iostream>
#include <list>
#include <fstream>
#include "WTAParse.h"

using namespace std;


const int yearstart=1920;
const int yearend=2022;
const string namefile="wta_matches_";

void AddFinals (string filename, list<Parse>& finals){
	ifstream filein(filename);
	string line;
	
	getline(filein, line);
	while (getline(filein, line)){
		Parse match(line);
		if (!match.fed() && match.final())
			finals.push_back(match);
	}
}
bool Compare (Parse& a, Parse& b){
	if (a.winner()<b.winner())
		return true;
	if (a.winner()>b.winner())
		return false;
	if (a.date()<b.date())
		return true;
	return false;
}

int main ()
{
	list<Parse> finals;
	
	for (int i=yearstart;i<=yearend;i++){
		AddFinals (namefile+to_string(i)+".csv", finals);
	}
	
	finals.sort(Compare);
	
	ofstream fileout("finals.csv");
	for (auto i=finals.begin();i!=finals.end();i++){
		for (int j=0;j<49;j++){
			fileout<<i->get_string(j) <<',';
		}
		fileout<<endl;
	}
}