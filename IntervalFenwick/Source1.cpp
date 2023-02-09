Skip to content
Product
Solutions
Open Source
Pricing
Search
Sign in
Sign up
ackoroa
/
UVa - Solutions
Public
Code
Issues
1
Pull requests
1
Actions
Projects
Wiki
Security
Insights
UVa - Solutions / UVa 12532 - Interval Product / src / UVa 12532 - Interval Product.cpp
@ackoroa
ackoroa IVa 12532
Latest commit 7dfdf75 on 2 Feb 2013
History
1 contributor
84 lines(70 sloc)  1.32 KB

#include <cstdio>
#include <vector>
using namespace std;

int x[100005];

int LSOne(int n) {
	return n & (-n);
}

class FT {
private:
	vector<int> ft;

public:
	FT(int n) {
		ft.assign(n + 1, 0);
	}
	int rsq(int b) {
		int sum = 0;
		for (; b; b -= LSOne(b))
			sum += ft[b];
		return sum;
	}
	int rsq(int a, int b) {
		return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
	}

	void adjust(int k, int v) {
		for (; k < (int)ft.size(); k += LSOne(k)) {
			ft[k] += v;
		}
	}
};

int main() {
	int n, k, d1, d2;
	char q;

	while (scanf("%d %d", &n, &k) != EOF) {
		FT ftNeg(n), ftZero(n);

		for (int i = 1; i <= n; i++) {
			scanf("%d", &x[i]);
			if (x[i] < 0)
				ftNeg.adjust(i, 1);
			if (x[i] == 0)
				ftZero.adjust(i, 1);
		}

		for (int i = 0; i < k; i++) {
			scanf("%c", &q);
			while (q != 'P' && q != 'C')
				scanf("%c", &q);
			scanf("%d %d", &d1, &d2);

			if (q == 'P') {
				if (ftZero.rsq(d1, d2)) {
					printf("0");
				}
				else if (ftNeg.rsq(d1, d2) % 2 == 0) {
					printf("+");
				}
				else {
					printf("-");
				}
			}
			else if (q == 'C') {
				if (x[d1] >= 0 && d2 < 0)
					ftNeg.adjust(d1, 1);
				else if (x[d1] < 0 && d2 >= 0)
					ftNeg.adjust(d1, 1);

				if (x[d1] != 0 && d2 == 0)
					ftZero.adjust(d1, 1);
				else if (x[d1] == 0 && d2 != 0)
					ftZero.adjust(d1, -1);

				x[d1] = d2;
			}
		}

		printf("\n");
	}

	return 0;
}
Footer
© 2022 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
