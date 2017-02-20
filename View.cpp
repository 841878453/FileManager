#include "stdafx.h"
#include "View.h"
#include "File.h"
#include "Dir.h"
#include "FileManager.h"
using namespace std;
View::View()
{

}
View::~View()
{

}

void View::Welcome()  //欢迎界面
{  
	string s;
	while (true)
	{
		system("cls");         //清屏函数
		cout << "******************************************************************" << endl;
		cout << "*                    欢迎使用文件管理系统                        *" << endl;
		cout << "*                                                                *" << endl;
		cout << "*                          1.登录                                *" << endl;
		cout << "*                          2.注册                                *" << endl;
		cout << "*                          3.帮助                                *" << endl;
		cout << "*                          4.版本                                *" << endl;
		cout << "*                                                    By Ray      *" << endl;
		cout << "******************************************************************" << endl;
		cout << "请输入操作：";
		cin >> s;
		if (s == "1")
		{
			Login();
		}
		else if (s == "2"){
			Register();
		}
		else if(s=="3"){
			system("cls");
			Help();
			system("pause");
		}
		else if (s == "4"){
			system("cls");
			cout << "version[1.0] By Ray"<<endl;
			system("pause");
		}
		else if (s == "exit"){
			exit(0);
		}
	}

}


void View::Register()//用户注册界面
{
	string username, password;
	cout << "账号：";
	cin >> username;
	if (username == "exit")
	{
		Welcome();
	}
	cout << "密码：";
	cin >> password;
	if (password == "exit")
	{
		Welcome();
	}
	ofstream out;
	out.open("user.txt", ios::app);
	out << username << " " << password << endl;
	out.close();
	cout << "注册成功!" << endl;
	system("pause");
	Welcome();
}

