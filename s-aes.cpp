#include<iostream>
#include<vector>
#include<unordered_map>
#include <algorithm>
using namespace std;

vector<vector<int>>keys;

unordered_map<string, string> sBox = {
    {"0000", "1001"},
    {"0001", "0100"},
    {"0010", "1010"},
    {"0011", "1011"}, 
    {"0100", "1101"},
    {"0101", "0001"},
    {"0110", "1000"},
    {"0111", "0101"},
    {"1000", "0110"},
    {"1001", "0010"},
    {"1010", "0000"},
    {"1011", "0011"},
    {"1100", "1100"},
    {"1101", "1110"},
    {"1110", "1111"},
    {"1111", "0111"}
};

vector<int> subNib(vector<int> w) {
    vector<int> ans;
    for (int i = 0; i < w.size(); i += 4) {
        string nibble;
        for (int j = 0; j < 4; j++) {
            nibble += to_string(w[i + j]);
        }
        nibble = sBox[nibble];
        for (char c : nibble) {
            int digit = c - '0'; // Convert char to int
            ans.push_back(digit); // Push int value as string
        }
    }
    return ans;
}

vector<int> invSubNib(vector<int> w){
	cout<<"input nibble - ";
      for(int i=0;i<16;i++){
	    cout<<w[i]<<" "; 	
	}
vector<int> ans =w;
    for (int i = 0; i < w.size(); i += 4) {
        string nibble;
        for (int j = 0; j < 4; j++) {
            nibble += to_string(w[i + j]);
            
        }
        cout<<"Nibble is - "<<nibble;
        cout<<endl;
        for(auto &it : sBox) {
	       cout<<"Nibble is - "<<nibble;
		cout<<endl; 
              if(it.second == nibble) { 
                 //cout<<" yes";
                 nibble = it.first;
                 //cout<<nibble<<" c ";
              } 
              
        } 
        for (char c : nibble) {
            int digit = c - '0'; // Convert char to int
            ans.push_back(digit); // Push int value as string
        }
    }
    return ans;
}
vector<int> rotNib(vector<int> w){
	vector<int> ans(8);
	for(int i=0;i<4;i++){
		ans[i]=w[i+4];
		ans[i+4]=w[i];
	}
	return ans;
}

void generateKey(vector<int> k){
	vector<int> w0,w1,w2,w3,w4,w5;
	for (int i = 0; i < 8; i++) {
        w0.push_back(k[i]);
        w1.push_back(k[i + 8]);
    }
	vector<int> c1={1,0,0,0,0,0,0,0};
	vector<int> c2={0,0,1,1,0,0,0,0};
	vector<int> rot,sub;
	rot= rotNib(w1);
	sub=subNib(rot);
	for(int i=0;i<8;i++){
		w2.push_back(w0[i]^c1[i]^sub[i]);
	}
	
	for(int i=0;i<8;i++){
		w3.push_back(w1[i]^w2[i]);
	}
	rot.clear();
	sub.clear();
	rot= rotNib(w3);
	sub=subNib(rot);
	for(int i=0;i<8;i++){
		w4.push_back(w2[i]^c2[i]^sub[i]);
	}
	for(int i=0;i<8;i++){
		w5.push_back(w3[i]^w4[i]);
	}
	
       w0.insert(w0.end(), w1.begin(), w1.end());
	keys.push_back(w0);
	w2.insert(w2.end(), w3.begin(), w3.end());
	keys.push_back(w2);
	w4.insert(w4.end(), w5.begin(), w5.end());
	keys.push_back(w4);
       
}
//vector<int> subNib(vector<int> w){
//	vector<int> ans(w.size());
//	for(int i=0;i<4;i++){
//		ans[i]=w[i+4];
//		ans[i+4]=w[i];
//	}
//	return ans;
//}

vector<int> ARK(vector<int> p,int round){
	vector<int> ans;
	for(int i=0;i<16;i++){
	    ans.push_back(p[i]^keys[round-1][i]); 	
	}
	return ans;
}

vector<int> shiftRow(vector<int> k){
    rotate(k.begin() + 4, k.begin() + 8, k.end());
   
    rotate(k.begin() + 8, k.begin() + 12, k.begin() + 8);
  
    return k;	
}

int main(){
	vector<int> k={0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,1};
//	vector<int> k1={0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,1};
//	for(int i=0;i<16;i++){
//	    cout<<k[i]<<" "; 	
//	}
	vector<int> p = {1,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0};
       generateKey(k);
       for(int i=0;i<3;i++){
       	cout<<"Key"<<i+1<<endl;
       	for(int j=0;j<16;j++){
       		cout<<keys[i][j]<<" ";
		}
		cout<<endl;
	}
	
//	vector<int> a = invSubNib(p);
//	cout<<endl;
//	for(int i=0;i<16;i++){
//	    cout<<a[i]<<" "; 	
//	}
	return 0;
}
