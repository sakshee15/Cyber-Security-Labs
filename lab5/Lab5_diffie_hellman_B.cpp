#include <iostream>
#include <cmath>
using namespace std;

int powmod(int base, int exponent, int mod)
{
    int result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result = (result * base) % mod;
    }
    return result;
}

int main()
{
    int G, P, privateKey, publicKeyA, publicKeyB, sharedKeyA, sharedKeyB;
    cout << "Enter value of P: ";
    cin >> P;
    cout << "Enter value of G: ";
    cin >> G;

    cout << "Enter private key: ";
    cin >> privateKey;

    publicKeyB = powmod(G, privateKey, P);
    cout << "Public key of B is: " << publicKeyB << endl;
    cout << "Enter public key of the other party (A): ";
    cin >> publicKeyA;
    sharedKeyA = powmod(publicKeyA, privateKey, P);
    cout << "Shared key for B is: " << sharedKeyA << endl;
    
    // cout << "Are you party A or party B?\n";
    // cout << "1. Party A\n";
    // cout << "2. Party B\n";
    // int choice;
    // cin >> choice;

    // switch (choice)
    // {
    // case 1:
    //     publicKeyA = powmod(G, privateKey, P);
    //     cout << "Public key of A is: " << publicKeyA << endl;
    //     cout << "Enter public key of the other party (B): ";
    //     cin >> publicKeyB;
    //     sharedKeyA = powmod(publicKeyB, privateKey, P);
    //     cout << "Shared key for A is: " << sharedKeyA << endl;
    //     break;
    // case 2:
    //     publicKeyB = powmod(G, privateKey, P);
    //     cout << "Public key of B is: " << publicKeyB << endl;
    //     cout << "Enter public key of the other party (A): ";
    //     cin >> publicKeyA;
    //     sharedKeyB = powmod(publicKeyA, privateKey, P);
    //     cout << "Shared key for B is: " << sharedKeyB << endl;
    //     break;
    // default:
    //     cout << "Invalid choice." << endl;
    //     break;
    // }

    return 0;
}