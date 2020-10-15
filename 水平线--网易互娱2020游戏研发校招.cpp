/*
伞屉国是一个以太阳能为主要发电手段的国家，因此他们国家中有着非常多的太阳能基站，链接着的基站会组合成一个发电集群。但是不幸的是伞屉国不时会遭遇滔天的洪水，当洪水淹没基站时，基站只能停止发电，同时被迫断开与相邻基站的链接。你作为伞屉国的洪水观察员，有着这样的任务：在洪水到来时，计算出发电集群被洪水淹没后被拆分成了多少个集群。

由于远古的宇宙战争的原因，伞屉文明是一个二维世界里的文明，所以你可以这样理解发电基站的位置与他们的链接关系：给你一个一维数组a，长度为n，表示了n个基站的位置高度信息。数组的第i个元素a[i]表示第i个基站的海拔高度是a[i],而下标相邻的基站才相邻并且建立链接，即x号基站与x-1号基站、x+1号基站相邻。特别的，1号基站仅与2号相邻，而n号基站仅与n-1号基站相邻。当一场海拔高度为y的洪水到来时，海拔高度小于等于y的基站都会被认为需要停止发电，同时断开与相邻基站的链接。


输入描述:
每个输入数据包含一个测试点。

第一行为一个正整数n，表示发电基站的个数 (0 < n <= 200000)

接下来一行有n个空格隔开的数字，表示n个基站的海拔高度，第i个数字a[i]即为第i个基站的海拔高度，对于任意的i(1<=i<=n),有(0 <= a[i] < 2^31-1)

接下来一行有一个正整数q(0 < q <= 200000)，表示接下来有q场洪水

接下来一行有q个整数，第j个整数y[j]表示第j场洪水的海拔为y[j],对于任意的j(1<=j<=n),有(-2^31 < y[j] < 2^31-1)


输出描述:
输出q行，每行一个整数，第j行的整数ans表示在第j场洪水中，发电基站会被分割成ans个集群。标准答案保证最后一个整数后也有换行。


示例1

输入
10
6 12 20 14 15 15 7 19 18 13
6
15 23 19 1 17 24

输出
2
0
1
1
2
0
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void Flood_Fighting() {
	int n = 0;//n个发电基站
	int q = 0;//q场洪水
	cin >> n;
	vector<pair<int,int>> power_station_height(n + 2);//存放每个发电基站的高度,n+2是为了防止下标越界，键值对，first用来保存发电站高度，second用来保存发电站位置

	for (int i = 1; i <= n; i++) {
		cin >> power_station_height[i].first;
		power_station_height[i].second = i;
	}

	cin >> q;
	vector<pair<int,int>> flood_height(q);//存放每场洪水的高度

	for (int i = 0; i < q; i++) {
		cin >> flood_height[i].first;
		flood_height[i].second = i;
	}

	vector<pair<int, int>> tmp(power_station_height);//临时数组,用于存放已排序的各发电站高度

	sort(tmp.begin() + 1, tmp.end() - 1);//对发电站高度排序
	sort(flood_height.begin(), flood_height.end());//对洪水高度排序

	vector<int> result(q, 0);//记录每次洪水过后的ans群数结果

	int r = 1;//用来记录上一次洪水淹没的最后一个发电站在tmp中的位置
	int count = 1;//因为洪水而分成的ans群数
	vector<int> sk(n + 2, 0);//状态数组，状态为0代表没有被淹，1代表被淹
	sk[0] = sk[n + 1] = 1;
	for (int i = 0; i < q; i++) {
		for ( int k = r ; k <= n; k++) {
			if (tmp[k].first <= flood_height[i].first) {
				sk[tmp[k].second] = 1;

				//每个沉下去的发电机有三种情况。
				//1. 两侧的发电机都沉下去了， 集群数 - 1;
				//2. 只有一侧的发电机沉下去， 集群数不变;
				//3. 两侧的发电机都未沉下去， 集群数 + 1.
				if (sk[tmp[k].second + 1] == 1 && sk[tmp[k].second - 1] == 1) {
					count--;
				}
				else if (sk[tmp[k].second + 1] != 1 && sk[tmp[k].second - 1] != 1) {
					count++;
				}

			}
			else {
				result[flood_height[i].second] = count;
				r = k;
				break;
			}
		}
	}

	for (auto e : result) {
		cout << e << endl;
	}
}

/*int main() {
	Flood_Fighting();
	return 0;
}*/