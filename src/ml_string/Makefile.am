AUTOMAKE_OPTIONS=foreign

# Create dynamic libraries
lib_LTLIBRARIES=libml_string.la
libml_string_la_SOURCES=ml_string.c
libml_string_la_CFLAGS=-g -I./


# 安装该包到 ($prefix}/include/meap_leaf/ml_string/ 下
ml_stringincludedir=$(includedir)/@PACKAGENAME@/ml_string
ml_stringinclude_HEADERS=ml_string.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_string/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_string

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_string/ 下
EXTRA_DIST=sample.c

ml_stringdatadir=$(datarootdir)/@PACKAGENAME@/ml_string
ml_stringdata_DATA=sample.c

