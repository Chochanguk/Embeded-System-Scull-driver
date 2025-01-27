#! /bin/bash
# 이 스크립트는 SCULL 커널 모듈을 로드하거나 언로드하기 위해 작성되었습니다.
# 로드 후 디바이스 파일을 생성하고, 필요시 언로드를 수행합니다.

module="scull"  # 커널 모듈 이름
device="scull"  # 디바이스 이름
mode="666"      # 디바이스 파일에 설정할 권한 (읽기/쓰기 모두 허용)
group=0         # 디바이스 파일의 소유 그룹 (기본값은 root 그룹)

# 커널 모듈을 로드하고 디바이스 파일을 생성하는 함수
function load() {
    # insmod 명령으로 커널 모듈을 삽입
    insmod ./$module.ko $* || exit 1

    # 기존에 생성된 디바이스 파일을 삭제하여 충돌 방지
    rm -f /dev/${device}[0-2]

    # /proc/devices 파일에서 SCULL 모듈의 메이저 번호를 가져옴
    major=$(awk -v device="$device" '$2==device {print $1}' /proc/devices)

    # 메이저 번호와 마이너 번호를 사용해 디바이스 파일 생성
    mknod /dev/${device}0 c $major 0  # 첫 번째 디바이스 파일
    mknod /dev/${device}1 c $major 1  # 두 번째 디바이스 파일
    mknod /dev/${device}2 c $major 2  # 세 번째 디바이스 파일

    # 생성된 디바이스 파일의 그룹을 설정 (기본 root 그룹)
    chgrp $group /dev/$device[0-2]

    # 생성된 디바이스 파일의 권한을 설정 (읽기/쓰기 허용)
    chmod $mode /dev/$device[0-2]
}

# 커널 모듈을 언로드하고 디바이스 파일을 삭제하는 함수
function unload() {
    # 디바이스 파일 삭제
    rm -f /dev/${device}[0-2]

    # rmmod 명령으로 커널 모듈 제거
    rmmod $module || exit 1
}

# 기본 동작은 "load"로 설정, 명령줄 인수를 통해 변경 가능
arg=${1:-"load"}

# 사용자로부터 전달받은 명령에 따라 작업 수행
case $arg in
    load)   # 모듈 로드 및 디바이스 파일 생성
        load ;;
    unload) # 모듈 언로드 및 디바이스 파일 삭제
        unload ;;
    reload) # 모듈을 재로드 (언로드 후 다시 로드)
        ( unload )
        load ;;
    *)      # 잘못된 명령어 입력 시 사용법 출력
        echo "Usage: $0 {load | unload | reload}"
        echo "Default is load"
        exit 1
        ;;
esac
