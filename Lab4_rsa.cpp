#include<iostream>
#include<math.h>
using namespace std;
// find gcd
int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}

int modInverse(int A, int M){
     int i=1;
     while(true){
     	if(A*i%M == 1) return i;
     	else i++;
     }
	
}

int modPower(int base, int exponent, int mod) {
    if (mod == 1) {
        return 0; 
    }

    int result = 1;
    base = base % mod;

    while (exponent > 0) {
          result =  (base * result) % mod;
          exponent--;
    }

    return result;
}

int main() {
   double p = 17;
   double q = 11;
   
   double n=p*q;
   
   double phi= (p-1)*(q-1);
  
   double e=2;
   
   //for checking e and phi(n) are coprime.
   while(e<phi) {
      if(gcd(e,phi)==1)
         break;
      else
         e++;
   }
   
   double d=modInverse(e,phi);
   
   double message = 88;
   
   double c = modPower(message,e,n); //encrypt message
   
   double m =modPower(c,d,n); //decrypt message
  
   cout<<"Original Message = "<<message;
   cout<<"\n"<<"p = "<<p;
   cout<<"\n"<<"q = "<<q;
   cout<<"\n"<<"n = pq = "<<n;
   cout<<"\n"<<"phi = "<<phi;
   cout<<"\n"<<"e = "<<e;
   cout<<"\n"<<"d = "<<d;
   cout<<"\n"<<"Encrypted message = "<<c;
   cout<<"\n"<<"Decrypted message = "<<m;

   return 0;
}