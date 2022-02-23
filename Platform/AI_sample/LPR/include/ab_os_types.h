/**
 *   @brief Header file of ability OS basic type definition.
 *
 *   @file ab_os_types.h
 *
 *   @note Nothing.
*/

#ifndef _AB_OS_TYPES_H_
#define _AB_OS_TYPES_H_

/********************************************************************
 *    INCLUDE FILES
********************************************************************/
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>
#include <sys/epoll.h>
#include <string.h>
#include <sys/timeb.h>
#include <sys/time.h>
#include <signal.h>
// #include <math.h>


/********************************************************************
 *    MACRO CONSTANTS DEFINITIONS
********************************************************************/
#ifndef TRUE
    #define TRUE            1
#endif  /* TRUE */

#ifndef FALSE
    #define FALSE           0
#endif  /* FALSE */

#ifndef SUCCESS
    #define SUCCESS (0)
#endif /* SUCCESS */

#ifndef FAIL
    #define FAIL (-1)
#endif /* FAIL */

#ifndef NULL
    #define NULL    ((void *)0)
#endif /* NULL */

#define AB_OS_TIME_NS_UINT  1
#define AB_OS_TIME_US_UINT  (1000 * AB_OS_TIME_NS_UINT)
#define AB_OS_TIME_MS_UINT  (1000 * AB_OS_TIME_US_UINT)
#define AB_OS_TIME_S_UINT   (1000 * AB_OS_TIME_MS_UINT)

#define BIT_0               0x00000001
#define BIT_1               0x00000002
#define BIT_2               0x00000004
#define BIT_3               0x00000008
#define BIT_4               0x00000010
#define BIT_5               0x00000020
#define BIT_6               0x00000040
#define BIT_7               0x00000080
#define BIT_8               0x00000100
#define BIT_9               0x00000200
#define BIT_10              0x00000400
#define BIT_11              0x00000800
#define BIT_12              0x00001000
#define BIT_13              0x00002000
#define BIT_14              0x00004000
#define BIT_15              0x00008000
#define BIT_16              0x00010000
#define BIT_17              0x00020000
#define BIT_18              0x00040000
#define BIT_19              0x00080000
#define BIT_20              0x00100000
#define BIT_21              0x00200000
#define BIT_22              0x00400000
#define BIT_23              0x00800000
#define BIT_24              0x01000000
#define BIT_25              0x02000000
#define BIT_26              0x04000000
#define BIT_27              0x08000000
#define BIT_28              0x10000000
#define BIT_29              0x20000000
#define BIT_30              0x40000000
#define BIT_31              0x80000000

#define AB_OS_THREAD_NAME_MAX_SIZE 16
// #define BIT(x)              (1<<x)


/********************************************************************
 *    DATA TYPE DEFINITION
********************************************************************/
/**
 *   Return Type
**/
typedef enum _AB_OS_RESULT_E {
    AB_OS_OK                      = 0,        ///< ok without any failure/error

    ///< general error
    AB_OS_ERR_GENERAL             = -1,       ///< general error
    AB_OS_ERR_NOT_SUPPORT         = -2,       ///< not support

    AB_OS_ERR_INIT_FAIL           = -3,       ///< initial fail
    AB_OS_ERR_DEINIT_FAIL         = -4,       ///< de-initial fail
    ///< execute error
    AB_OS_ERR_NG                  = -10,      ///< general execution failure
    AB_OS_ERR_SYS                 = -11,      ///< operating system call failure
    AB_OS_ERR_DRV                 = -12,      ///< driver call failure
    AB_OS_ERR_NOT_ALLOW           = -13,      ///< not allow in this case
    AB_OS_ERR_ABORT               = -14,      ///< ignored or skipped.
    AB_OS_ERR_TIMEDOUT            = -15,      ///< timeout occured
    AB_OS_ERR_FAIL                = -19,      ///< already executed and failed
    AB_OS_ERR_WAITPID             = -20,      ///< execute waitpid status error

    AB_OS_ERR_MAX                 = 4294967295/*INT32_MAX*/
} AB_OS_RESULT_ET; ///< ability os error code type


