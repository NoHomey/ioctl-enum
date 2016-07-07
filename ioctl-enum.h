#include <fstream>
#include <string>

// IOCTL_ENUM_JS, IOCTL_ENUM_TS, IOCTL_ENUM, IOCTL_ENUM_IOCTL, IOCTL_ENUM_EXPORT

#define _IOCTL_ENUM_DO_NOP() do { } while(0)

#ifdef IOCTL_ENUM_JS

#define _IOCTL_ENUM_JS(name) \
    std::string str_js = "exports."; \
    str_js += name; \
    str_js += " = {\n" \

#else

#define _IOCTL_ENUM_JS(name) _IOCTL_ENUM_DO_NOP()

#endif

#ifdef IOCTL_ENUM_TS

#define _IOCTL_ENUM_TS(name) \
    std::string str_ts = "export enum "; \
    str_ts += name; \
    str_ts += " {\n" \

#else

#define _IOCTL_ENUM_TS(name) _IOCTL_ENUM_DO_NOP()

#endif

#ifdef IOCTL_ENUM_JS

#define _IOCTL_ENUM_IOCTL_JS(ioctl, value) \
    str_js += "\t\""; \
    str_js += ioctl; \
    str_js += "\": "; \
    str_js += std::to_string(value); \
    str_js += ",\n"; \
    str_js += "\t\""; \
    str_js += std::to_string(value); \
    str_js += "\": \""; \
    str_js += ioctl; \
    str_js += "\",\n" \

#else

#define _IOCTL_ENUM_IOCTL_JS(ioctl, value) _IOCTL_ENUM_DO_NOP()

#endif

#ifdef IOCTL_ENUM_TS

#define _IOCTL_ENUM_IOCTL_TS(ioctl, value) \
    str_ts += "\t"; \
    str_ts += ioctl; \
    str_ts += " = "; \
    str_ts += std::to_string(value); \
    str_ts += ",\n" \

#else

#define _IOCTL_ENUM_IOCTL_TS(ioctl, value) _IOCTL_ENUM_DO_NOP()

#endif

#define IOCTL_ENUM_IOCTL(ioctl, value) \
    _IOCTL_ENUM_IOCTL_JS(ioctl, value); \
    _IOCTL_ENUM_IOCTL_TS(ioctl, value)

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
} \

#define IOCTL_ENUM(name) \
int main(void) { \
    std::ofstream out_file; \
    std::string enum_name = name;\
    std::string f_name; \
    std::string tmp; \
    _IOCTL_ENUM_JS(name); \
    _IOCTL_ENUM_TS(name) \