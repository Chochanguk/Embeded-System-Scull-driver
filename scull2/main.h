// 헤더 가드 => 동일한 헤더 파일의 내용을 중복 방지
// pragma once와 같음. ( 컴파일러마다 안될 경우도 있어서 헤더 가드로 작성)
#ifndef _MAIN_H //main.h의 identifier
#define _MAIN_H

// 리눅스 커널에서 제공하는 이중 연결 리스트(double linked list) 지원 헤더 파일
#include <linux/list.h>			/* 디바이스 데이터 블록을 연결리스트로 관리 */

#define MODULE_NAME		"scull"
#define SCULL_NR_DEVS		3
#define SCULL_BLOCK_SIZE	PAGE_SIZE		// one page per block

struct scull_block {
	loff_t offset;
	char data[SCULL_BLOCK_SIZE];
	struct list_head block_list;
};

struct scull_dev {
	int block_counter;		//record how many blocks now in the list
	struct mutex mutex;
	struct cdev cdev;
	struct list_head block_list;	//list of storage blocks
};

#endif
