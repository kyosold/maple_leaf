AUTOMAKE_OPTIONS=foreign

# Create dynamic libraries
lib_LTLIBRARIES=libml_log.la
libml_log_la_SOURCES=ml_log.c
libml_log_la_CFLAGS=-g -I./


# 安装该包到 ($prefix}/include/meap_leaf/ml_log/ 下
ml_logincludedir=$(includedir)/@PACKAGENAME@/ml_log
ml_loginclude_HEADERS=ml_log.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_log/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_log

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_log/ 下
EXTRA_DIST=sample.c

ml_logdatadir=$(datarootdir)/@PACKAGENAME@/ml_log
ml_logdata_DATA=sample.c

