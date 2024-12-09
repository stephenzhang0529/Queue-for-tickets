#include<iostream>
#include<vector>
#include<deque>
#include <algorithm>

using namespace std;
typedef struct Fan {
	int number;//购票编号
	int level;//票的等级 0：普通  1：VIP
}Fan;
bool comp(const Fan& a, const Fan& b)
{
	return a.number < b.number;
}
void addfan(deque<Fan>&ticket,deque<Fan>&vip)
{
	Fan newfan;
	cout << "购票者随机编号：";
	newfan.number = rand() % 10000 + 1;
	cout << newfan.number << endl;

	cout << "购票类型：";
	newfan.level = (0 < (rand() % 5)) ? 0 : 1;//五分之一概率为vip
	cout << newfan.level << endl;

	if (newfan.level == 0)//普通票
	{
		ticket.push_back(newfan);
	}
	else
	{
		vip.push_back(newfan);
	}
}
void buyticket(int command, deque<Fan>& ticket)
{
	if (ticket.empty())
	{
		return;
	}
	if (command == 0) {
		// 最小编号购票
		cout << "编号 " << ticket.front().number << " 的购票者购票成功。\n";
		ticket.pop_front();
	}
	else {
		// 最大编号购票
		cout << "编号 " << ticket.back().number << " 的购票者购票成功。\n";
		ticket.pop_back();
	}
}
void buyvip(int command, deque<Fan>& ticket, deque<Fan>& vip)
{
	if (vip.empty())//当vip队伍为空时，vip窗口可卖普通票
	{
		buyticket(command, ticket);
	}
	else
	{
		buyticket(command, vip);
	}
}
void function(int choice, deque<Fan>& ticket, deque<Fan>& vip)
{
	switch (choice)
	{
	case 1://加入购票者
		int m;
		cout << "请输入新来的购票者人数：\n";
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			addfan(ticket, vip);
		}
		sort(ticket.begin(), ticket.end(), comp);//小到大排序
		sort(vip.begin(), vip.end(), comp);

		//然后继续卖票
	case 2://继续卖票
		int command = rand() % 2; // 随机指令0或1
		cout << "随机指令为" << command << endl;
		buyticket(command, ticket);
		buyvip(command, ticket, vip);
		break;
	}
}
int main()
{
	int n = -1;
	deque<Fan> ticketqueue;
	deque<Fan> vipqueue;

	while (n <= 0)
	{
		cout << "请输入购票者数量：";//防止错误输入
		cin >> n;
		if (n > 0)break;
	}

	cout << "生成随机购票编号以及票的类型...\n";
	srand(static_cast<unsigned>(time(0))); // 随机种子

	for (int i = 0; i < n; ++i) {
		
		addfan(ticketqueue, vipqueue);
	}
	cout << endl;

	sort(ticketqueue.begin(), ticketqueue.end(),comp);//小到大排序
	sort(vipqueue.begin(), vipqueue.end(), comp);

	
	// 模拟售票过程
	cout << "开始售票...\n";
	srand(static_cast<unsigned>(time(0))); // 随机种子

	while (!ticketqueue.empty()||!vipqueue.empty()) {
		//是否有新来的购票者
		cout << "1：加入购票者 2：继续卖票" << endl;//此处是两个botton
		int choice, current = 0;
		cin >> choice;
		function(choice, ticketqueue, vipqueue);
		if (ticketqueue.empty() && vipqueue.empty())
		{
			cout << "1：加入购票者 2：退出" << endl;//此处是两个botton
			cin >> choice;
			if (choice == 2)break;
			function(1, ticketqueue, vipqueue);
		}
	}

	cout << "所有购票者已完成购票！\n";
}