#include <iostream>
#include <quantapi/ctp/CtpQuoter.h>
#include <quantapi/ctp/CtpTrader.h>
#include <quantapi/datastruct.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace QuantApi;
using namespace std;

/**
* @brief 接口实例   
*/
class MyTrader : public CtpTrader{
 public:
    MyTrader(char *front):CtpTrader(front) { };
    virtual ~MyTrader() { }

    virtual void on_tick(const TickData &tick) { 
        std::cout<<"*********************************"<<std::endl;    
        std::cout<<tick.price<<std::endl;
        std::cout<<"*********************************"<<std::endl;    
    }
 private:
    /* data */
};


int main(int argc, const char *argv[])
{

    // 期权
//    char quoter_front[]="tcp://27.17.62.149:42213";
//    char trader_front[]="tcp://27.17.62.149:42205";
     
    char trader_front[]="tcp://180.168.146.181:10000";
    char quoter_front[]="tcp://180.168.146.181:10100";

    Contract c;
    c.code = "jd1604" ;
    vector<Contract> clist;
    clist.push_back(c);

    std::cout<<"*********************************"<<std::endl;    
    CtpQuoter *quoter = new CtpQuoter(quoter_front);
    MyTrader *trader = new MyTrader(trader_front);
//    LogonInfo info("8888", "001061", "001061");
    LogonInfo info("0081", "01095", "WANGDJ1985");

    quoter->login(info, false);
    trader->login(info, false);


    Order order(OrderID(1), c, kKai, LONG,
                0, 1, std::chrono::system_clock::now(), kSpeculation, kMarket);
    std::this_thread::sleep_for(std::chrono::seconds(1));
//    quoter->reqTick(clist, false);
    trader->reqTick(c, false);
//    trader->order(order);
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}