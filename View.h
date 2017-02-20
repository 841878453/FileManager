#include "File.h"
#include "Dir.h"
#include "stdafx.h"
#include "FileManager.h"
class View
{
private:
	vector<FileManager*> fmv;//用于保存用户FileManager对象
public:
	View();
	~View();
	void Register();      //用户注册界面
	void Login();         //用户登录界面
	void Welcome();      //欢迎主界面
	void FunctionMenu();  //功能界面
	void Help();      //帮助文档	
};