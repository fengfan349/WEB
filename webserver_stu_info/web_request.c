#include "web_request.h"



HTML_FILE_ENTRY html_list[]={
	{"student_info.htm",html_stu_info,cgi_stu_info,0},
	{"vlan_status.htm",html_vlan_status,cgi_vlan_status,0},
	{"navigation.htm",html_navigation,0,0},
	{"lan.htm",html_lan,cgi_lan_info,0},
	{"lan_status.htm",html_lan_status,0,0},
	{0,0,0,0},
};


int webreq_refresh()
{
	char *htmlpath=NULL;
	char *env=NULL;
	char pathbuf[32];
	env=getenv("QUERY_STRING");
	int i;
	memset(pathbuf,'\0',32);
	get_char_para(env,"CUR_FORM=",pathbuf);
    debug("html path is:%s\n",pathbuf);
	if(!*pathbuf)
	{
		debug("get html path error!!\n");
		return 0;
	}
	for(i=0;;i++)
	{
		if(!html_list[i].path)
			break;
		if(!strcmp(html_list[i].path,pathbuf))
		{
			debug("match the path\n");
			if((*html_list[i].func)==0)
			{
				return 0;
			}
			(*html_list[i].func)();//函数指针变量,pFunc(), 或者Func(), 或者(*pFunc)() 建议使用第三种----代码正在使用函数指针, 这很明显.
			return 1;
		}
	}
	debug("This html entry is not existed!!!\n");
	return 0;
	
}
int webreq_config()
{
	char *htmlpath=NULL;
	char *env=NULL;
	char pathbuf[32];
	int i;
	env=getenv("QUERY_STRING");
	memset(pathbuf,'\0',32);
	get_char_para(env,"CUR_FORM=",pathbuf);
	debug("vlan config\n");
	if(!*pathbuf)
	{
		debug("get html path error!!\n");
		return 0;
	}
	for(i=0;;i++)
	{
		if(!html_list[i].path)
			break;
		if(!strcmp(html_list[i].path,pathbuf))
		{
			if((*html_list[i].func_cgi)==0)
			{
				return 0;
			}
			(*html_list[i].func_cgi)();//函数指针变量
			return 1;
		}
	}
	debug("This html entry is not existed!!!\n");
	return 0;
}


