#include <iostream>
#include<fstream>
#include<stdio.h>
#include"mine.h"
using namespace std;



int main()
{
    srand(time(NULL));
    int win_times[4]={0};
    for(int c=1; c<=3; c++)                //�ɹ�����
    {
        for(int i=0; i<100; i++)            //iΪ�򿪵ĵ�i���ļ�
        {
            mine mine1(i,c);                       //����ɨ���� mine1
            mine1.searcher1();                  //ʹ�õ�һ�ַ���ɨ��
            for(int b=0; b<=10; ++b)
            {
                //��һ�ڶ��ַ���ѭ����ɨ��
                mine1.searcher2();
                mine1.searcher1();
            }

            int ii=0;                                //ii��Ϊ�Ǻţ���һ��������ʼ��ȫ��
            do
            {
                mine1.judge();                     //�ж��Ƿ����
                if(mine1.status==-1) break;
                if(mine1.status==1) break;        //�ж��Ƿ����

                mine1.solve3();
                mine1.judge();                     //�ж��Ƿ����
                if(mine1.status==-1) break;
                if(mine1.status==1) break;                 //�����ֽ�ɨ�׷�����Ҳ�ǲ£��������⣬����ֱ�Ӳ¸��ʸߵ㣩
                for(int b=0; b<=4; ++b)
                {

                    mine1.searcher2();
                    mine1.searcher1();              //ѭ��ɨ
                }
                ii++;
                mine1.judge();                      //�ж�
                if(mine1.status==1) break;
                if(mine1.status==-1) break;
                if(ii>=8) mine1.guess();           //һ�������󣬿�ʼ�£���Ϊsolve3��ĳ����������²²��ˣ�
                for(int b=0; b<=4; ++b)
                {
                    mine1.searcher2();
                    mine1.searcher1();
                }                                    //������ѭ����һ��
            }
            while(mine1.status!=1);


          for(int i=0;i<mine1.row;i++){
                for(int j=0;j<mine1.col;j++){
                   //  cout<<mine1.qu[i][j];
                    cout<<mine1.live[i][j];
                  // cout<<mine1.an[i][j]<<" ";
                }
                cout<<endl;                           // �����ʾ

          }
            if(mine1.status==1) win_times[c]++;
        }

    }
        cout<<endl<<"�򵥼���ɹ���"<<win_times[1]<<"��";             //�ɹ�����
cout<<endl<<"�еȼ���ɹ���"<<win_times[2]<<"��";
    cout<<endl<<"���Ӽ���ɹ���"<<win_times[3]<<"��";
}










