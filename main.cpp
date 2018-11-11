#include <iostream>
#include<fstream>
#include<stdio.h>
#include"mine.h"
using namespace std;



int main()
{
    srand(time(NULL));
    int win_times[4]={0};
    for(int c=1; c<=3; c++)                //成功次数
    {
        for(int i=0; i<100; i++)            //i为打开的第i个文件
        {
            mine mine1(i,c);                       //定义扫雷类 mine1
            mine1.searcher1();                  //使用第一种方法扫雷
            for(int b=0; b<=10; ++b)
            {
                //第一第二种方法循环解扫雷
                mine1.searcher2();
                mine1.searcher1();
            }

            int ii=0;                                //ii作为记号，在一定次数后开始完全猜
            do
            {
                mine1.judge();                     //判断是否完成
                if(mine1.status==-1) break;
                if(mine1.status==1) break;        //判断是否完成

                mine1.solve3();
                mine1.judge();                     //判断是否完成
                if(mine1.status==-1) break;
                if(mine1.status==1) break;                 //第三种解扫雷方法，也是猜，（有问题，但比直接猜概率高点）
                for(int b=0; b<=4; ++b)
                {

                    mine1.searcher2();
                    mine1.searcher1();              //循环扫
                }
                ii++;
                mine1.judge();                      //判断
                if(mine1.status==1) break;
                if(mine1.status==-1) break;
                if(ii>=8) mine1.guess();           //一定次数后，开始猜（因为solve3在某种特殊情况下猜不了）
                for(int b=0; b<=4; ++b)
                {
                    mine1.searcher2();
                    mine1.searcher1();
                }                                    //猜完再循环解一次
            }
            while(mine1.status!=1);


          for(int i=0;i<mine1.row;i++){
                for(int j=0;j<mine1.col;j++){
                   //  cout<<mine1.qu[i][j];
                    cout<<mine1.live[i][j];
                  // cout<<mine1.an[i][j]<<" ";
                }
                cout<<endl;                           // 结果显示

          }
            if(mine1.status==1) win_times[c]++;
        }

    }
        cout<<endl<<"简单级别成功了"<<win_times[1]<<"次";             //成功计数
cout<<endl<<"中等级别成功了"<<win_times[2]<<"次";
    cout<<endl<<"复杂级别成功了"<<win_times[3]<<"次";
}










