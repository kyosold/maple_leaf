AUTOMAKE_OPTIONS=foreign

# Create dynamic libraries
lib_LTLIBRARIES=libml_hashmap.la
libml_hashmap_la_SOURCES=ml_hashmap.c
libml_hashmap_la_CFLAGS=-g -I./


# 安装该包到 ($prefix}/include/meap_leaf/ml_hashmap/ 下
ml_hashmapincludedir=$(includedir)/@PACKAGENAME@/ml_hashmap
ml_hashmapinclude_HEADERS=ml_hashmap.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_hashmap/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_hashmap

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_hashmap/ 下
EXTRA_DIST=sample.c

ml_hashmapdatadir=$(datarootdir)/@PACKAGENAME@/ml_hashmap
ml_hashmapdata_DATA=sample.c