typedef enum _AB_OS_WAIT_STATE_E {
    AB_OS_WAIT_STATE_WAIT_FOREVER = -1,       ///< waiting forever
    AB_OS_WAIT_STATE_NO_WAIT      = 0         ///< no waiting, execute immediately
} AB_OS_WAIT_STATE_ET;

/* exec */
typedef enum _AB_OS_EXEC_PIPE_E {
    AB_OS_EXEC_PIPE_OFF = 0,                  ///< execution pipe off
    AB_OS_EXEC_PIPE_ON  = 1,                  ///< execution pipe on
    AB_OS_EXEC_PIPE_MAX = 255                 ///< Max value for strcture aligment
} AB_OS_EXEC_PIPE_ET;

/**
 *   Thread Part
**/
typedef void *(*AB_OS_THREAD_FN)(void *arg);  ///< Thread function prototype

typedef struct _AB_OS_THREAD_S {
    char      sz_thread_name[AB_OS_THREAD_NAME_MAX_SIZE];       ///< name of thread
    uint32_t  b_is_detached;                                    ///< detached enable/disable
    //void*     pv_stack_start_addr;
    size_t    ui_stack_size;                                    ///< size of stack
    size_t    ui_guard_size;                                    ///< size of guard
    uint32_t  ui_priority;                                      ///< priority of thread
    uint32_t  b_set_scheduler;                                  ///< appoint scheduler or not. will use RR if set to 0.
    uint32_t  ui_scheduler;                                     ///< scheduler type. SCHED_NORMAL = 0, SCHED_FIFO = 1, SCHED_RR = 2, SCHED_BATCH = 3.
} AB_OS_THREAD_ST;

typedef struct _AB_OS_THREAD_CREATE_PARA_S {
    AB_OS_THREAD_ST s_thread_info;                              ///< struct of thread information
    AB_OS_THREAD_FN pfn_entry;                                  ///< callback function of thread
    void           *pv_para;                                    ///< parameter for callback function
} AB_OS_THREAD_CREATE_PARA_ST;

typedef struct _AB_OS_FLASH_INFO_S {
    uint64_t ul_size;                                           ///< mtd partion, total size, Byte
    uint32_t ui_erasesize;                                      ///< mtd partion, erase size, Byte
} AB_OS_FLASH_INFO_ST;

/**
 *   Semaphore Part
**/
#define AB_OS_SEMAPHORE_NAME_MAX_SIZE 32                        ///< max size of semephore name 

/**
 *   Semaphore Structure
**/
typedef struct _AB_OS_SEMAPHORE_S {
    char sz_sem_name[AB_OS_SEMAPHORE_NAME_MAX_SIZE];    ///< name of semaphore
    sem_t *ps_sem_t;                                    ///< the address of the new semaphore
} AB_OS_SEMAPHORE_ST;

/**
 *   Mutex Part
**/
typedef enum _AB_OS_MUTEX_PROTOCOL_E {
    AB_OS_MTX_PROTOCOL_NONE,                                    ///< Protocol None, PTHREAD_PRIO_NONE
    AB_OS_MTX_PROTOCOL_INHERIT,                                 ///< Protocol Inherit, PTHREAD_PRIO_INHERIT
    AB_OS_MTX_PROTOCOL_PROTECT                                  ///< Protocol Protect, PTHREAD_PRIO_PROTECT
} AB_OS_MUTEX_PROTOCOL_ET;


#define AB_OS_MTX_NAME_MAX_SIZE 32                              ///< max size of mutex name 

typedef struct _AB_OS_MUTEX_S {
    char                    sz_name[AB_OS_MTX_NAME_MAX_SIZE];   ///< name of mutex
    AB_OS_MUTEX_PROTOCOL_ET e_protocol;                         ///< Protocol type of mutex
    pthread_mutex_t         s_mutex;                            ///< file descriptor of mutex
} AB_OS_MUTEX_ST;

/**
 *   Event Part
**/
#define AB_OS_EVT_NAME_MAX_SIZE 32                              ///< max size of event name 

typedef enum _AB_OS_EVENT_OPTION_E {
    AB_OS_EVENT_OR,                                             ///< event option OR 
    AB_OS_EVENT_AND,                                            ///< event option AND
    AB_OS_EVENT_OR_CLEAR,                                       ///< event option OR & CLEAR
    AB_OS_EVENT_AND_CLEAR,                                      ///< event option AND & CLEAR
} AB_OS_EVENT_OPTION_ET;

