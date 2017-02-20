#include"FileManager.h"
#include "File.h"
#include "Dir.h"
#include"View.h"

FileManager::FileManager()     //初始化函数
{
	root = new Dir();
	root->dirname = "root";//默认用户根文件夹为root
	currentDir = root;//设置当前目录为根目录
	tempfile = NULL;//临时文件为空
	tempdir = NULL;//临时目录为空
}

FileManager::~FileManager()  //释放内存，防止内存泄漏
{
	delete currentDir;
	delete root;
	delete tempfile;
	delete tempdir;
}

void FileManager::newDir()//新建目录
{
	time_t t = time(0);//创建目录时间
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));//存入系统时间

	Dir *p = new Dir();      //指针指向新建目录
	cin >> p->dirname;       //输入新建目录名
	if (currentDir != NULL)//如果该目录链表指针不为空
	{
		if (currentDir->dirptr == NULL)//该目录下没有文件夹链表指针
		{
			currentDir->dirptr = p;
			p->preDir = currentDir;

			p->dircreatetime = tmp;
			p->altertime = tmp;
		}
		else//该目录下目录链表指针不为空
		{
			Dir *q;//该指针用于遍历
			q = currentDir->dirptr;
			while (q->nextDir != NULL)//遍历一遍，排除文件夹重名
			{
				if (!strcmp(p->dirname.c_str(), q->dirname.c_str()))//文件夹同名
				{
					cout << "同级目录不能重名！" << endl;
					return;
				}

				q = q->nextDir;
			}
			if (!strcmp(p->dirname.c_str(), q->dirname.c_str()))//比较最后一个文件名
			{
				cout << "同级目录不能重名！" << endl;
				return;
			}
			q->nextDir = p;
			p->preDir = currentDir;
			p->dircreatetime = tmp;
			p->altertime = tmp;
		}
		cout << "目录创建成功！" << endl;
	}
	else
	{
		cout << "不能在空目录下创建目录!" << endl;
	}
}
void FileManager::newFile()//新建文件
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	File *p = new File();
	cin >> p->filename;
	if (currentDir != NULL)
	{
		if (currentDir->fileptr == NULL)//该目录下没有文件链表指针
		{
			currentDir->fileptr = p;
			p->fcreatetime = tmp;
			p->altertime = tmp;

		}
		else//该目录下存在文件链表指针
		{
			File *q;
			q = currentDir->fileptr;
			while (q->nextFile != NULL)//检查有无同名文件
			{
				if (!strcmp(p->filename.c_str(), q->filename.c_str()))//同名
				{
					cout << "该文件已存在,请勿重复创建!" << endl;
					return;
				}
				q = q->nextFile;//指针指向下一个文件

			}
			if (!strcmp(p->filename.c_str(), q->filename.c_str()))//同名
			{
				cout << "该文件已存在,请勿重复创建!" << endl;
				return;
			}
			q->nextFile = p;
			p->fcreatetime = tmp;
			p->altertime = tmp;
		}
		cout << "文件创建成功！" << endl;
	}
	else
	{
		cout << "不能在空目录下创建文件!" << endl;
	}
}
void FileManager::showDir() //显示当前目录的内容
{
	int dirsize1 = 0, dirsize2 = 0;
	Dir *d;
	d = currentDir->dirptr;//d表示当前目录下的目录 
	File *f;
	f = currentDir->fileptr;//f表示当前目录下的文件 
	char buf[10];
	string str;
	if (d == NULL && f == NULL) {
		cout << "当前目录下无任何目录和文件" << endl;
	}
	Dir *d1;
	File *d2;

	//遍历当前目录
	cout << "*********************************** 当前目录信息 ***********************************" << endl << endl;

	cout << " 目录名称      " << "    数量             " << "     创建时间" << "               修改时间" << endl << endl;
	while (d != NULL) {

		d1 = d->dirptr;
		d2 = d->fileptr;

		while (d1 != NULL)
		{
			dirsize1++;//目录的个数
			d1 = d1->nextDir;
		}
		while (d2 != NULL)
		{
			dirsize2++;//文件的个数
			d2 = d2->nextFile;
		}
		d->dirsize = (dirsize1 + dirsize2);//该目录下文件和目录的个数
		itoa(d->dirsize, buf, 10);//将int转化为char*
		str = buf;

		cout << "    " << d->dirname << string(16 - (d->dirname.length()), ' ') << d->dirsize << string(16 - str.length(), ' ') << d->dircreatetime << "    " << d->altertime << endl;
		d = d->nextDir;
		dirsize1 = 0;
		dirsize2 = 0;
	}

	cout << endl << " 文件名称        " << "大 小            " << "创建时间" << "            修改时间" << "          文件属性" << endl << endl;

	//遍历当前文件指针
	while (f != NULL)
	{
		itoa(f->filesize, buf, 10);
		str = buf;
		if (f->rw)//判断读写情况                                                                                                                                                                                                                                                                                                                                                      
			cout << "    " << f->filename << string(14 - (f->filename.length()), ' ') << f->filesize << string(10 - str.length(), ' ') << f->fcreatetime << "    " << f->altertime << "   可读" << endl;
		else
			cout << "    " << f->filename << string(14 - (f->filename.length()), ' ') << f->filesize << string(10 - str.length(), ' ') << f->fcreatetime << "    " << f->altertime << "   可读可写" << endl;
		f = f->nextFile;
	}
}

