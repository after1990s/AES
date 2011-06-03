#ifndef __COMMON_H
#define __COMMON_H
#define MAXQSIZE 100
#define __USE_GNU 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <sys/inotify.h>
#include <pthread.h>
enum boolean {FALSE, TRUE};
typedef enum boolean BOOL;
typedef struct {
	int *base;
	int front;
	int rear;
} sq_queue;
void Error_report (const char *err_msg);
/*queue operation*/
void Q_init (sq_queue *Q);
void En_queue (sq_queue *Q, int elem);
int De_queue (sq_queue *Q);
void Q_destroy (sq_queue *Q);


/*address convert function*/
int Inet_aton (char *strptr, struct in_addr *addrptr);
char *Inet_ntoa (struct in_addr inaddr);
int Inet_pton (int family, char *strptr, void *addrptr);
const char *Inet_ntop (int family, void *src, char *dst, socklen_t size);

/*Basic socket API*/
int Socket (int family, int type, int protocol);
int Connect (int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
int Bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen (int sockfd, int backlog);
int Accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);

/*files and Dirs*/
int Stat (const char *pathname, struct stat *buf);
int Fstat (int filedes, struct stat *buf);
int Lstat (const char *pathname, struct stat *buf);
DIR *Opendir (const char *pathname);
int Chdir (const char *pathname);

/*pthread class function */
int Pthread_equal (pthread_t tid1, pthread_t tid2);
pthread_t Pthread_self (void);
int Pthread_create (pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void* arg);
void Pthread_exit (void *rval_ptr);
int Pthread_join (pthread_t thread, void **rval_ptr);
int Pthread_cancel (pthread_t tid);
int Pthread_detach (pthread_t tid);
int Pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int Pthread_mutex_destroy (pthread_mutex_t *mutex);
int Pthread_mutex_lock (pthread_mutex_t *mutex);
int Pthread_mutex_trylock (pthread_mutex_t *mutex);
int Pthread_mutex_unlock (pthread_mutex_t *mutex);


/*fopen*/
FILE *Fopen(const char *filename, const char *mode);
#endif
