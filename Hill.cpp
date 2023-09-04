#include <iostream>
#include <string.h>
using namespace std;

class Hill
{
	char Arr[26];
	int **invA;

public:
	Hill()
	{
		invA = new int *[2];
		for (int j = 0; j < 26; j++)
		{
			Arr[j] = (char)(97 + j);
		}
	}
	int stonum(char s)
	{
		for (int i = 0; i < 26; i++)
		{
			if (s == Arr[i])
				return i;
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

	int inverse(int i)
	{ // ax=1mod26
		i = mod26(i);
		for (int j = 0; j < 26; j++)
		{
			if ((i * j) % 26 == 1)
				return j;
		}
		return 0;
	}

	string hillencry(int ar[], int a[][2])
	{
		string enst = "";
		int x[2] = {0, 0};
		int k = 0;
		for (int i = 0; i < 2; i++)
		{ // i coloumn
			for (int j = 0; j < 2; j++)
			{ // j row
				x[i] += (ar[j] * a[j][i]);
			}
		}

		for (int i = 0; i < 2; i++)
		{

			enst = enst + Arr[mod26(x[i])];
		}

		return enst;
	}
	string hilldecry(int mat[], int **ki)
	{
		string dest = "";
		int x[2] = {0, 0};
		for (int i = 0; i < 2; i++)
		{ // i coloumn
			for (int j = 0; j < 2; j++)
			{ // j row
				x[i] += (mat[j] * ki[j][i]);
			}
		}

		for (int i = 0; i < 2; i++)
		{
			dest = dest + Arr[mod26(x[i])];
		}

		return dest;
	}
	int **matinverse(int mat[][2])
	{
		int **x = 0;
		int det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				cout << mat[x][y] << "\t";
			}
			cout << endl;
		}

		int a = inverse(det);

		if (a == 0)
		{
			cout << "given key matrix does not work" << endl;
			return x;
		}

		invA[0][0] = mod26(a * mat[1][1]);
		invA[0][1] = mod26(a * (-mat[0][1]));
		invA[1][0] = mod26(a * (-mat[1][0]));
		invA[1][1] = mod26(a * mat[0][0]);

		return invA;
	}

	void print()
	{
		for (int j = 0; j < 26; j++)
		{
			cout << Arr[j] << " ";
		}
	}

	void analysis(int kpt[], int kct[])
	{ // known plaintext attack
		int ptmat[2][2], ctmat[2][2];
		ptmat[0][0] = kpt[0];
		ptmat[0][1] = kpt[1];
		ptmat[1][0] = kpt[2];
		ptmat[1][1] = kpt[3];
		ctmat[0][0] = kct[0];
		ctmat[0][1] = kct[1];
		ctmat[1][0] = kct[2];
		ctmat[1][1] = kct[3];
		int **pinverse = matinverse(ptmat);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << pinverse[i][j] << "\t";
			}
			cout << endl;
		}

		int prekey[2][2] = {0, 0, 0, 0};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					prekey[i][j] += (pinverse[i][k] * ctmat[k][j]);
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				prekey[i][j] = mod26(prekey[i][j]);
			}
		}
		cout << "the predicted key is : " << endl
			 << endl;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << prekey[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	string st, ct = "", pt = "";
	getline(cin, st);
	int k[2][2];
	cout << "enter the key values " << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << i << "th," << j << "th:";
			cin >> k[i][j];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << k[i][j] << " ";
		}
		cout << endl;
	}
	Hill h;
	int mat[2];
	cout << "*************this is encryption****************" << endl;
	for (int i = 0; i < st.length(); i = i + 2)
	{
		mat[0] = st[i] - 97;
		mat[1] = st[i + 1] - 97;
		ct = ct + h.hillencry(mat, k);
	}
	cout << "the encrypted text is: " << ct << endl;
	cout << "***********this is decryption********************" << endl;
	// k is the key
	// ct is the ciphertext

	int **ki = new int *[2];

	ki = h.matinverse(k);

	cout << "cipher text:" << ct << endl;
	for (int i = 0; i < ct.length(); i = i + 2)
	{
		mat[0] = ct[i] - 97;
		mat[1] = ct[i + 1] - 97;
		pt = pt + h.hilldecry(mat, ki);
	}
	cout << "the decrypted text is: " << pt << endl;

	cout << "*************this is attack/analysis************************" << endl;
	cout << "enter the known plain text and cipher text pair: " << endl;
	string s1, s2;
	int m1[10], m2[10];
	int j = 0;
	for (int i = 0; i < 2; i++)
	{
		cin >> s1 >> s2;
		m1[i + j] = h.stonum(s1[0]);
		m2[i + j] = h.stonum(s2[0]);
		m1[i + j + 1] = h.stonum(s1[1]);
		m2[i + j + 1] = h.stonum(s2[1]);
		j = 1;
	}
	for (int i = 0; i < 4; i++)
	{
		cout << m1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << m2[i] << " ";
	}

	h.analysis(m1, m2);
	return 0;
}
