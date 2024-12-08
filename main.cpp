#include<iostream>
#include<vector>
#include<deque>
#include <algorithm>

using namespace std;

int main()
{
	int n=-1;
	vector<int>ticketnumber;
	int max = 0, min = 10000000;
	while (n <= 0)
	{
		cout << "请输入购票者数量：";//防止错误输入
		cin >> n;
		if (n > 0)break;
	}
	
	cout << "生成随机购票编号...\n";
	srand(static_cast<unsigned>(time(0))); // 随机种子

	for (int i = 0; i < n; ++i) {
		cout << "购票者随机编号：";
		int current = rand() % 10000 + 1;
		ticketnumber.push_back(current); // 随机编号1到10000
		cout << current << endl;
	}
	cout << endl;

	sort(ticketnumber.begin(), ticketnumber.end());//小到大排序
	deque<int> queue(ticketnumber.begin(), ticketnumber.end());
	// 模拟售票过程
	cout << "开始售票...\n";
	srand(static_cast<unsigned>(time(0))); // 随机种子

	while (!queue.empty()) {
		//是否有新来的购票者
		cout << "1：加入购票者 2：继续卖票" << endl;//此处是两个botton
		int choice, current = 0;
		cin >> choice;
		switch (choice)
		{
		case 1://加入购票者
			int m;
			cout << "请输入新来的购票者人数：\n";
			cin >> m;
			for (int i = 0; i < m; i++)
			{
				cout << "新的购票者随机编号：";
				current = rand() % 10000 + 1;
				queue.push_back(current);
				cout << current << endl;
			}
			sort(queue.begin(), queue.end());
			//然后继续卖票
		case 2://继续卖票
			int command = rand() % 2; // 随机指令0或1
			cout << "随机指令为" << command << endl;
			if (command == 0) {
				// 最小编号购票
				cout << "编号 " << queue.front() << " 的购票者购票成功。\n";
				queue.pop_front();
			}
			else {
				// 最大编号购票
				cout << "编号 " << queue.back() << " 的购票者购票成功。\n";
				queue.pop_back();
			}
			break;
		}
	}

	cout << "所有购票者已完成购票！\n";
}