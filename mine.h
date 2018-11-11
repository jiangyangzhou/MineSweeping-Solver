#ifndef MINE_H_INCLUDED
#define MINE_H_INCLUDED

#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<stdio.h>
#include<math.h>

using namespace std;

class intergerset{            //一个有关扫雷集合的类
private:
    int *c1;
    int *c2;                     //两个集合

public:

   intergerset(){
   c1=new int[101];
   c2=new int[101];
   for(int i=0;i<100;i++){c1[i]=0;c2[i]=0;}           //构造
   }
    int union_judge(const int c1[],const int c2[]);    //1:c1包含c2; 2:c2包含c1; 0无包含关系
    int *subtract(const int c1[],const int c2[]);      //返回p，p属于集合c1且不属于集合c2
     int numof_sub(const int c1[],const int c2[]);
    int x(int k){return (k-10000)/100;}
    int y(int k){return (k-10000)%100;}                        //用单一数字表示坐标，已填位置万位为1，千百位为横坐标，十个位为纵坐标
    ~intergerset(){delete[]c1;delete[]c2;}                       //x和y两个函数把单个数字的坐标还原
};



class mine: public intergerset{          // 又一个扫雷类

private:
int edge[200]={0};  //雷区的边缘，已填部分
int e[200]={0};      //雷区的边缘，空的部分
char now[100][100];   //live临时数组
int m[1000]={0};       //
 char an[100][100];     //读入的答案
   char qu[100][100];    //读入的题

public:
    int status=0;    //判断胜负
    char live[100][100];   //解扫雷的盘
       int row=16;      //行数
     int col=30;        //列数
   // int edge[1000]={0};
   // int e[1000]={0};

mine(int k,int c);                  //k指第k个文件

int numof_empty(int r,int t);        //live数组[r][t]边缘空的数量
int num_empty(int r,int t);           //now数组[r][t]边缘空的数量
int *emp(int s);                      //返回s坐标周围空的坐标，坐标都用单个数表示
int numof_mine(int r,int t);           //坐标周围雷的数量
int numof_mine(int r[]);               //指定集合内雷的数目
int num_mine(int r,int t);             //now数组坐标周围雷的数量
void get_edge();                       //获得当前局势边缘（已填）
void get_edgeemp();                     //获得当前局势边缘（未填）
bool around(int r, int p, bool state);   //依searcher1要求填雷，数字啊
void searcher1();                         //解法一
void searcher2();                        //解法2
void guess3();                          //解法3之猜法3（半成品）
int jud(int k);
void judge();                         //用于在guess3中辅助判断
void guess();                          //单纯地猜
void solve3();                        //统筹固guess3,构成第三种解法
};

#endif // MINE_H_INCLUDED
