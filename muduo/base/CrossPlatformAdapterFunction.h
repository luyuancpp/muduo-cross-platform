#ifndef CROSSPLATFORM_ADAPTER_FUNCTION_H
#define CROSSPLATFORM_ADAPTER_FUNCTION_H

#include <thread>

#include <muduo/base/Types.h>



#ifdef __linux__
#include <sys/types.h>
#include <sys/time.h>
#define auto_ptr unique_ptr
#endif // __linux__


//////////////////////WIN32/////////////////////////////////
#ifdef  WIN32
#pragma warning(disable:4068)
//head
#include <WS2tcpip.h>
#include <Windows.h>

#include <errno.h>
#include <io.h>
#include <process.h>
#include <string.h>
#include <stdio.h>  
#include <time.h>

#include <string>
#include <cstdint>
#include <cstdio>

//lib
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <Dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")

//function
#define S_ISREG(m) (((m) & 0170000) == (0100000))
#define S_ISDIR(m) (((m) & 0170000) == (0040000))

#define __builtin_expect(EXP, C)  (EXP)
#undef min
#undef max
#define timegm _mkgmtime

#define eventfd(initval, flags) sockets::createNonblockingOrDie(AF_INET)
#define timerfd_create(clockid, flags) muduo::net::sockets::createNonblockingOrDie(AF_INET)


#define SOL_TCP 0
#define TCP_INFO 0

//type 
#define ssize_t std::size_t
#define pid_t int32_t
#undef off_t
#define off_t std::size_t
#define sa_family_t int32_t
#define rlim_t uint64_t
typedef uint64_t uid_t;
typedef uint32_t in_addr_t;



//keyword
#define __thread __declspec( thread )
#define O_CLOEXEC 0
#define RLIMIT_AS 0
#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH
#define SSIZE_MAX 2147483647L
#define __MAX_ALLOCA_CUTOFF	65536
#undef POLLRDHUP
#define POLLRDHUP 0
#define EFD_NONBLOCK FIONBIO
#define EFD_CLOEXEC 0
#define CLOCK_MONOTONIC 0
#define TFD_NONBLOCK FIONBIO
#define TFD_CLOEXEC 0
#undef POLLPRI
#define POLLPRI 0
#define  SOCK_NONBLOCK 0
#define  SOCK_CLOEXEC 0


//struct 
struct iovec {
	void  *iov_base;    /* Starting address */
	ssize_t iov_len;     /* Number of bytes to transfer */
};

struct rlimit {
	rlim_t rlim_cur;  /* Soft limit */
	rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */
};

struct itimerspec {
	struct timespec it_interval;  /* Interval for periodic timer */
	struct timespec it_value;     /* Initial expiration */
};



//class 




//function
void setbuffer(FILE *stream, char *buf, size_t size);

char * strerror_r(int errnum, char *buf, size_t buflen);



size_t fwrite_unlocked(const void *ptr, size_t size, size_t n, FILE *stream);

struct tm *gmtime_r(const time_t *timep, struct tm *result);

int gettimeofday(struct timeval *tv, struct timezone *tz);

int gethostbyname_r(const char *name,
	struct hostent *ret, char *buf, size_t buflen,
	struct hostent **result, int *h_errnop);

/* Swap bytes in 16 bit value.  */
#define __bswap_constant_16(x) \
	((unsigned short int)((((x) >> 8) & 0xffu) | (((x) & 0xffu) << 8)))

/* Swap bytes in 32 bit value.  */
#define __bswap_constant_32(x) \
     ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >>  8) |	      \
      (((x) & 0x0000ff00u) <<  8) | (((x) & 0x000000ffu) << 24))

static __inline unsigned int
__bswap_32(unsigned int __bsx)
{
	return __bswap_constant_32(__bsx);
}

/* Swap bytes in 64 bit value.  */
# define __bswap_constant_64(x) \
     ((((x) & 0xff00000000000000ull) >> 56)				      \
      | (((x) & 0x00ff000000000000ull) >> 40)				      \
      | (((x) & 0x0000ff0000000000ull) >> 24)				      \
      | (((x) & 0x000000ff00000000ull) >> 8)				      \
      | (((x) & 0x00000000ff000000ull) << 8)				      \
      | (((x) & 0x0000000000ff0000ull) << 24)				      \
      | (((x) & 0x000000000000ff00ull) << 40)				      \
      | (((x) & 0x00000000000000ffull) << 56))

