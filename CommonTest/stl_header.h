#ifndef STL_HEADER_H
#define STL_HEADER_H

//container
#include <vector>
#include <deque>
#include <forward_list> //single list
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <queue>
#include <stack>
#include <bitset>

//common tools
#include <utility> //运算符和值对
#include <type_traits>
#include <typeindex> //将type_info 用作一个关键字或者哈希吗
#include <functional>
#include <memory> //资源管理指针
#include <scoped_allocator> //限定作用域的分配器
#include <ratio> //编译时有理数运算
#include <iterator>
#include <ctime> //C 风格日期和时间工具

//algorithm
#include <algorithm>
#include <cstdlib> //bsearch() qsort()

//concurrency
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
#include <atomic>

//diagnosis
#include <exception> //异常类
#include <stdexcept> //标准异常
#include <cassert> //断言宏
#include <cerrno> //C 风格错误处理
#include <system_error> //系统错误支持

//string
#include <string>
#include <cctype> //字符分类
#include <cwctype> //宽字符分类
#include <cstring> //C 风格字符串函数
#include <cwchar> //C 风格宽字符串函数
#include <regex> //正则表达式匹配

//i/o
#include <iosfwd> //I/O 组件的前置声明
#include <iostream>
#include <ios> //iostream的base class
#include <streambuf> //流缓冲
#include <iomanip> //操纵符
#include <cstdio>




#endif