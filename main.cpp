#include"hh.h"
#include<cstring>
#define N 0
using namespace std;
ATestStatus Autotest(ATest);
void printmatr(const Matrix<Num> &m, int k0){
	double max = 0;
	char buff[10];
	char buff2[10];
	char buff3[10];
	int k=(k0==0) ? 0 : k0+1,k1=0,t=0;
	for(int i = 0; i < m.getsizei(); i++){
		for(int j = 0; j < m.getsizej(); j++){
			if(fabs(m.get(i,j).val) > max){max = fabs(m.get(i,j).val);}
		}
	}
	while(max>1){
		max=max/10;
		k++;
	}
	t = m.getsizei();
	while(t!=0){
		t=t/10;
		k1++;
	}
	snprintf(buff2,10,"%%%dd",k);
	snprintf(buff3,10," %%%dd:| ",k1);
	for(int i = 0; i < k1+4; i++){
		cout << " ";
	}
	for(int i = 0; i < m.getsizej(); i++){
		snprintf(buff,10,buff2,i+1);
		cout <<buff<<":";
	}
	cout << "\n";
	for(int i = 0; i < k1+3;i++){
		cout << " ";
	}
	for(int i = 0; i <= m.getsizej()*(k+1);i++){
		cout << "-"; 
	}
	cout << "\n";
	snprintf(buff2,10,"%%%d.%dlf",k,k0);
	for(int i = 0; i < m.getsizei(); i++){
		snprintf(buff,10,buff3,i+1);
		cout << buff;
		for(int j = 0; j < m.getsizej(); j++){
			snprintf(buff,10,buff2,m.get(i,j).val);
			cout << buff << " "; 
		}
		snprintf(buff,10,"|:%d",i+1);
		cout << buff <<"\n";
	}

}
int main(){
	ATestStatus s = Autotest(ATest::ALL);
	if(s==ATestStatus::SUCCESS){cout << "Autotest passed!\n";}
	if(s==ATestStatus::RP_FAIL){cout << "Autotest: replace test error!!!\n";}
	if(s==ATestStatus::LC_FAIL){cout << "Autotest: linear combination test error!!!\n";}
	if(s==ATestStatus::SUM_FAIL){cout << "Autorest: sum test error!!!\n";}
	if(s==ATestStatus::SM_FAIL){cout << "Autotest: submatrix test fail!!!\n";}
	Matrix<Num>& m = *(new Matrix<Num>);
	cout << "\n Matrix: \n";
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			m.set(i,j,Num(i*j));
		}
	}
	printmatr(m,N);
	cout << "\n Changing some elements: (6,16)=1; (12,13)=123; (10,10) = 100; (1,1) = 10; \n";
	m.set(5,15,1);m.set(11,12,123);m.set(9,9,100);m.set(0,0,10);
	printmatr(m,N);
	cout << "\n Sum of elements from 6th to 11th in the sixth row: \n";
	cout << m.ssum(5,5,10).val <<"\n";
	cout << "\n Replace 6th and 7th row: \n";
	m.replace(6,5);
	printmatr(m,N);
	cout << "\n Submatrix from 3th to 9th row, from 4th to 6th collumn: \n";
	Matrix<Num> m2 = m.getPM(2,8,3,5);
	printmatr(m2,N);
	cout << "\n Yet another submatrix row={2,4,6,8}, collumn={3,5,7,9}: \n";
	Matrix<Num> m3 = m.getPM(set<int> {1,3,5,7},set<int> {2,4,6,8});
	printmatr(m3,N);
	cout<<"\n Linear combination 21th row = - 4th row; 7th row = 10*(6th row): \n";
	m.lcomb(20,3,-1);
	m.lcomb(6,5,10);
	printmatr(m,N);
	cout << "\n";
	delete &m;
	return 0;	
}
