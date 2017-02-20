#ifndef FILE_H
#define FILE_H
#include "stdafx.h"


typedef struct File          //文件结构体     
{
public:
	bool rw;					 //false为可读可写，true为只读
	string fcreatetime;			 //创建时间
	string altertime;			 //修改时间
	string filename;			 //文件名
	int filesize;				 //文件大小
	File * nextFile;			 //指向下一个文件
	string filecontent;			 //文件内容
	File();						 //初始化函数
	~File();					 //析构函数
}File;
#endif