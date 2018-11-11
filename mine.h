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

class intergerset{            //һ���й�ɨ�׼��ϵ���
private:
    int *c1;
    int *c2;                     //��������

public:

   intergerset(){
   c1=new int[101];
   c2=new int[101];
   for(int i=0;i<100;i++){c1[i]=0;c2[i]=0;}           //����
   }
    int union_judge(const int c1[],const int c2[]);    //1:c1����c2; 2:c2����c1; 0�ް�����ϵ
    int *subtract(const int c1[],const int c2[]);      //����p��p���ڼ���c1�Ҳ����ڼ���c2
     int numof_sub(const int c1[],const int c2[]);
    int x(int k){return (k-10000)/100;}
    int y(int k){return (k-10000)%100;}                        //�õ�һ���ֱ�ʾ���꣬����λ����λΪ1��ǧ��λΪ�����꣬ʮ��λΪ������
    ~intergerset(){delete[]c1;delete[]c2;}                       //x��y���������ѵ������ֵ����껹ԭ
};



class mine: public intergerset{          // ��һ��ɨ����

private:
int edge[200]={0};  //�����ı�Ե�������
int e[200]={0};      //�����ı�Ե���յĲ���
char now[100][100];   //live��ʱ����
int m[1000]={0};       //
 char an[100][100];     //����Ĵ�
   char qu[100][100];    //�������

public:
    int status=0;    //�ж�ʤ��
    char live[100][100];   //��ɨ�׵���
       int row=16;      //����
     int col=30;        //����
   // int edge[1000]={0};
   // int e[1000]={0};

mine(int k,int c);                  //kָ��k���ļ�

int numof_empty(int r,int t);        //live����[r][t]��Ե�յ�����
int num_empty(int r,int t);           //now����[r][t]��Ե�յ�����
int *emp(int s);                      //����s������Χ�յ����꣬���궼�õ�������ʾ
int numof_mine(int r,int t);           //������Χ�׵�����
int numof_mine(int r[]);               //ָ���������׵���Ŀ
int num_mine(int r,int t);             //now����������Χ�׵�����
void get_edge();                       //��õ�ǰ���Ʊ�Ե�����
void get_edgeemp();                     //��õ�ǰ���Ʊ�Ե��δ�
bool around(int r, int p, bool state);   //��searcher1Ҫ�����ף����ְ�
void searcher1();                         //�ⷨһ
void searcher2();                        //�ⷨ2
void guess3();                          //�ⷨ3֮�·�3�����Ʒ��
int jud(int k);
void judge();                         //������guess3�и����ж�
void guess();                          //�����ز�
void solve3();                        //ͳ���guess3,���ɵ����ֽⷨ
};

#endif // MINE_H_INCLUDED
