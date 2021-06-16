// simpleSocketClient.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include <winsock2.h>
#include <ws2tcpip.h> // inet_addr
#include <stdio.h> // printf
#include <crtdbg.h> // _ASSERTE

int main(int argc, char** argv)
{
    char sendBuffer[4096 * 100] = { 1, };

    // 윈속 초기화
    WSADATA wsaData;
    int result = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        return -1;
    }

    // 소켓 만들기
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", ::WSAGetLastError());
        goto CLEAN_UP;
    }

    // 접속할 서버 설정
    struct sockaddr_in addrSockSvr;
    addrSockSvr.sin_family = AF_INET;
    addrSockSvr.sin_port = htons(9988);
    addrSockSvr.sin_addr.S_un.S_addr = inet_addr("172.30.159.222");

    // 서버에 접속
    result = ::connect(clientSocket, (struct sockaddr*)&addrSockSvr, sizeof(addrSockSvr));
    if (result == SOCKET_ERROR) {
        printf("connect failed with error: %ld\n", ::WSAGetLastError());
        goto CLEAN_UP;
    }

    result = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
    _ASSERTE(result == sizeof(sendBuffer) && "result == sizeof(sendBuffer) 여야만 한다.");
    if (result <= 0) {
        printf("send failed with error: %ld\n", ::WSAGetLastError());
    }

CLEAN_UP:
    if (clientSocket != INVALID_SOCKET) {
        ::closesocket(clientSocket);
    }
    ::WSACleanup();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