void FileManager::openDir()//打开目录
{
	Dir *d = new Dir();
	cin >> d->dirname;
	bool flag = false;

	if (currentDir == NULL)
	{
		cout << "当前路径为空，无法进入!" << endl;
	}
	else
	{
		if (currentDir->dirptr == NULL)//当前目录下没有目录
		{
			cout << "请先创建一个目录!" << endl;
		}
		else
		{
			Dir *q;
			q = currentDir->dirptr;
			while (q != NULL)
			{
				if (!strcmp(d->dirname.c_str(), q->dirname.c_str()))//找到要进入的目录
				{
					currentDir = q;
					flag = true;
					break;
				}
				q = q->nextDir;

			}
			if (!flag)
			{
				cout << "该目录不存在" << endl;
			}
		}

	}
}

void FileManager::goback()//返回上一级目录
{
	if (currentDir != NULL)//当前目录不为空
	{
		if (currentDir == root)//如果为根目录，则无法返回
		{
			cout << "当前目录为根目录，无法返回!" << endl;
			return;
		}
		else
		{
			currentDir = currentDir->preDir;//修改当前目录为前继目录
		}
	}
	else
	{
		cout << "无前继目录可以返回!" << endl;
		return;
	}
}

void  FileManager::display()//显示当前路径
{
	vector<Dir*> v;
	ifstream in;
	in.open("userTemp.txt");
	string username;
	in >> username;
	Dir *p;
	p = root;
	if (p == currentDir)//根目录情况
	{
		cout << "用户：" << username << ">" << p->dirname << ":\\>";
	}
	else
	{
		cout << "用户：" << username << ">";
		Dir *q;
		q = currentDir;
		while (q != NULL)
		{
			v.push_back(q);
			q = q->preDir;
		}
		cout << v[v.size() - 1]->dirname << ":\\";//倒序输出
		for (int i = 1; i<v.size()-1; i++)
		{
			cout << v[v.size() - 1 - i]->dirname << "\\";
		}
		cout << v[0]->dirname << "\\>";

	}
	v.clear();
	in.close();
}

void FileManager::delete_Dir(Dir *dir) //递归删除所有目录
{
	if (dir->dirptr != NULL)//目录不为空
	{
		delete_Dir(dir->dirptr);//把该目录删除掉
	}
	if (dir->nextDir != NULL)//下一目录不为空
	{
		delete_Dir(dir->nextDir);//把该目录的下一目录也删除掉
	}
	delete dir; 
}

