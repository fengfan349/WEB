#include "ipc_init.h"

int ipc_init()
{
	share_mem=(share_data_struct*)shm_creat(IPC_SHM_KEY,0666,sizeof(share_data_struct));//�����ڴ��ʼ�����õ������ڴ��׵�ַ
	
	msg_web_fd=msg_creat(IPC_MSG_KEY,0666);// ��Ϣ���г�ʼ�����õ���Ϣ����������

	sem_fd=sem_create(IPC_SEM_KEY,IPC_SEM_MAX,0666);// �ź�����ʼ��
	//sem_initialize(sem_fd,IPC_SEM_MAX,1);

	return 0;
}

