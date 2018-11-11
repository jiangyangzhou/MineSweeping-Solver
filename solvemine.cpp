#include "mine.h"


bool mine::around(int r,int t,bool state)                //依searcher1要求在给定坐标四周填雷或数字，填对了返回true，错了返回false
{

    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            if(r+i>=0&&r+i<row&&t+j>=0&&t+j<col)
            {
                if(state&&live[r+i][t+j]=='e')
                {
                    live[r+i][t+j]=an[r+i][t+j];
                    if (live[r+i][t+j]=='m'&&an[r+i][t+j]!='m') return false;
                }
                else if(!state&&live[r+i][t+j]=='e')
                {
                    live[r+i][t+j]='m';
                }
            }
        }
    }
    return true;
}


void mine::searcher1()                         //最简单高效解法，
{
    for(int x=0; x<=30; x++)
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(live[i][j]==48&&numof_empty(i,j)!=0) around(i,j,true);     //假如坐标处为0，四周都填数字好了
                if(live[i][j]>48&&live[i][j]<56)                              //坐标处为1到8时
                {
                    if(live[i][j]-48==numof_mine(i,j)+numof_empty(i,j))          //若坐标数字等于它周围空的地方和已有雷，四周填雷
                    {
                        mine::around(i,j,false);
                    }
                    if(live[i][j]-48==numof_mine(i,j))                      //若坐标数字等于它周围已有雷，四周填数字
                    {
                        if(!around(i,j,true))
                        {
                            cout<<"game over"; status=-1;   //判断是否踩雷
                        }
                    }
                }
            }
        }
    }
}

void mine::searcher2()     //第二种解法
{

    get_edge();         //获取边缘

    for(int i=0; edge[i]!=0; i++)
    {
        for(int j=0; edge[j]!=0; j++)
        {

            if(union_judge(emp(edge[i]),emp(edge[j]))==1||union_judge(emp(edge[i]),emp(edge[j]))==0)  //判断两个坐标周围，两个集合是交叉关系
            {                                                                                         //或i集合包含j

              if(live[x(edge[i])][y(edge[i])]>=48&&live[x(edge[i])][y(edge[i])]<56&&
                 live[x(edge[j])][y(edge[j])]>=48&&live[x(edge[j])][y(edge[j])]<56){
            if(numof_sub(emp(edge[i]),emp(edge[j]))==
            (live[x(edge[i])][y(edge[i])]-numof_mine(x(edge[i]),y(edge[i])))-(live[x(edge[j])][y(edge[j])]-numof_mine(x(edge[j]),y(edge[j]))))
                {

                    int k=0,arr[8]= {0};                                         //ru若两个集合之差为应有的雷之差
                    while(subtract(emp(edge[i]),emp(edge[j]))[k]!=0)
                    {
                        arr[k]=subtract(emp(edge[i]),emp(edge[j]))[k];
                        k++;                                                 //用arr集合代替两集合相减，即得到属于i集合，不属于j集合的
                    }
                    for(int a=0; arr[a]!=0; a++)
                        live[x(arr[a])][y(arr[a])]='m';      //属于i集合，不属于j集合的地方放雷啊

                }

               if(live[x(edge[i])][y(edge[i])]-numof_mine(x(edge[i]),y(edge[i]))==live[x(edge[j])][y(edge[j])]-numof_mine(x(edge[j]),y(edge[j]))
                  &&union_judge(emp(edge[i]),emp(edge[j]))==1)
                {
                    int k=0,arr[8]= {0},w[8]= {0},rt[8]= {0};                            //两个集合应有的雷相等
                    while(subtract(emp(edge[i]),emp(edge[j]))[k]!=0)
                    {
                        arr[k]=subtract(emp(edge[i]),emp(edge[j]))[k];
                        w[k]=emp(edge[i])[k];
                        rt[k]=emp(edge[j])[k];
                        k++;
                    }


                    for(int a=0; arr[a]!=0; a++)
                    {
                        live[x(arr[a])][y(arr[a])]=an[x(arr[a])][y(arr[a])];            //同理放数字
                        if(live[x(arr[a])][y(arr[a])]=='m')     {cout<<" game over"; status=-1;}
                    }
                }
                delete [] subtract(emp(edge[i]),emp(edge[j]));

            }
            }


            delete [] emp(edge[i]);
            delete [] emp(edge[j]);
         }

    }
}


void mine::guess(){
   get_edgeemp();
  int t,k,i=0,j=0;
  for(t=0;e[t]!=0;t++) {};
if(t!=0){
    k=rand()%t;
    live[x(e[k])][y(e[k])]=an[x(e[k])][y(e[k])];
    if(live[x(e[k])][y(e[k])]=='m') {cout<<"game over";status=-1;}
}
else{
while(live[i][j]!='e'){
    i=rand()%row;
    j=rand()%col;
}
    live[i][j]=an[i][j];
    if(live[i][j]=='m') {cout<<"game over";status=-1;}
}
}

void mine::judge(){
   bool flag=false;
if(status==-1)cout<<"失败"<<endl;
else {
        flag=true;
for(int i=0;i<row;i++)
for(int j=0;j<col;j++){
    if(live[i][j]=='e'){ flag=false; break;}
}
if (flag==true)  {status=1;cout<<"成功"<<endl;
}
}
}

void mine::guess3(){
    bool flag;
   long long int k=0;
   int i=0,t=0;

for(k=0;k<pow(2,15);k++){
  flag=true;
   for(t=0;t<=14&&e[t]!=0;t++){
       long  int g=pow(2,t);
if((k%(2*g))/g==1) now[x(e[t])][y(e[t])]='m';
else if((k%(2*g))/g==0) now[x(e[t])][y(e[t])]='e';     //,k的二进制第t位若是1 ,放雷；
if(jud(t)==0){ flag=false;break;}              //否则放‘e’
   }
 for(t=0;t<=14&&e[t]!=0;t++){
   if(jud(t)==2){ flag=false;break;}
 }
if(flag==true){
    for(i=0;i<15&&e[i]!=0;i++){
  if(now[x(e[i])][y(e[i])]=='m') m[i]++;         //判断
}
}
for(int z=0;e[z]!=0;z++)  now[x(e[t])][y(e[t])]='e';
}
}


void mine::solve3(){
     for(int i=0; i<row; i++)
        strcpy(now[i],live[i]);
        get_edgeemp();
  guess3();
int i=0,minone=m[0],num=0;
for(i=0;e[i]!=0;i++){
        if(m[i]<minone){
        minone=m[i];
        num=i;
     }
}
     live[x(e[num])][y(e[num])]=an[x(e[num])][y(e[num])];   //放雷次数最少的地方填数字
     if(live[x(e[num])][y(e[num])]=='m')
        { cout<<"game over"<<x(e[num])<<y(e[num])<<" ";status=-1;}
     for(int j=0;e[j]!=0;j++){
        e[j]=0;
        m[j]=0;
     }
}










