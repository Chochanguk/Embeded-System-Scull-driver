# Scull Driver README
**🖥️Embeded System: 특정한 기능을 수행하도록 설계된 전용 컴퓨터 시스템**

---

## 📌 목차
1. [프로젝트 소개](#1-프로젝트-소개)  
   - [프로젝트 개요](#11-프로젝트-개요)  
   - [프로젝트 목적](#12-프로젝트-목적)  
   - [개발 환경](#13-개발-환경)  
   - [파일 설명](#14-파일-설명)  
2. [Linux Device Driver Architecture](#2-linux-device-driver-architecture)  
3. [Implementation Description](#3-implementation-description)  
   - [make (Compiling the source code)](#make-compiling-the-source-code)  
   - [Shell Script (insmod and mknode)](#shell-script-insmod-and-mknode)  
   - [사용자 프로그램(C)로 드라이버 구현 확인](#사용자-프로그램-c로-드라이버-구현-확인)  
   - [멀티 프로세서 환경에서 뮤텍스 실행 확인](#멀티-프로세서-환경에서-뮤텍스-실행-확인)
4. [프로젝트의 주요 구현방안](#4-프로젝트의-주요-구현방안)  

---

## 1. 프로젝트 소개

### 1.1. 프로젝트 개요
- `scull driver`는 문자 기반 드라이버로, Linux 커널에서 드라이버 개발 및 커널 모듈 프로그래밍을 교육용으로 사용되거나 디버깅 용도로 활용됨.
- 메모리에 데이터를 저장하거나 가져오는 작은 고립된 블록을 통해 가상의 문자 디바이스를 만듦.
- 가상의 문자 디바이스를 통해 사용자 공간 프로세스와 커널 간의 데이터 송수신을 수행.

### 1.2. 프로젝트 목적  
이 프로젝트의 최종 목표는 **SCULL 드라이버를 개발**하고, Linux 셸 명령어와 사용자 애플리케이션을 통해 드라이버에 데이터를 읽고 쓰는 과정을 확인하며 **드라이버의 동작 원리를 이해**하는 것.

### 1.3. 개발 환경
- **사용 언어:** C  
- **운영 체제:** Ubuntu 22.04  
- **가상화 툴:** VirtualBox 7.0  

### 1.4. 파일 설명
| 파일명     | 설명 |
|------------|--------------------------------------|
| `fops`     | 디바이스 파일의 동작(예: 읽기, 쓰기)을 정의하며, 사용자 요청을 처리함. |
| `main.c`   | 드라이버의 초기화 및 종료 로직을 담당하며, 커널에 드라이버를 등록함. |
| `project1.c` | `scull0` 디바이스의 `open`, `write`, `read`, `close` 동작을 구현함. |

---

## 2. Linux Device Driver Architecture

<details>
<summary>🖼️ 이미지 보기</summary>

<img src="https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/88d06841-e0b4-443e-b4bb-27c79494352a" width=65%/>
<img src="https://github.com/Chochanguk/Embeded-System-Scull-driver/assets/119058637/eccf5199-9670-411e-bf14-51e5f251138a" width=30%/>

</details>

- User Application에서 파일 입출력 함수 사용 시 `SWI`(Software Interrupt)가 실행됨.
- SWI Handler가 File System에 접근하고, 해당 Device Driver를 통해 요청을 처리함.
- **Block Device**  
  - 데이터를 한 번 읽을 때 **큰 Block 단위**로 가져오며, 추가 데이터를 **버퍼에 저장**함.  
  - 대량의 데이터를 처리할 수 있고, 데이터는 **Block Size 단위로 캐싱**됨.  
  - (사용 예: HDD, SSD 등)  
- **Character Device**  
  - 데이터를 **문자 단위**로 읽고 쓰며, **순차적으로 처리**함.  
  - (사용 예: 터미널, 마우스, 키보드, 프린터 등)  
- **MAJOR# / MINOR#**  
  - `MAJOR#`: 디바이스 드라이버의 **고유 식별 번호**  
  - `MINOR#`: 해당 `MAJOR#` 내에서 특정 디바이스를 나타냄.  
- **커널의 동작 방식**  
  - 특정 디바이스 파일이 열릴 때, 해당 `file_operations` 구조체에서 인스턴스를 찾아 사용함.

<details>
<summary>🖼️ 디바이스 드라이버 구조</summary>

<img src="https://github.com/user-attachments/assets/75b915f8-0051-4ef9-b2dc-3ad45638ee6c">

</details>

---

## 3. Implementation Description

### <a id="make-compiling-the-source-code"></a> 3.1. make (Compiling the source code)

<details>
<summary>🖼️ 코드 보기</summary>
<img src="https://github.com/user-attachments/assets/d003c728-2d70-4192-a69d-367edf667f21">
</details>

<details>
<summary>📜 설명 보기</summary>

- `make`는 `Makefile`을 읽어 빌드 프로세스를 자동화함.
- 커널 빌드 시스템을 호출하여 **캐릭터 디바이스 모듈을 빌드**함.

</details>

---

### <a id="shell-script-insmod-and-mknode"></a> 3.2. Shell Script (insmod and mknode)

<details>
<summary>🖼️ 코드 보기</summary>

<img src="https://github.com/user-attachments/assets/7ac720f6-b22b-4c3f-8ce2-df38139654e6">
</details>

<details>
<summary>📜 설명 보기</summary>

- 디바이스 파일은 **커널 모듈과 사용자 프로그램 간의 인터페이스** 역할을 수행.
1. 모듈 정보 정의 (Read/Write 권한 설정)
2. `insmod`를 사용하여 `scull.ko`를 커널에 로드
3. `main.c`의 `register_chdev`를 통해 **동적 MAJOR# 할당**
4. `mknod`를 이용하여 `/dev/scullN` 디바이스 파일 생성

</details>

---

### <a id="사용자-프로그램-c로-드라이버-구현-확인"></a> 3.3. 사용자 프로그램(C)로 드라이버 구현 확인

<details>
<summary>🖼️ 이미지 보기</summary>
<img src="https://github.com/user-attachments/assets/48ca5657-d9de-4af2-b48f-f3d8ec3e5e09">
</details>

---

### <a id="멀티-프로세서-환경에서-뮤텍스-실행-확인"></a> 3.4. 멀티 프로세서 환경에서 뮤텍스 실행 확인

<details>
<summary>🖼️ 이미지 보기</summary>
<img src="https://github.com/user-attachments/assets/f36cb79b-9f95-4c57-b3e9-4e2ad082d07a">
</details>

---

## 4. 프로젝트의 주요 구현방안

1. `kmalloc`을 통한 **동적 할당**으로 **메모리 효율성 증가**  
2. **양방향 연결 리스트**를 이용하여 삽입/삭제 시 **탐색 시간 단축**  
3. **Mutex**를 활용하여 **동시성 제어**, 다중 프로세스 환경에서 **데드락 방지**  

