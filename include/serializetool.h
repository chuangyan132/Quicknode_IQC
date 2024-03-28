#ifndef SERIALIZE_HELPER_H
#define SERIALIZE_HELPER_H

#include "base.h"
#include <tuple>
#include <type_traits>
#include <cassert>
#include <string>
#include <map>
#include <unordered_map>
#include <array>
#include <vector>

UTILS_BEGIN

//===========================================================================
//  Function：用于结构体序列化和反序列化(部分待完善)
//  序列化时存入实体数据,数据大小以及对应的结构体中变量的偏移地址
//  对C++基本类型做出优化,直接通过内存块拷贝加快速度
//  检测对象内存连续性进行相关优化,直接通过内存块拷贝加快速度
//  反序列化通过存储的结构体成员变量偏移倒推出成员变量内存地址
//  目前可序列化类型有所有C++基本类型(bool,char,wchar_t,int,short,int,double,以及枚举等)
//  和std::vector,std::map,std::unordered_map,std::string,std::wstring,std::array,std::pair等各种嵌套
//  其中VarForwarderSerial模板是通过template的SFINAE特性来判断参数是否有序列化函数的实例,从而可以实现嵌套,参考于微软开源库rDSN中json_forwarder的实现
//  https://github.com/microsoft/rDSN/blob/master/include/dsn/cpp/json_helper.h
//  可以通过标准库检测出POD类型的数据结构,将直接通过整块内存拷贝
//  无法通过标准库检测POD判断的数据,但是事实上内存连续可使用DEFINE_POD_TYPE用于显式声明POD类型,即可以直接内存拷贝的结构体,用于加速(除非明确了解,否则不要使用此宏)
//  TODO 嵌套还是有部分问题,待完善list,queue...
//  TODO 不支持有虚函数表的结构体
//  Author：                       by QIYI
//  Time：                         2020.02.25 edit
//  ----------以下是使用方法----------
//      typedef struct Test {
//          int a;
//          std::vector<std::array<float, 5>> b;
//          std::map<int, std::string> c;
//          DEFINE_SERIALIZATION(a, b, c); //*定义序列化函数宏*
//      }Test;
//
//      std::string rawData = test.serialize();//序列化
//
//      Test test1;
//      test1.deserialize(rawData);//反序列化
//  --------------------------------
//===========================================================================


namespace serializeHelper {

    static const size_t dataSize = NULL;

    //初始开辟空间,当然最后超过了也没事,最后会shrink到最小大小
#define CAPACITY (1024)
#define HEAD_LENGTH (sizeof(size_t) * 2)
#define DEFINE_POD_TYPE void definePodType();
#define DEFINE_SERIALIZATION(...)                                                               \
    /*此函数序列化使用了string,会有频繁内存拷贝,1000W点规模序列化大概需要180ms*/                     \
    std::string serialize() const {                                                             \
        std::string rawData;                                                                    \
        rawData.reserve(CAPACITY);                                                              \
        rawData.append(HEAD_LENGTH,'\0');                                                       \
        serializeInternalEntrance(reinterpret_cast<void*>(&rawData), this, __VA_ARGS__);        \
        appendHead(rawData.data());                                                             \
        shrinkData(rawData);                                                                    \
        return std::move(rawData);                                                              \
    }                                                                                           \
    /*可以直接写入指定地址,1000W点规模序列化大概需要28ms,一般用于增量点云更新,返回序列化后所用空间 */  \
    size_t serialize(void *des) const {                                                         \
        memset(des, NULL, HEAD_LENGTH);                                                         \
        serializeInternalEntrance(des, this, __VA_ARGS__);                                      \
        appendHead(static_cast<char*>(des));                                                    \
        return *(reinterpret_cast<size_t*>(des) + 1);                                           \
    }                                                                                           \
    /*反序列化,1000W点反序列化大概需要44ms*/                                                      \
    void deserialize(const std::string& rawData){                                               \
        deserializeEntrance(this, rawData.data() + HEAD_LENGTH);                                \
    }                                                                                           \
    void deserialize(const char* rawData){                                                      \
        deserializeEntrance(this, rawData + HEAD_LENGTH);                                       \
    }                                                                                           \
    /*获得结构体类型的元组*/                                                                      \
    auto getTuple()->decltype(getTupleInternal(__VA_ARGS__));

