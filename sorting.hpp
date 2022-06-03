#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

const int RAZ = 1000;	
typedef int TElem;
typedef TElem TMatr[RAZ][RAZ];

int n;
 
int nCheck(int n){
	if((n >= 1)&&(n <= (RAZ/2))) return 1;
	else return 0;
}

int getNFromFile(char *filename){
	
	ifstream fin(filename);
	fin >> n;
	return n;
}

void input_matrix(TMatr a, char *filename){
	
	ifstream fin(filename);
	fin >> n;
	
	for(int i = 0; i < 2*n; i++)
		for(int j = 0; j < 2*n; j++)
			fin >> a[i][j];
	
}

void rand_input_matrix(TMatr a){
	
	int k = 0;
	
	for(int i = 0; i < 2*n; i++)
		for(int j = 0; j < 2*n; j++){
				a[i][j] = k;
				k++;
		}
	
}

void zerofication(TMatr a){
	
	for(int i = 0; i < 2*n; i++)
		for(int j = 0; j < 2*n-1-i; j++)
				a[i][j] = 0;
}

void sorting(TMatr a){
		
	int CollumnMin, t, MinInd;
		
	for (int i = 1; i < 2*n; i++){
		
		for(int k = 2*n-1-i; k < 2*n-1; k++){
			CollumnMin = INT_MAX;
			for(int g = k; g < 2*n; g++){
				if(a[g][i] < CollumnMin){
					CollumnMin = a[g][i];
					MinInd = g;
				}
			}
			if(MinInd != k){
				t = a[k][i];
				a[k][i] = a[MinInd][i];
				a[MinInd][i] = t;
			}			
		}
	}	

}

void output_matrix(TMatr a){
	
	cout << endl << "--------------------" << endl;
	
	for(int i = 0; i < 2*n; i++){
		for(int j = 0; j < 2*n; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
}
