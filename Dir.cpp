#include "Dir.h"
Dir::Dir()                         //���ڳ�ʼ���ĺ���
{
	altertime = "";
	dircreatetime = "";
	dirsize = 0;
	nextDir = NULL;
	preDir = NULL;
	fileptr = NULL;
	dirptr = NULL;
}
Dir::Dir(string time, string name, int size, Dir *nextdir, Dir*predir, File *fileptrtemp, Dir *dirptrtemp)//��ֵ����
{
	dircreatetime = time;
	dirname = name;
	dirsize = size;
	nextDir = nextdir;
	preDir = predir;
	fileptr = fileptrtemp;
	dirptr = dirptrtemp;
}
Dir::~Dir(){

}