    //只需要获得类型元组,所以只需要函数声明就可以,无需实现
    template<typename... Args>
    auto getTupleInternal(Args ...args)->std::tuple<Args...>;

    template<typename> struct VarForwarderSerial;

    //检测是否属于POD类型,用于整块内存拷贝
    template<typename T>
    struct CheckisPod
    {
        template<typename T>
        static auto checkIsDefPodType(T*)->typename std::is_same<decltype(std::declval<T>().definePodType()), void>::type;
        template<typename>
        static auto checkIsDefPodType(...)->decltype(std::false_type());
        typedef decltype(checkIsDefPodType<T>(0)) check;
        template<typename T>
        static auto checkIsImplicitPodType(T*)->typename std::is_pod<T>::type;
        typedef decltype(checkIsImplicitPodType<T>(0)) checkIsImplicit;
        static const bool value = std::is_same<check, std::true_type>::value | std::is_same<checkIsImplicit, std::true_type>::value;
    };

    static inline void appendHead(const char* ptr) {
        auto size = reinterpret_cast<size_t*>(const_cast<char*>(ptr)) + 1;
        *size += HEAD_LENGTH;
    }

    static inline void dataAppend(const void* out, const char* data, const size_t size) {
        //std::string
        if (*reinterpret_cast<const size_t*>(out) != NULL) {
            auto str = reinterpret_cast<std::string*>(const_cast<void*>(out));
            auto allSize = reinterpret_cast<size_t*>(const_cast<char*>(str->data())) + 1;
            *allSize += size;
            str->append(data, size);
        }
        else {
            auto allSize = reinterpret_cast<size_t*>(const_cast<void*>(out)) + 1;
            auto dataLoc = reinterpret_cast<char*>(allSize + 1);
            memcpy(dataLoc + *allSize, data, size);
            *allSize += size;
        }
    }

    static inline void dataAppend(const void* out, const std::string& in) {
        dataAppend(out, in.data(), in.size());
    }

    static inline void shrinkData(std::string& out) {
        auto ptr = const_cast<char*>(out.data());
        auto allSize = reinterpret_cast<size_t*>(ptr) + 1;
        out.resize(*allSize);
    }

    //基本数字类型和枚举类型
    template<typename T>
    inline typename std::enable_if<std::is_arithmetic<T>::value | std::is_enum<T>::value>::type
        externalSerialization(const void* out, const T& t) {
        dataAppend(out, reinterpret_cast<const char*>(&t), sizeof(T));
    }

    //未知类型,直接编译失败
    //template<typename T>
    //inline typename std::enable_if<!std::is_arithmetic<T>::value>::type
    //    externalSerialization(const void* out, const T& t) {
    //    static_assert(false, "unknown type");
    //}

    //string and wstring
    template<typename T>
    inline typename std::enable_if<std::is_same<std::string, T>::value | std::is_same<std::wstring, T>::value>::type
        externalSerialization(const void* out, const T& t) {
        externalSerialization(out, t.size());
        dataAppend(out, reinterpret_cast<const char*>(t.c_str()), t.size() * sizeof(std::decay_t<decltype(t)>::value_type));
    }

    //array
    //对象如果是基本类型做直接内存拷贝
    template<typename T, size_t SIZE>
    inline typename std::enable_if <std::is_arithmetic<T>::value>::type
        externalSerialization(const void* out, const std::array<T, SIZE>& t) {
        dataAppend(out, reinterpret_cast<const char*>(t.data()), SIZE * sizeof(T));
    }

    //array
    //其它类型只能迭代操作
    template<typename T, size_t SIZE>
    inline typename std::enable_if <!std::is_arithmetic<T>::value>::type
        externalSerialization(const void* out, const std::array<T, SIZE>& t) {
        //externalSerialization(out, t.size()); //array类型可以直接得到size,所以这里已经不需要了
        for (auto& ite : t)
            VarForwarderSerial<T>::call(out, nullptr, ite);
    }

    //数组类型
    //数组如果是基本类型做直接内存拷贝
    template<typename T>
    inline typename std::enable_if <std::is_array<std::remove_reference_t<T>>::value&
        std::is_arithmetic<std::remove_pointer_t<std::decay_t<T>>>::value>::type //需要去引用,否则匹配失败
        externalSerialization(const void* out, const T& t) {
        externalSerialization(out, sizeof(t));
        dataAppend(out, reinterpret_cast<const char*>(t), sizeof(T));
    }

