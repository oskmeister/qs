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
		//Reduce matrix
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
	}

	std::bitset<c> operator[](int _r){
		return data[_r];
	}
};