static __inline uint64_t
__bswap_64(uint64_t __bsx)
{
	return __bswap_constant_64(__bsx);
}

static __inline unsigned short int
__bswap_16(unsigned short int __bsx)
{
	return __bswap_constant_16(__bsx);
}

# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define htobe16(x) __bswap_16 (x)
#  define htole16(x) __uint16_identity (x)
#  define be16toh(x) __bswap_16 (x)
#  define le16toh(x) __uint16_identity (x)

#  define htobe32(x) __bswap_32 (x)
#  define htole32(x) __uint32_identity (x)
#  define be32toh(x) __bswap_32 (x)
#  define le32toh(x) __uint32_identity (x)

#  define htobe64(x) __bswap_64 (x)
#  define htole64(x) __uint64_identity (x)
#  define be64toh(x) __bswap_64 (x)
#  define le64toh(x) __uint64_identity (x)

# else
#  define htobe16(x) __uint16_identity (x)
#  define htole16(x) __bswap_16 (x)
#  define be16toh(x) __uint16_identity (x)
#  define le16toh(x) __bswap_16 (x)

#  define htobe32(x) __uint32_identity (x)
#  define htole32(x) __bswap_32 (x)
#  define be32toh(x) __uint32_identity (x)
#  define le32toh(x) __bswap_32 (x)

#  define htobe64(x) __uint64_identity (x)
#  define htole64(x) __bswap_64 (x)
#  define be64toh(x) __uint64_identity (x)
#  define le64toh(x) __bswap_64 (x)
# endif

ssize_t pread(int fd, void *buf, size_t count, off_t offset);

ssize_t winreadsock(int fd, void *buf, size_t count);

ssize_t winwritesock(int fd, const void *buf, size_t count);

ssize_t winclosesock(int fd);

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

void bzero(void *s, size_t n);

char *basename(const char* full_path);

int nanosleep(const struct timespec *req, struct timespec *rem);

int setrlimit(int resource, const struct rlimit *rlim);

int timerfd_settime(int fd, int flags,
	const struct itimerspec *new_value,
	struct itimerspec *old_value);

unsigned int sleep(unsigned int seconds);

int poll(struct pollfd *fds, size_t nfds, int timeout);

uid_t geteuid();

struct tcp_info {
    typedef uint32_t __u8;
    typedef uint32_t __u32;
    typedef uint64_t __u64;
    __u8	tcpi_state;		   //tcp state: TCP_SYN_SENT,TCP_SYN_RECV,TCP_FIN_WAIT1,TCP_CLOSE etc
    __u8	tcpi_ca_state;     //congestion state��
    __u8	tcpi_retransmits;  //�ش�������ʾ��ǰ���ش��İ��������ֵ���ش���Ϻ�����
    __u8	tcpi_probes;		///* ������ʱ���򱣻ʱ��������δȷ�ϵĶ���*/
    __u8	tcpi_backoff;		//�������������ʱ������һ�����ֵ��ָ���˱��㷨ָ�����ڴ��ͳ�ʱ�ǻ������
    __u8	tcpi_options;		//tcpͷ��ѡ���Ƿ��������չ���ӡ�ʱ�����MSS������
    __u8	tcpi_snd_wscale : 4, tcpi_rcv_wscale : 4; //��չ������ֵ
    __u8	tcpi_delivery_rate_app_limited : 1;  //���ٱ�־

    __u32	tcpi_rto;		//�ش���ʱʱ�䣬�����RTT�й�ϵ��RTTԽ��rtoԽ��
    __u32	tcpi_ato;		//������ʱȷ�ϵĹ�ֵ����λΪ΢��. 
                            //���յ�TCP����ʱ������ݱ������ϴν��յ�ʱ�������������ƣ��������ӳ�ȷ�϶�ʱ��Ҳ�����
                            //�����޸ĸ�ֵ
    __u32	tcpi_snd_mss;	// ���˵�MSS
    __u32	tcpi_rcv_mss;	// �Զ˵�MSS