    //数组类型
    //数组如果是其它类型
    template<typename T>
    inline typename std::enable_if <std::is_array<std::remove_reference_t<T>>::value &
        !std::is_arithmetic<std::remove_pointer_t<std::decay_t<T>>>::value>::type //需要去引用,否则匹配失败
        externalSerialization(const void* out, const T& t) {
        //TODO QIYI
        static_assert(false, "unknown type");
    }

    template<typename T>
    inline void serializeMap(const void* out, const T& t) {
        externalSerialization(out, t.size());
        for (auto it = t.begin(); it != t.end(); ++it) {
            VarForwarderSerial<typename std::decay<decltype(it->first)>::type>::call(out, nullptr, it->first);
            VarForwarderSerial<typename std::decay<decltype(it->second)>::type>::call(out, nullptr, it->second);
        }
    }

    //std::map
    template<typename KEY, typename VAL>
    inline void externalSerialization(const void* out, const std::map<KEY, VAL>& t) {
        serializeMap(out, t);
    }

    //std::unordered_map
    template<typename KEY, typename VAL>
    inline void externalSerialization(const void* out, const std::unordered_map<KEY, VAL>& t) {
        serializeMap(out, t);
    }

    //char
    //inline void externalSerialization(const void* out, const char* t) { out.append(t); } //不支持,反序列化时无空间可放

    //std::pair
    template<typename First, typename Second>
    inline void externalSerialization(const void* out, const std::pair<First, Second>& t) {
        VarForwarderSerial<typename First>::call(out, nullptr, t.first);
        VarForwarderSerial<typename Second>::call(out, nullptr, t.second);
    }

    //std::vector
    //支持POD类型走此,直接通过内存块操作
    template<typename T>
    inline typename std::enable_if <CheckisPod<T>::value>::type
        externalSerialization(const void* out, const std::vector<T>& t) {
        auto size = t.size();
        dataAppend(out, reinterpret_cast<const char*>(&size), sizeof(std::vector<T>::size_type));
        dataAppend(out, reinterpret_cast<const char*>(t.data()), size * sizeof(T));
    }

    //std::vector
    //自定义类型只能通过迭代操作
    template<typename T>
    inline typename std::enable_if <!CheckisPod<T>::value>::type
        externalSerialization(const void* out, const std::vector<T>& t) {
        auto size = t.size();
        dataAppend(out, reinterpret_cast<const char*>(&size), sizeof(std::vector<T>::size_type));
        for (auto& ite : t)
            VarForwarderSerial<T>::call(out, nullptr, ite);
    }

    //计入结构体变量偏移值
    inline void writeOffset(const void* rawData, const char* base, const char* cur) {
        if (base && cur)
            externalSerialization(rawData, (size_t)(cur - base));
    }

    template<typename T>
    struct VarForwarderSerial {
    private:
        template<typename C>
        static auto checkFun(C*)->typename std::is_same<decltype(std::declval<C>().serialize()), std::string>::type;
        template<typename>
        static std::false_type checkFun(...);

        typedef decltype(checkFun<T>(0)) HasSerializeFun;

        //显式声明POD类型直接内存拷贝
        template<typename T1>
        static inline void chooseSerialize(const void* out, const T1& t, std::true_type) {
            if (*reinterpret_cast<const size_t*>(out) != NULL) {
                dataAppend(out, std::string((char*)const_cast<T1*>(&t), sizeof(T1)));
            }
            else {
                auto allSize = reinterpret_cast<size_t*>(const_cast<void*>(out)) + 1;
                auto dataLoc = reinterpret_cast<char*>(allSize + 1);
                memcpy(dataLoc + *allSize, &t, sizeof(T1));
                *allSize += sizeof(T1);
            }
        }

        //未显式声明POD类型走老方法
        template<typename T1>
        static inline void chooseSerialize(const void* out, const T1& t, std::false_type) {
            if (*reinterpret_cast<const size_t*>(out) != NULL) {
                dataAppend(out, t.serialize());
            }
            else {
                auto allSize = reinterpret_cast<size_t*>(const_cast<void*>(out)) + 1;
                auto dataLoc = reinterpret_cast<char*>(allSize + 1);
                auto subSize = t.serialize(dataLoc + *allSize);
                *allSize += subSize;
            }
        }

