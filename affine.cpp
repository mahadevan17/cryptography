#include <iostream>       											//hnzano rnhhlbn:secret message 
using namespace std;
class Affine
{
	char Arr[26];

public:
	Affine()
	{
		for (int j = 0; j < 26; j++)
		{
			Arr[j] = (char)(97 + j);
		}
	}
	int mod26(int i)
	{
		if (i >= 0)
			return i % 26;
		else
		{
			while (i < 0)
			{
				i += 26;
			}
			return i;
		}
	}

	string affinencry(string st, int a, int b)
	{
		string enst = "";
		for (int i = 0; i < st.length(); i++)
		{
			if (st[i] == ' ')
				enst += " ";
			else
			{

				enst = enst + Arr[mod26((a * (st[i] - 97) + b))];
			}
		}
		return enst;
	}

	int inverse(int i)
	{ // ax=1mod26
		for (int j = 0; j < 26; j++)
		{
			if ((i * j) % 26 == 1)
				return j;
		}
	}

	string affinedecry(string st, int a, int b)
	{
		string decrst = "";
		for (int i = 0; i < st.length(); i++)
		{
			if (st[i] == ' ')
				decrst += " ";
			else
			{

				decrst = decrst + Arr[mod26((inverse(a) * (st[i] - 97 - b)))];
			}
		}
		return decrst;
	}

	/*void print()
	{
		for (int j = 0; j < 26; j++)
		{
			cout << Arr[j] << " ";
		}
	}*/

	int gcd(int a, int b)
	{
		if (b == 0)
			return a;
		else
			return gcd(b, a % b);
	}

	int cona(int a)
	{ // to check if gcd(a,26)==1
		if (a < 26 && gcd(26, a) == 1)
			return 1;
	}

	string analysis(string ct, int a, int b)
	{
		string ar = "";
		int i = 0, ainverse;
		if (cona(a))
		{
			ainverse = inverse(a);
			cout << endl;
			while (i < ct.length())
			{
				if (ct[i] == ' ')
				{
					ar += " ";
				}
				else
				{
					ar += Arr[mod26((ct[i] - 'a' - b) * ainverse)];
				}
				i++;
			}
		}
		return ar;
	}
};

int main()
{
	string st, ct, pt, cipher;
	getline(cin, st);
	int k1, k2;
	cout << "enter the keys values ";
	cin >> k1 >> k2;
	Affine a;
	ct = a.affinencry(st, k1, k2);
	cout << ct << endl;
	cout << "***********************" << endl;
	pt = a.affinedecry(ct, k1, k2);
	cout << pt << endl;
	cout << "***********************" << endl;
	for (int i = 3; i < 26; i = i + 2)
	{
		for (int j = 1; j < 26; j++)
		{
			cout << a.analysis(ct, i, j) << "	: " << i << "   " << j << endl;
		}
	}
	return 0;
}
