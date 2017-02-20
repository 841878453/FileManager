#include "File.h"
File::File(){
	rw = false;
	fcreatetime = "";
	altertime = "";
	filesize = 0;
	nextFile = NULL;
	filecontent = "";
}
File::~File(){

}