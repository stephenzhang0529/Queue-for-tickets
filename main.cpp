#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// 基类：Fan
class Fan {
protected:
    int number; // 购票编号
public:
    Fan(int num) : number(num) {}
    virtual ~Fan() {}

    int getNumber() const { return number; }
    virtual string getType() const = 0; // 纯虚函数，用于获取购票者类型
};

// 普通购票者类
class TicketFan : public Fan {
public:
    TicketFan(int num) : Fan(num) {}
    string getType() const override { return "普通购票者"; }
};

// VIP购票者类
class VIPFan : public Fan {
public:
    VIPFan(int num) : Fan(num) {}
    string getType() const override { return "VIP购票者"; }
};

// 按编号排序
bool comp(const Fan* a, const Fan* b) {
    return a->getNumber() < b->getNumber();
}

// 添加购票者
void addFan(deque<Fan*>& ticketQueue, deque<Fan*>& vipQueue) {
    int randomNumber = rand() % 10000 + 1;
    int randomType = (rand() % 5 == 0) ? 1 : 0; // 五分之一概率为 VIP

    if (randomType == 0) {
        ticketQueue.push_back(new TicketFan(randomNumber));
        cout << "加入购票者编号: " << randomNumber << ", 类型: 普通购票者\n";
    }
    else {
        vipQueue.push_back(new VIPFan(randomNumber));
        cout << "加入购票者编号: " << randomNumber << ", 类型: VIP购票者\n";
    }
}

// 购票处理
void buyTicket(int command, deque<Fan*>& queue) {
    if (queue.empty()) return;

    if (command == 0) {
        cout << queue.front()->getType() << "编号 " << queue.front()->getNumber() << " 购票成功。\n";
        delete queue.front(); // 删除对象释放内存
        queue.pop_front();
    }
    else {
        cout << queue.back()->getType() << "编号 " << queue.back()->getNumber() << " 购票成功。\n";
        delete queue.back(); // 删除对象释放内存
        queue.pop_back();
    }
}

// VIP窗口购票
void buyVIP(int command, deque<Fan*>& ticketQueue, deque<Fan*>& vipQueue) {
    if (vipQueue.empty()) {
        buyTicket(command, ticketQueue);
    }
    else {
        buyTicket(command, vipQueue);
    }
}

// 功能选择
void function(int choice, deque<Fan*>& ticketQueue, deque<Fan*>& vipQueue) {
    switch (choice) {
    case 1: {
        int m;
        cout << "请输入新来的购票者人数：\n";
        cin >> m;
        for (int i = 0; i < m; ++i) {
            addFan(ticketQueue, vipQueue);
        }
        sort(ticketQueue.begin(), ticketQueue.end(), comp);
        sort(vipQueue.begin(), vipQueue.end(), comp);
        break;
    }
    case 2: {
        int command = rand() % 2; // 随机指令 0 或 1
        cout << "随机指令为: " << command << endl;
        buyTicket(command, ticketQueue);
        buyVIP(command, ticketQueue, vipQueue);
        break;
    }
    }
}

// 主函数
int main() {
    int n = -1;
    deque<Fan*> ticketQueue;
    deque<Fan*> vipQueue;

    cout << "请输入购票者数量：";
    while (n <= 0) {
        cin >> n;
        if (n > 0) break;
    }

    cout << "生成随机购票编号以及票的类型...\n";
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < n; ++i) {
        addFan(ticketQueue, vipQueue);
    }
    cout << endl;

    sort(ticketQueue.begin(), ticketQueue.end(), comp);
    sort(vipQueue.begin(), vipQueue.end(), comp);

    cout << "开始售票...\n";

    while (!ticketQueue.empty() || !vipQueue.empty()) {
        cout << "1：加入购票者 2：继续卖票\n";
        int choice;
        cin >> choice;

        function(choice, ticketQueue, vipQueue);

        if (ticketQueue.empty() && vipQueue.empty()) {
            cout << "1：加入购票者 2：退出\n";
            cin >> choice;
            if (choice == 2) break;
            function(1, ticketQueue, vipQueue);
        }
    }

    cout << "所有购票者已完成购票！\n";

    // 清理剩余队列中的对象
    for (Fan* fan : ticketQueue) delete fan;
    for (Fan* fan : vipQueue) delete fan;

    return 0;
}
