#ifndef __AES_KEY_H
#define __AES_KEY_H
#define E_LENGTH 128
#define BIT_128_LOOP_START 3
#define BIT_128_LOOP_END 42/*43-1*/
#define BIT_192_LOOP_START 5
#define BIT_192_LOOP_END 50/*51-1*/
#define BIT_256_LOOP_START 7
#define BIT_256_LOOP_END 58/*59-1*/

#define BIT_256_ENCRYPT_LOOP_STEP 13
#define BIT_192_ENCRYPT_LOOP_STEP 11
#define BIT_128_ENCRYPT_LOOP_STEP 9
#define PLAIN_TEXT_LENGTH 128

#define SUB_BYTE_START 0
#define SUB_BYTE_END 16
#define SWAP(A,B,T) T=B;B=A;A=T;
#include "common.h"

//#define HOMEWORK
enum encrypt_class {BIT_128, BIT_192, BIT_256};
typedef enum encrypt_class E_CLASS;
struct key_inform{
	unsigned char (*key)[4];/*调入密钥扩展前填写*/
	unsigned char (*begin)[4];/*调入密钥扩展前填写*/
	unsigned int key_loop;/*调入密钥扩展前不填写*/
	//unsigned int loop;
	E_CLASS type;/*调入密钥扩展前填写*/

};
typedef struct key_inform KEY_INFO;
struct aes_inform{
	unsigned char (*input)[4];/*/*调入加密前填写，行优先排列[4][4]*/
	//unsigned char (*key)[4];//？？？？？看起来不需要
	unsigned int loop;/*调入加密前不填写*/
	E_CLASS type;/*调入加密前填写*/
	const KEY_INFO *key_info;/*调入加密前填写*/
};

typedef struct aes_inform AES_INFO;
extern unsigned char s_box[256];
extern unsigned char inv_s_box[256];
extern unsigned char mix_colum[4][4];
extern unsigned char inv_mix_colum[4][4];
extern char processing_filename[100];
extern unsigned long int t0[256];
extern unsigned long int t1[256];
extern unsigned long int t2[256];
extern unsigned long int t3[256];
/*key expansion related function*/
/*从0算起，loop最小是3，type为BIT_128最多43，BIT_192最多51，BIT_256最多59*/
void create_key_file(void);
void sig_alrm(int sigo);
void key_expansion_wrap(KEY_INFO *key_info);
	/*每次扩展四轮*/
	void key_expansion(unsigned char (*key)[4], E_CLASS type, unsigned int loop);
/* 参数 all_input是 AES_INFO类型, 返回 char *input，即加密后到内容*/
void aes_encrypt_wrap (char *input_filename);
	void xor_16bytes(void *left, void *right);
	void *aes_encrypt (void *input);/*input应该填写好加密类型，密钥指针，明文快*/
		void sub_bytes_shift_rows (AES_INFO *all_input);
		void add_round_key (AES_INFO *all_input);
	/*	void shift_rows(AES_INFO *all_input); */
		void mix_columns(AES_INFO *all_input);
			unsigned char aes_mul (int a, int b);
void inv_aes_encrypt_wrap (char *filename);
	void *inv_aes_encrypt (void *input);
		/*void add_round_key (AES_INFO *all_input);*/
		void inv_shift_rows(AES_INFO *all_input);
		void inv_mix_columns(AES_INFO *all_input);
		void inv_sub_bytes (AES_INFO *all_input);

void destroy_key(void);



#endif
