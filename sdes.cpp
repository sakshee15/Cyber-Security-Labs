#include <iostream>

using namespace std;
int p10[10] = {3,5,2,7,4,10,1,9,8,6};
int p8[8] = {6,3,7,4,8,5,10,9};
int p4[4] = {2,4,3,1};
int s0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int s1[4][4] = {{ 0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3 }};
int ip[8] = {2,6,3,1,4,8,5,7};
int ip1[8] = {4,1,3,5,7,2,8,6};

void p_10(int key[]) {
   int temp[10];

   for (int i = 0; i < 10; i++) {
      temp[i] = key[i];
   }
   for (int i = 0; i < 10; i++) {
      key[i] = temp[p10[i] - 1];
   }
}

void p_8(int key[]) {
   int temp[10];
   for (int i = 0; i < 10; i++) {
      temp[i] = key[i];
   }
   for (int i = 0; i < 8; i++) {
      key[i] = temp[p8[i] - 1];
   }
}

void p_4(int key[]) {
   int temp[4];
   for (int i = 0; i < 4; i++) {
      temp[i] = key[i];
   }
   for (int i = 0; i < 4; i++) {
      key[i] = temp[p4[i] - 1];
   }
}

void left_shift(int key[], int n) {

   int temp = key[0];
   for (int i = 1; i < 5; i++) {
      key[i - 1] = key[i];
   }
   key[4] = temp;
   if (n == 2) {
      left_shift(key, 1);
   }

}

void generate_key(const int key[], int round, int key_out[]) {
   int local_key[10]; 
   int left[5], right[5];

   // Copy the elements from the original key to the local_key array
   for (int i = 0; i < 10; i++) {
      local_key[i] = key[i];
   }

   p_10(local_key);

   for (int i = 0; i < 5; i++) {
      left[i] = local_key[i];
      right[i] = local_key[5 + i];
   }

   left_shift(left, 1);
   left_shift(right, 1);

   if (round == 1) {
      for (int i = 0; i < 5; i++) {
         key_out[i] = left[i];
         key_out[i + 5] = right[i];
      }
      p_8(key_out);
   } else {
      left_shift(left, 2);
      left_shift(right, 2);

      for (int i = 0; i < 5; i++) {
         key_out[i] = left[i];
         key_out[i + 5] = right[i];
      }
      p_8(key_out);
   }
}

void i_p(int key[]) {
   
   int temp[8];
   for (int i = 0; i < 8; i++) {
      temp[i] = key[i];
   }
   for (int i = 0; i < 8; i++) {
      key[i] = temp[ip[i] - 1];
   }
}
void i_p_inv(int key[]) {
   int temp[8];
   
   for (int i = 0; i < 8; i++) {
      temp[i] = key[i];
   }
   for (int i = 0; i < 8; i++) {
      key[i] = temp[ip1[i] - 1];
   }
}

int * e_p(int key[], int ep[]) {
   int temp[4];
   static int expanded_right[8];

   for (int i = 0; i < 4; i++)
      temp[i] = key[i];

   for (int i = 0; i < 8; i++) {
      expanded_right[i] = temp[ep[i] - 1];

   }
   return expanded_right;
}

int get_s(int key[], int s[4][4]) {
   int row = key[3] + key[0] * 2;
   int column = key[2] + key[1] * 2;
   return s[row][column];
}

int * fk(int p[], int key[]) {
   
   int l1[4], r1[4], left[4], right[4];
   int a, b;
   int ep[8] = {4,1,2,3,2,3,4,1};

   for (int i = 0; i < 4; i++) {
      left[i] = p[i];
      right[i] = p[i + 4];
   }

   int * temp = e_p(right, ep);
   for (int i = 0; i < 8; i++) {
      temp[i] ^= key[i];
   }

   for (int i = 0; i < 4; i++) {
      l1[i] = temp[i];
      r1[i] = temp[i + 4];
   }
   
   a = get_s(l1, s0);
   b = get_s(r1, s1);
   l1[0] = a / 2;
   l1[1] = a % 2;
   l1[2] = b / 2;
   l1[3] = b % 2;
   
   p_4(l1);
   
   for (int i = 0; i < 4; i++) {
      left[i] = left[i] ^ l1[i];
   }
   
   for (int i = 0; i < 4; i++) {
      temp[i] = left[i];
      temp[i + 4] = right[i];
   }

   return temp;

}

void swap(int p[]) {

   for (int i = 0; i < 4; i++) {
      int temp = p[i];
      p[i] = p[4 + i];
      p[4 + i] = temp;
   }

}

int main() {
   int p[8] = {1,0,1,0,0,1,0,1};
   int key[10] = {0,0,1,0,0,1,0,1,1,1};
   int key1[8], key2[8];
   int * temp;
   cout << "Plain text - ";
   for (int i = 0; i < 8; i++) {
      cout << p[i];
   }
   
   //    cout << "Enter key (10 bits): ";
   //    for (int i = 0; i < 10; i++) {
   //        cin >> key[i];
   //    }
   
   //KEY Generation
   generate_key(key, 1, key1);
   generate_key(key, 2, key2);

   cout << "\n\nGenerated keys:\n";
   cout << "Key1 - ";
   for (int i = 0; i < 8; i++) {
      cout << key1[i];
   }

   cout << "\nKey2 - ";
   for (int i = 0; i < 8; i++) {
      cout << key2[i];
   }
   
   //Encryption
   i_p(p);
   temp = fk(p, key1);
   swap(temp);
   temp = fk(temp, key2);
   i_p_inv(temp);
   cout << "\n\nEncrypted text - ";
   for (int i = 0; i < 8; i++) {
      cout << temp[i];
   }
   
   cout << "\n";
   for (int i = 0; i < 8; i++) {
      p[i] = temp[i];
   }
   
   //Decryption
   i_p(p);
   temp = fk(p, key2);
   swap(temp);
   temp = fk(temp, key1);
   i_p_inv(temp);
   cout << "\nDecrypted text - ";
   for (int i = 0; i < 8; i++) {
      cout << temp[i];
   }
   return 0;
}
