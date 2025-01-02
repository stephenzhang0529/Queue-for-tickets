#include "fun.h"
#define MAXSIZE 10
#define LEFT 20
set<int>ticketset, vipset;
#include<iostream>

#include<deque>
#include <algorithm>
#include <cstdlib>
bool comp(const Fan& a, const Fan& b)
{
    return a.number < b.number;
}
Fan fun::addfan()
{
    int randomType = (rand() % 5 == 0) ? 1 : 0; // 五分之一概率为 VIP
    int randomNumber;
    Fan newfan;
    if(!judgefull(ticketset) && !judgefull(vipset))
    {
        if (randomType == 0) {
            randomNumber = generate(ticketset);

            newfan.number=randomNumber;
            newfan.level=0;
            ticket.push_back(newfan);

        }
        else {
            randomNumber = generate(vipset);
            newfan.number=randomNumber;
            newfan.level=1;
            vip.push_back(newfan);

        }
    }
    else if (judgefull(ticketset) && !judgefull(vipset))
    {
        randomNumber = generate(vipset);
        newfan.number=randomNumber;
        newfan.level=1;
        vip.push_back(newfan);

    }
    else if (!judgefull(ticketset) && judgefull(vipset))
    {
        randomNumber = generate(ticketset);
        newfan.number=randomNumber;
        newfan.level=0;
        ticket.push_back(newfan);

    }
    else
    {
        newfan={-1,-1};
    }
    return newfan;
}
Fan fun::buyTicket(int command)
{
    Fan fan;
    fan.level=0;
    if (ticket.empty())
    {
        return {-1,-1};
    }
    else
    {
        if(command==0)
        {
            ticketset.erase(ticket.front().number);
            fan.number=ticket.front().number;
            ticket.pop_front();
        }
        else
        {
            ticketset.erase(ticket.back().number);
            fan.number=ticket.back().number;
            ticket.pop_back();
        }
    }
    return fan;
}

// VIP窗口购票
Fan fun::buyVIP(int command)
{
    Fan fan;
    fan.level=1;
    if(vip.empty())
    {
        return buyTicket(command);
    }
    else
    {
        if(command==0)
        {
            vipset.erase(vip.front().number);
            fan.number=vip.front().number;
            vip.pop_front();
        }
        else
        {
            vipset.erase(vip.back().number);
            fan.number=vip.back().number;
            vip.pop_back();
        }
    }
    return fan;
}
void fun::SortTicket()
{
    sort(ticket.begin(),ticket.end(),comp);
}
void fun::SortVip()
{
    sort(vip.begin(),vip.end(),comp);
}
void fun::updatadeque(deque<Fan> d,deque<Fan> vipd)
{
    ticket=d;
    vip=vipd;
}
deque<Fan> fun::Getticket()
{
    return ticket;
}
deque<Fan> fun::Getvip()
{
    return vip;
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
