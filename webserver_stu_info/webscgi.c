#include "webscgi.h"


int cgi_stu_info()
{
	char* env;
	char agebuf[32];
	char idbuf[32];
	user_info_struct info;
	msg_queue_struct msg_snd;
	msg_queue_struct msg_rcv;

	memset(&msg_rcv,0,sizeof(msg_queue_struct));
	memset(&msg_snd,0,sizeof(msg_queue_struct));
	memset(&info,0,sizeof(user_info_struct));
	
	env=getenv("QUERY_STRING");
	get_char_para(env,"STU_NAME=",info.name);
	get_char_para(env,"STU_SEX=",info.sex);
	memset(agebuf,0,sizeof(agebuf));
	memset(idbuf,0,sizeof(idbuf));
	get_char_para(env,"STU_AGE=",agebuf);
    get_char_para(env,"STU_ID=",idbuf);
    info.age=atoi(agebuf);
	info.stu_id=atoi(idbuf);
	
	msg_snd.data.module=MSG_USER_INFO;
	memcpy(msg_snd.data.msg_data_buf,&info,sizeof(user_info_struct));
	GET_REP_TO_WEB(msg_snd,msg_rcv);

	return 0;
}
int cgi_vlan_status()
{
	int i;
	int ret;
	char* env=NULL;
	char intbuf[16];
	msg_queue_struct msg_snd;
	msg_queue_struct msg_rcv;

	memset(&msg_rcv,0,sizeof(msg_queue_struct));
	memset(&msg_snd,0,sizeof(msg_queue_struct));
	
	env=getenv("QUERY_STRING");
	debug("port_list:%s\n",env);
	int portvlan_buf[MAX_PORT_NUM];
	
	memset(portvlan_buf,0,sizeof(portvlan_buf));
	
	memset(intbuf,0,16);
	get_char_para(env,"port1_list=",intbuf);
	portvlan_buf[1]=atoi(intbuf);
	

	memset(intbuf,0,16);
	get_char_para(env,"port2_list=",intbuf);
	portvlan_buf[2]=atoi(intbuf);

	memset(intbuf,0,16);
	get_char_para(env,"port3_list=",intbuf);
	portvlan_buf[3]=atoi(intbuf);

	memset(intbuf,0,16);
	get_char_para(env,"port4_list=",intbuf);
	portvlan_buf[4]=atoi(intbuf);
	
	for(i=VLAN_PORT_START;i<=VLAN_PORT_END;i++)
	{
		msg_snd.data.msg_data_buf[i]=portvlan_buf[i];
	}
	msg_snd.data.module = MSG_PORTVLAN_INFO;
	GET_REP_TO_WEB(msg_snd,msg_rcv);
	debug("msg snd member is 0x%x\r\n",msg_snd.data.msg_data_buf[1]);
	return 0;
}

int cgi_lan_info()
{
	char tmp[32];
	char* env=NULL;
	char intbuf[16];
	int mode;
	msg_queue_struct msg_snd;
	msg_queue_struct msg_rcv;
	port_status_struct port_status;

	memset(&port_status,0,sizeof(port_status_struct));
	memset(&msg_rcv,0,sizeof(msg_queue_struct));
	memset(&msg_snd,0,sizeof(msg_queue_struct));

	env=getenv("QUERY_STRING");
	debug("port_list:%s\n",env);
	
	memset(tmp,0,32);
	get_char_para(env,"CUR_PORT=",tmp);
	port_status.lan_id=atoi(tmp);

	memset(tmp,0,32);
	get_char_para(env,"Mode=",tmp);
	mode=atoi(tmp);
	switch(mode)
	{
		case 1://auto speed
			port_status.speed_status = SPEED_AUTO;
			break;
		case 2://100M FUll
			port_status.speed_status = SPEED_100M;
			port_status.duplex_status = DUPLEX_FULL;
			break;
		case 3://100M HALF
			port_status.speed_status = SPEED_100M;
			port_status.duplex_status = DUPLEX_HALF;
			break;
		case 4://10M FUll
			port_status.speed_status = SPEED_10M;
			port_status.duplex_status = DUPLEX_FULL;
			break;
		case 5://10M HALF
			port_status.speed_status = SPEED_10M;
			port_status.duplex_status = DUPLEX_HALF;
			break;
		default:
			break;		
	}
	COPYFROM_STRUCT(msg_snd.data.msg_data_buf,port_status);
	msg_snd.data.module=MSG_PORT_INFO;
	GET_REP_TO_WEB(msg_snd,msg_rcv);
	return 0;
}

