AUTOMAKE_OPTIONS=foreign

# Create dynamic libraries
lib_LTLIBRARIES=libml_hash.la
libml_hash_la_SOURCES=ml_hash.c hash_crc32.c hash_md.c hash_sha.c
libml_hash_la_CFLAGS=-g -I./


# 安装该包到 ($prefix}/include/meap_leaf/ml_hash/ 下
ml_hashincludedir=$(includedir)/@PACKAGENAME@/ml_hash
ml_hashinclude_HEADERS=ml_hash.h hash_crc32.h hash_md.h hash_sha.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_hash/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_hash

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_hash/ 下
EXTRA_DIST=sample.c

ml_hashdatadir=$(datarootdir)/@PACKAGENAME@/ml_hash
ml_hashdata_DATA=sample.c

