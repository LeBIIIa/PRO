#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void matrixOut(int n, vector<vector<int>>& A, vector<vector<int>>& B) {
	int i, j;
	cout << endl << "Matrix A" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << "Matrix B:" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << B[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
void resOut(int n, vector<vector<int>>& Y) {
	int i, j;
	cout << endl << "Result matrix Y:" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << Y[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
vector<vector<int>> MMM(vector<vector<int>> a, vector<vector<int>> b, int size) {
	vector<vector<int>> res;
	res.resize(size);
	for (int i = 0; i < size; ++i) {
		res[i].resize(size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			res[i][j] = 0;
			for (int k = 0; k < size; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return res;
}

int main() {
	srand(time(NULL));
	int i, j, n, k;
	cout << "Enter matrix size(n): ";
	cin >> n;
	vector<vector<int>> A(n, vector<int>(n, 0)), B(n, vector<int>(n, 0)), Y(n, vector<int>(n, 0));
	for (i = 0; i < n; ++i) 
	{
		for (j = n - i - 1, k = n; j >= 0; --j, k--)
		{
			A[i][j] = k;
		}
	}
	for (i = 0; i < n; ++i) 
	{ 
		for (j = n / 2; j < n; j++)
		{ 
			B[i][j] = rand() % 10; 
		} 
	}
	matrixOut(n, A, B);
	Y = MMM(A, B, n);
	resOut(n, Y);
	return 0;
}