void FileManager::deleteFileInDir(Dir *dir) //删除目录中的文件
{
	if (dir->fileptr != NULL)
	{
		dir->fileptr = NULL;
	}
}

void FileManager::deleteDir()//删除目录
{
	Dir *p = new Dir();
	cin >> p->dirname;
	bool flag = false;
	if (currentDir->dirptr == NULL)
	{
		cout << "当前路径下不存在目录!" << endl;
		return;
	}
	else
	{
		Dir *q;
		q = currentDir->dirptr;
		if (q->nextDir == NULL)
		{
			if (q->dirname == p->dirname)//如果当前遍历的目录名==需要删除的目录名
			{
				if (q->dirptr == NULL)//如果目录里面没有子目录
				{
					deleteFileInDir(q);//删除文件
					currentDir->dirptr = NULL;
				}
				else//如果目录里面有子目录
				{
					deleteFileInDir(q);//删除文件
					delete_Dir(q->dirptr);//删除子目录
					q->dirptr = NULL;
					currentDir->dirptr = NULL;
				}
				flag=true;
			}
		}
		else//下一目录不为空。
		{
			if (q->dirname == p->dirname)//如果当前遍历的目录名==需要删除的目录名
			{
				flag=true;
				if (q->dirptr == NULL)
				{
					deleteFileInDir(q);
					currentDir->dirptr = q->nextDir;
				}
				else
				{
					deleteFileInDir(q);
					delete_Dir(q->dirptr);
					q->dirptr = NULL;
					//delete q->dirptr;
					currentDir->dirptr = q->nextDir;
				}
			}
			else//如果当前遍历的目录名==需要删除的目录名
			{
				while (q->nextDir != NULL)//遍历
				{
					if (q->nextDir->dirname == p->dirname)
					{
						if (q->nextDir->dirptr == NULL)
						{
							deleteFileInDir(q->nextDir);
							q->nextDir = q->nextDir->nextDir;
						}
						else
						{
							deleteFileInDir(q->nextDir);
							delete_Dir(q->nextDir->dirptr);
							q->nextDir->dirptr = NULL;
							q->nextDir = q->nextDir->nextDir;
						}
						flag=true;//判断删除是否成功
						break;
					}
					q = q->nextDir;
				}
			}
		}
		if (flag)
		{
			cout << "目录删除成功！" << endl;
		}
		else
		{
			cout << "不存在指定要删除的目录!" << endl;
		}
	}

}

void FileManager::deleteFile() //删除文件
{
	File *p = new File();
	cin >> p->filename;
	bool flag = false;
	if (currentDir->fileptr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *q;
		q = currentDir->fileptr;
		if (q->nextFile == NULL)//下一文件为空
		{
			if (q->filename == p->filename)//判断是否为需要删除的文件
			{
				currentDir->fileptr = NULL;
				flag = true;
			}
		}
		else
		{
			if (q->filename == p->filename)
			{
				currentDir->fileptr = q->nextFile;
				flag = true;
			}
			else
			{
				while (q->nextFile != NULL)
				{
					if (q->nextFile->filename == p->filename)
					{
						q->nextFile = q->nextFile->nextFile;
						flag = true;
						break;
					}
					q = q->nextFile;
				}
			}
		}
		if (flag)
			cout << "文件删除成功！" << endl;
		else
			cout << "不存在指定要删除的文件!" << endl;

	}
}