    __u32	tcpi_unacked;	//δȷ�ϵ����ݶ���
    __u32	tcpi_sacked;    //2�����壺server����listen�׶Σ����Խ������ӵ��������յ���SACK��������
    __u32	tcpi_lost;		//�����ڷ��ͳ�ȥ����ʧ�ı��������ش���ɺ�����
    __u32	tcpi_retrans;   /* �ش���δȷ�ϵ����ݶ��� */
    __u32	tcpi_fackets;

    /* Times. */
    __u32	tcpi_last_data_sent;	//��ǰʱ��-���һ�����ķ���ʱ�䣬��λ�Ǻ���
    __u32	tcpi_last_ack_sent;     /* δʹ��*/
    __u32	tcpi_last_data_recv;	//��ǰʱ��-����������ݰ���ʱ�䣬��λ�Ǻ���
    __u32	tcpi_last_ack_recv;     //��ǰʱ��-�������ack��ʱ�䣬��λ�Ǻ���

    /* Metrics. */
    __u32	tcpi_pmtu;			/* ���һ�θ��µ�·��MTU */
    __u32	tcpi_rcv_ssthresh;   //��ǰ���մ��ڵĴ�С
    __u32	tcpi_rtt;			//smoothed round trip time,΢��	
    __u32	tcpi_rttvar;		//����RTT��ƽ��ƫ���ֵԽ��˵��RTT����Խ��
    __u32	tcpi_snd_ssthresh;  //ӵ����������ʼ��ֵ
    __u32	tcpi_snd_cwnd;		//ӵ�����ƴ��ڴ�С
    __u32	tcpi_advmss;		//���˵�MSS����
    __u32	tcpi_reordering;	/* û�ж���ʱ������������������ݶ��� */

    __u32	tcpi_rcv_rtt;		// ��Ϊ���նˣ������RTTֵ����λΪ΢��. ���ֵ���ǶԷ����㲢���͹�����rtt��������Ϊ���նˣ���û�������ݵ������
                                // ͨ�����շ��Ͷ˷��͵����ݵ��������õ���rttֵ�������ݷ��ͷ���������������ݣ����ֵһ�������Ϊ0��
    __u32	tcpi_rcv_space;		/* ��ǰ���ջ���Ĵ�С */

    __u32	tcpi_total_retrans;  //ͳ�����ش��İ���������������

    __u64	tcpi_pacing_rate;		//��������
    __u64	tcpi_max_pacing_rate;	//��������ʣ�Ĭ����unlimited������ͨ��SO_MAX_PACING_RATE������
    __u64	tcpi_bytes_acked;    /* RFC4898 tcpEStatsAppHCThruOctetsAcked */
    __u64	tcpi_bytes_received; /* RFC4898 tcpEStatsAppHCThruOctetsReceived */
    __u32	tcpi_segs_out;	     /* RFC4898 tcpEStatsPerfSegsOut */
    __u32	tcpi_segs_in;	     /* RFC4898 tcpEStatsPerfSegsIn */

    __u32	tcpi_notsent_bytes;
    __u32	tcpi_min_rtt;
    __u32	tcpi_data_segs_in;	/* RFC4898 tcpEStatsDataSegsIn */
    __u32	tcpi_data_segs_out;	/* RFC4898 tcpEStatsDataSegsOut */

    __u64   tcpi_delivery_rate;

    __u64	tcpi_busy_time;      /* Time (usec) busy sending data */
    __u64	tcpi_rwnd_limited;   /* Time (usec) limited by receive window */
    __u64	tcpi_sndbuf_limited; /* Time (usec) limited by send buffer */
};

int getsockopt(int sockfd, int level, int optname,
    int *optval, socklen_t *optlen);
void setsockopt(int sockfd, int level, int optname,
    int *optval, socklen_t optlen);
int getsockopt(int sockfd, int level, int optname,
    tcp_info *optval, socklen_t *optlen);
int accept4(int sockfd, struct sockaddr *addr,
    socklen_t *addrlen, int flags);

namespace muduo
{
    namespace ProcessInfo
    {

        std::string hostname();
    }

}//namespace muduo

#endif//WIN32




#endif // !CROSSPLATFORM_ADAPTER_FUNCTION_H

	
