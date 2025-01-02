#ifndef FUN_H
#define FUN_H
#include<deque>
#include<set>
using namespace std;
typedef struct Fan {
    int number;//购票编号
    int level;//票的等级 0：普通  1：VIP
}Fan;
class fun
{
private:
    deque<Fan> ticket;
    deque<Fan> vip;
public:
    Fan addfan();
    Fan buyTicket(int command);
    Fan buyVIP(int command);
    void function(int choice);
    void updatadeque(deque<Fan> d,deque<Fan> vip);
    void SortTicket();
    void SortVip();
    deque<Fan> Getticket();
    deque<Fan> Getvip();
};

//随机生成不重复的编号
int generate(set<int>& ticketset);

//判断是否满员
bool judgefull(set<int>& ticketset);
#endif // FUN_H
