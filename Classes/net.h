#ifndef __NET_SCENE_H__
#define __NET_SCENE_H__
#include "ODSocket.h"
#include<thread>
#include<mutex>
#include<deque>
enum Landlord
{
	p1 = 1,
	p2,
	p3,
	none
};
enum Turn {
	player1 = 1,
	player2,
	player3
};

class Net
{
public:
	bool makeClient();//�����ͻ���
	void clientRecv(std::string temp);//�ͻ��˷�������
	void CheckConn(const fd_set& fdRead, const fd_set& fdWrite, const fd_set& fdExcept, Connection* conn);//�ͻ��˼���Ƿ�ɶ�д
	bool TryRead(Connection* pConn);//������
	bool TryWrite(Connection* pConn);//д����
	bool PassiveShutdown(SOCKET sd, const char* buff, int len);
	bool createUdpSocket();//����udp�׽���
	void sendStringC(std::string temp);//�ͻ��˷�����Ϣ
	static Net* getInstance()
	{
		if (m_net == NULL)
		{
			m_net = new Net();
		}
		return m_net;
	}
	void destroyInstance()
	{
		if (connectSocket)
		{
			delete connectSocket;
			connectSocket = NULL;
		}
		if (clientConnection)
		{
			delete clientConnection;
			clientConnection = NULL;
		}
		if (m_net)
			delete m_net;
		m_net = NULL;
	}
	void manageStr(std::string temp, bool isClient);
	void DeleteSocket();
	std::deque<std::string> clientStr;//�ͻ�����Ϣ
	int playerNum; //��¼��ұ��
	std::mutex m_mutex;//���ڿ���clientStr�������
	std::mutex m_mutex2;//���ڿ��ƿͻ���sendBuffer�Ļ������
	Connection* clientConnection;//�ͻ��˵Ķ�д��Ϣ
	bool exit;//���������߳�
	static Net* m_net;
private:
	ODSocket* connectSocket;//�ͻ��������׽���
	ODSocket* udpSocket;//udp�׽��֣����ڽ��չ㲥��Ϣ
	std::string serverIP;//������IP
	int serverPort;//�������˿ں�
	bool connect;//����Ƿ��������������
	int maxfd;//Linux��ʹ�ü�¼����ļ�������

	Net() :udpSocket(NULL), connectSocket(NULL), connect(false), maxfd(-1), clientConnection(NULL), playerNum(0)
	{
		serverIP = "49.140.162.151";
		exit = false;
	}
};

#endif // __NET_SCENE_H__