void FileManager::renameDir()//目录重命名
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	//renamedir 原来的名字 新的名字
	Dir *p = new Dir();//旧名字
	cin >> p->dirname;
	Dir *q = new Dir();
	cin >> q->dirname;//新名字
	int flag = 0, flag1 = 0;
	if (currentDir->dirptr == NULL)
		cout << "当前路径下不存在目录!" << endl;
	else
	{
		Dir *ptr;
		ptr = currentDir->dirptr;
		Dir *ptr1;
		ptr1 = currentDir->dirptr;
		while (ptr != NULL)
		{
			if (ptr->dirname == p->dirname)//当前路径下存在要重命名的目录
			{
				flag++;
				while (ptr1 != NULL)
				{
					if (ptr1->dirname == q->dirname)//重命名后的目录名字与原来存在的目录相同
					{
						flag1++;
						break;
					}
					ptr1 = ptr1->nextDir;
				}
				if (!flag1)
				{
					ptr->dirname = q->dirname;
					ptr->altertime = tmp;
				}
				break;
			}

			ptr = ptr->nextDir;
		}

		if (!flag)
			cout << "不存在指定要重命名的目录!" << endl;
		if (flag)
		{
			if (flag1)
				cout << "无效重命名，新目录名与原有目录名重名!" << endl;
			else
				cout << "目录重命名成功！" << endl;
		}
	}
}

void FileManager::renameFile()//重命名文件
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));
	//renamef 原来的名字 新的名字
	File *p = new File();//旧名字
	cin >> p->filename;
	File *q = new File();
	cin >> q->filename;//新名字
	int flag = 0, flag1 = 0;
	if (currentDir->fileptr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *ptr = new File();
		ptr = currentDir->fileptr;
		File *ptr1 = new File();
		ptr1 = currentDir->fileptr;
		while (ptr != NULL)
		{
			if (ptr->filename == p->filename)//当前路径下存在要重命名的目录
			{
				flag++;
				while (ptr1 != NULL)
				{
					if (ptr1->filename == q->filename)//重命名后的目录名字与原来存在的目录相同
					{
						flag1++;
						break;
					}
					ptr1 = ptr1->nextFile;
				}
				if (!flag1)
				{
					ptr->filename = q->filename;
					ptr->altertime = tmp;
				}
				break;
			}

			ptr = ptr->nextFile;
		}

		if (!flag)
			cout << "不存在指定要重命名的文件!" << endl;
		if (flag)
		{
			if (flag1)
				cout << "无效重命名，新文件名与原有文件名重名!" << endl;
			else
				cout << "文件重命名成功！" << endl;
		}
	}
}

void FileManager::readFile()//读出文件,显示文件内容
{
	File *p = new File();
	cin >> p->filename;
	int flag = 0;
	if (currentDir->fileptr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *q;
		q = currentDir->fileptr;
		while (q != NULL)
		{
			if (q->filename == p->filename)//文件名相同
			{
				cout << "文件" << q->filename << ":" << q->filecontent << endl;
				cout << "文件读出成功！" << endl;
				flag++;
				break;
			}
			q = q->nextFile;
		}
		if (!flag)
			cout << "不存在指定要打开的文件!" << endl;

	}
}

void FileManager::writeFile()//编辑文件
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	File *p = new File();
	cin >> p->filename;
	string s;//编辑内容
	int flag = 0;
	getline(cin, s);
	if (currentDir->fileptr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *q;
		q = currentDir->fileptr;
		while (q != NULL)
		{
			if (q->filename == p->filename)
			{

				if (q->rw == false)//文件可读写
				{

					q->filecontent = s;
					if (s != ""){//忽略一个前置空格
						q->filesize = s.length() - 1;
					}else{
						q->filesize = s.length();
					}
					q->altertime = tmp;
					flag++;
					cout << "文件写入成功！" << endl;
					break;
				}
				else
				{
					cout << "该文件为只读文件，不能写入!" << endl;
				}

			}
			q = q->nextFile;
		}
		if (!flag)
			cout << "不存在指定要编辑的文件!" << endl;

	}
}

void FileManager::copyFile()
{
	File *p = new File();
	cin >> p->filename;
	int flag = 0;
	tempfile = new File();
	if (currentDir->fileptr == NULL)       //当前目录下没有文件
		cout << "当前路径下不存在文件!" << endl;
	else							   //当前目录下有文件，就从current->ptr开始查询到相同的
	{
		File *q;
		q = currentDir->fileptr;

		while (q->nextFile != NULL)
		{
			if (q->nextFile->filename == p->filename)
			{
				tempfile = q->nextFile;

				flag++;
				break;
			}
			q = q->nextFile;
		}
		if (currentDir->fileptr->filename == p->filename)//第一项
		{
			tempfile = currentDir->fileptr;
			flag++;
		}
		if (flag)
			cout << "文件复制成功!" << endl;
		else
			cout << "不存在指定要复制的文件!" << endl;
	}

}

