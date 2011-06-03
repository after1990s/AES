/*
 ============================================================================
 Name        : main.c
 Author      : wqj
 Version     : 0.1
 Copyright   : Your copyright notice
 Description : Ansi-style
 ============================================================================
 */

#include "common.h"
#include "aes.h"

int main(int argc, char *argv[]) {
	/*一次读入两倍与加密类型到数据，分配给两个线程，都结束后，一起写入,住函数要设定加密类型，读入密钥和明文或密文f,程序出错后，不能在磁盘留下任何建立的
	 * 文件(使用atexit函数）*
	 * 参数 -e 加密文件，密钥从key文件读入
	 * 参数 -k 输入字符，生成key文件
	 * 参数 -d 解密文件，密钥从key文件读入
	 * key文件开头记录密钥长度
	 * */

	clock_t begin, end;
	begin = times((struct tms *)NULL);

	/*128 testing*/
/*	unsigned char key[60][4] = {{0x2b,0x7e,0x15,0x16},{0x28,0xae,0xd2,0xa6},{0xab,0xf7,0x15,0x88},{0x09,0xcf,0x4f,0x3c}};
	unsigned char input[4][4] = {{0x32,0x43,0xf6,0xa8},{0x88,0x5a,0x30,0x8d},{0x31,0x31,0x98,0xa2},{0xe0,0x37,0x07,0x34}};
	AES_INFO all_input_first, all_input_second;
	KEY_INFO key_input;
	key_input.key = key;
	key_input.begin = key;
	key_input.type = BIT_128;
	all_input_first.key_info = &key_input;
	all_input_first.input = input;
	all_input_first.type = BIT_128;
	key_expansion_wrap(&key_input);
	aes_encrypt((void *)&all_input_first);
*/
	if (argc == 1){
		printf("aes [OPTION] [FILENAME]\n-e	encrypt file, read key from file \"key\"\n-d	decrypt file, read key from file \"key\"\n-k	create file \"key\"\n--destroy-key	destroy key file,didn't need filename\n");
		exit(0);
	}
	if (strncmp(argv[1],"-k",2) == 0){
		create_key_file();
	}
	else if (strncmp(argv[1],"-e",2) == 0){
		if (argc != 3){
			printf("you must input filename");
			exit (0);
		}
		aes_encrypt_wrap (argv[2]);

	}
	else if (strncmp(argv[1],"-d",2) == 0){
		if (argc != 3){
					printf("you must input filename");
					exit (0);
				}
		inv_aes_encrypt_wrap(argv[2]);
	}
	else if (strncmp(argv[1],"--destroy-key",13)==0){
		destroy_key();
	}
	else {
		printf("aes [OPTION] [FILENAME]\n-e	encrypt file, read key from file \"key\"\n-d	decrypt file, read key from file \"key\"\n-k	create file \"key\"\n	--destroy-key destroy key file\n");
		exit(0);
	}

	end = times(NULL);
	printf("%ld0ms\n", end - begin);
	printf("DONE \n");

   return 0;
}
