/*
小Q在周末的时候和他的小伙伴来到大城市逛街，一条步行街上有很多高楼，共有n座高楼排成一行。
小Q从第一栋一直走到了最后一栋，小Q从来都没有见到这么多的楼，所以他想知道他在每栋楼的位置处能看到多少栋楼呢？（当前面的楼的高度大于等于后面的楼时，后面的楼将被挡住）

输入描述 :
输入第一行将包含一个数字n，代表楼的栋数，接下来的一行将包含n个数字wi(1 <= i <= n)，代表每一栋楼的高度。
1 <= n <= 100000;
1 <= wi <= 100000;


输出描述:
输出一行，包含空格分割的n个数字vi，分别代表小Q在第i栋楼时能看到的楼的数量。
示例1
输入
6
5 3 8 3 2 5
输出
3 3 5 4 4 4
说明
当小Q处于位置3时，他可以向前看到位置2, 1处的楼，向后看到位置4, 6处的楼，加上第3栋楼，共可看到5栋楼。
当小Q处于位置4时，他可以向前看到位置3处的楼，向后看到位置5, 6处的楼，加上第4栋楼，共可看到4栋楼。
*/

#include<iostream>
#include<vector>
#include<stack>

using namespace std;

//单调栈实现
void CanSeeManyHouse() {
	int n = 0;
	cin >> n;
	vector<int> height(n, 0);
	for (int i = 0; i < height.size(); i++) {
		cin >> height[i];
	}
	vector<int> left(n, 0);//存储每个位置往自己的左边看，能看到的大楼数
	vector<int> right(n, 0);//存储每个位置往自己的右边看，能看到的大楼数
	stack<int> sk;
	for (int i = 0; i < n; i++) {
		left[i] = sk.size();//当前i位置往左边看能看到的大楼数
		//如果i位置之前的楼的高度小于等于i位置楼的高度，则从栈中取出，表示大于i的位置看不到i之前的大楼
		while (!sk.empty() && sk.top() <= height[i]) {
			sk.pop();
		}
		//把i位置的大楼压入栈中，表示大于i的位置能看到i位置的大楼
		sk.push(height[i]);
	}
	//清空栈
	while (!sk.empty()) {
		sk.pop();
	}
	//右边原理上述左边原理
	for (int i = n - 1; i >= 0; i--) {
		right[i] = sk.size();
		while (!sk.empty() && sk.top() <= height[i]) {
			sk.pop();
		}
		sk.push(height[i]);
	}
	for (int i = 0; i < n; i++) {
		//输出当前位置往左往右能看到的大楼数之和，并且加上自身
		cout << left[i] + right[i] + 1 << " ";
	}
}
//粗暴遍历：时间复杂度O(n²)
void CanSeeManyHouse1() {
	int n = 0;
	cin >> n;
	vector<int> height(n, 0);
	for (int i = 0; i < height.size();i++) {
		cin >> height[i];
	}

	vector<int> count(n, 0);
	int i = 0;
	while (i < height.size()) {
		int Count = 0;
		if (i == 0) {
			Count = 2;//第一个位置最起码可以看到自己当前所在大楼和相邻的一个大楼
			//与当前位置相邻的大楼也是一定可以看见的，所以直接从相隔一个的大楼开始判断
			for (int j = i + 2; j < height.size(); j++) {
				int flag = 1;//表示当前大楼是否可以看见，0代表不可以，1代表可以
				for (int k = j - 1; k > i; k--) {
					if (height[k] < height[j]) {
						continue;
					}
					else {
						flag = 0;
						break;
					}
				}
				if (flag == 1) {
					Count++;
				}
			}
		}
		//最后一个位置最起码可以看到自己当前所在大楼和相邻的一个大楼
		else if (i == height.size() - 1) {
			Count = 2;
			//与当前位置相邻的大楼也是一定可以看见的，所以直接从相隔一个的大楼开始判断
			for (int j = i - 2; j >= 0; j--) {
				int flag = 1;//表示当前大楼是否可以看见，0代表不可以，1代表可以
				for (int k = j + 1; k < i; k++) {
					if (height[k] < height[j]) {
						continue;
					}
					else {
						flag = 0;
						break;
					}
				}
				if (flag == 1) {
					Count++;
				}
			}
		}
		else {
			Count = 3;//其他位置最起码可以看到自己当前所在大楼和左右相邻的两个个大楼
			for (int j = i + 2; j < height.size(); j++) {
				int flag = 1;//表示当前大楼是否可以看见，0代表不可以，1代表可以
				for (int k = j - 1; k > i; k--) {
					if (height[k] < height[j]) {
						continue;
					}
					else {
						flag = 0;
						break;
					}
				}
				if (flag == 1) {
					Count++;
				}
			}
			for (int j = i - 2; j >= 0; j--) {
				int flag = 1;//表示当前大楼是否可以看见，0代表不可以，1代表可以
				for (int k = j + 1; k < i; k++) {
					if (height[k] < height[j]) {
						continue;
					}
					else {
						flag = 0;
						break;
					}
				}
				if (flag == 1) {
					Count++;
				}
			}
		}
		count[i] = Count;
		i++;
	}
	for (int i = 0; i < count.size(); i++) {
		cout << count[i] << " ";
	}
}



/*int main() {
	CanSeeManyHouse();
	return 0;
}*/