/**@defgroup 命令行模块
@{

@brief 通过命令行,调用中间件服务端及客户端的函数,用于中间件的调试等.

@version 1.0.0 2015/02/04 初稿
*/
#ifndef __TCLI_H__
#define __TCLI_H__


#ifdef __cplusplus
extern "C" {
#endif

/**
@brief 自动添加TCLI命令的宏,在代码的任意位置使用该宏实现自动注册.

添加后,可通过tcli命令行工具使用该命令.

@note 调用者需保证所有的字符串一直有效.

@code 示例代码
static void run_my_cmd(int i,char* s)
{
//any thing here
}
TOS_TCLI_COMMAND(mycmd,"short help of mycmd","long help\nof mycmd","is",run_my_cmd);//out of function, it will auto run.
@endcode

@param[in] name 命令名称
@param[in] shortHelp 简短帮助,使用help命令列出所有命令时,简短帮助会列到命令的后面.
@param[in] longHelp 详细帮助,使用help 命令名称命令时,会列出这些信息.
@param[in] argParse 有s(表示字符串)和i(表示整数)组成的参数描述符.如"isi"表示命令函数的第一个参数为int,第二个为const char*,第三个为int.
@param[in] func 执行此语句的函数.
*/
#if defined(__GNUC__)
#define TOS_TCLI_COMMAND(name, shortHelp, longHelp, argParse, func) \
    __attribute__((constructor)) static void TCLICMD_##name(){tos_tcli_addCommand(#name, shortHelp, longHelp, argParse, func);}
#else
#error TOS_TCLI_COMMAND() for this configuration must be defined
#endif

/**
@brief 交互输出回调函数定义

当命令执行时,若需要输出执行信息(如开始执行了,执行结果等),TCLI会调用此函数,用于在CLI交互时输出.
*/
typedef void (*tos_tcli_onOutput)(const char* prompt,void* userdata);


/**
@brief 初始化TCLI模块

@return return 成功返回0,失败返回<0的错误代码.
*/
int tos_tcli_init(void);

/**
@brief 反初始化TCLI模块

@return return 成功返回0,失败返回<0的错误代码.
*/
int tos_tcli_destroy(void);

/**
@brief 在命令执行函数中,使用此接口输出执行交互过程.

实际会调用到tos_tcli_execute函数out参数执行的函数用于输出,同时也会在CLOG输出.

@note 仅能在命令执行函数中调用.

@param[in] format 日志内容,支持printf中的%d等参数
*/
void tos_tcli_printf(const char* fmt,...);

/**
@brief 添加一个命令到TCLI中

一般情况下,请通过TOS_TCLI_COMMAND调用,不建议直接使用本接口.
@return return 成功返回0,失败返回<0的错误代码.
*/
int tos_tcli_addCommand(const char* name,const char *shortHelp,const char *longHelp,const char *argParse, void *func);


/**
@brief 执行一条TCLI命令(暂未实现)

@param[in] cmd 命令字符串,utf8格式.
@param[in] out 交互输出回调函数,命令执行过程中需要交互时会将交互信息通过此函数发出.
@return return 成功返回0,失败返回<0的错误代码.
*/
int tos_tcli_execute(const char* cmd,tos_tcli_onOutput out,void* userdata);

/**
@brief 执行一条TCLI命令

@param[in] argc 命令参数数量
@param[in] argv 命令或参数,其中argv[0]必须为命令,后面的为参数
@param[in] out 交互输出回调函数,命令执行过程中需要交互时会将交互信息通过此函数发出.
@return return 成功返回0,失败返回<0的错误代码.
*/
int tos_tcli_executeByargs(int argc,char* argv[],tos_tcli_onOutput out,void* userdata);



#ifdef __cplusplus
}
#endif
/** @} */
#endif