#include <iostream>
#include <math.h>
using namespace std;

int gcd(int a, int b)
{
   int t;
   while (1)
   {
      t = a % b;
      if (t == 0)
         return b;
      a = b;
      b = t;
   }
}

int modInverse(int A, int M)
{
   int i = 1;
   while (true)
   {
      if (A * i % M == 1)
         return i;
      else
         i++;
   }
}
int modPower(int base, int exponent, int mod)
{
   if (mod == 1)
   {
      return 0;
   }

   int result = 1;
   base = base % mod;

   while (exponent > 0)
   {
      result = (base * result) % mod;
      exponent--;
   }

   return result;
}

// Function to generate RSA keys
void generateRSAKeys(double p, double q, double &n, double &e, double &d)
{
   n = p * q;
   double phi = (p - 1) * (q - 1);
   e = 2;
   while (e < phi)
   {
      if (gcd(e, phi) == 1)
         break;
      else
         e++;
   }

   d = modInverse(e, phi);
}

int main()
{
   double p, q, n, e, d, message;
   double c, m;

   cout << "RSA Encryption/Decryption" << endl;
   cout << "--------------------------------------------------------\n"
        << endl;

   cout << "Enter the first prime number (p): ";
   cin >> p;

   cout << "Enter the second prime number (q): ";
   cin >> q;

   generateRSAKeys(p, q, n, e, d);
   cout << "\nKey Generation:" << endl;
   cout << "p = " << p << endl;
   cout << "q = " << q << endl;
   cout << "n = pq = " << n << endl;
   cout << "e = " << e << endl;
   cout << "d = " << d << endl;

   cout << "\nEnter the message: ";
   cin >> message;

   c = modPower(message, e, n);
   cout << "\nEncrypted message (Ciphertext) = " << c << endl;

   m = modPower(c, d, n);
   cout << "\nDecrypted message (Plaintext) = " << m << endl;

   return 0;
}
