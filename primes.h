#pragma once

#include<vector>

struct prime_sieve {

	int N;
	bool* not_prime;


public:

	prime_sieve(int _N) : N(_N) {
		not_prime = new bool[N];
	}

	~prime_sieve() {
		delete not_prime;
	}

	std::vector<int> sieve(){
		for(int i = 2; i<N; i++)
			if(!not_prime[i])
				for(int j = 2; j*i <N; j++)
					not_prime[j*i] = true;

		std::vector<int> prime_list;
		for(int i = 2; i<N; i++) if(!not_prime[i]) prime_list.push_back(i);
		return prime_list;
	}

};