void View::Login()//用户登录界面
{
	string username, password;
	string readusername, readpassword;
	bool flag = false;
	time_t t = time(0);
	char tmp[64];
	cout << "账号：";
	cin >> username;
	if (username == "exit")
	{
		Welcome();
	}
	cout << "密码：";
	cin >> password;
	if (password == "exit")
	{
		Welcome();
	}

	ifstream inFile;
	while (!flag)
	{
		inFile.open("user.txt");
		while (!inFile.eof())
		{
			inFile >> readusername >> readpassword;
			if (readusername == username && readpassword == password)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			cout << "账号或密码错误，请重试。" << endl;
			cout << "账号：";
			cin >> username;
			if (username == "exit")
			{
				Welcome();
			}
			cout << "密码：";
			cin >> password;
			if (password == "exit")
			{
				Welcome();
			}
		}else{
			ofstream out;
			out.open("userLog.txt",ios::app);
			strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));//系统时间
			out << username <<" 登录时间："<< tmp << endl;
			out.close();
			out.open("userTemp.txt");
			out << username << endl;
			out.close();
		}
		inFile.close();
	}
	system("cls");
	FunctionMenu();//进入功能界面
}
void View::FunctionMenu()//功能界面
{
	FileManager fm;
	bool flag = false;//用于判断是否为新用户
	string username;
	ifstream in;
	in.open("userTemp.txt");
	in >> username;
	in.close();
	for (int i = 0; i < fmv.size(); i++){
		if (username == fmv[i]->username){
			fm = *fmv[i];
			flag = true;
			break;
		}
	}
	if (!flag){//是新用户就添加
		fm.username = username;
		fmv.push_back(&fm);
	}
	string s;
	time_t t = time(0);      //创建目录时间
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));//存入系统时间
	cout << "欢迎使用文件管理系统|" << tmp << endl;
	while (true)
	{
		fm.display();
		while (cin >> s)
		{
			if (s == "mkdir")
				fm.newDir();
			else if (s == "mk")
				fm.newFile();
			else if (s == "ls")
				fm.showDir();
			else if (s == "cd")
				fm.openDir();
			else if (s == "cls")
				system("cls");
			else if (s == "logout")
				Welcome();
			else if (s == "cd..")
				fm.goback();
			else if (s == "exit")
				exit(0);
			else  if (s == "help")
			{
				Help();
				system("pause");
				system("cls");
			}
			else if (s == "rmdir")
				fm.deleteDir();
			else if (s == "rm")
				fm.deleteFile();
			else if (s == "renamedir")
				fm.renameDir();
			else if (s == "renamefile")
				fm.renameFile();
			else if (s == "read")
				fm.readFile();
			else if (s == "vi")
				fm.writeFile();
			else if (s == "copydir")
				fm.copyDir();
			else if (s == "pastedir")
				fm.pasteDir();
			else if (s == "copyfile")
				fm.copyFile();
			else if (s == "pastefile")
				fm.pasteFile();
			else if (s == "alterfile")
				fm.filerw();
			else if (s == "mkdir?")
				cout << "创建一个目录: mkdir 目录名 (例:mkdir dirname)" << endl;
			else if (s == "mk?")
				cout << "创建一个文件: mk   文件名 (例:mk   filename)" << endl;
			else if (s == "ls?")
				cout << "显示当前路径下的目录和文件: ls " << endl;
			else if (s == "cd?")
				cout << "进入下级目录: cd 目录名 (例:cd dirname)" << endl;
			else if (s == "cls?")
				cout << "清 屏: cls " << endl;
			else if (s == "logout?")
				cout << "注 销(返回欢迎界面): logout " << endl;
			else if (s == "cd..?")
				cout << "返回上级目录: cd.. " << endl;
			else if (s == "exit?")
				cout << "退出系统: exit" << endl;
			else if (s == "help?")
				cout << "显示帮助文档: help" << endl;
			else if (s == "rmdir?")
				cout << "删除一个目录: rmdir 目录名 (例:rmdir dirname)" << endl;
			else if (s == "rm?")
				cout << "删除一个文件: rm   文件名 (例:rm   filename)" << endl;
			else if (s == "renamedir?")
				cout << "重命名目录: renamedir 旧目录名 新目录名 (例:renamedir olddirname newdirname)" << endl;
			else if (s == "renamefile?")
				cout << "重命名文件: renamefile   旧文件名 新文件名 (例:renamefile   oldfilename newfilename)" << endl;
			else if (s == "read?")
				cout << "读出文件: read 文件名 (例:read filename)" << endl;
			else if (s == "vi?")
				cout << "写入文件: vi 文件名 编辑内容 (例:vi filename content)" << endl;
			else if (s == "copydir?")
				cout << "复制目录: copydir 目录名 (例:copydir dirname)" << endl;
			else if (s == "pastedir?")
				cout << "粘贴目录: pastedir " << endl;
			else if (s == "copyfile?")
				cout << "复制文件: copyfile 文件名 (例:copyfile filename)" << endl;
			else if (s == "pastfile?")
				cout << "粘贴文件: pastfile " << endl;
			else if (s == "alterfile?")
				cout << "修改文件读写属性: alterfile 文件名  (例:alterfile filename)" << endl;
			else
			{
				cout << "找不到对应指令,请重新输入" << endl;
			}

			fm.display();

		}
	}
}

void View::Help()//帮助文档
{	
	cout << "*****************************************************************\n";
	cout << "*帮助：								*\n";
	cout << "*	目录操作:						*\n"
		<< "*		mkdir		新建目录			*\n"
		<< "*		rmdir		删除目录			*\n"
		<< "*		renamedir	重命名目录			*\n"
		<< "*		copydir		复制目录			*\n"
		<< "*		pastedir	粘贴目录			*\n"
		<< "*		ls		显示当前路径下的文件夹和文件	*\n"
		<< "*		cd		打开目录			*\n"
		<< "*		cd..		返回上一级目录			*\n"
		<< "*	文件操作:						*\n"
		<< "*		mk		新建文件			*\n"
		<< "*		rm		删除文件			*\n"
		<< "*		renamefile	重命名文件			*\n"
		<< "*		copyfile	复制文件			*\n"
		<< "*		pastefile	粘贴文件			*\n"
		<< "*		read		打开文件			*\n"
		<< "*		vi		编辑文件			*\n"
		<< "*		alertfile	修改文件属性			*\n"
		<< "*	系统指令:						*\n"
		<< "*		help		帮助				*\n"
		<< "*		cls		清屏				*\n"
		<< "*		logout		注销				*\n"
		<< "*		exit		直接退出			*\n"
	<< "*****************************************************************\n";
}

