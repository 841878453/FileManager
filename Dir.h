#ifndef DIR_H
#define DIR_H
#include "stdafx.h"
#include "File.h"

typedef struct Dir         //Ŀ¼�ṹ��
{
	string dircreatetime; //����ʱ��
	string altertime;     //�޸�ʱ��
	string dirname;               //Ŀ¼��
	int dirsize;                  //Ŀ¼��С
	Dir * nextDir;                //���Ŀ¼
	Dir * preDir;                 //ǰ��Ŀ¼
	File * fileptr;               //�ļ�����ָ��
	Dir * dirptr;                 //Ŀ¼����ָ��
	Dir();                        //���ڳ�ʼ���ĺ���
	Dir(string time, string name, int size, Dir *nextdir, Dir*predir, File *fileptrtemp, Dir *dirptrtemp);//�������ĳ�ʼ������
	~Dir();						  //��������
}Dir;
#endif