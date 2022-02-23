/**
 *   @brief Header file of ability OS API definition.
 *
 *   @file ab_os_api.h
 *
 *   @note Nothing.
*/

#ifndef _AB_OS_API_H_
#define _AB_OS_API_H_

/********************************************************************
 *    INCLUDE FILES
*********************************************************************/
#include "libabos_version.h"
#include "ab_os_types.h"


/********************************************************************
 *    MACRO CONSTANT DEFINITIONS
********************************************************************/


/********************************************************************
 *    DATA TYPE DEFINITION
********************************************************************/


/********************************************************************
 *    GLOBAL (or EXTERN) VARIABLES
********************************************************************/


/********************************************************************
 *    FUNCTION PROTOTYPES DECLARATIONS
********************************************************************/

/**
 * Utility part
**/


/**
 *  @brief ab_os_exec_command, launch Linux command via this unified API
 *
 *  @param e_pipe_type pipe:      [in] pipe on/off
 *  @param psz_cmd:               [in] command string
 *  @param psz_ui_pipefd_buff:    [out] catch stdout string
 *  @param ui_pipefd_buff_size:   [in] The stdout_ptr buffer size
 *  @return 
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *  @details More details
 */
AB_OS_RESULT_ET ab_os_exec_command_ex(AB_OS_EXEC_PIPE_ET e_pipe_type, char *psz_cmd, char *psz_ui_pipefd_buff,
                                      uint32_t ui_pipefd_buff_size,
                                      const char *psz_func, uint32_t ui_line);

#define ab_os_exec_command(e_pipe_type, psz_cmd, psz_ui_pipefd_buff, ui_pipefd_buff_size) \
    ab_os_exec_command_ex(e_pipe_type, psz_cmd, psz_ui_pipefd_buff, ui_pipefd_buff_size, __func__, __LINE__)

/**
 * @brief OS initial API, which include process signal registration.
 *
 *
 * @param s_init:      [in] init structure
 *
 *  @return 
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
**/
AB_OS_RESULT_ET ab_os_init(AB_OS_INIT_ST s_init);

/**
 * @brief ab_os_init_filesystem, to mount rootfs1 or rootfs2 
 *
 *
 * @param e_init_fs_type:      [in] init mount filesystem type
 *
 *  @return 
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
**/
AB_OS_RESULT_ET ab_os_init_filesystem(AB_OS_INIT_FS_TYPE_ET e_init_fs_type);



/**
 *  @brief ab_os_log_init to open the console or file
 *
 *  @param e_out_dest:     [in] console or file
 *  @param psz_path:       [in] path for console or file

 *  @return 
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *  @details More details
 */
AB_OS_RESULT_ET ab_os_log_init(AB_OS_LOG_OUT_DEST_ET e_out_dest, char *psz_path);

/**
 *  @brief lab_os_log_deinit to close the console or file
 *
 *  @return 
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *  @details More details
 */
AB_OS_RESULT_ET ab_os_log_deinit(void);

/**
 * @brief ab_os_log_printf which same as stand printf
 *
 *
 * @param psz_text_format:      [in] text format
 * @param ...:                  [in] parameters if needed
 *
 * @return
 *    - @b  void
**/
void ab_os_log_printf(const char *psz_text_format, ...);

/**
 * @brief ab_os_log print with error level
 *
 * @param e_log_level:      [in] log level, error/warn/message/debug
 * @param psz_fmt:          [in] print text format
 * @param ...:              [in] parameters if needed
 *
 * @return
 *    - @b  void
**/
void ab_os_log_ex(AB_OS_LOG_LEVEL_ET e_log_level, bool b_detail, const char *pc_launchfunc, uint32_t ui_line,
                  const char *psz_fmt, ...) \
__attribute__((format(printf, 5, 6))) ;

