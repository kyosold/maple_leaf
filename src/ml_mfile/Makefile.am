AUTOMAKE_OPTIONS=foreign

# [动态库]
lib_LTLIBRARIES=libml_mfile.la
libml_mfile_la_SOURCES=ml_mfile.c
libml_mfile_la_CFLAGS=-g -I./

# 安装该包到 ($prefix}/include/meap_leaf/ml_mfile/ 下
ml_mfileincludedir=$(includedir)/@PACKAGENAME@/ml_mfile
ml_mfileinclude_HEADERS=ml_mfile.h queue.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_mfile/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_mfile

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_mfile/ 下
EXTRA_DIST=sample.c

ml_mfiledatadir=$(datarootdir)/@PACKAGENAME@/ml_mfile
ml_mfiledata_DATA=sample.c