        static void callInner(const void* out, const T& t, std::true_type) { chooseSerialize(out, t, typename CheckisPod<std::decay_t<T>>::check{}); }
        static void callInner(const void* out, const T& t, std::false_type) { externalSerialization(out, t); }
    public:
        static void call(const void* out, const char* obj, const T& t) {
            writeOffset(out, obj, reinterpret_cast<const char*>(&t));
            callInner(out, t, HasSerializeFun{});
        }
    };

    template<typename STRUCTTYPE>
    void serializeInternal(const void* rawData, STRUCTTYPE&& structClass) {
        //结构体为空,不进行任何操作
    }

    //最后一次状态转移
    template<typename STRUCTTYPE, typename T>
    void serializeInternal(const void* rawData, STRUCTTYPE&& obj, T&& t) {
        //这里类型不能退化,否则将数组将退化成指针,无法再获得对象长度
        VarForwarderSerial<std::remove_reference_t<T>>::call(rawData, reinterpret_cast<const char*>(obj), t);
    }

    template<typename STRUCTTYPE, typename T, typename... Args>
    void serializeInternal(const void* rawData, STRUCTTYPE&& obj, T&& t, Args&& ...args) {
        VarForwarderSerial<std::remove_reference_t<T>>::call(rawData, reinterpret_cast<const char*>(obj), t);
        serializeInternal(rawData, obj, std::forward<Args>(args)...);
    }

    //POD声明,直接内存拷贝
    template<typename STRUCTTYPE, typename... Args>
    inline void chooseSerializeInternal(const void* rawData, STRUCTTYPE&& obj, std::true_type, Args&& ...args) {
        using rawType = std::remove_const_t<std::remove_pointer_t<std::remove_reference_t<STRUCTTYPE>>>;
        if (*reinterpret_cast<const size_t*>(rawData) != NULL) {
            dataAppend(rawData, (char*)(obj), sizeof(rawType));
        }
        else {
            auto allSize = reinterpret_cast<size_t*>(const_cast<void*>(rawData)) + 1;
            auto dataLoc = reinterpret_cast<char*>(allSize + 1);
            memcpy(dataLoc, (char*)(obj), sizeof(rawType));
            *allSize += sizeof(rawType);
        }
    }

    template<typename STRUCTTYPE, typename... Args>
    inline void chooseSerializeInternal(const void* rawData, STRUCTTYPE&& obj, std::false_type, Args&& ...args) {
        serializeInternal(rawData, obj, std::forward<Args>(args)...);
    }


    //实现每个形参序列化的入口
    template<typename STRUCTTYPE, typename... Args>
    inline void serializeInternalEntrance(const void* rawData, STRUCTTYPE&& obj, Args&& ...args) {
        //decay 无法退化,原因不知
        using rawType = std::remove_const_t<std::remove_pointer_t<std::remove_reference_t<STRUCTTYPE>>>;
        chooseSerializeInternal(rawData, obj, typename CheckisPod<rawType>::check{}, std::forward<Args>(args)...);
    }

    ///////////////////以下是反序列化实现///////////////////

    template<typename> struct VarForwarderdeSerial;

    //根据具体类型来反序列化
    template <typename T, typename Enable = void>
    struct DeserializeHelper;

    //基本数字类型和枚举类型
    template<typename T>
    struct DeserializeHelper<T, typename std::enable_if<std::is_arithmetic<T>::value | std::is_enum<T>::value>::type> {
        static void deserialize(char* pos, char** rawData) {
            memcpy_s(pos, sizeof(T), *rawData, sizeof(T));
            *rawData += sizeof(T);
        }
    };

    //string and wstring
    template<typename T>
    struct DeserializeHelper<T, typename std::enable_if<std::is_same<std::string, T>::value | std::is_same<std::wstring, T>::value>::type> {
        static void deserialize(char* pos, char** rawData) {
            using decayType = std::decay_t<T>;
            decayType* p = reinterpret_cast<decayType*>(pos);
            auto size = reinterpret_cast<size_t*>(*rawData);
            *rawData += sizeof(size_t);
            auto temp = decayType(reinterpret_cast<typename decayType::value_type*>(*rawData), *size);
            p->swap(temp);
            *rawData += *size * sizeof(decayType::value_type);
        }
    };