typedef struct _AB_OS_EVENT_S {
    char            sz_name[AB_OS_EVT_NAME_MAX_SIZE];           ///< name of event
    pthread_mutex_t s_mutex;                                    ///< file descriptor of mutex                               
    pthread_cond_t  s_cond;                                     ///< file descriptor of condition
    uint32_t        ui_event_flag;                              ///< info of event flag
    uint32_t        ui_post_flag;                               ///< info of post flag
    uint32_t        ui_got_flag;                                ///< info of got flag
} AB_OS_EVENT_ST;

/**
 *   Init Part
**/

typedef enum _AB_OS_SIGNAL_E {
    AB_OS_SIGNAL_ID_SD_READONLY = 1,                               ///< Kernel Capture SD card mount as read-only signal
    AB_OS_SIGNAL_ID_MAX = 0xFFFFFFFF                               ///< Just Aligment 4Byte
} AB_OS_SIGNAL_ID_ET;


typedef struct _AB_OS_INIT_S {
     void(*signal_callback)(int value);                         ///< Process signal handle callback function
} AB_OS_INIT_ST;

typedef enum _AB_OS_INIT_FS_TYPE_E {
    AB_OS_INIT_FS_TYPE_ROOTFS1,                                      ///< To mount rootfs1, this is for read/write /etc purpose.
    AB_OS_INIT_FS_TYPE_ROOTFS2                                       ///< To mount rootfs2, this is for read/write /mnt/resource purpose.
} AB_OS_INIT_FS_TYPE_ET;


/**
 *   Ramdisk Part
**/
typedef enum _AB_OS_RAMDISK_RESULT_E {
    AB_OS_RAMDISK_RESULT_SUCCESS                        = 0,    ///< operation success
    AB_OS_RAMDISK_RESULT_CREATE_FOLDER_FAIL             = 1,    ///< create folder fail
    AB_OS_RAMDISK_RESULT_FAIL,                                  ///< operation fail
} AB_OS_RAMDISK_RESULT_ET;

/**
 *   FW upgrade Part
**/
typedef enum _AB_OS_FWUPGRADE_UTIL_RETURN_E {
    AB_OS_FWUPGRADE_UTIL_RETURN_SUCCESS     = 0,                ///< operation success
    AB_OS_FWUPGRADE_UTIL_RETURN_FAIL        = 1,                ///< operation fail
    AB_OS_FWUPGRADE_UTIL_RETURN_TOTAL,
} AB_OS_FWUPGRADE_UTIL_RETURN_ET;

typedef enum _AB_OS_FWUPGRADE_STATUS_E {
    AB_OS_FWUPGRADE_STATUS_IDLE                 = 0,            ///< firmware upgrade status idle
    AB_OS_FWUPGRADE_STATUS_UPDATE_SUCCESS       = 1,            ///< firmware upgrade status success
    AB_OS_FWUPGRADE_STATUS_CHECKING_SH256,
    AB_OS_FWUPGRADE_STATUS_CHECKING_SH256_FAIL,
    AB_OS_FWUPGRADE_STATUS_CHECKING_SH256_SUCCESS,
    AB_OS_FWUPGRADE_STATUS_UPDATING,
    AB_OS_FWUPGRADE_STATUS_CHECKING_PACKAGE,                    ///< firmware upgrade status check package
    AB_OS_FWUPGRADE_STATUS_CHECKING_PACKAGE_FAIL,               ///< firmware upgrade status check package fail
    AB_OS_FWUPGRADE_STATUS_CHECKING_PACKAGE_SIZETOOBIG,         ///< firmware upgrade status check package size
    AB_OS_FWUPGRADE_STATUS_CHECKING_PACKAGE_SUCCESS,            ///< firmware upgrade status check package success
    AB_OS_FWUPGRADE_STATUS_UPDATING_READ_FAIL,                  ///< firmware upgrade status updating read fail
    AB_OS_FWUPGRADE_STATUS_UPDATING_WRITE_VERIFY_FAIL,          ///< firmware upgrade status updating write verify fail
    AB_OS_FWUPGRADE_STATUS_UPDATE_FAIL,                         ///< firmware upgrade status fail
} AB_OS_FWUPGRADE_STATUS_ET;

