/**
  **************************************************************************************
  *  @file           : user_log.h
  *  @brief          : Print your Log information
  **************************************************************************************
  *  @useage
  * Include this header file in the program file that you want to print logs.
	* Using the function: 
	* `user_printf()`
	* `user_main_info()`
	* `user_main_debug()`
	* `user_main_error()`  to print the log.
  * Define "PRINT_USER_LOG" if you want to print logs and annotations it if you don't.
  **************************************************************************************
 **/
#ifndef __USER_LOG_H
#define __USER_LOG_H

#define PRINT_USER_LOG	//define for print log

#ifdef PRINT_USER_LOG

#define user_printf(format, ...) printf( format "\r\n", ##__VA_ARGS__)

#define user_main_info(format, ...) printf(" [info] main.c: " format "\r\n", ##__VA_ARGS__)
#define user_main_debug(format, ...) printf(" [debug] main.c: " format "\r\n", ##__VA_ARGS__)
#define user_main_error(format, ...) printf(" [error] main.c: " format "\r\n",##__VA_ARGS__)

#define user_file_info(format, ...) printf(" [info] file.c: " format "\r\n", ##__VA_ARGS__)
#define user_file_debug(format, ...) printf(" [debug] file.c: " format "\r\n", ##__VA_ARGS__)
#define user_file_error(format, ...) printf(" [error] file.c: " format "\r\n",##__VA_ARGS__)

#else

#define user_printf(format, ...)

#define user_main_info(format, ...)
#define user_main_debug(format, ...)
#define user_main_error(format, ...)

#define user_file_info(format, ...)
#define user_file_debug(format, ...)
#define user_file_error(format, ...)

#endif	/* PRINT_USER_LOG */

#endif  /* __USER_LOG_H */
