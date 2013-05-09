#ifndef __ORG_APACHE_HARMONY_LUNI_PLATFORM_IFILESYSTEM__
#define __ORG_APACHE_HARMONY_LUNI_PLATFORM_IFILESYSTEM__

#include "xmlvm.h"

// Preprocessor constants for interfaces:
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_read___long_byte_1ARRAY_int_int 7
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_write___long_byte_1ARRAY_int_int 17
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_readv___long_long_1ARRAY_int_1ARRAY_int_1ARRAY_int 8
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_writev___long_java_lang_Object_1ARRAY_int_1ARRAY_int_1ARRAY_int 18
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_readDirect___long_long_int_int 6
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_writeDirect___long_long_int_int 16
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_lock___long_long_long_int_boolean 4
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_unlock___long_long_long 15
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_seek___long_long_int 9
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_fflush___long_boolean 2
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_close___long 1
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_truncate___long_long 12
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_getAllocGranularity__ 3
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_open___byte_1ARRAY_int 5
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_transfer___long_java_io_FileDescriptor_long_long 11
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_ttyAvailable__ 13
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_available___long 0
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_size___long 10
#define XMLVM_ITABLE_IDX_org_apache_harmony_luni_platform_IFileSystem_ttyRead___byte_1ARRAY_int_int 14
// Implemented interfaces:
// Super Class:
#include "java_lang_Object.h"

// Circular references:
#ifndef XMLVM_FORWARD_DECL_java_io_FileDescriptor
#define XMLVM_FORWARD_DECL_java_io_FileDescriptor
XMLVM_FORWARD_DECL(java_io_FileDescriptor)
#endif

XMLVM_DEFINE_CLASS(org_apache_harmony_luni_platform_IFileSystem, 0, 0)

extern JAVA_OBJECT __CLASS_org_apache_harmony_luni_platform_IFileSystem;
extern JAVA_OBJECT __CLASS_org_apache_harmony_luni_platform_IFileSystem_1ARRAY;
extern JAVA_OBJECT __CLASS_org_apache_harmony_luni_platform_IFileSystem_2ARRAY;
extern JAVA_OBJECT __CLASS_org_apache_harmony_luni_platform_IFileSystem_3ARRAY;
#ifndef XMLVM_FORWARD_DECL_org_apache_harmony_luni_platform_IFileSystem
#define XMLVM_FORWARD_DECL_org_apache_harmony_luni_platform_IFileSystem
typedef struct org_apache_harmony_luni_platform_IFileSystem org_apache_harmony_luni_platform_IFileSystem;
#endif

void __INIT_org_apache_harmony_luni_platform_IFileSystem();
void __INIT_IMPL_org_apache_harmony_luni_platform_IFileSystem();
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_SHARED_LOCK_TYPE();
void org_apache_harmony_luni_platform_IFileSystem_PUT_SHARED_LOCK_TYPE(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_EXCLUSIVE_LOCK_TYPE();
void org_apache_harmony_luni_platform_IFileSystem_PUT_EXCLUSIVE_LOCK_TYPE(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_SEEK_SET();
void org_apache_harmony_luni_platform_IFileSystem_PUT_SEEK_SET(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_SEEK_CUR();
void org_apache_harmony_luni_platform_IFileSystem_PUT_SEEK_CUR(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_SEEK_END();
void org_apache_harmony_luni_platform_IFileSystem_PUT_SEEK_END(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_RDONLY();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_RDONLY(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_WRONLY();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_WRONLY(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_RDWR();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_RDWR(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_RDWRSYNC();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_RDWRSYNC(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_APPEND();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_APPEND(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_CREAT();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_CREAT(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_EXCL();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_EXCL(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_NOCTTY();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_NOCTTY(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_NONBLOCK();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_NONBLOCK(JAVA_INT v);
JAVA_INT org_apache_harmony_luni_platform_IFileSystem_GET_O_TRUNC();
void org_apache_harmony_luni_platform_IFileSystem_PUT_O_TRUNC(JAVA_INT v);

#endif