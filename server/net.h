#ifndef __NET_SCENE_H__
#define __NET_SCENE_H__
#include "ODSocket.h"
#include<thread>
#include<mutex>
#include<deque>
#include"rules.h"
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
	bool makeServer();//����������
	//bool makeClient();//�����ͻ���
	//void clientRecv(std::string temp);//�ͻ��˷�������
	//virtual void Manage(float dt);
	void accept();//��������������
	//void SendBroadcast();//���͹㲥
	//void RecvBroadcast();//���չ㲥
	//void RecvBroadcastFunc();
	void ResetFDSet(fd_set& fdRead, fd_set& fdWrite, fd_set& fdExcept, SOCKET sdListen, const ConnectionList& conns);
	int CheckAccept(const fd_set& fdRead, const fd_set& fdExcept, SOCKET sdListen, ConnectionList& conns);//�����������
	void CheckConn(const fd_set& fdRead, const fd_set& fdWrite, const fd_set& fdExcept, ConnectionList& conns);//����������Ƿ�ɶ�д
	//void CheckConn(const fd_set& fdRead, const fd_set& fdWrite, const fd_set& fdExcept, Connection* conn);//�ͻ��˼���Ƿ�ɶ�д
	bool TryRead(Connection* pConn);//������
	bool TryWrite(Connection* pConn);//д����
	bool PassiveShutdown(SOCKET sd, const char* buff, int len);
	bool createUdpSocket();//����udp�׽���
	void cardManage();//�����˿˴���ϴ�Ʒ���
	void makeCards();
	void shuffleCards();
	void giveCards();//����
	void giveCardsA();//�ط���
	void manageServerMessage(std::string temp);//������������Ϣ
	//void sendStringC(std::string temp);//�ͻ��˷�����Ϣ
	void sendStringS(std::string temp);//����ҷ�����Ϣ
	void sendStringTo(std::string temp, int num);//�򵥸���ҷ�����Ϣ
	void manageLandlord(std::string temp);//����е����׶ε���Ϣ
	void manageTimeOut(std::string temp);//����ʱ��Ϣ
	void manageTuoGuan(std::string temp);//�����й���Ϣ
	void sendLandlordCards();//���͵�����
	void managePuke(std::string temp);//���������Ϣ
	std::vector<puke> makeCards(std::string temp);//�����ַ��������˿�����
	void insertLandlordCards(int num);
	std::vector<puke> getHintCards(int num);//ӵ������Ȩʱ�Զ�������
	void removePuke(std::string temp);//�Ƴ��˿�
	std::vector<puke> getTuoGuanCards(int player);//��ȡ�й�ʱ����������
	//��ȡ�й�ʱָ������
	std::vector<puke> getType1(int player);//�ɻ���
	std::vector<puke> getType2(int player);//�Ĵ�һ���
	std::vector<puke> getType3(int player);//����
	std::vector<puke> getType4(int player);//˳��
	std::vector<puke> getType5(int player);//����һ / ��,����
	std::vector<puke> getType6(int player);//ը������
	std::vector<puke> getType7(int player);//���ƻ����
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
		if (listenSocket)
		{
			delete listenSocket;
			listenSocket = NULL;
		}
		for (std::vector<Connection*>::iterator it = clientList.begin(); it != clientList.end(); it++)
		{
			if (*it)
			{
				delete *it;
				*it = NULL;
			}
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
    std::deque<std::string> serverStr;//��������Ϣ
	std::deque<std::string> clientStr;//�ͻ�����Ϣ
	std::vector<puke> myCards;//���ڿͻ��˽����Լ�����
	int playerNum; //��¼��ұ��
	std::mutex m_mutex;//���ڿ���clientStr�������
	std::mutex m_mutex2;//���ڿ��ƿͻ���sendBuffer�Ļ������
	std::mutex m_mutex1;//���ڿ��Ʒ�����sendBuffer�Ļ������
	std::mutex m_mutex3;//���ڿ��Ʒ�����serverStr�Ļ������
	int firstNum; //��¼��һ����ʼ�����
	Connection* clientConnection;//�ͻ��˵Ķ�д��Ϣ
	bool exit;//���������߳�
	static Net* m_net;
private:
	
	std::vector<int> readyPlayer;//�Ѿ�׼���õ����
	int circleNum;//��¼�׶���Ϣ��0�е����׶Σ�1�������׶Σ�2���ƽ׶�
	ODSocket* connectSocket;//�ͻ��������׽���
	ODSocket* listenSocket;//�����׽���
	ODSocket* udpSocket;//udp�׽��֣����ڽ��չ㲥��Ϣ
	ConnectionList clientList;//�����ӿͻ����б�
	std::string serverIP;//������IP
	int serverPort;//�������˿ں�
	int readyNum;//��׼���õĿͻ�������
	Landlord callLandlord;//�е������
	Landlord grabLandlord;//���������
	Turn big;//��ǰ�������
	bool connect;//����Ƿ��������������
	std::vector<puke> allCards;//�洢���е���
	std::vector<puke> lastCards;//�洢��һ�γ�����
	std::vector<std::vector<puke>> playerCards;//��¼ÿ����ҵ���
	int maxfd;//Linux��ʹ�ü�¼����ļ�������

	bool discardCards;//�Ƿ��Ѿ�������
	Rules rule;//�ж���Ϸ����
	std::vector<int> cardsNum;//��¼ÿ����ҵ��˿�����,���Կ���ɾ������playerCards����
	Rules rules;
	//std::vector<bool> isTuoGuanState;//
	Net() :listenSocket(NULL), udpSocket(NULL), connectSocket(NULL), connect(false), maxfd(-1), clientConnection(NULL), playerNum(0)
	{
		clientList.clear();
		serverIP.clear();
		exit = false;
		readyNum = 0;
		discardCards = false;
		circleNum = 0;
		callLandlord = none;
		grabLandlord = none;
		for (int i = 0; i < 3; i++)
		{
			cardsNum.push_back(17);//��ʼ�����������
			playerCards.push_back(std::vector<puke>());//
			//isTuoGuanState.push_back(false);//��ʼ���й�״̬
		}
	}
};

#endif // __NET_SCENE_H__