#define ab_os_log(e_log_level, psz_fmt, sz_arg...) \
    ab_os_log_ex(e_log_level, false, __FUNCTION__, __LINE__, psz_fmt, ##sz_arg)


/**
 * @brief ab_os_log_set_level, to set log level
 *
 * @param e_set_log_level:      [in] log level, error/warn/message/debug
 *
 * @return
 *    - @b  void
**/
void ab_os_log_set_level(AB_OS_LOG_LEVEL_ET e_set_log_level);

AB_OS_LOG_LEVEL_ET ab_os_log_get_level(void);

/**
 * @brief ab_os_utility_get_timestamp, to get time stamp by different time unit
 *
 * @param e_ts_unit:      [in] time unit, usec/msec/second
 *
 * @return
 *    - @b  current timestamp
**/
uint64_t ab_os_utility_get_timestamp(AB_OS_UTILITY_TIME_UNIT_ET e_ts_unit);

/**
 * @brief ab_os_utility_sleep, to set sleep by different time unit
 *
 * @param e_tse_sleep_unit_unit:      [in] time unit, usec/msec/second
 * @param ui_value:                   [in] how much time to sleep
 *
 *  @return 
 *     - @b  0    : Success.
 *     - @b  < 0  : Some error happened.
**/
int32_t ab_os_utility_sleep(AB_OS_UTILITY_TIME_UNIT_ET e_sleep_unit, uint32_t ui_value);


/**
 * @brief ab_os_utility_pwroff, 
 *
 * @param NULL:
 *
 *  @return 
 *     - @b  x    : No return.
**/
int32_t ab_os_utility_pwroff(void);

/**
 * @brief change root password, 
 *
 * @param passwd: target password.
 *
 *  @return 
 *     - @b  0    : success.
 *     - @b  != 0    : failed.
**/
int32_t ab_os_utility_root_chpasswd(char *passwd);

/**
 * @brief enable/disable library internal print log
 *
 * @param e_opt_en_dis:      [in] enable or disable
 * @param e_level_type:      [in] error/warn/message/debug
 * @param ui_trace_mask:     [in] module mask bit
 *
 * @return
 *     - @b  0     : Success.
 *     - @b  < 0   : Some error happened.
 *
**/
int32_t ab_os_debug_set(AB_OS_DEBUG_SET_OPTION_ET e_opt_en_dis, AB_OS_DEBUG_LEVEL_ET e_level_type,
                        uint32_t ui_trace_mask);



/**
 * Semaphore part
**/


/**
 * @brief ab_os_semaphore_create, create semaphore
 *
 * @param ps_ab_os_sem:      [in] handle of semaphore
 * @param psz_name:          [in] name of semaphore
 * @param ui_init_count:     [in] initial value
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
AB_OS_RESULT_ET ab_os_semaphore_create_ex(AB_OS_SEMAPHORE_ST *ps_ab_os_sem, char *psz_name, uint32_t ui_init_count,
        const char *psz_cf, uint32_t ui_line);
#define ab_os_semaphore_create(ps_ab_os_sem, psz_name, ui_init_count) \
    ab_os_semaphore_create_ex(ps_ab_os_sem, psz_name, ui_init_count, __FUNCTION__, __LINE__)

/**
 * @brief ab_os_semaphore_destory, destory semaphore
 *
 * @param ps_ab_os_sem:      [in] handle of semaphore
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
AB_OS_RESULT_ET ab_os_semaphore_destroy_ex(AB_OS_SEMAPHORE_ST *ps_ab_os_sem, const char *psz_cf, uint32_t ui_line);
#define ab_os_semaphore_destroy(ps_ab_os_sem) \
    ab_os_semaphore_destroy_ex(ps_ab_os_sem, __FUNCTION__, __LINE__)

/**
 * @brief ab_os_semaphore_get, to decrement (locks) the semaphore
 *
 * @param ps_ab_os_sem:      [in] handle of semaphore
 * @param i_wait_ms:         [in] time to wait (ms), or no wait/wait forever (AB_OS_WAIT_STATE_ET)
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
AB_OS_RESULT_ET ab_os_semaphore_get_ex(AB_OS_SEMAPHORE_ST *ps_ab_os_sem, int32_t i_wait_ms, const char *psz_cf,
                                       uint32_t ui_line);
#define ab_os_semaphore_get(ps_ab_os_sem, i_wait_ms) \
    ab_os_semaphore_get_ex(ps_ab_os_sem, i_wait_ms, __FUNCTION__, __LINE__)

/**
 * @brief ab_os_semaphore_put, to increment (unlocks) the semaphore
 *
 * @param ps_ab_os_sem:      [in] handle of semaphore
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
AB_OS_RESULT_ET ab_os_semaphore_put_ex(AB_OS_SEMAPHORE_ST *ps_ab_os_sem, const char *psz_cf, uint32_t ui_line);
#define ab_os_semaphore_put(ps_ab_os_sem) \
    ab_os_semaphore_put_ex(ps_ab_os_sem, __FUNCTION__, __LINE__)


/**
 * Thread part
**/


/**
 * @brief create thread
 *
 * @note Create a thread with indicated stack size. if uiAutoStart is set or thread is resume,
 *       the pfn_entry will be execute by the task with pv_param.
 *       priority of thread is set by ui_priority. About parameters, refer to AB_OS_THREAD_CREATE_PARA_ST.
 *
 * @param ps_thread:         [in] handle of thread
 * @param pc_name:           [in] thread name
 * @param pfn_entry:         [in] entry of thread
 * @param pv_param:          [in] parameter of entry
 * @param ui_stack_size:     [in] thread stack size (byte), 0 = default
 * @param ui_priority:       [in] thread priority
 *
 * @return
 *     - @b  AB_OK: Success.
 *     - @b  < 0:   Some error happened.
 *
 * Example:
 * @code
 * {
 *     TBD;
 * }
 * @endcode
**/
AB_OS_RESULT_ET ab_os_thread_create_ex(pthread_t *ps_thread_id, AB_OS_THREAD_CREATE_PARA_ST s_arg,
                                       uint32_t b_is_nonblocking, const char *pc_cf, uint32_t ui_line);
#define ab_os_nonblocking_thread_create(s_arg) \
    ab_os_thread_create_ex(NULL, s_arg, TRUE, __func__, __LINE__)
#define ab_os_blocking_thread_create(s_arg) \
    ab_os_thread_create_ex(NULL, s_arg, FALSE, __func__, __LINE__)

/**
 * @brief ab_os_thread_dump_current, dump current thread information
 *
 * @param None
 *
 * @return
 *     - @b  void
 *
**/
void ab_os_thread_dump_current_ex(const char *pc_cf, uint32_t ui_line);
#define ab_os_thread_dump_current() \
    ab_os_thread_dump_current_ex(__func__, __LINE__)

/**
 * @brief ab_os_thread_dump_current, dump all thread information
 *
 * @param None
 *
 * @return
 *     - @b  void
 *
**/
void ab_os_thread_dump_all_ex(const char *pc_cf, uint32_t ui_line);
#define ab_os_thread_dump_all() \
    ab_os_thread_dump_all_ex(__func__, __LINE__)


/**
 * Memory part
**/


/**
 * @brief Alloc memory buffer.
 *
 * @note Alloc a memory buffer, and set buffer data to 0. Buffer size is ui_item_num * ui_size.
 *
 * @param ui_item_num:  [in] unit ram size
 * @param ui_size:      [in] unit number
 * @param ui_use_cache: [in] option for use cache or non-cache., Currently not support Non-Cache
 *
 * @return
 *     - @b  not NULL  : Success.
 *     - @b  NULL      : Some error happend.
 *
 * Example:
 * @code
 * {
 *     TBD;
 * }
 * @endcode
**/
void *ab_os_mem_calloc_ex(uint32_t ui_item_num, uint32_t ui_size, int8_t ui_use_cache, const char *pc_func_name,
                          int32_t i_line_num);
#define ab_os_mem_calloc(ui_item_num, ui_size, ui_use_cache) \
    ab_os_mem_calloc_ex(ui_item_num, ui_size, ui_use_cache, __func__, __LINE__)

/**
 * @brief Alloc memory buffer.
 *
 * @note Alloc a memory buffer.
 *
 * @param ui_size:          [in] buffer size
 * @param ui_align_size:    [in] align size for non-cache option
 * @param ui_use_cache:     [in] option for use cache or non-cache.
 *
 * @return
 *     - @b  not NULL  : Success.
 *     - @b  NULL      : Some error happend.
 *
 * Example:
 * @code
 * {
 *     TBD;
 * }
 * @endcode
**/
void *ab_os_mem_malloc_ex(uint32_t ui_size, uint32_t ui_align_size, int8_t ui_use_cache, const char *pc_func_name,
                          int32_t i_line_num);
#define ab_os_mem_malloc(ui_size, ui_align_size, ui_use_cache) \
    ab_os_mem_malloc_ex(ui_size, ui_align_size, ui_use_cache, __func__, __LINE__)

/**
 * @brief Free memory buffer.
 *
 * @note Free a memory buffer.
 *
 * @param pv_addr:  [in] buffer address
 *
 * @return
 *     - @b  Always success.
 *
 * Example:
 * @code
 * {
 *     TBD;
 * }
 * @endcode
**/
void ab_os_mem_free_ex(void *pv_addr, const char *pc_func_name, int32_t i_line_num);
#define ab_os_mem_free(pv_addr) \
    ab_os_mem_free_ex(pv_addr, __func__, __LINE__)


/**
 * Mutex part
**/

/**
 * @brief ab_os_mutex_create, initialize a mutex
 *
 * @param ps_mtx:      [in] AB_OS_MUTEX_ST{sz_name/e_protocol/s_mutex}
 * @param pc_name:     [in] name of mutex
 * @param e_protocol:  [in] none/inherit/protect
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_mutex_create_ex(AB_OS_MUTEX_ST *ps_mtx, char *pc_name,
        AB_OS_MUTEX_PROTOCOL_ET e_inherit, const char *pc_func, uint32_t ui_line);
#define ab_os_mutex_create(ps_mtx, pc_name, e_protocol) \
    ab_os_mutex_create_ex(ps_mtx, pc_name, e_protocol, __func__, __LINE__)

/**
 * @brief ab_os_mutex_destroy, destory a mutex
 *
 * @param ps_mtx:      [in] AB_OS_MUTEX_ST{sz_name/e_protocol/s_mutex}
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_mutex_destroy_ex(AB_OS_MUTEX_ST *ps_mtx, const char *pc_func, uint32_t ui_line);
#define ab_os_mutex_destroy(ps_mtx) \
    ab_os_mutex_destroy_ex(ps_mtx, __func__, __LINE__)

/**
 * @brief ab_os_mutex_get, get (lock) a mutex
 *
 * @param ps_mtx:      [in] AB_OS_MUTEX_ST{sz_name/e_protocol/s_mutex}
 * @param i_wait_opt:  [in] time to wait (ms), or no wait/wait forever (AB_OS_WAIT_STATE_ET)
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_mutex_get_ex(AB_OS_MUTEX_ST *ps_mtx, int32_t i_wait_opt,
        const char *ps_func, uint32_t ui_line);
#define ab_os_mutex_get(ps_mtx, i_wait_opt) \
    ab_os_mutex_get_ex(ps_mtx, i_wait_opt, __func__, __LINE__)


/**
 * @brief ab_os_mutex_put, put (unlock) a mutex
 *
 * @param ps_mtx:      [in] AB_OS_MUTEX_ST{sz_name/e_protocol/s_mutex}
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_mutex_put_ex(AB_OS_MUTEX_ST *ps_mtx, const char *ps_func, uint32_t ui_line);
#define ab_os_mutex_put(ps_mtx) \
    ab_os_mutex_put_ex(ps_mtx, __func__, __LINE__)


/**
 * Event part
**/

/**
 * @brief ab_os_event_create, initialize a event
 *
 * @param ps_event:     [in] AB_OS_EVENT_ST{sz_name/s_mutex/s_cond/ui_event_flag/ui_post_flag/ui_got_flag}
 * @param pca_name:     [in] name of event
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_event_create_ex(AB_OS_EVENT_ST *ps_event, char *pca_name, const char *pca_func,
        uint32_t ui_line);
#define ab_os_event_create(ps_event, pca_name) \
    ab_os_event_create_ex(ps_event, pca_name, __func__, __LINE__)

/**
 * @brief ab_os_event_destroy, destory a event
 *
 * @param ps_event:     [in] AB_OS_EVENT_ST{sz_name/s_mutex/s_cond/ui_event_flag/ui_post_flag/ui_got_flag}
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_event_destroy_ex(AB_OS_EVENT_ST *ps_event, const char *pca_func, uint32_t ui_line);
#define ab_os_event_destroy(ps_event) \
    ab_os_event_destroy_ex(ps_event, __func__, __LINE__)


/**
 * @brief ab_os_event_get, get an event
 *
 * @param ps_event:       [in] AB_OS_EVENT_ST{sz_name/s_mutex/s_cond/ui_event_flag/ui_post_flag/ui_got_flag}
 * @param ui_req_flag:    [in] flag of a request event
 * @param ui_option:      [in] AB_OS_EVENT_OPTION_ET{OR/AND/OR_CLEAR/AND_CLEAR}
 * @param pui_actual_flag:[out] actual flag of a request event
 * @param i_wait_option:  [in] time to wait (ms), or no wait/wait forever (AB_OS_WAIT_STATE_ET)
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_event_get_ex(AB_OS_EVENT_ST *ps_event, uint32_t ui_req_flag,
        uint32_t ui_option, uint32_t *pui_actual_flag, int32_t i_wait_option,
        const char *pca_func, uint32_t ui_line);
#define ab_os_event_get(ps_event, ui_req_flag, ui_option, pui_actual_flag, i_wait_option) \
    ab_os_event_get_ex(ps_event, ui_req_flag, ui_option, pui_actual_flag, i_wait_option, __func__, __LINE__)

/**
 * @brief ab_os_event_set, set a event
 *
 * @param ps_event:       [in] AB_OS_EVENT_ST{sz_name/s_mutex/s_cond/ui_event_flag/ui_post_flag/ui_got_flag}
 * @param ui_setflag:     [in] flag of a set event
 * @param ui_option:      [in] AB_OS_EVENT_OPTION_ET{OR/AND/OR_CLEAR/AND_CLEAR}
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
 *
**/
extern AB_OS_RESULT_ET ab_os_event_set_ex(AB_OS_EVENT_ST *ps_event, uint32_t ui_setflag, uint32_t ui_option,
        const char *pca_func, uint32_t ui_line);
#define ab_os_event_set(ps_event, ui_setflag, ui_option) \
    ab_os_event_set_ex(ps_event, ui_setflag, ui_option, __func__, __LINE__)

/**
 * @brief ab_os_time_get, get OS time
 *
 * @note to get the current time as seconds and milliseconds
 *  since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
 *  The unit of value is ms (1/1000 second)
 *
 * @param None
 *
 * @return
 *     - @b  value of Os time.
 *
**/
uint64_t ab_os_time_get_ex(const char *pc_func, uint32_t ui_line);

#define ab_os_time_get( ) \
    ab_os_time_get_ex( __func__, __LINE__ )

/**
 * @brief ab_os_timer_create, create a timer to execute function when time out.
 *
 *
 * @param ps_timer:          [in] structure of timer information, please refer to AB_OS_TIMER_ST
 * @param pc_Name:           [in] name of timer
 * @param pf_timeout_cb:     [in] callback function when timeout
 * @param ul_param:          [in] parameter for callback function
 * @param ul_first_timeout:  [in] time for first timeout
 * @param ul_repeat_timeout: [in] time for repeat (interval) timeout
 * @param uc_auto_start:     [in] true/false
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
**/
int32_t ab_os_timer_create_ex(AB_OS_TIMER_ST *ps_timer, char *pc_Name,
                              AB_OS_EPOLL_CALLBACK_FUNC pf_timeout_cb, uint64_t ul_param,
                              uint64_t ul_first_timeout, uint64_t ul_repeat_timeout, uint8_t uc_auto_start, const char *pc_func, uint32_t ui_line);
#define ab_os_timer_create( ps_timer, pc_Name, pf_timeout_cb, ul_param, ul_first_timeout, ul_repeat_timeout, uc_auto_start) \
    ab_os_timer_create_ex( ps_timer, pc_Name, pf_timeout_cb, ul_param, ul_first_timeout, ul_repeat_timeout, uc_auto_start, __func__, __LINE__ )

/**
 * @brief ab_os_timer_delete, delete a timer
 *
 *
 * @param ps_timer:          [in] structure of timer information, please refer to AB_OS_TIMER_ST
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
**/
int32_t ab_os_timer_delete_ex(AB_OS_TIMER_ST *ps_Timer, const char *pc_func, uint32_t ui_line);
#define ab_os_timer_delete( ps_Timer ) \
    ab_os_timer_delete_ex( ps_Timer, __func__, __LINE__ )

/**
 * @brief ab_os_timer_enable, enable/disable a timer
 *
 *
 * @param ps_timer:          [in] structure of timer information, please refer to AB_OS_TIMER_ST
 * @param bEnable:           [in] true/false
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
**/
int32_t ab_os_timer_enable_ex(AB_OS_TIMER_ST *ps_Timer, int8_t c_enable, const char *pc_func, uint32_t ui_line);
#define ab_os_timer_enable( ps_Timer, bEnable ) \
    ab_os_timer_enable_ex( ps_Timer, bEnable, __func__, __LINE__ )

/**
 * @brief ab_os_timer_query, get timer configuration
 *
 *
 * @param ps_timer:             [in] structure of timer information, please refer to AB_OS_TIMER_ST
 * @param pui_active:           [out] timer is active or inactive
 * @param pul_first_timeout:    [out] time for first timeout
 * @param pul_repeat_timeout:   [out] time for repeat (interval) timeout
 *
 * @return
 *     - @b  AB_OS_OK: Success.
 *     - @b  < 0     : Some error happened.
**/
int32_t ab_os_timer_query_ex(AB_OS_TIMER_ST *ps_timer, int8_t **ppc_name, uint32_t *pui_active,
                             uint64_t *pul_first_timeout, uint64_t *pul_repeat_timeout, AB_OS_TIMER_ST **pp_next_timer, const int8_t *pc_func,
                             uint32_t ui_line);
#define ab_os_timer_query( ps_timer, pui_active, pul_first_timeout, pul_repeat_timeout ) \
    ab_os_timer_query_ex(ps_timer, NULL, pui_active, pul_first_timeout, pul_repeat_timeout, NULL, __func__ , __LINE__ )


/**
 * @brief ab_os_version, to show (print) out os version
 *
 *
 * @param None
 *
 * @return
 *     - @b  void
**/
#define ab_os_version() do{ ab_os_log_printf("Libabos version: %d.%d.%d\n", LIBABOS_VERSION_MAJOR, LIBABOS_VERSION_MINOR, LIBABOS_VERSION_PATCH); }while(0);

/**
 * @brief file memory map function.
 *
 * @param i_fd:             [in] mapping file's description
 * @param i_file_offset:    [in] the start offset of mapping file
 * @param i_map_length:     [in] the length of mapping file.
 * @param e_map_type:       [in] AB_OS_MEM_MMAP_TYPE_ET
 * @param e_map_flag:       [in] AB_OS_MEM_MMAP_FLAG_ET
 *
 * @return
 *     - @b  NULL - mmap fail.
 *     - @b  memory address - success.
 *
**/
void* ab_os_mem_mmap_ex(int ifd_fd, int32_t i_file_offset, int32_t i_map_length, AB_OS_MEM_MMAP_TYPE_ET e_map_type, AB_OS_MEM_MMAP_FLAG_ET e_map_flag, const char *pc_func_name, int32_t i_line_num);
#define ab_os_mem_mmap(idf_fd, i_file_offset, i_map_length, e_map_type, e_map_flag) \
    ab_os_mem_mmap_ex(idf_fd, i_file_offset, i_map_length, e_map_type, e_map_flag, __func__, __LINE__)

/**
 * @brief file memory unmap function.
 *
 * @param pv_mmap_addr:     [in] ab_os_mem_mmap_ex mapped address
 * @param i_map_length:     [in] the length of mapping file.
 *
 * @return
 *     - @b  AB_OS_RESULT_ET.
 *
**/
int32_t ab_os_mem_munmap_ex(void* pv_mmap_addr, int32_t i_map_length, const char *pc_func_name, int32_t i_line_num);
#define ab_os_mem_munmap(pv_mmap_addr, i_map_length) \
    ab_os_mem_munmap_ex(pv_mmap_addr, i_map_length, __func__, __LINE__)

/**
 * @brief file memory memory sync flush function.
 *
 * @param pv_mmap_addr:     [in] memory address section you want sync
 * @param i_map_length:     [in] the length of mapping file.
 * @param e_sync_flag:      [in] msync flag.
 *
 * @return
 *     - @b  AB_OS_RESULT_ET.
 *
**/
int32_t ab_os_mem_msync_ex(void* pv_mmap_addr, int32_t i_map_length, AB_OS_MEM_MSYNC_FLAG_ET e_sync_flag, const char *pc_func_name, int32_t i_line_num);
#define ab_os_mem_msync(pv_mmap_addr, i_map_length, e_sync_flag) \
    ab_os_mem_msync_ex(pv_mmap_addr, i_map_length, e_sync_flag, __func__, __LINE__)

/**
 * @brief Physical address map to virutal memory space, just for DSP using.
 * @note If using external memory, address from 0x20000000 to 0x60000000 
 * @param i_physical_addr:     [in] physical address 
 * @param i_map_length:        [in] the length of physical address.
 * @param e_map_type:          [in] read/write/read_write type
 * @param e_map_flag:          [in] map as shared type.
 *
 * @return
 *     - @b  NULL - mmap fail.
 *     - @b  memory address - success.
 *
**/
void* ab_os_mem_physical_mmap_to_virtual_ex(int32_t i_physical_addr, int32_t i_map_length, AB_OS_MEM_MMAP_TYPE_ET e_map_type, AB_OS_MEM_MMAP_FLAG_ET e_map_flag, const char *pc_func_name, int32_t i_line_num);
#define ab_os_mem_physical_mmap_to_virtual(i_phy_addr, i_map_length, e_map_type, e_map_flag) \
    ab_os_mem_physical_mmap_to_virtual_ex(i_phy_addr, i_map_length, e_map_type, e_map_flag, __func__, __LINE__)

#endif /* _AB_OS_API_H_ */