void FileManager::pasteFile()//粘贴文件
{
	int flag = 0;
	if (tempfile == NULL) //没有复制文件，临时文件为空
	{
		cout << "请先复制文件再粘贴!" << endl;
	}

	if (currentDir->fileptr == NULL)//目录中没有文件，则直接将复制的文件粘贴
	{
		currentDir->fileptr = new File();
		currentDir->fileptr->fcreatetime = tempfile->fcreatetime;
		currentDir->fileptr->altertime = tempfile->altertime;
		currentDir->fileptr->filecontent = tempfile->filecontent;
		currentDir->fileptr->filename = tempfile->filename;
		currentDir->fileptr->filesize = tempfile->filesize;
		currentDir->fileptr->rw = tempfile->rw;
		cout << "粘贴文件成功!" << endl;
	}
	else  //如果目录中有文件，则找到最后一个文件，放在最后
	{

		File *q;
		q = currentDir->fileptr;

		while (q->nextFile != NULL)//直到为空
		{
			if (q->filename == tempfile->filename)
			{
				flag++;
				break;
			}
			q = q->nextFile;
			if (q->nextFile == NULL && q->filename == tempfile->filename)//判断最后一项
			{
				flag++;
			}
		}
		if (currentDir->fileptr->filename == tempfile->filename)//判断链表第一个文件是否与要粘贴的同名
		{
			flag++;
		}

		if (!flag)
		{
			q->nextFile = new File();
			q->nextFile->fcreatetime = tempfile->fcreatetime;
			q->nextFile->altertime = tempfile->altertime;
			q->nextFile->filecontent = tempfile->filecontent;
			q->nextFile->filename = tempfile->filename;
			q->nextFile->filesize = tempfile->filesize;
			q->nextFile->rw = tempfile->rw;
			cout << "文件粘贴成功！" << endl;
		}
		else
			cout << "同名文件已存在!" << endl;
	}
}

void FileManager::copyDir()//复制目录    
{
	Dir *p = new Dir();
	cin >> p->dirname;
	int flag = 0;
	if (currentDir->dirptr == NULL)//目录为空
		cout << "当前路径下不存在目录!" << endl;
	else//找到需要复制的目录
	{
		Dir *q;
		q = currentDir->dirptr;
		while (q != NULL)
		{
			if (q->dirname == p->dirname)
			{
				tempdir = q;
				flag++;
				break;
			}
			q = q->nextDir;
		}
		if (flag)
			cout << "目录复制成功！" << endl;
		else
			cout << "不存在指定要复制的目录!" << endl;
	}
}

