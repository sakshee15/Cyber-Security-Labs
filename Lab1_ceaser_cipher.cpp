#include<iostream>

using namespace std;

string encrypt(string str, int shift){
	string res="";
	for(int i=0;i<str.length();i++){
		if(isupper(str[i])){
			res+= char(int(str[i])+ shift % 26);
		}else{
			res+= char(int(str[i])+ shift % 26);
		}
	}
	return res;
}

string decrypt(string str, int shift){
	string res="";
	for(int i=0;i<str.length();i++){
		if(isupper(str[i])){
			res+= char((int(str[i]))+(26-shift)% 26);
		}else{
			res+= char((int(str[i]))+(26-shift)% 26);
		}
	}
	return res;
}

int main(){
    int shift,choice;
	string s;
	cout<<"1.Encrypt a plain text\n2.Decrypt a cipher text\nEnter your choice -  ";
	cin>>choice;
	switch(choice){
	case 1:
	       cout<<"Enter plain text - ";
	       cin>>s;
	       cout<<"Enter shift key - ";
	       cin>>shift;
	       cout<<"Cipher text is "<<encrypt(s,shift);
	       break;
	case 2:
	       cout<<"Enter cipher text - ";
	       cin>>s;
	       cout<<"Enter shift key - ";
	       cin>>shift;
	       cout<<"Original text is "<<decrypt(s,shift);
	       break;
	default:
		cout<<"Invalid choice!!";
}
       return 0;
}
