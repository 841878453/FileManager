#ifndef FILE_H
#define FILE_H
#include "stdafx.h"


typedef struct File          //�ļ��ṹ��     
{
public:
	bool rw;					 //falseΪ�ɶ���д��trueΪֻ��
	string fcreatetime;			 //����ʱ��
	string altertime;			 //�޸�ʱ��
	string filename;			 //�ļ���
	int filesize;				 //�ļ���С
	File * nextFile;			 //ָ����һ���ļ�
	string filecontent;			 //�ļ�����
	File();						 //��ʼ������
	~File();					 //��������
}File;
#endif