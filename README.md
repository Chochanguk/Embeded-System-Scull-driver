# Scull-driver README
**🖥️Embeded System: 특정한 기능을 수행하도록 설계된 전용 컴퓨터 시스템**

<br>

## 1. 프로젝트 소개

- scull driver는 문자 기반 드라이버로써, 주로 Linux 커널에서 드라이버 개발 및 커널 모듈 프로그래밍을 교육용으로 사용되거나 디버깅하는 용도로 사용됩니다.
- scull dirver는 메모리에 데이터를 가져저장하거나 가져오는 작은 고립된 블록을 통해 가상의 문자 디바이스를 만듭니다.
- scull driver는 이런 가상의 문자 디바이스를 통해 사용자 공간 프로세스와 커널 간의 데이터 송수신을 합니다.
- scull driver를 Linux Shell commands와 User Application를 통해 데이터를 드라이버 쓰고 읽음을 확인함으로써 드라이버의 동작원리를 이해하는게 이 프로젝트의 최종 목적입니다.
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
- 커널은 특정 디바이스 파일이 열릴 때, 그 디바이스에 대한 file_operations 구조체의 인스턴스(inode)를 찾아 사용한다.
  
<div align="center">
  ![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/975ef459-3c7d-4a32-b89d-064bd93b5d2c)
</div>

<br>

## 3. Implementation Description
![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/d627cfb5-d9ba-4d75-beb4-b3f54803472b)
![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/04c88cd2-0259-47aa-897d-c87994e91f09)
![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/a111e214-84f6-4282-b3d1-5965c2a5c04a)
![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/bdde6c7e-04ba-4b23-913d-809170a7edd6)
![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/d04ff61c-b7c9-48a4-a93a-3f71bf9cec1f)
![image](https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/e10b2cd9-1ba7-4140-b54b-65532dcb66f1)










