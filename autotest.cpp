#include"hh.h"
#include<cstdlib>
#include<ctime>
#define N 100
int rn(int n){
	int k = n/RAND_MAX;
	int r = rand();
	return r*k+rand()%(n-r*k);	
}
ATestStatus Autotest(ATest t){
	srand(static_cast<unsigned int>(time(NULL)));
	int i0,i1,j0,j1,k,l;
	Num **matr = new Num*[N];
	for(int i = 0; i < N; i++){
		matr[i] = new  Num[N];
	}
	Matrix<Num> &m = *(new Matrix<Num>);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N;j++){
			Num a(rn(N)*1e-3);
			matr[i][j] = a;
			m.set(i,j,a);
		}
	}
	if(t == ATest::ALL || t == ATest::RP){
		for(int x = 0; x < 100; x++){
		k = rn(N); l = rn(N);
		m.replace(k,l);
		for(int i = 0; i < N; i++){
			if(matr[k][i]!=m.get(l,i)){return ATestStatus::RP_FAIL;}
			if(matr[l][i]!=m.get(k,i)){return ATestStatus::RP_FAIL;}
		}
		m.replace(k,l);
		for(int i = 0; i < N; i++){
			if(matr[k][i]!=m.get(k,i)){return ATestStatus::RP_FAIL;}
			if(matr[l][i]!=m.get(l,i)){return ATestStatus::RP_FAIL;}
		}
		}
	}	
	if(t == ATest::ALL || t == ATest::SUM){
		for(int x = 0; x < 100; x++){
		k = rn(N),j0 = rn(N),j1 = j0+rn(N-j0);
		Num sum{},sum2{};
		for(int i = j0; i <= j1; i++){
			sum=sum+matr[k][i];
		}
		sum2=m.ssum(k,j0,j1);
		if(sum!=sum2){return ATestStatus::SUM_FAIL;}
		}
	}
	if(t == ATest::ALL || t == ATest::LC){
		for(int x = 0; x < 100; x++){
		Num a(rn(N)*1.0);
		k= rn(N); l = rn(N);
		m.lcomb(k,l,a);
		for(int i = 0; i < N; i++){;
			matr[k][i] = matr[k][i]+a*matr[l][i];
			if(matr[k][i]!=m.get(k,i)){return ATestStatus::LC_FAIL;}
		}
		}
	}
	if(t == ATest::ALL || t == ATest::SM){
		for(int x = 0; x < 100; x++){
		i0 = rn(N); i1 = i0+rn(N-i0); j0=rn(N); j1 = j0+rn(N-j0);
		Matrix<Num> m2 = m.getPM(i0,i1,j0,j1);
		for(int i = i0; i <= i1; i++){
			for(int j = j0; j <= j1; j++){
				if(matr[i][j]!=m2.get(i-i0,j-j0)){return ATestStatus::SM_FAIL;}
			}
		}
		}
	}
	delete &m;
	for(int i = 0; i < N; i++){
		delete[] matr[i];
	}
	delete[] matr;
	return ATestStatus::SUCCESS;
}

