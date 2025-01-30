# Scull-driver README
**🖥️Embeded System: 특정한 기능을 수행하도록 설계된 전용 컴퓨터 시스템**

<br>

## 1. 프로젝트 소개

### 1.1. 프로젝트 개요
- scull driver는 문자 기반 드라이버로써, 주로 Linux 커널에서 드라이버 개발 및 커널 모듈 프로그래밍을 교육용으로 사용되거나 디버깅하는 용도로 사용됩니다.
- scull driver는 메모리에 데이터를 저장하거나 가져오는 작은 고립된 블록을 통해 가상의 문자 디바이스를 만듭니다.
- scull driver는 이런 가상의 문자 디바이스를 통해 사용자 공간 프로세스와 커널 간의 데이터 송수신을 합니다.

### 1.2. 프로젝트 목적  
이 프로젝트의 최종 목적은 SCULL 드라이버를 개발하고, Linux 셸 명령어와 사용자 애플리케이션을 통해 드라이버에 데이터를 읽고 쓰는 과정을 확인하며 **드라이버의 동작 원리를 이해**하는 것입니다.

### 1.3. 개발 환경
사용 언어: C
운영 체제: Ubuntu 22.04
가상화 툴: VirtualBox 7.0

### 1.4. 파일 설명
fops: 디바이스 파일의 동작(예: 읽기, 쓰기)을 정의하며, 사용자 요청을 처리합니다.
main.c: 드라이버의 초기화와 종료 로직을 담당하며, 커널에 드라이버를 등록합니다.
project1.c: scull0 디바이스의 open, write, read, close 동작을 구현합니다.

## 2. Linux Device Dirver Architecture
<div>
  <img src="https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/88d06841-e0b4-443e-b4bb-27c79494352a" width=65%/>
  <img src="https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/eccf5199-9670-411e-bf14-51e5f251138a" width=30%/>
</div>

- User Application에서 파일 입출력 함수 사용시 SWI가 실행.
- SWI Handler가 File System에 접근 하고, 각각의 Device Driver에 접근하여 해당 함수 처리.
- Block Device: 데이터를 한번 읽을때, 큰 Block 단위를 갖고 오며 나머지 Block은 버퍼에 저장한다. 이를 통해 큰양의 데이터를 처리 가능하며, 데이터는 Block size만큼 cache된다. 추가적으로 블록 크기만큼의 데이터를 순차적이지 않은 위치에서 읽거나 쓸 수 있다. (사용 예:HDD,SSD 등)
- Character Device: 데이터를 문자 단위로 데이터를 읽고 쓰는 디바이스. 문자 스트림을 사용하므로 데이터를 순차적인 접근을 하고 순차적으로 처리 된다.(사용 예: 터미널,마우스,키보드,프린터 등에서 사용)
- MAJOR#는 디바이스 드라이버의 고유 식별 번호 MINOR#는 해당 MAJOR#의 특정 디바이스를 뜻한다.
- 커널은 특정 디바이스 파일이 열릴 때, 그 디바이스에 대한 file_operations 구조체에서 인스턴스(inode)를 찾아 사용한다.
  
<div align="center">
  <img src="https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/975ef459-3c7d-4a32-b89d-064bd93b5d2c">
</div>

<br>

## 3. Implementation Description

### 3.1. make(Compiling the source code)
![image](https://github.com/user-attachments/assets/b8415a6a-9981-40f5-a6a3-821cb56b26c3)
make는 Makefile 이라는 설정 파일을 읽어 빌드 프로세스를 자동화함.
커널 빌드 시스템을 호출하여 모듈 빌드 수행. 이때 캐릭터 디바이스로 모듈 빌드

#### 결과
![image](https://github.com/user-attachments/assets/e78629ad-3d7d-4b4d-8720-9a5b7ee1b4b6)

### 3.3. Shell Script (insmod and mknode )
![image](https://github.com/user-attachments/assets/3ce43449-45a5-491a-b596-92fcae2c0380)

디바이스 파일은 커널 모듈과 사용자 프로그램간의 인터페이스 역할을 수행합니다.

1: 모듈 정보 정의(Read,Write 권한)
2: insmod로 scull.ko를 커널에 추가하여 모듈을 사용가능하게 로드.
3: main.c의 register_chdev를 통해 major#를 동적으로 할당 받은 후 mknode로 디바이스 파일 생성 (/dev/scullN)

#### 결과
![image](https://github.com/user-attachments/assets/824b1a95-d8a7-4fef-a22c-0b9553c90ff0)

### 3.4. 사용자 프로그램(C)로 드라이버 구현 확인

### 3.5. 멀티 프로세서 환경에서 뮤텍스 실행확인
![image](https://github.com/user-attachments/assets/f36cb79b-9f95-4c57-b3e9-4e2ad082d07a)

### 4. 프로젝트의 주요 구현방안
1. kmalloc을 통한 동적 할당으로 필요한 메모리만 할당하여 메모리 효율성 증가
2. 할당된 메모리는 양방향 연결 리스트로 구현해 삽입 및 삭제 시 탐색 시간 단축
3. Mutex를 활용하여 공유 자원에 대해 동시성 제어로 다중 프로세스 환경에서 데드락 방지









