#ifndef BASE_H
#define BASE_H

#ifdef UTIL_EXPORTS
#define UTIL_EXPORTS_DEL __declspec(dllexport)
#else
#define UTIL_EXPORTS_DEL __declspec(dllimport)
#endif

#define UTILS_BEGIN  namespace Utils{
#define UTILS_END   }


#define STRINGTOOLS_BEGIN  UTILS_BEGIN namespace StringTools{
#define STRINGTOOLS_END    UTILS_END }


#define COMMONTOOLS_BEGIN  UTILS_BEGIN namespace CommonTools{
#define COMMONTOOLS_END    UTILS_END }


#define LOG_INFO_FUN_BEGIN LOG(INFO) << ">>>>>>>>>>"<< __FUNCTION__ << " Begin ";
#define LOG_INFO_FUN_END LOG(INFO) <<   "<<<<<<<<<<"<< __FUNCTION__ << " End ";
#define RETURN {LOG_INFO_FUN_END return;}
#define RETURN_A(ARG) { LOG_INFO_FUN_END return ARG; }
#endif