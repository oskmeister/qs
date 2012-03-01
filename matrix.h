#pragma once
#include "debug.h"
#include <bitset>
#include <cstdlib>
/*
	A matrix that only supports 0, 1.
*/
template<int r, int c>
struct matrix {

	std::bitset<c> data[r];
	
	std::bitset<c> solve(){
		//Reduce matrix into row-echelon
		/*
			For every column, we search every row until we find one where this column is 1.
			We then swap rows, and XOR it with all rows below which has this column as 1.
		*/
		for(int i = 0; i<r; i++){
			for(int j = i; j<r; j++){
				if(data[j][i]){
					swap(data[i], data[j]);
					break;
				}
			}
			if(data[i][i]){
				for(int j = i+1; j<r; j++){
					if(data[j][i]){
						data[j] ^= data[i];
					}
				}
			}
		}
		/*
			Back-subsitute into matrix
		*/
		for(int i = r-1; i>=0; i--){
			if(data[i][i]){
				for(int j = 0; j<r; j++){
					if(i != j && data[j][i]) data[j] ^= data[i];
				}
			}
		}
		/*
			Semi-randomly assign values to variables
		*/
		std::bitset<c> sol;
		int inc = 0;
		for(int i = r; i>=0; i--){
			bool val = (inc < r/2) || rand()%5 == 0;
			for(int j = r-1; j>=0; j--){
				if(data[j][i] && data[j].count() == 1){
					val = data[j][c-1];
					break;
				}
			}
			for(int j = 0; j<r; j++){
				if(data[j][i] && data[j].count() != 1){
					data[j][i] = false;
					data[j][c-1] = data[j][c-1]^val;
				}
			}
			inc += val;
			sol[i] = val;
		}
		return sol;
	}

	std::bitset<c>& operator[](int _r) {
		return data[_r];
	}
};
