#include<pthread.h>
#include<stdio.h>
#include<windows.h>
#define _CRT_SECURE_NO_WARNINGS

char magic[4] = { 0x57,0x41,0x56,0x45 };
char H[2] = {'.'};
void *ProgressBar()
{

}
int FormatCheck(FILE *fp, char **argv)
{
	char name[20];
	int namelen = strlen(name);
	strcpy(name, argv[1]);
	char magic2[4] = "wav";
	int j = 0;
	while (1)
	{
		if (name[j] != '.')
		{
			j++;
		}
		else
		{
			break;
		}
		if (j == namelen&&name[j] != H[0])
		{
			printf("�޺�׺��");
			return -1;
		}
	}
	for (int i = 0; i<3; i++)
	{
		if (name[j + 1] == magic[i] || name[j + 1] == magic2[i])
		{
			j++;

		}
		else {
			printf("����ĺ�׺��");
			return -1;
		}
	}

	fseek(fp, 0, SEEK_END);
	long long int len = ftell(fp);
	char *buf = NULL;
	buf = (char *)malloc(4);
	fseek(fp, 0, SEEK_SET);
	if (buf == NULL)
	{
		return -1;
	}

	fseek(fp, 8, SEEK_SET);
	for (int i = 0; i<4; i++)
	{
		fread(buf + i, 1, 1, fp);
		if (buf[i] != magic[i])
		{
			printf("File format isn't match");
			return -1;
		}
	}

	fclose(fp);
	free(buf);
}
int main(int argc, char **argv)
{

   // pthread_t thread;
    //void *ch =NULL;
    if(argc!=4) //���������Ƿ�����
    {
        printf("Usage: %s [FILE1] [FILE2] [SEEK]",argv[0]);
        return -1;
    }
char _swap[sizeof(argv[3])];
int _Pseek;
strcpy(_swap,argv[3]);        //��argv[3]����תΪint��
_Pseek=atoi(_swap);

FILE *fp = fopen(argv[1], "rb"); //�Զ����Ʒ�ʽ���ļ���ֻ�����ļ�ͷ��ʽ��飩
	if (fp == NULL)
	{
		printf("Read File error");
        return -1;
	}
FormatCheck(fp, argv);
FILE *tar = fopen(argv[1], "rb+");
FILE *src = fopen(argv[2], "rb"); //����Ҫ���ص��ļ�
    if(tar==NULL||src==NULL)
    {
    	printf("Read File error");
    	return -1;
    }
int SEEK_DATA = 0x2c;//data����ʼλ��
fseek(src, 0, SEEK_END);
unsigned long long int SLen = ftell(src);  //SLen:Դ�ļ���С
fseek(src, 0, SEEK_SET);

char buf[8];
memcpy(&buf,&SLen,8);

fseek(tar,0,SEEK_END);
long long int TLen = ftell(tar);
fseek(tar, 0, SEEK_SET);
unsigned long long int Total=SEEK_DATA+_Pseek*SLen;
    if(Total+4>TLen)
    {
     printf("The file is too big");
    return -1;
    }
    printf("The size of file is %d          The end of file is %d\n",SLen,Total);
char *Bsrc = (char *)malloc(SLen);

	for (int i = 0; i<SLen; i++)
	{
		fread(Bsrc + i, 1, 1, src); //������Ҫ��д���ļ�
	}


	for(int i=0;i<8;i++)//д��Դ�ļ��Ĵ�С
    {
        fseek(tar, SEEK_DATA, SEEK_SET);
        fwrite(&buf[i],1,1,tar);
        SEEK_DATA+=_Pseek;

    }
	for (int i = 0; i<SLen; i++)//����SEEKƫ����д���ļ�
	{
		fseek(tar, SEEK_DATA, SEEK_SET);
		fwrite(Bsrc + i, 1, 1, tar);
		SEEK_DATA+=_Pseek;
	}
	/*for (int i = 0; i<4; i++)//д�������־
	{
		fseek(tar, SEEK_DATA, SEEK_SET);
		fwrite(&END[i], 1, 1, tar);
		SEEK_DATA += _Pseek;
	}*/
    printf("The task is finished\n");
	system("pause");
	return 0;
}
