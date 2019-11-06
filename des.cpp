#include <string>
#include <bitset>
#include <iostream>
#include <vector>
#include<algorithm>
#include <time.h> 
using namespace std;

struct timespec start, stop;
double total_time;

//the next probably 30 lines are going to be me initializing s-boxes

int a1[] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7, \
0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8, \
4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,\
15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int a2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,\
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,\
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,\
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};


int a3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,\
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,\
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,\
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int a4[] = {7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,\
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,\
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,\
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int a5[] = {2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,\
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,\
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,\
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int a6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,\
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,\
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,\
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int a7[] = {4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,\
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,\
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,\
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int a8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12, 7,\
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,\
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,\
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

vector<int> s1(a1, a1 + sizeof(a1)/sizeof(int));
vector<int> s2(a2, a2 + sizeof(a2)/sizeof(int));
vector<int> s3(a3, a3 + sizeof(a3)/sizeof(int));
vector<int> s4(a4, a4 + sizeof(a4)/sizeof(int));
vector<int> s5(a5, a5 + sizeof(a5)/sizeof(int));
vector<int> s6(a6, a6 + sizeof(a6)/sizeof(int));
vector<int> s7(a7, a7 + sizeof(a7)/sizeof(int));
vector<int> s8(a8, a8 + sizeof(a8)/sizeof(int));
vector<vector<int>> sBox;

//initializes the sboxes in a big 2D array
void initSBox(){
	sBox.push_back(s1);
	sBox.push_back(s2);
	sBox.push_back(s3);
	sBox.push_back(s4);
	sBox.push_back(s5);
	sBox.push_back(s6);
	sBox.push_back(s7);
	sBox.push_back(s8);
}

//converts an int to binary
vector<int> toBinary(int n){
	vector<int> ans;
	while(n>1){
		ans.push_back(n%2);
		n=n/2;
	}
	ans.push_back(n%2);
	for(int i = ans.size(); i < 8; ++i)
		ans.push_back(0);
	reverse(ans.begin(), ans.end());
	return ans;
}

//converts strings to binary
vector<int> sToBin(string s){
	vector<int> letters;
	for (int i = 0; i < s.size(); i++){
		vector<int> tempVec = toBinary((int)s[i]);
		letters.insert(letters.end(), tempVec.begin(), tempVec.end());
	}
	return letters;
}

//converts a vector (of binary) to an int
int toNum(int i, int j, int k, int l){
	int sum = 0;
	if(i == 1) sum+=8;
	if(j == 1) sum+=4;
	if(k == 1) sum+=2;
	if(l == 1) sum+=1;	
	return sum;
}

//expansion by adding the bit # at location vPos[i] to location addPos[i]
vector<int> expansion(vector<int> v){
	int addPos[] = {0, 5, 6, 11, 12, 17, 18, 23, 24, 29, 30, 35, 36, 41, 42, 47};
	int vPos[] = {32, 5, 4, 9, 8, 13, 12, 17, 16, 21, 20, 25, 24, 29, 28, 1};
	vector<int> output = v;
	for(int i = 0; i < 16; i++){
		output.insert(output.begin()+addPos[i], 1, v[vPos[i]-1]);
	}
	//cout<<output.size();
	//for(int i = 0; i < output.size(); i++)
	//	cout<<output[i]<<" ";
	return output;
}

//substitution using s-boxes
vector<int> subs(vector<int> v){
	vector<vector<int>> blocks;
	vector<int> block;
	vector<int> finalAns;
	int sX = 0;
	int sY = 0;
	for(int i = 1; i <= 48; i++){
		block.push_back(v[i-1]);
		if(i%6 == 0)
			blocks.push_back(block);
		block.clear();	
	}

	//below goes through each row of 6 bits and finds the corresponding value in the sbox global variable
	for(int i = 0; i < 8; i++){
		sX = toNum(0, 0, blocks[i][0], blocks[i][5]);
		sY = toNum(blocks[i][1], blocks[i][2], blocks[i][3], blocks[i][4]); 
		vector<int> tempVec = toBinary(sBox[i][(sX*16)+sY]);
		finalAns.insert(finalAns.end(), tempVec.begin(), tempVec.end());
	}

	return finalAns;
}

//hard coded final permutation of mangler
vector<int> perm(vector<int> v){
	vector<int> tempVec;
	tempVec.push_back(v[15]);tempVec.push_back(v[6]);tempVec.push_back(v[19]);
	tempVec.push_back(v[20]);tempVec.push_back(v[28]);tempVec.push_back(v[11]);
	tempVec.push_back(v[27]);tempVec.push_back(v[16]);tempVec.push_back(v[0]);
	tempVec.push_back(v[14]);tempVec.push_back(v[22]);tempVec.push_back(v[25]);
	tempVec.push_back(v[4]);tempVec.push_back(v[17]);tempVec.push_back(v[30]);
	tempVec.push_back(v[9]);tempVec.push_back(v[1]);tempVec.push_back(v[7]);
	tempVec.push_back(v[23]);tempVec.push_back(v[13]);tempVec.push_back(v[31]);
	tempVec.push_back(v[26]);tempVec.push_back(v[2]);tempVec.push_back(v[8]);
	tempVec.push_back(v[18]);tempVec.push_back(v[12]);tempVec.push_back(v[29]);
	tempVec.push_back(v[5]);tempVec.push_back(v[21]);tempVec.push_back(v[10]);
	tempVec.push_back(v[3]);tempVec.push_back(v[24]);
	return tempVec;
}

//XOR takes place here. 
vector<int> mangler(vector<int> v, vector<int> k){
	vector<int> afterXor;
	vector<int> expandedVec = expansion(v);
	vector<int> afterSubs;
	for(int i = 0; i < 48; i++)
		afterXor.push_back(v[i]^k[i]);
	return perm(subs(afterXor));
	
}


int main(){
	clock_gettime(CLOCK_REALTIME, &start);
	string plaintext;
	initSBox();

	plaintext = "8letters";
	int k[] = {0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0};
	vector<int> key(k, k + sizeof(k)/sizeof(int));
	vector<int> output;
	vector<int> block = sToBin(plaintext);

	for(int i = block.size()/2; i < block.size(); i++)
		output.push_back(block[i]);
	vector<int> leftOutput = output;
	vector<int> rightOutput;
	vector<int> mangledBlock = mangler(output, key);
	//for(int i = 0; i < mangledBlock.size(); i++)
	//	cout<<mangledBlock[i];
	for(int i = 0; i < block.size()/2; i++)
		rightOutput.push_back(leftOutput[i]^mangledBlock[i]);	

	

	leftOutput.insert(leftOutput.end(), rightOutput.begin(), rightOutput.end());

	for(int i = 0; i < leftOutput.size(); i++)
		cout<<leftOutput[i];

	cout<<endl;
	clock_gettime(CLOCK_REALTIME, &stop);
	total_time = (stop.tv_sec-start.tv_sec)+0.000000001*(stop.tv_nsec-start.tv_nsec);
	printf("time (sec) = %8.4f\n", total_time);



}