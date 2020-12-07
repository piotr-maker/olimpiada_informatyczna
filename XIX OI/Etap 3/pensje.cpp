#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct Worker {
	int parent;
	int salary;
	int child = -1;
	int childs = -1;
	void setChild(int child_index) {
		if(this->child == -1) this->child = child_index;
		else this->child = 0;
	}
};

Worker *workers;
bool *used;

bool salary_comp(int l, int r) {
	return workers[l].salary < workers[r].salary;
}

vector<int> salary_unused(int max) {
	vector<int> result;
	static int min;
	
	for(int i = min + 1; i < max; i++) {
		if(!used[i]) result.push_back(i);
	}

	if(result.size()) min = result.back();
	return result;
}

int main() {
	int n, p, z, temp;
	vector<int> boss;
    
	scanf("%d", &n);
	workers = new Worker[n+1];
	used = new bool[n+1];
	for(int i = 1; i <= n; i++) used[i] = false;
	used[0] = true;

	// pobranie informacji do stosu
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &p, &z);
		if(i == p) z = n;
		if(z) { boss.push_back(i); used[z] = true; }
		else workers[p].setChild(i);

		workers[i].parent = p;		
		workers[i].salary = z;
	}

	// obliczenie ilości podwładnych dla każdego szefa
	for(int i = 1; i <= n; i++) {
		temp = i;
		while(workers[temp].salary == 0) temp = workers[temp].parent;
		workers[i].parent = temp;
		workers[temp].childs += 1;
	}

	sort(boss.begin(), boss.end(), salary_comp);

	// próba wyliczenia pozostałych pensji
    int left = 0;
    int current_boss;
	vector<int> unused;
	for(int i = 0; i < boss.size(); i++) {
        current_boss = boss[i];
		temp = current_boss;
		if(workers[temp].childs > 0) {
			unused = salary_unused(workers[temp].salary);			
            left += unused.size();
			if(left == workers[temp].childs) {
				while(unused.size() && workers[temp].child > 0) {
					temp = workers[temp].child;
					workers[temp].salary = unused.back();
					unused.pop_back();
				}
			}

			left -= workers[current_boss].childs;
		}
	}

	for(int i = 1; i <= n; i++)
		printf("%d\n", workers[i].salary);

	delete [] used;
	delete [] workers;
	return 0;    
}