typedef enum _AB_OS_FWUPGRADE_RESULT_E {
    AB_OS_FWUPGRADE_RESULT_SUCCESS              = 0,            ///< firmware upgrade success
    AB_OS_FWUPGRADE_RESULT_NOT_INIT             = -1,            ///< firmware upgrade no initialization
    AB_OS_FWUPGRADE_RESULT_FAIL                 = -2,           ///< firmware upgrade fail
    AB_OS_FWUPGRADE_RESULT_BIN_TOO_BIG          = -3,           ///< firmware upgrade FW.bin size is too big
    AB_OS_FWUPGRADE_RESULT_FAIL_FILE_NOT_EXIST  = -4            ///< firmware upgrade fail, FW.bin not exist
} AB_OS_FWUPGRADE_RESULT_ET;

typedef enum _AB_OS_FWUPGRADE_ROOTFS1_NEW_OLD_MODE_E {
    AB_OS_FWUPGRADE_ROOTFS1_KEEP_OLD              = 0,           ///< Need to keep old etc if fw upgrade success
    AB_OS_FWUPGRADE_ROOTFS1_TO_DEFAULT            = 1            ///< ignore old etc. like 
} AB_OS_FWUPGRADE_ROOTFS1_NEW_OLD_MODE_ET;


typedef enum _AB_OS_FWUPGRADE_CHK_BIN_E {
    AB_OS_FWUPGRADE_CHK_BIN_SUCCESS              = 0,            ///< firmware upgrade bin check ok
    AB_OS_FWUPGRADE_CHK_BIN_FAIL                 = -1,           ///< firmware upgrade bin check fail
    AB_OS_FWUPGRADE_CHK_BIN_SIZE_TOO_BIG         = -2,           ///< firmware upgrade bin file too big
    AB_OS_FWUPGRADE_CHK_BIN_SHA256_FAIL          = -3            ///< firmware upgrade bin sha256 mismatch
} AB_OS_FWUPGRADE_CHK_BIN_ET;

typedef enum _AB_OS_FLASH_CHECK_BAD_BLOCK_E {
    AB_OS_FLASH_CHECK_BAD_BLOCK_FALSE       = 0,                ///< check bad block false
    AB_OS_FLASH_CHECK_BAD_BLOCK_TRUE        = 1,                ///< check bad block true
} AB_OS_FLASH_CHECK_BAD_ET;

typedef enum _AB_OS_FLASH_GET_INFO_RESULT_E {
    AB_OS_FLASH_GET_INFO_SUCCESS                = 0,            ///< get infomation success
    AB_OS_FLASH_GET_INFO_OPEN_DEV_ERROR         = 1,            ///< get infomation open device error
    AB_OS_FLASH_GET_INFO_READ_DEV_ERROR         = 2,            ///< get infomation read device error
} AB_OS_FLASH_GET_INFO_RESULT_ET;

typedef enum _AB_OS_FLASH_ERASE_RESULT_E {
    AB_OS_FLASH_ERASE_SUCCESS               = 0,    ///< erase success
    AB_OS_FLASH_ERASE_DEV_OPEN_FAIL         = -1,   ///< device open fail
    AB_OS_FLASH_ERASE_DEV_GET_INFO_FAIL     = -2,   ///< device get info fail
    AB_OS_FLASH_ERASE_ADDR_INVALID          = -3,   ///< input address invalid
    AB_OS_FLASH_ERASE_OUT_OF_SIZE           = -4,   ///< erase size out of partition size
    AB_OS_FLASH_ERASE_ERASE_FAIL            = -5,   ///< erase fail
} AB_OS_FLASH_ERASE_RESULT_ET;

typedef enum _AB_OS_FLASH_WRITE_RESULT_E {
    AB_OS_FLASH_WRITE_SUCCESS               = 0,    ///< write success
    AB_OS_FLASH_WRITE_DEV_OPEN_FAIL         = -1,   ///< device open fail
    AB_OS_FLASH_WRITE_DEV_GET_INFO_FAIL     = -2,   ///< device get info fail
    AB_OS_FLASH_WRITE_OUT_OF_SIZE           = -3,   ///< write size out of partition size
    AB_OS_FLASH_WRITE_NO_MEM                = -4,   ///< memory alloc fail
    AB_OS_FLASH_WRITE_FAIL                  = -5,   ///< write fail
} AB_OS_FLASH_WRITE_RESULT_ET;