    //std::array
    template<typename T, size_t SIZE>
    struct DeserializeHelper<std::array<T, SIZE>, typename std::enable_if<true>::type> {
        static void deserialize(char* pos, char** rawData) {
            std::array<T, SIZE>* p = reinterpret_cast<std::array<T, SIZE>*>(pos);
            //auto size = reinterpret_cast<size_t*>(*rawData); //array 不需要
            //TODO QIYI 此处可以优化
            for (auto i = NULL; i < SIZE; i++) {
                DeserializeHelper<T>::deserialize(reinterpret_cast<char*>(const_cast<T*>(p->data())) + i * sizeof(T), rawData);
            }
        }
    };

    //这里数组已经变成*了 这也许是std::tuple的特性
    //可以直接内存拷贝的数组
    template<typename T>
    struct DeserializeHelper<T, typename std::enable_if<std::is_pointer<T>::value&
        std::is_arithmetic<std::remove_pointer_t<T>>::value>::type> {
        static void deserialize(char* pos, char** rawData) {
            auto* p = reinterpret_cast<T>(pos);
            auto size = reinterpret_cast<size_t*>(*rawData);
            *rawData += sizeof(size_t);
            memcpy_s(pos, *size, *rawData, *size);
            *rawData += *size;
        }
    };

    //不可以直接内存拷贝的数组
    template<typename T>
    struct DeserializeHelper<T, typename std::enable_if<std::is_pointer<T>::value &
        !std::is_arithmetic<std::remove_pointer_t<T>>::value>::type> {
        static void deserialize(char* pos, char** rawData) {
            //TODO QIYI
        }
    };

    //vector
    template<typename T>
    struct DeserializeHelper<std::vector<T>, typename std::enable_if<true>::type> {

        //POD类型走此,直接通过内存块操作
        template<typename T>
        static inline typename std::enable_if<CheckisPod<T>::value>::type
            deserializeElement(char* pos, char** rawData, T&& t) {
            std::vector<T>* p = reinterpret_cast<std::vector<T>*>(pos);
            auto size = reinterpret_cast<size_t*>(*rawData);
            *rawData += sizeof(size_t);
            p->clear();
            p->resize(*size);
            memcpy_s(const_cast<T*>(p->data()), *size * sizeof(T), *rawData, *size * sizeof(T));
            *rawData += (*size * sizeof(T));
        }

        //其它类型只能循环赋值
        template<typename T>
        static inline typename std::enable_if<!CheckisPod<T>::value>::type
            deserializeElement(char* pos, char** rawData, T&& t) {
            std::vector<T>* p = reinterpret_cast<std::vector<T>*>(pos);
            auto size = reinterpret_cast<size_t*>(*rawData);
            *rawData += sizeof(size_t);
            p->clear();
            p->resize(*size);
            for (auto i = NULL; i < *size; i++) {
                VarForwarderdeSerial<T>::call(reinterpret_cast<char*>((&(*p)[i])), rawData);
                //DeserializeHelper<T>::deserialize(reinterpret_cast<char*>(const_cast<T*>(p->data())) + i * sizeof(T), rawData);
            }
        }

        static void deserialize(char* pos, char** rawData) {
            deserializeElement(pos, rawData, T()); //此处T可以不需要实体,但是还要嵌套对象偏特化.需要优化
        }
    };


    template<typename T>
    void deserializeMapHelper(char* pos, char** rawData) {
        T* p = reinterpret_cast<T*>(pos);
        auto size = reinterpret_cast<size_t*>(*rawData);
        *rawData += sizeof(size_t);
        p->clear();
        for (auto i = NULL; i < *size; i++) {
            typename T::key_type key;
            typename T::mapped_type val;
            DeserializeHelper<typename T::key_type>::deserialize(reinterpret_cast<char*>(&key), rawData);
            DeserializeHelper<typename T::mapped_type>::deserialize(reinterpret_cast<char*>(&val), rawData);
            (*p)[key] = val;
        }
    }

    //map
    template<typename KEY, typename VAL>
    struct DeserializeHelper<std::map<KEY, VAL>, typename std::enable_if<true>::type> {
        static void deserialize(char* pos, char** rawData) {
            deserializeMapHelper<std::map<KEY, VAL>>(pos, rawData);
        }
    };

