#include"mine.h"


 int intergerset::union_judge(const int c1[],const int c2[]){      //有关两个集合关系判断的函数
     bool l1=false,l2=false;                                       //返回值为： 1:c1包含c2; 2:c2包含c1; 0：无包含关系；  3:c1==c2
   int flag=0,i,j;

 for( i=0;c1[i]!=0;i++)
 {
     l1=false;
   for(j=0;c2[j]!=0;j++){
   if(c1[i]==c2[j]) { l1=true;}
   }
   if(l1==false)break;
 }

 for( j=0;c2[j]!=0;j++)
 {
   l2=false;
   for(i=0;c1[i]!=0;i++){
   if(c2[j]==c1[i]) {l2=true;}
   }
   if(l2==false)break;
 }
 if(l1&&!l2) return 2;
 if(!l1&&l2) return 1;
 if(!l1&&!l2) return 0;
 if(l1&&l2)  return 3;
 }                                                   //1:c1包含c2; 2:c2包含c1; 0无包含关系；3:c1==c2



int *intergerset::subtract(const int c1[],const int c2[]){         //返回p属于集合c1且不属于集合c2
    bool flag;
    int k=0,j=0,i=0;
    int *p;
    p=new int[8];
    for(i=0;i<=7;i++)
    p[i]=0;

    for( i=0;c1[i]!=0;i++){
            flag=false;
        for(j=0;c2[j]!=0;j++){
        if(c1[i]==c2[j]) {flag=true;break;}
        }
    if(!flag) {p[k]=c1[i]; k++;}
        }

    return p;
}

int intergerset::numof_sub(const int c1[],const int c2[])
{
    int i;

    for( i=0;subtract(c1,c2)[i]!=0;i++){};                      //返回上个函数得到集合的元素数量

    return i;
}