typedef enum _AB_OS_FLASH_READ_RESULT_E {
    AB_OS_FLASH_READ_SUCCESS               = 0,     ///< read success
    AB_OS_FLASH_READ_DEV_OPEN_FAIL         = -1,    ///< device open fail
    AB_OS_FLASH_READ_FAIL                  = -2,    ///< read fail
} AB_OS_FLASH_READ_RESULT_ET;

typedef enum _AB_OS_FLASH_FORCE_WRITE_RESULT_E {
    AB_OS_FLASH_FORCE_WRITE_SUCCESS               = 0,  ///< force write success
    AB_OS_FLASH_FORCE_WRITE_DEV_OPEN_FAIL         = -1, ///< device open fail
    AB_OS_FLASH_FORCE_WRITE_FAIL                  = -2, ///< force write success
} AB_OS_FLASH_FORCE_WRITE_RESULT_ET;

typedef int32_t (*AB_OS_EPOLL_CALLBACK_FUNC)(uint64_t);

typedef enum _AB_OS_FD_TYPE_E {
    AB_OS_FD_TYPE_EVENT,                                        ///< FD type event
    AB_OS_FD_TYPE_TIMER,                                        ///< FD type timer
    AB_OS_FD_TYPE_SIGNAL                                        ///< FD type signal
} AB_OS_FD_TYPE_ET;

typedef struct _AB_OS_EPOLL_FD_HANDLER_S {
    int                         ifd_monitor_fd;                 ///< file descriptor be monitored by epoll
    AB_OS_FD_TYPE_ET            e_fd_type;                      ///< file descriptor type
    AB_OS_EPOLL_CALLBACK_FUNC   pf_timer_cb;                    ///< callback function
    uint64_t                    ul_param;                       ///< parameter for callback function
} AB_OS_EPOLL_FD_HANDLER_ST;

typedef struct _AB_OS_EPOLL_S {
    int                   ifd_epoll_fd;                 ///< file descriptor of epoll
    int32_t               i_max_monitor_fd;             ///< maximum number of monitor file descriptor
    struct epoll_event    *ps_fd_events;                ///< total event pointer will be monitored
    int8_t                c_epoll_thread_run;           ///< enable/disable epoll thread
    int8_t                c_epoll_terminate;            ///< enable/disable epoll terminate
    AB_OS_THREAD_CREATE_PARA_ST s_timer_thread;         ///< epoll watcher thread create structure
    int8_t                c_thread_end;                 ///< wait thread finish
} AB_OS_EPOLL_ST;

typedef struct _AB_OS_TIMER_S {
    int                         ifd_timer_fd;           ///< file descriptor of timer
    int8_t                      *pc_timer_name;         ///< name of timer
    int8_t                      c_timer_enabled;        ///< enable/disable timer
    struct itimerspec           s_timer_value;          ///< value ot timer
    AB_OS_EPOLL_FD_HANDLER_ST   *ps_fd_handler;         ///< handle of epoll fd
    AB_OS_EPOLL_ST              s_epoll;                ///< epoll instance for timer
} AB_OS_TIMER_ST;

typedef int32_t (*AB_OS_NTP_CALLBACK_FUNC)(uint32_t);

/* Mmap */
typedef enum _AB_OS_MEM_MMAP_TYPE_E {
    AB_OS_MEM_MMAP_TYPE_RD,
    AB_OS_MEM_MMAP_TYPE_WR,
    AB_OS_MEM_MMAP_TYPE_RW,
} AB_OS_MEM_MMAP_TYPE_ET;

typedef enum _AB_OS_MEM_MMAP_FLAG_E {
    AB_OS_MEM_MMAP_FLAG_SHARED,
} AB_OS_MEM_MMAP_FLAG_ET;

typedef enum _AB_OS_MEM_MSYNC_FLAG_E {
    AB_OS_MEM_MSYNC_FLAG_MS_SYNC,
} AB_OS_MEM_MSYNC_FLAG_ET;