    //std::pair
    template<typename First, typename Second>
    struct DeserializeHelper<std::pair<First, Second>, typename std::enable_if<true>::type> {
        static void deserialize(char* pos, char** rawData) {
            std::pair<First, Second>* p = reinterpret_cast<std::pair<First, Second>*>(pos);
            First first;
            Second second;
            DeserializeHelper<typename First>::deserialize(reinterpret_cast<char*>(&first), rawData);
            DeserializeHelper<typename Second>::deserialize(reinterpret_cast<char*>(&second), rawData);
            *p = std::make_pair(first, second);
        }
    };

    //unordered_map
    template<typename KEY, typename VAL>
    struct DeserializeHelper<std::unordered_map<KEY, VAL>, typename std::enable_if<true>::type> {
        static void deserialize(char* pos, char** rawData) {
            deserializeMapHelper<std::map<KEY, VAL>>(pos, rawData);
        }
    };

    /*   template<typename T>
    struct DeserializeHelper < T, typename std::is_same<decltype(std::declval<T>().serialize()), void>::type > {
    static void deserialize(char* pos, char** rawData) {

    }
    };*/

    template<typename T>
    struct VarForwarderdeSerial {
    private:
        template<typename C>
        static auto checkFun(C*)->typename std::is_same<decltype(std::declval<C>().serialize()), std::string>::type;
        template<typename>
        static std::false_type checkFun(...);

        typedef decltype(checkFun<T>(0)) HasSerializeFun;

        //显式声明POD类型直接内存拷贝
        static void callInner(char* pos, char** rawData, std::true_type) {
            memcpy(pos, *rawData, sizeof(T));
            *rawData += sizeof(T);
        }

        //未显式声明POD类型走老方法
        static void callInner(char* pos, char** rawData, std::false_type) {
            //结构体嵌套走此
            T* p = reinterpret_cast<T*>(pos);
            auto dataSize = reinterpret_cast<size_t*>(*rawData) + 1; //这里是要去掉标志位
            p->deserialize(*rawData);
            *rawData += (*dataSize);
        }

        static void chooseDeserialize(char* pos, char** rawData, std::true_type) { callInner(pos, rawData, typename CheckisPod<std::decay_t<T>>::check{}); }
        static void chooseDeserialize(char* pos, char** rawData, std::false_type) { DeserializeHelper<T>::deserialize(pos, rawData); }

    public:
        static void call(char* pos, char** rawData) {
            chooseDeserialize(pos, rawData, HasSerializeFun{});
        }
    };

    template<typename TUPLE, size_t SIZE>
    struct DeserializeInternal {
        static void call(char* obj, char* rawData) {
            //获得结构体偏移值
            auto offset = reinterpret_cast<size_t*>(rawData);
            rawData += sizeof(size_t);
            //DeserializeHelper<std::tuple_element<std::tuple_size<TUPLE>::value - SIZE, TUPLE>::type>::deserialize(obj + *offset, &rawData);
            VarForwarderdeSerial<std::tuple_element<std::tuple_size<TUPLE>::value - SIZE, TUPLE>::type>::call(obj + *offset, &rawData);
            DeserializeInternal<TUPLE, SIZE - 1>::call(reinterpret_cast<char*>(obj), const_cast<char*>(rawData));
        }
    };

    template<typename TUPLE>
    struct DeserializeInternal<TUPLE, 0> {
        static void call(char* obj, char* rawData) {
        }
    };

    //POD类型直接内存拷贝
    template<typename STRUCTTYPE>
    inline void chooseDeserializeInternal(STRUCTTYPE obj, const char* rawData, std::true_type) {
        memcpy(obj, rawData, sizeof(std::remove_pointer_t<STRUCTTYPE>));
    }

    template<typename STRUCTTYPE>
    inline void chooseDeserializeInternal(STRUCTTYPE obj, const char* rawData, std::false_type) {
        using tupleType = decltype(std::declval<STRUCTTYPE>()->getTuple());
        DeserializeInternal<tupleType, std::tuple_size<tupleType>::value>::call(reinterpret_cast<char*>(obj), const_cast<char*>(rawData));
    }

    //解序列化
    template<typename STRUCTTYPE>
    inline void deserializeEntrance(STRUCTTYPE obj, const char* rawData) {
        chooseDeserializeInternal(obj, const_cast<char*>(rawData),typename CheckisPod<std::remove_pointer_t<STRUCTTYPE>>::check{});
    }


}

UTILS_END

#endif