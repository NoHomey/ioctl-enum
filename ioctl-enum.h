#include <fstream>
#include <string>

#define _IOCTL_ENUM_DO_NOP() do { } while(0)

#define _IOCTL_ENUM_SINGLE(extention, begin, end) \
    std::string str_##extention = begin; \
    str_##extention += enum_name; \
    str_##extention += end \

#ifdef IOCTL_ENUM_JS

#define _IOCTL_ENUM_JS(name) _IOCTL_ENUM_SINGLE(js, "exports.", " = {\n")

#else

#define _IOCTL_ENUM_JS(name) _IOCTL_ENUM_DO_NOP()

#endif

#ifdef IOCTL_ENUM_TS

#define _IOCTL_ENUM_TS(name)  _IOCTL_ENUM_SINGLE(ts, "export const enum ", "{\n")

#else

#define _IOCTL_ENUM_TS(name) _IOCTL_ENUM_DO_NOP()

#endif

#define _IOCTL_ENUM_IOCTL_SINGLE(extention, ioctl, value, separator) \
    str_##extention += "\t"; \
    str_##extention += ioctl; \
    str_##extention += separator; \
    str_##extention += std::to_string(value); \
    str_##extention += ",\n" \

#ifdef IOCTL_ENUM_JS

#define _IOCTL_ENUM_IOCTL_JS(ioctl, value) _IOCTL_ENUM_IOCTL_SINGLE(js, ioctl, value, ": ")

#else

#define _IOCTL_ENUM_IOCTL_JS(ioctl, value) _IOCTL_ENUM_DO_NOP()

#endif

#ifdef IOCTL_ENUM_TS

#define _IOCTL_ENUM_IOCTL_TS(ioctl, value) _IOCTL_ENUM_IOCTL_SINGLE(ts, ioctl, value, " = ")

#else

#define _IOCTL_ENUM_IOCTL_TS(ioctl, value) _IOCTL_ENUM_DO_NOP()

#endif

#define IOCTL_ENUM_IOCTL(ioctl, value) \
    _IOCTL_ENUM_IOCTL_JS(ioctl, value); \
    _IOCTL_ENUM_IOCTL_TS(ioctl, value) \

#define _IOCTL_ENUM_EXPORT_SINGLE(extention) \
    tmp = str_##extention; \
    tmp.pop_back(); \
    tmp.pop_back(); \
    tmp += "\n};\n"; \
    f_name = enum_name; \
    f_name += "."; \
    f_name += #extention; \
    out_file.open(f_name.c_str()); \
    out_file << tmp; \
    out_file.close() \

#ifdef IOCTL_ENUM_JS

#define  _IOCTL_ENUM_EXPORT_JS() _IOCTL_ENUM_EXPORT_SINGLE(js)

#else 

#define _IOCTL_ENUM_EXPORT_JS() _IOCTL_ENUM_DO_NOP()

#endif

#ifdef IOCTL_ENUM_TS

#define  _IOCTL_ENUM_EXPORT_TS() _IOCTL_ENUM_EXPORT_SINGLE(ts)

#else 

#define _IOCTL_ENUM_EXPORT_TS() _IOCTL_ENUM_DO_NOP()

#endif

#define IOCTL_ENUM_EXPORT() \
    _IOCTL_ENUM_EXPORT_JS(); \
    _IOCTL_ENUM_EXPORT_TS(); \
    return 0; \
}

#define IOCTL_ENUM(name) \
int main(void) { \
    std::ofstream out_file; \
    std::string enum_name = name; \
    std::string f_name; \
    std::string tmp; \
    _IOCTL_ENUM_JS(); \
    _IOCTL_ENUM_TS(); \

