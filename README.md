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

Define for which language you want to export for: (JavaScript, TypeScript or both) (see #FAQ why defines must be before including the header):

## JavaScript

```c++
#define IOCTL_ENUM_JS
```

## TypeScript

```c++
#define IOCTL_ENUM_TS
```

Name your enum (required for JavaScript compatibility with TypeScript enums, see #FAQ why):

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

```c
// ara_tester.h
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
	"ARA_TESTER_PAUSE": 16128,
	"16128": "ARA_TESTER_PAUSE",
	"ARA_TESTER_RESUME": 16129,
	"16129": "ARA_TESTER_RESUME",
	"ARA_TESTER_SET_DIR": 1074282242,
	"1074282242": "ARA_TESTER_SET_DIR",
	"ARA_TESTER_SET_T_MAX": 1074282243,
	"1074282243": "ARA_TESTER_SET_T_MAX",
	"ARA_TESTER_SET_T_MIN": 1074282244,
	"1074282244": "ARA_TESTER_SET_T_MIN",
	"ARA_TESTER_SET_T_DELTA": 1074282245,
	"1074282245": "ARA_TESTER_SET_T_DELTA",
	"ARA_TESTER_SET_LINEAR": 1074282246,
	"1074282246": "ARA_TESTER_SET_LINEAR",
	"ARA_TESTER_GET_ACTIVE": 2148024071,
	"2148024071": "ARA_TESTER_GET_ACTIVE",
	"ARA_TESTER_GET_PAUSE": 2148024072,
	"2148024072": "ARA_TESTER_GET_PAUSE",
	"ARA_TESTER_GET_TOTAL": 2148024073,
	"2148024073": "ARA_TESTER_GET_TOTAL",
	"ARA_TESTER_GET_COUNTER": 2148024074,
	"2148024074": "ARA_TESTER_GET_COUNTER",
	"ARA_TESTER_GET_MOVMENT_STATE": 2148024075,
	"2148024075": "ARA_TESTER_GET_MOVMENT_STATE",
	"ARA_TESTER_EXEC": 2148024076,
	"2148024076": "ARA_TESTER_EXEC"
};
```

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

## What are the JavaScript to TypeSript compatibilities ?

There are two compatibilities:

### How exported ioctls wrapper is required:

```typescript
// In TypeScript
import { SomeName } from './SomeName';
```

```javascript
// In JavaScript
const { SomeName } = require('./SomeName');
```


## How ioctl-enum works ?

Using IOCTL_ENUM, IOCTL_ENUM_IOCTL and IOCTL_ENUM_EXPORT forms a whole C++ program that has it's own int main function wich generates strings as you use the macros and that writes those strings to files.

Under the hood: this is how main function looks like for exporting both to JavaScript and TypeScript:

```c++
int main(void) {
    std::ofstream out_file;
    std::string enum_name = "ARA_TESTER";
    std::string f_name;
    std::string tmp;
    std::string str_js = "exports.";
    str_js += "ARA_TESTER";
    str_js += " = {\n";
    std::string str_ts = "export enum ";
    str_ts += "ARA_TESTER";
    str_ts += " {\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_PAUSE";
    str_js += "\": ";
    str_js += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((0)) << 0) | ((0) << ((0 +8)+8))));
    str_js += ",\n"; str_js += "\t\""; str_js += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((0)) << 0) | ((0) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_PAUSE";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_PAUSE";
    str_ts += " = ";
    str_ts += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((0)) << 0) | ((0) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_RESUME";
    str_js += "\": ";
    str_js += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((1)) << 0) | ((0) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((1)) << 0) | ((0) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_RESUME";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_RESUME";
    str_ts += " = ";
    str_ts += std::to_string((((0U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((1)) << 0) | ((0) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_SET_DIR";
    str_js += "\": ";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((2)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((2)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_SET_DIR";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_SET_DIR";
    str_ts += " = ";
    str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((2)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_SET_T_MAX";
    str_js += "\": ";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((3)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((3)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_SET_T_MAX";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_SET_T_MAX";
    str_ts += " = ";
    str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((3)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8)))); str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_SET_T_MIN";
    str_js += "\": ";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((4)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((4)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_SET_T_MIN";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_SET_T_MIN";
    str_ts += " = ";
    str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((4)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_SET_T_DELTA";
    str_js += "\": ";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((5)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((5)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_SET_T_DELTA";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_SET_T_DELTA";
    str_ts += " = ";
    str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((5)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_SET_LINEAR";
    str_js += "\": ";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((6)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((6)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_SET_LINEAR";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_SET_LINEAR";
    str_ts += " = ";
    str_ts += std::to_string((((1U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((6)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_GET_ACTIVE";
    str_js += "\": ";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((7)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((7)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_GET_ACTIVE";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_GET_ACTIVE";
    str_ts += " = ";
    str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((7)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_GET_PAUSE";
    str_js += "\": ";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((8)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8)));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((8)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_GET_PAUSE";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_GET_PAUSE";
    str_ts += " = ";
    str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((8)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_GET_TOTAL";
    str_js += "\": ";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((9)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((9)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8)));
    str_js += "\": \"";
    str_js += "ARA_TESTER_GET_TOTAL";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_GET_TOTAL";
    str_ts += " = ";
    str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((9)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8)));
    str_ts += ",\n";
    str_js += "\t\""; 
    str_js += "ARA_TESTER_GET_COUNTER";
    str_js += "\": ";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((10)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((10)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_GET_COUNTER";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_GET_COUNTER";
    str_ts += " = ";
    str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((10)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_GET_MOVMENT_STATE";
    str_js += "\": ";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((11)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n";
    str_js += "\t\"";
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((11)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_GET_MOVMENT_STATE";
    str_js += "\",\n";
    str_ts += "\t";
    str_ts += "ARA_TESTER_GET_MOVMENT_STATE";
    str_ts += " = ";
    str_ts += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((11)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_ts += ",\n";
    str_js += "\t\"";
    str_js += "ARA_TESTER_EXEC";
    str_js += "\": "
    str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((12)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += ",\n"; str_js += "\t\""; str_js += std::to_string((((2U) << (((0 +8)+8)+14)) | ((('?')) << (0 +8)) | (((12)) << 0) | ((((sizeof(unsigned long)))) << ((0 +8)+8))));
    str_js += "\": \"";
    str_js += "ARA_TESTER_EXEC";
    str_js += "\",\n";
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




