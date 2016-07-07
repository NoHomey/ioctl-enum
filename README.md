# ioctl-enum

C++ macro oriented framework in single header file for easier export of ioctl numbers to JavaScript and TypeScript. Removes the need of building native C++ Node.js Addons

# Installation

Install with npm:

```bash
$ npm install ioctl-enum
```

# Usage

Before including the header file:

```c++
#include "node_modules/ioctl-enum/ioctl-enum.h"
```

Define for which language you want to export for: (JavaScript, TypeScript or both) (see FAQ why defines must be before including the header):

## JavaScript

```c++
#define IOCTL_ENUM_JS
```

## TypeScript

```c++
#define IOCTL_ENUM_TS
```

Give a name to your enum:

```c++
IOCTL_ENUM("SomeName");
```
Add ioctl numbers to your enum:

```c++
IOCTL_ENUM("IOCTL_NUMBER", IOCTL_NUMBER);
```

Export your enum to language/s you defined with IOCTL_ENUM_[J/T]S:

```c++
IOCTL_ENUM_EXPORT();
```

Compile the file with g++ and C++11 Standart turned on (see FAQ why only g++ can be used) and run it:

```bash
g++ -std=c++11 <program name>.c/cc/cpp
./a.out
```

This will generate SomeName.[j/t]s file/s depending on the language of your choice.

# Example

## JavaScript:

```c
// ara_tester_ioctl.h
#ifndef _ARA_TESTER_H
#define _ARA_TESTER_H

#ifdef __KERNEL__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/errno.h>
#include "ara_tester_axis.h"

static int on_open(struct inode* inode, struct file* file);
static int on_release(struct inode* inode, struct file* file);
static long on_unlocked_ioctl(struct file * file, unsigned int command, unsigned long arguemnt);
static int __init on_init(void);
static void on_exit(void);

#else

#include <sys/ioctl.h>

#endif

#define ARA_TESTER_MAGIC_NUMBER '?'

#define _ARA_TESTER_DEFINE_IOCTL(action, number) _IO##action(ARA_TESTER_MAGIC_NUMBER, number, unsigned long)

#define ARA_TESTER_PAUSE _IO(ARA_TESTER_MAGIC_NUMBER, 0)
#define ARA_TESTER_RESUME _IO(ARA_TESTER_MAGIC_NUMBER, 1)

#define ARA_TESTER_SET_DIR _ARA_TESTER_DEFINE_IOCTL(W, 2)
#define ARA_TESTER_SET_T_MAX _ARA_TESTER_DEFINE_IOCTL(W, 3)
#define ARA_TESTER_SET_T_MIN _ARA_TESTER_DEFINE_IOCTL(W, 4)
#define ARA_TESTER_SET_T_DELTA _ARA_TESTER_DEFINE_IOCTL(W, 5)
#define ARA_TESTER_SET_LINEAR _ARA_TESTER_DEFINE_IOCTL(W, 6)

#define ARA_TESTER_GET_ACTIVE _ARA_TESTER_DEFINE_IOCTL(R, 7)
#define ARA_TESTER_GET_PAUSE _ARA_TESTER_DEFINE_IOCTL(R, 8)
#define ARA_TESTER_GET_TOTAL _ARA_TESTER_DEFINE_IOCTL(R, 9)
#define ARA_TESTER_GET_COUNTER _ARA_TESTER_DEFINE_IOCTL(R, 10)
#define ARA_TESTER_GET_MOVMENT_STATE _ARA_TESTER_DEFINE_IOCTL(R, 11)
#define ARA_TESTER_EXEC _ARA_TESTER_DEFINE_IOCTL(R, 12)

#define ARA_TESTER_LAST_IOCTL 12

#endif
```

```c++
// export_ioctl_js.cc
#define IOCTL_ENUM_JS
#include "ioctl-enum.h"
#include <ara_tester_ioctl.h>

IOCTL_ENUM("ARA_TESTER");
IOCTL_ENUM_IOCTL("ARA_TESTER_PAUSE", ARA_TESTER_PAUSE);
IOCTL_ENUM_IOCTL("ARA_TESTER_RESUME", ARA_TESTER_RESUME);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_DIR", ARA_TESTER_SET_DIR);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_T_MAX", ARA_TESTER_SET_T_MAX);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_T_MIN", ARA_TESTER_SET_T_MIN);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_T_DELTA", ARA_TESTER_SET_T_DELTA);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_LINEAR", ARA_TESTER_SET_LINEAR);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_ACTIVE", ARA_TESTER_GET_ACTIVE);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_PAUSE", ARA_TESTER_GET_PAUSE);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_TOTAL", ARA_TESTER_GET_TOTAL);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_COUNTER", ARA_TESTER_GET_COUNTER);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_MOVMENT_STATE", ARA_TESTER_GET_MOVMENT_STATE);
IOCTL_ENUM_IOCTL("ARA_TESTER_EXEC", ARA_TESTER_EXEC);
IOCTL_ENUM_EXPORT();
```

