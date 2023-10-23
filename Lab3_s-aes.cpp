#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bitset>
using namespace std;

vector<vector<int>> keys;

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

// Helper function to perform multiplication in GF(2^4)
char gf_mul(char a, char b)
{
    char p = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (b & 1)
        {
            p ^= a;
        }
        bool hi_bit_set = a & 0x8;
        a <<= 1;
        if (hi_bit_set)
        {
            a ^= 0x3; // 0x3 corresponds to the irreducible polynomial x^4 + x + 1 in GF(2^4)
        }
        b >>= 1;
    }
    return p & 0xF; // Modulo with 0xF to ensure results stay within GF(2^4)
}

// Mix Columns function
vector<vector<char>> mix_columns(const vector<vector<char>> &s, vector<vector<char>> me)
{
    vector<vector<char>> result(2, vector<char>(2, 0));

    for (int col = 0; col < 2; ++col)
    {
        for (int row = 0; row < 2; ++row)
        {
            for (int k = 0; k < 2; ++k)
            {
                result[row][col] ^= gf_mul(me[row][k], s[k][col]);
            }
        }
    }
    return result;
}

vector<vector<char>> convertTo2x2Matrix(const vector<int> &input)
{
    vector<vector<char>> result(2, vector<char>(2, 0));

    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            int index = (j * 8) + (i * 4);
            int value = (input[index] << 3) | (input[index + 1] << 2) | (input[index + 2] << 1) | input[index + 3];
            result[i][j] = static_cast<char>(value);
        }
    }

    return result;
}

vector<int> convertToVector(const vector<vector<char>> &input)
{
    vector<int> result;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            bitset<4> bits(input[j][i]);
            for (int k = 3; k >= 0; --k)
            {
                result.push_back(bits[k]);
            }
        }
    }
    return result;
}

vector<int> subNib(vector<int> w)
{
    vector<int> ans;
    for (int i = 0; i < w.size(); i += 4)
    {
        string nibble;
        for (int j = 0; j < 4; j++)
        {
            nibble += to_string(w[i + j]);
        }
        nibble = sBox[nibble];
        for (char c : nibble)
        {
            int digit = c - '0';  // Convert char to int
            ans.push_back(digit); // Push int value as string
        }
    }
    return ans;
}

vector<int> invSubNib(vector<int> w)
{
    vector<int> ans;
    for (int i = 0; i < w.size(); i += 4)
    {
        string nibble, n;
        for (int j = 0; j < 4; j++)
        {
            nibble += to_string(w[i + j]);
        }

        for (auto &it : sBox)
        {
            if (it.second == nibble)
            {
                n = it.first;
            }
        }
        for (char c : n)
        {
            int digit = c - '0';  // Convert char to int
            ans.push_back(digit); // Push int value as string
        }
    }

    return ans;
}

vector<int> rotNib(vector<int> w)
{
    vector<int> ans(8);
    for (int i = 0; i < 4; i++)
    {
        ans[i] = w[i + 4];
        ans[i + 4] = w[i];
    }
    return ans;
}

void generateKey(vector<int> k)
{
    vector<int> w0, w1, w2, w3, w4, w5;
    for (int i = 0; i < 8; i++)
    {
        w0.push_back(k[i]);
        w1.push_back(k[i + 8]);
    }
    vector<int> c1 = {1, 0, 0, 0, 0, 0, 0, 0};
    vector<int> c2 = {0, 0, 1, 1, 0, 0, 0, 0};
    vector<int> rot, sub;
    rot = rotNib(w1);
    sub = subNib(rot);
    for (int i = 0; i < 8; i++)
    {
        w2.push_back(w0[i] ^ c1[i] ^ sub[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        w3.push_back(w1[i] ^ w2[i]);
    }
    rot.clear();
    sub.clear();
    rot = rotNib(w3);
    sub = subNib(rot);
    for (int i = 0; i < 8; i++)
    {
        w4.push_back(w2[i] ^ c2[i] ^ sub[i]);
    }
    for (int i = 0; i < 8; i++)
    {
        w5.push_back(w3[i] ^ w4[i]);
    }

    w0.insert(w0.end(), w1.begin(), w1.end());
    keys.push_back(w0);
    w2.insert(w2.end(), w3.begin(), w3.end());
    keys.push_back(w2);
    w4.insert(w4.end(), w5.begin(), w5.end());
    keys.push_back(w4);
}

vector<int> ARK(vector<int> p, int round)
{
    vector<int> ans;
    for (int i = 0; i < 16; i++)
    {
        ans.push_back(p[i] ^ keys[round - 1][i]);
    }
    return ans;
}

vector<int> shiftRow(vector<int> k)
{
    rotate(k.begin() + 4, k.begin() + 8, k.end());

    rotate(k.begin() + 8, k.begin() + 12, k.begin() + 8);

    return k;
}

vector<int> encryption(vector<int> p)
{
    vector<int> r1, r2, r3, r4;
    r1 = shiftRow(subNib(ARK(p, 1)));

    r2 = convertToVector(mix_columns(convertTo2x2Matrix(r1), {{1, 4}, {4, 1}}));

    r3 = shiftRow(subNib(ARK(r2, 2)));

    r4 = ARK(r3, 3);

    return r4;
}

vector<int> decryption(vector<int> p)
{
    vector<int> r1, r2, r3, r4;
    r1 = ARK(p, 3);

    r2 = ARK((invSubNib(shiftRow(r1))), 2);

    r3 = convertToVector(mix_columns(convertTo2x2Matrix(r2), {{9, 2}, {2, 9}}));

    r4 = ARK((invSubNib(shiftRow(r3))), 1);

    return r4;
}

int main()
{
    vector<int> k = {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1};
    vector<int> p = {1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0};
    vector<int> s = {0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0};
    generateKey(k);
    cout << "\nKeys are - ";
    for (int i = 0; i < 3; i++)
    {
        cout << "\nKey" << i + 1 << " - ";
        for (int j = 0; j < 16; j++)
        {
            cout << keys[i][j] << " ";
        }
    }

    vector<int> ans = encryption(p);
    cout << "\n\nAfter Encryption- \nCipher text is - ";
    for (int j = 0; j < 16; j++)
    {
        cout << ans[j] << " ";
    }

    vector<int> ans1 = decryption(ans);
    cout << "\n\nAfter Decryption - \nPlain text is - ";
    for (int j = 0; j < 16; j++)
    {
        cout << ans1[j] << " ";
    }

    return 0;
}