void FileManager::pasteDir() //粘贴目录
{
	int flag = 0;
	if (tempdir == NULL)
	{
		cout << "不存在复制目录，不能粘贴!" << endl;
	}
	Dir *ptr;
	ptr = currentDir;
	while (ptr != NULL)
	{
		if (ptr->dirname == tempdir->dirname)//父目录不能粘贴到子目录下
		{
			cout << "不能将父目录复制到子目录下!" << endl;
		}
		ptr = ptr->preDir;//回溯
	}

	if (currentDir->dirptr == NULL)//当前目录下没有子目录
	{

		currentDir->dirptr = new Dir();

		if (tempdir->dirptr == NULL)//tempdir没有子目录
		{
			currentDir->dirptr->dircreatetime = tempdir->dircreatetime;
			currentDir->dirptr->altertime = tempdir->altertime;
			currentDir->dirptr->dirname = tempdir->dirname;
			currentDir->dirptr->dirsize = tempdir->dirsize;
			currentDir->dirptr->preDir = currentDir;

			pasteFileInDir(tempdir->fileptr, currentDir->dirptr);
		}
		else	//temp有子目录，先粘贴自己，再贴子目录
		{
			currentDir->dirptr->dircreatetime = tempdir->dircreatetime;
			currentDir->dirptr->altertime = tempdir->altertime;
			currentDir->dirptr->dirname = tempdir->dirname;
			currentDir->dirptr->dirsize = tempdir->dirsize;
			currentDir->dirptr->preDir = currentDir;

			pasteFileInDir(tempdir->fileptr, currentDir->dirptr);
			//----自己部分结束
			//把current ptr的ptr给temp的ptr 两边子目录对接
			currentDir->dirptr->dirptr = new Dir();//子目录起始位置开始粘贴
			currentDir->dirptr->dirptr->dircreatetime = tempdir->dirptr->dircreatetime;
			currentDir->dirptr->dirptr->altertime = tempdir->dirptr->altertime;
			currentDir->dirptr->dirptr->dirname = tempdir->dirptr->dirname;
			currentDir->dirptr->dirptr->dirsize = tempdir->dirptr->dirsize;
			currentDir->dirptr->dirptr->preDir = currentDir->dirptr;
			//子文件复制
			pasteFileInDir(tempdir->dirptr->fileptr, currentDir->dirptr->dirptr);
			//子目录
			pasteSubDir(tempdir->dirptr, currentDir->dirptr->dirptr);
		}

		cout << "文件粘贴成功！" << endl;
	}
	else
	{
		Dir *q;
		q = currentDir->dirptr;

		while (q->nextDir != NULL)
		{
			if (q->nextDir->dirname == tempdir->dirname)
			{
				flag++;
				break;
			}
			q = q->nextDir;
			if (q->nextDir == NULL && q->dirname == tempdir->dirname)//判断最后链表最后一个目录是否与要粘贴的同名
			{
				flag++;
			}
		}
		if (currentDir->dirptr->dirname == tempdir->dirname)
		{
			flag++;
		}
		if (!flag)
		{
			q->nextDir = new Dir();
			if (tempdir->dirptr == NULL)
			{
				q->nextDir->dircreatetime = tempdir->dircreatetime;
				q->nextDir->altertime = tempdir->altertime;
				q->nextDir->dirname = tempdir->dirname;
				q->nextDir->dirptr->dirsize = tempdir->dirsize;
				q->nextDir->preDir = currentDir;
				//复制文件
				pasteFileInDir(tempdir->fileptr, q->nextDir);

			}
			else
			{
				q->nextDir->dircreatetime = tempdir->dircreatetime;
				q->nextDir->altertime = tempdir->altertime;
				q->nextDir->dirname = tempdir->dirname;
				q->nextDir->dirsize = tempdir->dirsize;
				q->nextDir->preDir = currentDir;
				
				pasteFileInDir(tempdir->fileptr, q->nextDir);

				q->nextDir->dirptr = new Dir();
				q->nextDir->dirptr->dircreatetime = tempdir->dirptr->dircreatetime;
				q->nextDir->dirptr->altertime = tempdir->dirptr->altertime;
				q->nextDir->dirptr->dirname = tempdir->dirptr->dirname;
				q->nextDir->dirptr->dirsize = tempdir->dirptr->dirsize;
				q->nextDir->dirptr->preDir = q->nextDir;
				
				pasteFileInDir(tempdir->dirptr->fileptr, q->nextDir->dirptr);
				pasteSubDir(tempdir->dirptr, q->nextDir->dirptr);
				cout << "粘贴目录成功!" << endl;
			}
		}
		else
			cout << "同名目录已存在!" << endl;

	}

}

