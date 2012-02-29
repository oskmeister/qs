#pragma once
#include "debug.h"
#include <bitset>
/*
	A matrix that only supports 0, 1.
*/
template<int r, int c>
struct matrix {
	std::bitset<c> data[r];

	std::bitset<c> solve(){
		dprintf("Solving this matrix:\n");
		for(int i = 0; i<r; i++){
			for(int j = 0; j<c; j++){
				bool b = data[i][j];
				dprintf("%d ", b);
			}
			dprintf("\n");
		}

		//Reduce matrix
		/*
			For every column, we search every row until we find one where this column is 1.
			We then swap rows, and XOR it with all rows below which has this column as 1.
		*/
		for(int i = 0; i<c; i++){
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
			We have values for some of the variables (i.e. they must be 0) - remove them!
		*/
		for(int i = c-1; i>=0; i--){
			if(data[i][i] && data[i].count() == 1){
				for(int j = 0; j<r; j++){
					if(i != j) data[j][i] = 0;
				}
			}
		}

		/*
			Remove empty and duplicate
		*/
		int rowCount = 0;
		for(int i = 0; i<r; i++){
			bool same = false;
			for(int j = 0; j<rowCount; j++)
				if(data[j] == data[i]){
					same = true;
				}
			if(data[i].count() && !same){
				data[rowCount++] = data[i];
				skip:;
			}
		}

		dprintf("Reduced to: \n");
		for(int i = 0; i<rowCount; i++){
			for(int j = 0; j<c; j++)
				dprintf("%d ", (bool)data[i][j]);
			dprintf("\n");
		}
	}

	std::bitset<c>& operator[](int _r) {
		return data[_r];
	}
};