/**
 *   Utility Part
**/

/**
 *   Time Unit
**/
typedef enum _AB_OS_UTILITY_TIME_UNIT_T {
    AB_OS_UTILITY_TIME_UNIT_US  = 0x0,          ///< micro sec
    AB_OS_UTILITY_TIME_UNIT_MS  = 0x1,          ///< mini sec
    AB_OS_UTILITY_TIME_UNIT_S   = 0x2,          ///< sec
    AB_OS_UTILITY_TIME_UNIT_MAX = 0xFF
} AB_OS_UTILITY_TIME_UNIT_ET;

/**
 *   Log Part
**/
/**
 *   Log Level
**/
typedef enum _AB_OS_LOG_LEVEL_E {
    AB_OS_LOG_LEVEL_ERR     = 0x0,              ///< log level error           
    AB_OS_LOG_LEVEL_WRN     = 0x1,              ///< log level warning
    AB_OS_LOG_LEVEL_MSG     = 0x2,              ///< log level message
    AB_OS_LOG_LEVEL_DBG     = 0x3,              ///< log level debug
    AB_OS_LOG_LEVEL_MAX     = 0xff,
    _E_ = AB_OS_LOG_LEVEL_ERR,                  ///< abbreviation of log level error  
    _W_ = AB_OS_LOG_LEVEL_WRN,                  ///< abbreviation of log level warning
    _M_ = AB_OS_LOG_LEVEL_MSG,                  ///< abbreviation of log level message
    _D_ = AB_OS_LOG_LEVEL_DBG                   ///< abbreviation of log level debug
} AB_OS_LOG_LEVEL_ET;

/**
    Log Out Destination
*/
typedef enum _AB_OS_LOG_OUT_DEST_E {
    AB_OS_LOG_OUT_DEST_CONSOLE  = 0x1,          ///< log out destination - console 
    AB_OS_LOG_OUT_DEST_FILE     = 0x2,          ///< log out destination - file
    AB_OS_LOG_OUT_DEST_MAX      = 0xFF
} AB_OS_LOG_OUT_DEST_ET;

/**
 *   Debug Part
**/
/**
 *   ab os internal debug level
**/
typedef enum _AB_OS_DEBUG_MASK_E {
    AB_OS_DEBUG_MASK_EXEC     = BIT_0,          ///< debug mask exection (command)
    AB_OS_DEBUG_MASK_THREAD   = BIT_1,          ///< debug mask thread
    AB_OS_DEBUG_MASK_MTX      = BIT_2,          ///< debug mask mutex
    AB_OS_DEBUG_MASK_EVT      = BIT_3,          ///< debug mask event
    AB_OS_DEBUG_MASK_SEMA     = BIT_4,          ///< debug mask semaphore
    AB_OS_DEBUG_MASK_UTILITY  = BIT_5,          ///< debug mask utility
    AB_OS_DEBUG_MASK_INIT     = BIT_6,          ///< debug mask init
    AB_OS_DEBUG_MASK_MAX      = 0xFFFFFFFF
} AB_OS_DEBUG_MASK_ET;

typedef enum _AB_OS_DEBUG_LEVEL_E {
    AB_OS_DEBUG_LEVEL_ERR     = 0x0,             ///< debug level error   
    AB_OS_DEBUG_LEVEL_WRN     = 0x1,             ///< debug level warning
    AB_OS_DEBUG_LEVEL_MSG     = 0x2,             ///< debug level message
    AB_OS_DEBUG_LEVEL_DBG     = 0x3,             ///< debug level debug
    AB_OS_DEBUG_LEVEL_MAX     = 0xff
} AB_OS_DEBUG_LEVEL_ET;

/**
 *   ab os internal debug set options
**/
typedef enum _AB_OS_DEBUG_SET_OPTION_E {
    AB_OS_DEBUG_SET_ENABLE  = 0x0,              ///< debug set enable
    AB_OS_DEBUG_SET_DISABLE = 0x1               ///< debug set disable
} AB_OS_DEBUG_SET_OPTION_ET;

/********************************************************************
 *    GLOBAL (EXTERN) VARIABLES
********************************************************************/


/********************************************************************
 *    FUNCTION PROTOTYPES DECLARATIONS
********************************************************************/


#endif
