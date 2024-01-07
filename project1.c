#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/scull0"  // scull 디바이스 파일 경로

int main() {
    int file_descriptor;
    char buffer[100];

    // 디바이스 파일 열기
    file_descriptor = open(DEVICE_FILE, O_RDWR);
    if (file_descriptor < 0) {
        perror("Failed to open the device file");
        exit(EXIT_FAILURE);
    }

    // 디바이스에 데이터 쓰기
    printf("Enter data to write to the device: ");
    scanf("%s", buffer);

    if (write(file_descriptor, buffer, sizeof(buffer)) < 0) {
        perror("Failed to write to the device");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    // 디바이스에서 데이터 읽기
    if (read(file_descriptor, buffer, sizeof(buffer)) < 0) {
        perror("Failed to read from the device");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    printf("Data read from the device: %s\n", buffer);

    // 디바이스 파일 닫기
    close(file_descriptor);

    return 0;
}