void FileManager::pasteSubDir(Dir *dir1, Dir *dir2)//粘贴子函数  1是复制了的目录     2是要复制到的目录
{

	if (dir1->dirptr != NULL)//1不空，把1放到2里面
	{
		dir2->dirptr = new Dir();
		dir2->dirptr->dircreatetime = dir1->dirptr->dircreatetime;
		dir2->dirptr->altertime = dir1->dirptr->altertime;
		dir2->dirptr->dirname = dir1->dirptr->dirname;
		dir2->dirptr->dirsize = dir1->dirptr->dirsize;
		dir2->dirptr->preDir = dir2;
		//文件复制
		pasteFileInDir(dir1->dirptr->fileptr, dir2->dirptr);
		//递归
		pasteSubDir(dir1->dirptr, dir2->dirptr);
	}

	if (dir1->nextDir != NULL)//1有同级后续 继续复制
	{
		dir2->nextDir = new Dir();
		dir2->nextDir->dircreatetime = dir1->nextDir->dircreatetime;
		dir2->nextDir->altertime = dir1->nextDir->altertime;
		dir2->nextDir->dirname = dir1->nextDir->dirname;
		dir2->nextDir->dirsize = dir1->nextDir->dirsize;
		dir2->nextDir->preDir = dir2->preDir;
		//文件复制
		pasteFileInDir(dir1->nextDir->fileptr, dir2->nextDir);

		pasteSubDir(dir1->nextDir, dir2->nextDir);
	}

}

void FileManager::pasteFileInDir(File *file, Dir *dir)//file要复制的文件，dir复制到的目录
{
	File *file1;
	file1 = file;
	Dir *dir1;
	dir1 = dir;
	if (dir1->fileptr != NULL)
	{
		File *ptr;
		ptr = dir1->fileptr;
		while (ptr->nextFile != NULL) //同级后续文件复制
		{
			ptr = ptr->nextFile;
		}
		ptr->nextFile = new File();
		ptr->nextFile->fcreatetime = file1->fcreatetime;
		ptr->nextFile->altertime = file1->altertime;
		ptr->nextFile->filecontent = file1->filecontent;
		ptr->nextFile->filename = file1->filename;
		ptr->nextFile->filesize = file->filesize;
		ptr->nextFile->rw = file->rw;
	}
	else
	{
		if (file == NULL){//没有文件，直接粘贴
			dir->fileptr = file1;
		}
		else{
			File *ptr = new File();
			ptr = file1;
			File *tempfile = new File();
			tempfile->fcreatetime = file1->fcreatetime;
			tempfile->altertime = file1->altertime;
			tempfile->filecontent = file1->filecontent;
			tempfile->filename = file1->filename;
			tempfile->filesize = file1->filesize;
			tempfile->rw = file1->rw;
			ptr = tempfile;
			while (file1->nextFile != NULL)
			{
				File *tempfile2 = new File();
				tempfile->fcreatetime = file1->fcreatetime;
				tempfile->altertime = file1->altertime;
				tempfile->filecontent = file1->filecontent;
				tempfile->filename = file1->filename;
				tempfile->filesize = file1->filesize;
				tempfile->rw = file1->rw;
				ptr->nextFile = tempfile2;
				ptr = ptr->nextFile;

			}
			dir->fileptr = tempfile;
		}
	}

}

void FileManager::filerw()//修改文件属性
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	File *p = new File();
	cin >> p->filename;
	int flag = 0;

	if (currentDir->fileptr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *q;
		q = currentDir->fileptr;
		while (q != NULL)
		{
			if (q->filename == p->filename)
			{

				cout << "选择修改的属性: 0为可读可写 1为只读" << endl;
				bool a;
				cin >> a;
				while (q->rw == a)
				{
					cout << "该文件已为该属性，无需修改!" << endl;
					cout << "请重新选择:" << endl;
					cin >> a;

				}

				if (q->rw == false)
				{
					q->altertime = tmp;
					q->rw = a;
					cout << "文件已修改为只读!" << endl;
				}
				else
				{
					q->altertime = tmp;
					q->rw = a;
					cout << "文件已修改为可读可写!" << endl;
				}

				flag++;
				break;
			}
			q = q->nextFile;
		}
		if (!flag)
			cout << "不存在指定要编辑的文件!" << endl;

	}
}