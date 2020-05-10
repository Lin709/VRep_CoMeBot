#include "winsock2.h"
#define BUFSIZE 1024
#include "main.h"
#include "Data_Format.h"

using namespace cv;


int main(int argc, char* argv[])
{
	printf("Start Program\n");
	clientID = simxStart((simxChar*)"127.0.0.1", 9200, true, true, 5000, 5);

	char cMsg;




	int n = simxSynchronous(clientID, true);
	if (n == simx_return_remote_error_flag) {
		printf("%d\n", n);
	}
	simxInt error = simxStartSimulation(clientID, simx_opmode_oneshot_wait);
	if (error != simx_error_noerror) {
		throw std::string("Unable to start the simulation");
	}

	std::thread recvimg;
	recvimg = std::thread(getimage);

	if (clientID != -1) {
		printf("Connection Established\n");
		init();
		while (simxGetConnectionId(clientID) != -1)
		{
			if (kbhit())
			{
				int key = _getch();
				printf("%d\t", key);

				switch (key) {
				case S_COMMAND:
					std::cout << "Back\n";
					_Back_flag = true;		_Front_flag = false;	_Left_flag = false;		_Right_flag = false;
					break;
				case W_COMMAND:
					std::cout << "Front\n";
					_Front_flag = true;		_Back_flag = false;		_Left_flag = false;		_Right_flag = false;
					break;
				case A_COMMAND:
					std::cout << "LEF\n";
					_Left_flag = true;		_Front_flag = false;	_Back_flag = false;		_Right_flag = false;
					break;
				case D_COMMAND:
					std::cout << "RIG\n";
					_Right_flag = true;		_Left_flag = false;		_Front_flag = false;	_Back_flag = false;
					break;
				case R_COMMAND:
					std::cout << "Read\n";
					if (_Reading_flag)		_Reading_flag = false;	else					_Reading_flag = true;
					break;

				case TAB_COMMAND:
					if (simulation_run) {
						simulation_run = false;
						std::cout << "Stop\n";
					}
					else {
						simulation_run = true;
						std::cout << "Go\n";
					}
					break;
				default:
					break;
				}
			}



			// 만약 충격이나 들어올림 플래그가 서면 따로 저장해두고 그 패킷 보내기







			if (simulation_run == true)
			{
				if (_Back_flag == true) {
					/*      initial Pos      */
					num = 0;
					writedevice(num);
					simxSynchronousTrigger(clientID);
				}
				else if (_Front_flag == true) {
					num = 1;
					writedevice(num);
					simxSynchronousTrigger(clientID);
				}
				else if (_Left_flag == true) {
					num = 2;
					writedevice(num);
					simxSynchronousTrigger(clientID);
				}
				else if (_Right_flag == true) {
					num = 3;
					writedevice(num);
					simxSynchronousTrigger(clientID);
				}
				if (_Reading_flag == true) {
					forcesensor();			getpos();
					simxSynchronousTrigger(clientID);
					if ((force_cur < -0.1805) & (force_cur > -0.1835))	force_flag = 0;
					else												force_flag = 1;
					printf("\t%d", force_flag);//printf("%lf\n", force_cur);
					printf("\t%f\t%f\t%f\n", getposition[0], getposition[1], getposition[2]);
				}
			}
			Sleep(0);
		}
		recvimg.join();
		simxStopSimulation(clientID, simx_opmode_oneshot);
		simxFinish(clientID);
	}
	return 0;
}