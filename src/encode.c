#include<string.h>
#include<stdio.h>
char END[]="WEnD";
int j=3;
int ret=0;
void EndCheck(char *fmt,int z) //检查文件是否到特定结尾"WEnD"
{
    int count=0;      //与特定结尾匹配个数，count=4完全匹配，ret置1准备写文件
    for(int F=0;F<4;F++)
    {
        if(fmt[z-F]!=END[j-F])
        {
            ret=0;
            return;
        }
        else
        {
            count++;
        }
        if(count==4)
        {
            ret=1;
            return;
        }

    }
}
int main(int argc,char **argv)
{
   char swap[20];
   int seek;
   strcpy(swap,argv[3]);        //将argv[3]参数转为int型
   seek=atoi(swap);
    int Pos=0x2c;               //文件开始读取位置
    FILE *fp=fopen(argv[1],"rb");
    FILE *tar=fopen(argv[2],"wb+");
    fseek(fp,0,SEEK_END);
    long long int sLen=ftell(fp); //获取原文件大小

    char *src=(char *)malloc(sLen);
int i;
    for( i=0;i<sLen;i++)
    {
        fseek(fp,Pos,SEEK_SET);
        fread(src+i,1,1,fp);
       // printf("%x i=%d\n",(unsigned char)src[i],i);

       // Sleep(100);
        if(i>4)
        {
        EndCheck(src,i);
            if(ret==1)
            {
                break;
            }
        }


        Pos+=seek;
    }

    //int TLen=strlen(src);
    int TLen = i;
    for(int g=0;g<(TLen-3);g++)
    {
        fwrite(src+g,1,1,tar);
    }

    printf("%d",TLen);

    return 0;
}
