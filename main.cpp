#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

#define MAXSIZE  10 //改变此数值可改变数据大小
set<int>ticketset, vipset;

// 基类：Fan
class Fan {
protected:
    int number; // 购票编号
public:
    Fan(int num) : number(num) {}
    virtual ~Fan() {}

    int getNumber() const { return number; }
    virtual int getInt() const = 0;
    virtual string getType() const = 0; // 纯虚函数，用于获取购票者类型
};

// 普通购票者类
class TicketFan : public Fan {
public:
    TicketFan(int num) : Fan(num) {}
    int getInt() const override { return 0; }
    string getType() const override { return "普通购票者"; }
};

// VIP购票者类
class VIPFan : public Fan {
public:
    VIPFan(int num) : Fan(num) {}
    int getInt() const override { return 1; }
    string getType() const override { return "VIP购票者"; }
};

// 按编号排序
bool comp(const Fan* a, const Fan* b) {
    return a->getNumber() < b->getNumber();
}

//随机生成不重复的编号
int generate(set<int>& ticketset)
{
    int num;
    do {
        num= rand() % MAXSIZE + 1;
    } while (ticketset.count(num));
    ticketset.insert(num);
    return num;
}

//判断是否满员
bool judgefull(set<int>& ticketset)
{
    if (ticketset.size() == MAXSIZE)
    {
        return true;
    }
    return false;
}

// 添加购票者
void addFan(deque<Fan*>& ticketQueue, deque<Fan*>& vipQueue, bool break_) {
    int randomType = (rand() % 5 == 0) ? 1 : 0; // 五分之一概率为 VIP
    int randomNumber;

    if(!judgefull(ticketset) && !judgefull(vipset))
    {
        if (randomType == 0) {
            randomNumber = generate(ticketset);
            ticketQueue.push_back(new TicketFan(randomNumber));
            cout << "加入购票者编号: " << randomNumber << ", 类型: 普通购票者\n";
        }
        else {
            randomNumber = generate(vipset);
            vipQueue.push_back(new VIPFan(randomNumber));
            cout << "加入购票者编号: " << randomNumber << ", 类型: VIP购票者\n";
        }
    }
    else if (judgefull(ticketset) && !judgefull(vipset))
    {
        randomNumber = generate(vipset);
        vipQueue.push_back(new VIPFan(randomNumber));
        cout << "加入购票者编号: " << randomNumber << ", 类型: VIP购票者\n";
    }
    else if (!judgefull(ticketset) && judgefull(vipset))
    {
        randomNumber = generate(ticketset);
        ticketQueue.push_back(new TicketFan(randomNumber));
        cout << "加入购票者编号: " << randomNumber << ", 类型: 普通购票者\n";
    }
    else
    {
        cout << "全部满员！\n";
        break_ = true;
    }
    
}

// 购票处理
void buyTicket(int command, deque<Fan*>& queue) {
    if (queue.empty()) return;

    if (command == 0) {
        cout << queue.front()->getType() << "编号 " << queue.front()->getNumber() << " 购票成功。\n";
        if (queue.front()->getInt() == 1)//判断vip还是普通
        {
            vipset.erase(queue.front()->getNumber());
        }
        else
        {
            ticketset.erase(queue.front()->getNumber());
        }
        delete queue.front(); // 删除对象释放内存
        queue.pop_front();
    }
    else {
        cout << queue.back()->getType() << "编号 " << queue.back()->getNumber() << " 购票成功。\n";
        if (queue.back()->getInt() == 1)//判断vip还是普通
        {
            vipset.erase(queue.back()->getNumber());
        }
        else
        {
            ticketset.erase(queue.back()->getNumber());
        }
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
        do {
            cin >> m;
        } while (m < 0);//错误输入保护
        for (int i = 0; i < m; ++i) {
            bool break_ = false;
            addFan(ticketQueue, vipQueue,break_);
            if (break_)
            {
                break;
            }
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

    function(1, ticketQueue, vipQueue);
    
    srand(static_cast<unsigned>(time(0)));

    cout << endl;

    cout << "开始售票...\n";

    while (!ticketQueue.empty() || !vipQueue.empty()) {
        cout << "1：加入购票者 2：继续卖票\n";
        int choice;
        cin >> choice;//此处界面用两个botton替代

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