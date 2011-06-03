#include "common.h"

void Error_report (const char *err_msg)
{
	/*Developer use */
	fprintf(stderr, "%s:%s\n", err_msg, strerror(errno));
	/*User use*/
	//fprintf(stderr, "%s\n", err_msg);
}
/*queue operation*/
void Q_init (sq_queue *Q)
{
	if ((Q->base = (int *)malloc (MAXQSIZE * sizeof(int))) == NULL){
		Error_report ("have not enough virtual memory");
		exit (0);
	}
	Q->front = 0;
	Q->rear = 0;
}
void En_queue (sq_queue *Q, int elem)
{
	if ((Q->rear+1) % MAXQSIZE == Q->front){
		Error_report ("insert element at full queue");
		exit (0);
	}
	Q->base[Q->rear] = elem;
	Q->rear = (Q->rear +1) % MAXQSIZE;
}
int De_queue (sq_queue* Q)
{
	int r = Q->front;
	if (Q->front == Q->rear){
		Error_report ("queue empty");
		exit (0);
	}
	Q->front = (Q->front + 1) % MAXQSIZE;
	return Q->base[r];
}
void Q_destroy (sq_queue *Q)
{
	free (Q->base);
}


/*address convert nfunction*/
int Inet_aton (char *strptr, struct in_addr *addrptr)
{
	if (strptr == NULL)
		Error_report ("strptr should not be NULL");
	return inet_aton (strptr, addrptr);
}
char *Inet_ntoa (struct in_addr inaddr)
{
	return inet_ntoa (inaddr);
}
int Inet_pton (int family, char *strptr, void *addrptr)
{
	int result = inet_pton (family, strptr, addrptr);
	if (result == 0){
		Error_report ("illegeal network address");
		exit(0);
	}
	if (result == -1){
		Error_report ("network address convert failure");
		exit(0);
	}
	return result;
}
const char *Inet_ntop (int family, void *src, char *dst, socklen_t size)
{
	const char *result = inet_ntop (family, src,dst,size);
	if (result == NULL){
		Error_report ("network address convert failure");
		exit(0);
	}
	return result;
}

/*Basic socket API*/
int Socket (int family, int type, int protocol)
{
	int socketfd;
	switch(family){
		case AF_INET:
		case AF_INET6:
		case AF_LOCAL:
		case AF_ROUTE:
		case AF_KEY:
			break;
		default:
			Error_report("socket family error");
			exit(0);
	}
	switch(type){
		case SOCK_STREAM:
		case SOCK_DGRAM:
		case SOCK_SEQPACKET:
		case SOCK_RAW:
			break;
		default:
			Error_report("socket type error");
			exit(0);
	}
	if ((socketfd = socket (family, type, protocol)) == -1)
	{
		Error_report ("socket initallized error");
		exit(0);
	}
	return socketfd;
}

int Connect (int sockfd, struct sockaddr *serv_addr, socklen_t addrlen)
{
	int result;
	if ((result = connect (sockfd, serv_addr, addrlen)) == -1){
		Error_report ("connect fail");
		exit(0);
	}
	return result;
}
int Bind (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int status;
	if ((status = bind (sockfd, addr, addrlen)) == -1){
		Error_report ("bind error");
		exit(0);
	}
	return status;
}
int Listen (int sockfd, int backlog)
{
	int status;
	if ((status = listen (sockfd, backlog)) == -1){
		Error_report ("listen error");
		exit(0);
	}
	return status;
}
int Accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int accfd;
	if ((accfd = accept (sockfd, cliaddr, addrlen)) == -1){
		Error_report ("accept error");
		exit(0);
	}
	return accfd;
}


int Stat (const char *pathname, struct stat *buf)
{
	if (stat (pathname, buf)==-1){
		Error_report ("wrong pathname in function stat");
		exit(0);
	}
	return 0;
}


int Fstat (int filedes, struct stat *buf)
{
	if (fstat (filedes, buf) ==-1){
		Error_report ("fstat error");
		exit(0);
	}
	return 0;
}

int Lstat (const char *pathname, struct stat *buf)
{
	if (lstat (pathname, buf) == -1)
	{
		Error_report ("lstat error");
		exit(0);
	}
	return 0;
}

DIR *Opendir (const char *pathname)
{
	DIR *curpath;
	if ((curpath = opendir(pathname))==NULL){
		Error_report ("can't open dirctory");
		exit(0);
	}
	return curpath;
}

int Chdir (const char *pathname)
{
	if (chdir (pathname) <0){
		Error_report ("chdir failed");
		exit(0);
	}
	return 0;
}

/*pthread class function*/
int Pthread_equal (pthread_t tid1, pthread_t tid2)
{
	return pthread_equal (tid1, tid2);
}
pthread_t Pthread_self (void)
{
	return pthread_self();
}
int Pthread_create (pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg)
{
	int i;
	if ((i = pthread_create (tidp, attr, start_rtn, arg)) != 0){
		Error_report ("pthread error");
		exit (0);
	}
	return i;
}
void Pthread_exit (void *rval_ptr)
{
	pthread_exit (rval_ptr);
}

int Pthread_join (pthread_t thread, void **rval_ptr)
{
	int i;
	if ((i = pthread_join (thread, rval_ptr)) != 0){
		Error_report ("pthread_join error");
		if (i == EDEADLK) {
			printf("EDEADLK");
		}
		else if (i == EINVAL) {
			printf ("EINVAL");
		}
		else if (i == EINVAL) {
			printf("EINVAL");
		}
		else {
			printf("ESRCH");
		}
		exit (0);
	}

	return i;
}

int Pthread_cancel (pthread_t tid)
{
	int i;
	if ((i = pthread_cancel(tid)) != 0){
		Error_report ("pthread_cancel error");
		exit (0);
	}
	return i;
}

int Pthread_detach (pthread_t tid)
{
	int i;
	if ((i = pthread_detach (tid)) != 0){
		Error_report ("pthread_detach error");
		exit(0);
	}
	return i;
}

int Pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	int i;
	if ((i = pthread_mutex_init (mutex, attr)) != 0){
		Error_report ("pthread_mutex_init error");
		exit (0);
	}
	return i;
}

int Pthread_mutex_destroy (pthread_mutex_t *mutex)
{
	int i;
	if ((i = pthread_mutex_destroy (mutex)) != 0){
		Error_report ("pthread_mutex_destory error");
		exit (0);
	}
	return i;
}

int Pthread_mutex_lock (pthread_mutex_t *mutex)
{
	int i;
	if  ((i = pthread_mutex_lock (mutex)) != 0){
		Error_report ("pthread_mutex_lock error");
		exit (0);
	}
	return i;
}

int Pthread_mutex_trylock (pthread_mutex_t *mutex)
{
	int i;
	if ((i = pthread_mutex_trylock (mutex)) != 0){
		Error_report ("pthread_mutex_trylock error");
		exit (0);
	}
	return i;
}

int Pthread_mutex_unlock (pthread_mutex_t *mutex)
{
	int i;
	if ((i = pthread_mutex_unlock(mutex)) != 0){
		Error_report ("pthread_mutex_unlock error");
		exit (0);
	}
	return i;
}

/*streams function*/
FILE *Fopen(const char *filename, const char *mode)
{
	FILE *fp;
	if ((fp = fopen(filename, mode)) == NULL){
		printf("no such file:%s\n", filename);
		exit (0);
	}
	return fp;
}
