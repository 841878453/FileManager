#ifndef FILEMANAGWE_H
#define FILEMANAGWE_H
#include "File.h"
#include "Dir.h"

class FileManager
{

public:
	string username;			//用户名
	FileManager();
	~FileManager();

	//目录
	void newDir();               //新建目录
	void deleteDir();             //删除目录
	void openDir();              //打开目录
	void renameDir();             //重命名目录
	void copyDir();               //复制目录    
	void pasteSubDir(Dir *dir1, Dir *dir2);//粘贴子函数
	void pasteDir();                      //粘贴目录
	void goback();                       //返回上一级目录
	void delete_Dir(Dir *dir);            //目录删除子函数，删除要删除目录下的目录
	void deleteFileInDir(Dir *dir);       //目录删除子函数，删除要删除目录下的文件

	//文件
	void newFile();                //新建文件
	void deleteFile();             //删除文件
	void readFile();               //打开文件
	void writeFile();              //编辑文件
	void renameFile();             //重命名文件
	void copyFile();               //复制文件
	void pasteFile();              //粘贴文件
	void pasteFileInDir(File *file, Dir*dir);//粘贴复制目录下的文件
	void showDir();                //显示当前目录的内容
	void display();               //显示当前路径
	void filerw();                 //修改文件属性为可读
private:
	Dir * root;                 //根目录
	Dir * currentDir;           //当前目录
	File * tempfile;            //存放复制的文件
	Dir * tempdir;              //存放复制的目录
};
#endif