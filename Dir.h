#ifndef DIR_H
#define DIR_H
#include "stdafx.h"
#include "File.h"

typedef struct Dir         //目录结构体
{
	string dircreatetime; //创建时间
	string altertime;     //修改时间
	string dirname;               //目录名
	int dirsize;                  //目录大小
	Dir * nextDir;                //后继目录
	Dir * preDir;                 //前继目录
	File * fileptr;               //文件链表指针
	Dir * dirptr;                 //目录链表指针
	Dir();                        //用于初始化的函数
	Dir(string time, string name, int size, Dir *nextdir, Dir*predir, File *fileptrtemp, Dir *dirptrtemp);//带参数的初始化函数
	~Dir();						  //析构函数
}Dir;
#endif