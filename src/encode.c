#include<string.h>
#include<stdio.h>




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

  unsigned char *src=(unsigned char *)malloc(sLen);
    long long int size;
    char buf[8];
    for(int i=0;i<8;i++)
    {
        fseek(fp,Pos,SEEK_SET);
        fread(&buf[i],1,1,fp);
        Pos+=seek;
    }
    memcpy(&size,&buf,8);
    int i;
    for( i=0;i<size;i++)
    {
        fseek(fp,Pos,SEEK_SET);
        fread(src+i,1,1,fp);



        Pos+=seek;
    }


    int TLen = i;
    for(int g=0;g<(TLen-3);g++)
    {
        fwrite(src+g,1,1,tar);
    }

    printf("%d",TLen);

    return 0;
}
