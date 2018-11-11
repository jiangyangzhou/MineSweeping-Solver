#include"mine.h"
#include<stdio.h>
mine::mine(int k, int c)
{
    char filename_q[30],filename_a[30];                    //读取第k个文件,
    memset(filename_q,0,sizeof(filename_q));
    memset(filename_a,0,sizeof(filename_a));
    switch(c)
    {
    case 1:
    {
        sprintf(filename_q,"datanew/easyinit/init%d.txt",k);
        sprintf(filename_a,"datanew/easyres/res%d.txt",k);
        row=9;col=9;break;
    }
    case 2:
    {
        sprintf(filename_q,"datanew/mediuminit/init%d.txt",k);
        sprintf(filename_a,"datanew/mediumres/res%d.txt",k);
        row=16;col=16;break;
    }
    case 3:
    {
        sprintf(filename_q,"datanew/hardinit/init%d.txt",k);
        sprintf(filename_a,"datanew/hardres/res%d.txt",k);
        row=16;col=30;break;
    }
    }

    cout<<filename_q;
    ifstream init;
    ifstream res;
    init.open(filename_q);
    res.open (filename_a);

    if(init.fail()) cout<<"fail";

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            init>>qu[i][j];
            res>>an[i][j];

            if(qu[i][j]=='-')
            {
                init>>qu[i][j];
                qu[i][j]='e';               // e为空
            }

            if(an[i][j]=='-')
            {
                res>>an[i][j];
                an[i][j]='m';               //m为雷
            }
        }
    }
    for(int i=0; i<row; i++)            //生成live数组
        strcpy(live[i],qu[i]);


    }


    int mine::numof_empty(int r,int t)            //返回live数组[r][t]边缘空的数量
    {
        int num=0;
        for(int i=-1; i<=1; i++)
        {
            for(int j=-1; j<=1; j++)
            {
                if(r+i<0||r+i>=row||t+j<0||t+j>=col)continue;
                else if(live[r+i][t+j]=='e') ++num;
            }
        }
        return num;
    }


    int mine::num_empty(int r,int t)             // 返回now数组[r][t]边缘空的数量
    {
        int num=0;
        for(int i=-1; i<=1; i++)
        {
            for(int j=-1; j<=1; j++)
            {
                if(r+i<0||r+i>=row||t+j<0||t+j>=col)continue;
                if(now[r+i][t+j]=='e') ++num;
            }
        }
        return num;
    }


    int mine::numof_mine(int r,int t)               //坐标周围雷的数量
    {
        int num=0;
        for(int i=-1; i<=1; i++)
        {
            for(int j=-1; j<=1; j++)
            {
                if(r+i<0||r+i>row||t+j<0||t+j>col) continue;
                if(live[r+i][t+j]=='m') ++num;
            }
        }
        return num;
    }

    int mine::num_mine(int r,int t)           //指定集合内雷的数目
    {
        int num=0;
        for(int i=-1; i<=1; i++)
        {
            for(int j=-1; j<=1; j++)
            {
                if(r+i<0||r+i>row||t+j<0||t+j>col) continue;
                if(now[r+i][t+j]=='m') ++num;
            }
        }
        return num;
    }



    int mine::numof_mine(int r[])           //由给定单个数的坐标，返回它四周的雷的数目
    {
        int *p;
        p=&r[0];
        int num=0;
        for(int i=0; r[i]>0; i++)
        {
            if(live[x(r[i])][y(r[i])]=='m')
                num++;
        }
        return num;
    }


    void mine::get_edge()                   //获取边缘
    {
        int k=0;
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {

                if(numof_empty(i,j)>0&&numof_empty(i,j)<9&&live[i][j]!='e'&&live[i][j]!='m')
                {
                    edge[k]=10000+i*100+j;
                    k++;
                }
            }
        }
    }


    int *mine::emp(int s)               //返回s坐标周围空的坐标，坐标都用单个数表示
    {
        int *emp;
        emp= new int[10];
        for(int i=0; i<10; i++) emp[i]=0;
        int k=0,r=0,t=0,i,j;
        r=x(s);
        t=y(s);
//cout<<"r="<<r;
        for(i=-1; i<=1; i++)
        {
            for( j=-1; j<=1; j++)
            {
                if(r+i<0||r+i>=row||t+j<0||t+j>=col) continue;
                else if(live[r+i][t+j]=='e')
                {
                    emp[k]=10000+100*(r+i)+t+j;
                    k++;
                    //  cout<<emp[k-1]<<endl;
                }
            }
        }
        return emp;
    }

    void mine::get_edgeemp()           //获得当前局势边缘（还未扫的部分）
    {
        int k=0;
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {

                if(i>0&&i<row-1&&j>0&&j<col-1&&numof_empty(i,j)+numof_mine(i,j)>0&&numof_empty(i,j)+numof_mine(i,j)<9&&now[i][j]=='e')
                {
                    e[k]=10000+i*100+j;
                    k++;
                }
                else if((((i==0||i==row-1)&&j!=0&&j!=col-1)||((j==0||j==col-1)&&i!=0&&i!=row-1))&&now[i][j]=='e')
                {
                    if(numof_empty(i,j)+numof_mine(i,j)>0&&numof_empty(i,j)+numof_mine(i,j)<6)
                    {
                        e[k]=10000+i*100+j;
                        k++;
                    }
                }
                else if((i==0||i==row-1)&&(j==0||j==col-1)&&numof_empty(i,j)+numof_mine(i,j)>0
                        &&numof_empty(i,j)+numof_mine(i,j)<4&&now[i][j]=='e')
                {
                    e[k]=10000+i*100+j;
                    k++;
                }

            }
        }
    }

int mine::jud(int k)           //辅助guess3判断,填法是否符合要求，但好像有问题
{
        int flag;
        flag=1;
        for(int i=-1; i<=1; i++)
        {
            for(int j=-1; j<=1; j++)
                if(x(e[k])+i>=0&&x(e[k])+i<row&&y(e[k])+j>=0&&y(e[k])+j<col
                        &&now[x(e[k])+i][y(e[k])+j]!='m'&&now[x(e[k])+i][y(e[k])+j]!='e')
                {
                    if(num_empty(x(e[k])+i,y(e[k])+j)==0&&now[x(e[k])+i][y(e[k])+j]-48!=num_mine(x(e[k])+i,y(e[k])+j))
                        flag=2;

                    if(now[x(e[k])+i][y(e[k])+j]-48<num_mine(x(e[k])+i,y(e[k])+j))
                    {
                        flag=0;
                        return flag;
                    }
                }
        }
        return flag;
}