```bash
g++ -std=c++11 export_ioctl_js.cc
./a.out
```

```javascript
// ARA_TESTER.js
exports.ARA_TESTER = {
	ARA_TESTER_PAUSE: 16128,
	ARA_TESTER_RESUME: 16129,
	ARA_TESTER_SET_DIR: 1074282242,
	ARA_TESTER_SET_T_MAX: 1074282243,
	ARA_TESTER_SET_T_MIN: 1074282244,
	ARA_TESTER_SET_T_DELTA: 1074282245,
	ARA_TESTER_SET_LINEAR: 1074282246,
	ARA_TESTER_GET_ACTIVE: 2148024071,
	ARA_TESTER_GET_PAUSE: 2148024072,
	ARA_TESTER_GET_TOTAL: 2148024073,
	ARA_TESTER_GET_COUNTER: 2148024074,
	ARA_TESTER_GET_MOVMENT_STATE: 2148024075,
	ARA_TESTER_EXEC: 2148024076
};
```

And then require and use the generated object:

```javascript
// In JavaScript
const { ARA_TESTER } = require('./ARA_TESTER');
console.log(ARA_TESTER.ARA_TESTER_EXEC);
```

## TypeScript:

```c++
// export_ioctl_ts.cc
#define IOCTL_ENUM_TS
#include "ioctl-enum.h"
#include <ara_tester_ioctl.h>

IOCTL_ENUM("ARA_TESTER");
IOCTL_ENUM_IOCTL("ARA_TESTER_PAUSE", ARA_TESTER_PAUSE);
IOCTL_ENUM_IOCTL("ARA_TESTER_RESUME", ARA_TESTER_RESUME);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_DIR", ARA_TESTER_SET_DIR);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_T_MAX", ARA_TESTER_SET_T_MAX);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_T_MIN", ARA_TESTER_SET_T_MIN);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_T_DELTA", ARA_TESTER_SET_T_DELTA);
IOCTL_ENUM_IOCTL("ARA_TESTER_SET_LINEAR", ARA_TESTER_SET_LINEAR);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_ACTIVE", ARA_TESTER_GET_ACTIVE);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_PAUSE", ARA_TESTER_GET_PAUSE);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_TOTAL", ARA_TESTER_GET_TOTAL);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_COUNTER", ARA_TESTER_GET_COUNTER);
IOCTL_ENUM_IOCTL("ARA_TESTER_GET_MOVMENT_STATE", ARA_TESTER_GET_MOVMENT_STATE);
IOCTL_ENUM_IOCTL("ARA_TESTER_EXEC", ARA_TESTER_EXEC);
IOCTL_ENUM_EXPORT();
```

```bash
g++ -std=c++11 export_ioctl_ts.cc
./a.out
```

```typescript
// ARA_TESTER.ts
export const enum ARA_TESTER{
	ARA_TESTER_PAUSE = 16128,
	ARA_TESTER_RESUME = 16129,
	ARA_TESTER_SET_DIR = 1074282242,
	ARA_TESTER_SET_T_MAX = 1074282243,
	ARA_TESTER_SET_T_MIN = 1074282244,
	ARA_TESTER_SET_T_DELTA = 1074282245,
	ARA_TESTER_SET_LINEAR = 1074282246,
	ARA_TESTER_GET_ACTIVE = 2148024071,
	ARA_TESTER_GET_PAUSE = 2148024072,
	ARA_TESTER_GET_TOTAL = 2148024073,
	ARA_TESTER_GET_COUNTER = 2148024074,
	ARA_TESTER_GET_MOVMENT_STATE = 2148024075,
	ARA_TESTER_EXEC = 2148024076
};
```
And then require and use the generated const enum:

```typescript
// In TypeScript
import { ARA_TESTER } from './ARA_TESTER';
console.log(ARA_TESTER.ARA_TESTER_EXEC);
```

## Both:

Just add both defines before any including:

```c++
#define IOCTL_ENUM_JS
#define IOCTL_ENUM_TS
```

# Warning

Add ioctl_enum's ioctls exporting to your building. Generate the TypeScript enum/ JavaScript object for each machine your project will be running at, ioctl_enum just uses the result of _IO, _IOR, _IOW, _IOWR macros wich is unsigned long C number and it differs at different Unixes, Distributions and versions. Just like you would build the native C++ Addon that wrapps the ioctl numbers on each machine !!!

Example:

