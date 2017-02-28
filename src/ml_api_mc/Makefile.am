AUTOMAKE_OPTIONS=foreign

# [动态库]
lib_LTLIBRARIES=libml_api_mc.la
libml_api_mc_la_SOURCES=ml_api_mc.c
libml_api_mc_la_CFLAGS=-g -I./

# 安装头文件到 {$prefix}/include/meap_leaf/ml_api_mc/ 下
ml_api_mcincludedir=$(includedir)/@PACKAGENAME@/ml_api_mc
ml_api_mcinclude_HEADERS=ml_api_mc.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_api_mc/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_api_mc

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_api_mc/ 下
EXTRA_DIST=sample.c

ml_api_mcdatadir=$(datarootdir)/@PACKAGENAME@/ml_api_mc
ml_api_mcdata_DATA=sample.c
