#include "File.h"
#include "Dir.h"
#include "stdafx.h"
#include "FileManager.h"
class View
{
private:
	vector<FileManager*> fmv;//���ڱ����û�FileManager����
public:
	View();
	~View();
	void Register();      //�û�ע�����
	void Login();         //�û���¼����
	void Welcome();      //��ӭ������
	void FunctionMenu();  //���ܽ���
	void Help();      //�����ĵ�	
};