```typescript
// Ran on my laptop (Ubuntu 16.04)
// ARA_TESTER.ts
export enum ARA_TESTER {
	ARA_TESTER_PAUSE = 16128,
	ARA_TESTER_RESUME = 16129,
	ARA_TESTER_SET_DIR = 1074282242,
	ARA_TESTER_SET_T_MAX = 1074282243,
	ARA_TESTER_SET_T_MIN = 1074282244,
	ARA_TESTER_SET_T_DELTA = 1074282245,
	ARA_TESTER_SET_LINEAR = 1074282246,
	ARA_TESTER_GET_ACTIVE = 2148024071,
	ARA_TESTER_GET_PAUSE = 2148024072,
	ARA_TESTER_GET_TOTAL = 2148024073,
	ARA_TESTER_GET_COUNTER = 2148024074,
	ARA_TESTER_GET_MOVMENT_STATE = 2148024075,
	ARA_TESTER_EXEC = 2148024076
};
```

```typescript
// Ran on my Raspberry Pi 2 B+ (Raspbian May 2016 2016-05-27 4.4.1.17)
// ARA_TESTER.ts
export enum ARA_TESTER {
	ARA_TESTER_PAUSE = 16128,
	ARA_TESTER_RESUME = 16129,
	ARA_TESTER_SET_DIR = 1074020098,
	ARA_TESTER_SET_T_MAX = 1074020099,
	ARA_TESTER_SET_T_MIN = 1074020100,
	ARA_TESTER_SET_T_DELTA = 1074020101,
	ARA_TESTER_SET_LINEAR = 1074020102,
	ARA_TESTER_GET_ACTIVE = 2147761927,
	ARA_TESTER_GET_PAUSE = 2147761928,
	ARA_TESTER_GET_TOTAL = 2147761929,
	ARA_TESTER_GET_COUNTER = 2147761930,
	ARA_TESTER_GET_MOVMENT_STATE = 2147761931,
	ARA_TESTER_EXEC = 2147761932
};
```

# FAQ

## Why using ioctl_enum instead of writing C++ addon ?

A: Well beacuse just for exporting N ioctl numbers to Node.js you will write alot of code for just creating a JavaScript Object why not let ioctl-enum do it for you ?  Also exporting with ioctl-enum is going to cost you N + 4 lines of code just to export you ioctls so you can controll your device driver from Node.js.

## Q: Why defines must be before including the header file ?

A: Because they tell the framework for which language to implement exporting functionality.
The header file is structured like this:

```c++
#define IOCTL_ENUM_OPERATION_SINGLE(arg1, arg2) /* ... */

#ifdef IOCTL_ENUM_X

#define _IOCTL_ENUM_OPERATION_X()   _IOCTL_ENUM_OPERATION_SINGLE(arg1, arg2)

#else

IOCTL_ENUM_OPERATION_X()   _IOCTL_ENUM_DO_NOP()

#endif

#define IOCTL_ENUM_OPERATION() \
	_IOCTL_ENUM_OPERATION_X(); \
	_IOCTL_ENUM_OPERATION_Y() \
```

Which is the only way to simulate the language agnostic construction:

```c++
if(X) {
/* ... */
}
```

Also this way the code is modular it's easy to add more exporting formats for more languages (eg. JSON).

## Q: Why g++ is the only supported compiler ?

