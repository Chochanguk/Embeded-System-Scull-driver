# 커널 빌드 시스템에 의해 호출된 경우
ifneq ($(KERNELRELEASE),)
    # 커널 컴파일러 플래그를 설정
    # -std=gnu99: GNU99 표준을 사용하여 컴파일
    # -DENABLE_DEBUG: 디버깅을 활성화하는 매크로 정의
    ccflags-y := -std=gnu99 -DENABLE_DEBUG

    # SCULL 모듈에 포함될 개별 오브젝트 파일 지정
    scull-objs := main.o fops.o

    # SCULL 모듈을 빌드하도록 설정
    obj-m := scull.o

# 커널 빌드 시스템이 아닌 사용자가 직접 호출한 경우
else
    # 현재 사용하는 커널 소스 디렉토리 설정
    KERNELDIR ?= /lib/modules/$(shell uname -r)/build

    # 현재 작업 디렉토리를 PWD에 저장
    PWD := $(shell pwd)

    # 'modules' 타겟: 커널 모듈을 빌드
.PHONY: clean
modules:
	# 커널 빌드 시스템을 호출하여 모듈 빌드 수행 (C 옵션: 캐릭터 디바이스 드라이버)
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

# 'clean' 타겟: 빌드된 파일들을 삭제
.PHONY: clean
clean:
	# 커널 빌드 시스템을 호출하여 빌드 파일 정리
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

# main.o와 fops.o 컴파일 시 디버깅 활성화를 위한 플래그 설정
CFLAGS_main.o := -DDEBUG
CFLAGS_fops.o := -DDEBUG
