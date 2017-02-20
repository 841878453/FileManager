#ifndef FILEMANAGWE_H
#define FILEMANAGWE_H
#include "File.h"
#include "Dir.h"

class FileManager
{

public:
	string username;			//�û���
	FileManager();
	~FileManager();

	//Ŀ¼
	void newDir();               //�½�Ŀ¼
	void deleteDir();             //ɾ��Ŀ¼
	void openDir();              //��Ŀ¼
	void renameDir();             //������Ŀ¼
	void copyDir();               //����Ŀ¼    
	void pasteSubDir(Dir *dir1, Dir *dir2);//ճ���Ӻ���
	void pasteDir();                      //ճ��Ŀ¼
	void goback();                       //������һ��Ŀ¼
	void delete_Dir(Dir *dir);            //Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ�Ŀ¼
	void deleteFileInDir(Dir *dir);       //Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ��ļ�

	//�ļ�
	void newFile();                //�½��ļ�
	void deleteFile();             //ɾ���ļ�
	void readFile();               //���ļ�
	void writeFile();              //�༭�ļ�
	void renameFile();             //�������ļ�
	void copyFile();               //�����ļ�
	void pasteFile();              //ճ���ļ�
	void pasteFileInDir(File *file, Dir*dir);//ճ������Ŀ¼�µ��ļ�
	void showDir();                //��ʾ��ǰĿ¼������
	void display();               //��ʾ��ǰ·��
	void filerw();                 //�޸��ļ�����Ϊ�ɶ�
private:
	Dir * root;                 //��Ŀ¼
	Dir * currentDir;           //��ǰĿ¼
	File * tempfile;            //��Ÿ��Ƶ��ļ�
	Dir * tempdir;              //��Ÿ��Ƶ�Ŀ¼
};
#endif