A: Alot of gcc and respectively g++ hacks are used in to make the framework as easy to use as possible (eg. operators #, ##) Also g++ is avalible for all unixes and unix is the platform where ioctls are used in first place so there shouldn't be a problem whith g++ beeing required.

## Q: Which versions of g++ are supported ?

A: g++ with version above 4.8 is garanted to work since it's C++11 future complate.
Earlier versions may work as well infact any version that supports std::to_string will work.

## Q: How ioctl-enum works ?

A: Using IOCTL_ENUM, IOCTL_ENUM_IOCTL and IOCTL_ENUM_EXPORT forms a whole C++ program that has it's own int main function wich generates strings as you use IOCTL_ENUM and IOCTL_ENUM_IOCTL and than writes those strings to files when you call IOCTL_ENUM_EXPORT.

Under the hood: this is how int main function would looked like if ioctl numbers from exaple were exported both to JavaScript and TypeScript:

```c++
int main(void) {
	std::ofstream out_file;
	std::string enum_name = "ARA_TESTER";
	std::string f_name;
	std::string tmp;
	std::string str_js = "exports.";
	str_js += enum_name;
	str_js += " = {\n";
	std::string str_ts = "export const enum ";
	str_ts += enum_name;
	str_ts += "{\n";;
	str_js += "\t";
	str_js += "ARA_TESTER_PAUSE";
	str_js += ": ";
	str_js += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((0)) << 0) | ((0) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_PAUSE";
	str_ts += " = ";
	str_ts += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((0)) << 0) | ((0) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_RESUME";
	str_js += ": ";
	str_js += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((1)) << 0) | ((0) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_RESUME";
	str_ts += " = ";
	str_ts += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((1)) << 0) | ((0) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_SET_DIR";
	str_js += ": ";
	str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((2)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_SET_DIR";
	str_ts += " = ";
	str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((2)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_SET_T_MAX";
	str_js += ": ";
	str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((3)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_SET_T_MAX";
	str_ts += " = ";
	str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((3)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_SET_T_MIN";
	str_js += ": ";
	str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((4)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_SET_T_MIN";
	str_ts += " = ";
	str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((4)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_SET_T_DELTA";
	str_js += ": ";
	str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((5)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_SET_T_DELTA";
	str_ts += " = ";
	str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((5)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_SET_LINEAR";
	str_js += ": ";
	str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((6)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_SET_LINEAR";
	str_ts += " = ";
	str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((6)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_GET_ACTIVE";
	str_js += ": ";
	str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((7)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_GET_ACTIVE";
	str_ts += " = ";
	str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((7)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_GET_PAUSE";
	str_js += ": ";
	str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((8)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_GET_PAUSE";
	str_ts += " = ";
	str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((8)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_GET_TOTAL";
	str_js += ": ";
	str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((9)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_GET_TOTAL";
	str_ts += " = ";
	str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((9)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_GET_COUNTER";
	str_js += ": ";
	str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((10)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_GET_COUNTER";
	str_ts += " = ";
	str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((10)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_GET_MOVMENT_STATE";
	str_js += ": ";
	str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((11)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_GET_MOVMENT_STATE";
	str_ts += " = ";
	str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((11)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	str_js += "\t";
	str_js += "ARA_TESTER_EXEC";
	str_js += ": ";
	str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((12)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_js += ",\n";
	str_ts += "\t";
	str_ts += "ARA_TESTER_EXEC";
	str_ts += " = ";
	str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((12)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
	str_ts += ",\n";
	tmp = str_js;
	tmp.pop_back();
	tmp.pop_back();
	tmp += "\n};\n";
	f_name = enum_name;
	f_name += ".";
	f_name += "js";
	out_file.open(f_name.c_str());
	out_file << tmp;
	out_file.close();
	tmp = str_ts;
	tmp.pop_back();
	tmp.pop_back();
	tmp += "\n};\n";
	f_name = enum_name;
	f_name += ".";
	f_name += "ts";
	out_file.open(f_name.c_str());
	out_file << tmp;
	out_file.close();
	return 0;
};
```

You can check for fun yours with the following Node.js code:

```javascript
// get_main.js
// node get_main.js export_ioctl_both.cc
var fs = require('fs');
var { exec } = require('child_process');
exec(`g++ -std=c++11 -E ${process.argv[2]}`, {maxBuffer: 100000000000}, (err, out) => {
    if (err) {
        console.error(err);
    } else {
        out = out.substr(out.indexOf("int main"), out.length);
        out = out.replace(/\n\# \d+ \"gen.c\"( 3 4)?\n/g, '');
        out = out.replace(/; /g, ';\n');
        out = out.replace(/ std::ofstream/g, '\nstd::ofstream');
        for(var c of 'stfor') {
            out = out.replace(new RegExp('\n' + c, 'g'), '\n\t' + c);
        }
        console.log(out);
    }

});
```

## Q: Why are you natively supporting TypeScript ?

A: Well as a kernel hacker and developer who is making JavaScript MVC** IoT interfaces and some Node.js addons I'm using C and C++ alot and having staticly typed code is how big projects are done right. Also I like TypeScript it's the first good thing in Microsoft I see ... But more about me in About me section below.

# About me

## Q: Who I'm ?

A: I'm Ivo Stratev and I'm 19 years old who just finished hihg school at Technological school "Electronic Systems" at the Technical University - Sofia with 5.85 of possible 6.00.

There I've learn to code. I'm self taught in kernel programming currenlty only under Linux. I'm doing alot of IoT and for the interfaces I used to use Angular.js but now I'm using React and the new version of Angular (known as Angular 2) also using Node.js (express and Hapi) for middle layer in the communication with the device drivers I make.

I haven't always been staticly typed fan I used to do alot of Ruby, Python and CoffeeScipt but after my last big project which at the end was more than 10K lines of code I realised that static type do pay of so I recommend every JavaScript programmer to use TypeScript (even if I my self hate Microsoft and what they have done ... mainly for IE, any way there are two good things created by them: AJAX and TypeScript).

Besides programming (coding) I'm training every day.




