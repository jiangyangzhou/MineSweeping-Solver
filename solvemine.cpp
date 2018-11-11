#include "mine.h"


bool mine::around(int r,int t,bool state)                //��searcher1Ҫ���ڸ��������������׻����֣�����˷���true�����˷���false
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


void mine::searcher1()                         //��򵥸�Ч�ⷨ��
{
    for(int x=0; x<=30; x++)
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(live[i][j]==48&&numof_empty(i,j)!=0) around(i,j,true);     //�������괦Ϊ0�����ܶ������ֺ���
                if(live[i][j]>48&&live[i][j]<56)                              //���괦Ϊ1��8ʱ
                {
                    if(live[i][j]-48==numof_mine(i,j)+numof_empty(i,j))          //���������ֵ�������Χ�յĵط��������ף���������
                    {
                        mine::around(i,j,false);
                    }
                    if(live[i][j]-48==numof_mine(i,j))                      //���������ֵ�������Χ�����ף�����������
                    {
                        if(!around(i,j,true))
                        {
                            cout<<"game over"; status=-1;   //�ж��Ƿ����
                        }
                    }
                }
            }
        }
    }
}

void mine::searcher2()     //�ڶ��ֽⷨ
{

    get_edge();         //��ȡ��Ե

    for(int i=0; edge[i]!=0; i++)
    {
        for(int j=0; edge[j]!=0; j++)
        {

            if(union_judge(emp(edge[i]),emp(edge[j]))==1||union_judge(emp(edge[i]),emp(edge[j]))==0)  //�ж�����������Χ�����������ǽ����ϵ
            {                                                                                         //��i���ϰ���j

              if(live[x(edge[i])][y(edge[i])]>=48&&live[x(edge[i])][y(edge[i])]<56&&
                 live[x(edge[j])][y(edge[j])]>=48&&live[x(edge[j])][y(edge[j])]<56){
            if(numof_sub(emp(edge[i]),emp(edge[j]))==
            (live[x(edge[i])][y(edge[i])]-numof_mine(x(edge[i]),y(edge[i])))-(live[x(edge[j])][y(edge[j])]-numof_mine(x(edge[j]),y(edge[j]))))
                {

                    int k=0,arr[8]= {0};                                         //ru����������֮��ΪӦ�е���֮��
                    while(subtract(emp(edge[i]),emp(edge[j]))[k]!=0)
                    {
                        arr[k]=subtract(emp(edge[i]),emp(edge[j]))[k];
                        k++;                                                 //��arr���ϴ�����������������õ�����i���ϣ�������j���ϵ�
                    }
                    for(int a=0; arr[a]!=0; a++)
                        live[x(arr[a])][y(arr[a])]='m';      //����i���ϣ�������j���ϵĵط����װ�

                }

               if(live[x(edge[i])][y(edge[i])]-numof_mine(x(edge[i]),y(edge[i]))==live[x(edge[j])][y(edge[j])]-numof_mine(x(edge[j]),y(edge[j]))
                  &&union_judge(emp(edge[i]),emp(edge[j]))==1)
                {
                    int k=0,arr[8]= {0},w[8]= {0},rt[8]= {0};                            //��������Ӧ�е������
                    while(subtract(emp(edge[i]),emp(edge[j]))[k]!=0)
                    {
                        arr[k]=subtract(emp(edge[i]),emp(edge[j]))[k];
                        w[k]=emp(edge[i])[k];
                        rt[k]=emp(edge[j])[k];
                        k++;
                    }


                    for(int a=0; arr[a]!=0; a++)
                    {
                        live[x(arr[a])][y(arr[a])]=an[x(arr[a])][y(arr[a])];            //ͬ�������
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
if(status==-1)cout<<"ʧ��"<<endl;
else {
        flag=true;
for(int i=0;i<row;i++)
for(int j=0;j<col;j++){
    if(live[i][j]=='e'){ flag=false; break;}
}
if (flag==true)  {status=1;cout<<"�ɹ�"<<endl;
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
else if((k%(2*g))/g==0) now[x(e[t])][y(e[t])]='e';     //,k�Ķ����Ƶ�tλ����1 ,���ף�
if(jud(t)==0){ flag=false;break;}              //����š�e��
   }
 for(t=0;t<=14&&e[t]!=0;t++){
   if(jud(t)==2){ flag=false;break;}
 }
if(flag==true){
    for(i=0;i<15&&e[i]!=0;i++){
  if(now[x(e[i])][y(e[i])]=='m') m[i]++;         //�ж�
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
     live[x(e[num])][y(e[num])]=an[x(e[num])][y(e[num])];   //���״������ٵĵط�������
     if(live[x(e[num])][y(e[num])]=='m')
        { cout<<"game over"<<x(e[num])<<y(e[num])<<" ";status=-1;}
     for(int j=0;e[j]!=0;j++){
        e[j]=0;
        m[j]=0;
     }
}










