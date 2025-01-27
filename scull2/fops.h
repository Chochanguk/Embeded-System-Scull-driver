#ifndef _FOPS_H
#define _FOPS_H

//  다른 파일에서 호출될 수 있도록 extern 키워드 사용

// 1.1. inode: 디바이스 파일의 inode 구조체 포인터.
// 1.2. filp: 파일 구조체 포인터로, 디바이스 파일의 정보를 포함.

// 1. 디바이스 파일을 열 때 호출.
// 주요 작업: 디바이스 초기화 및 필요 시 데이터를 초기화합니다.
extern int scull_open(struct inode *inode, struct file *filp);

// 2. 디바이스 파일을 닫을 때 호출됩니다.
//주요 작업: 디바이스와 관련된 리소스를 해제하거나 정리합니다.
extern int scull_release(struct inode *inode, struct file *filp);

// 3. 디바이스에서 데이터를 읽어 사용자 영역으로 복사.
//copy_to_user를 사용해 커널 공간 데이터를 사용자 공간으로 복사합니다.
extern ssize_t scull_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);

// 4. 사용자로부터 데이터를 받아 디바이스에 저장합니다.
// copy_from_user를 사용해 사용자 데이터를 커널 공간으로 복사하고, 디바이스에 저장합니다.
extern ssize_t scull_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);

// 5. 디바이스에 저장된 모든 데이터를 초기화합니다
// 디바이스의 모든 데이터 블록을 제거하고 메모리를 해제합니다.
extern void scull_trim(struct scull_dev *dev);

#endif
