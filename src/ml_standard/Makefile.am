AUTOMAKE_OPTIONS=foreign

# Create dynamic libraries
lib_LTLIBRARIES=libml_standard.la
libml_standard_la_SOURCES=ml_base64.c ml_utils.c
libml_standard_la_CFLAGS=-g -I./


# 安装该包到 ($prefix}/include/meap_leaf/ml_standard/ 下
ml_standardincludedir=$(includedir)/@PACKAGENAME@/ml_standard
ml_standardinclude_HEADERS=ml_standard.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_standard/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_standard

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_standard/ 下
EXTRA_DIST=sample.c

ml_standarddatadir=$(datarootdir)/@PACKAGENAME@/ml_standard
ml_standarddata_DATA=sample.c

