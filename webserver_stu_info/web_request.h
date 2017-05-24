#ifndef _WEB_REQUEST_H
#define _WEB_REQUEST_H
#include "main.h"

#include "getform.h"
#include "webshtm.h"
#include "webscgi.h"

typedef struct html_file_entry
{
	char *path;
	int ((*func)(void)); //����ָ�������ָ������ڵ�ָ�����
	int ((*func_cgi)(void));//ͬ��
	int size;
}HTML_FILE_ENTRY;


int webreq_config();
int webreq_refresh();

#endif
