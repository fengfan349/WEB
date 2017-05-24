#include "main.h"
int main(int argc,char **argv)
{
	char* env=NULL;
	char* url=NULL;
	ipc_init();
	if ((log_file = fopen (LOG_FILE, "w")) == NULL)
    {
        fprintf (stderr, "Open File Err: %s\n", strerror (errno));  /*以只写方式打开一个文件 */
        return -1;
    }
	if ((url = getenv ("SCRIPT_NAME")) == NULL)
	{
		perror("get url error:\n");
		debug("I am here url error!!!!\n");
	}
	
	//if((strcasecmp(url,HTML_REFRESH))==0)
	if((strcasecmp(url,HTML_REFRESH))==0)
	{
		webreq_refresh();
	}
	if((strcasecmp(url,HTML_CONFIG))==0)
	{
		webreq_config();
	}

	fclose (log_file);
	return 1;
}
