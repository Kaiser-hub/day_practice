/*
小Q在进行一场竞技游戏,这场游戏的胜负关键就在于能否能争夺一条长度为L的河道,即可以看作是[0,L]的一条数轴。
这款竞技游戏当中有n个可以提供视野的道具−真视守卫,第i个真视守卫能够覆盖区间[xi,yi]。现在小Q想知道至少用几个真视守卫就可以覆盖整段河道。

输入描述:
输入包括n+1行。

第一行包括两个正整数n和L(1<=n<=105,1<=L<=109)

接下来的n行,每行两个正整数xi,yi(0<=xi<=yi<=109),表示第i个真视守卫覆盖的区间。



输出描述:
一个整数，表示最少需要的真视守卫数量, 如果无解, 输出-1。
示例1
输入
4 6
3 6
2 4
0 2
4 7

输出
3

*/


#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//用vector创建二维数组实现会超时
//所以在这里改用键值对实现
int FightOfView() {
	int n = 0;//商店拥有真视守卫的数量
	int L = 0;//河道的长度
	cin >> n >> L;

	vector<pair<int,int>> XY(n);//存放各个真视守卫的覆盖区间【xi，yi】
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		XY[i] = make_pair(x, y);
	}

	//按每个真视守卫的x进行升序排序
	sort(XY.begin(), XY.end());

	//若最小的x无法覆盖0或者最大的y无法覆盖L，那么一定不可能覆盖整个河道，返回-1
	if (XY[0].first > 0 || XY[n - 1].second < L) {
		return -1;
	}
	int count = 1;
	for (int i = 1; i < n; i++) {
		//如果当前守卫的x在前一个守卫的范围之间，那么可以选用
		if (XY[i].first <= XY[i - 1].second) {
			//继续往后查找，看看是否有更合适的守卫(x同样满足要求并且y更大)
			int j = i + 1;
			int k = i - 1;
			int max_y = XY[i].second;
			while ((j < n)&&(XY[j].first <= XY[k].second)) {
				if (XY[j].second > max_y) {
					max_y = XY[j].second;
					i = j;
					j++;
				}
				else {
					j++;
				}
			}
			count++;
			if (XY[i].second >= L) {
				break;
			}
		}
		//否则，证明中间有覆盖不到的部分
		else {
			return -1;
		}
	}
	return count;
}

/*int main() {
	cout << FightOfView() << endl;
	return 0;
}*/