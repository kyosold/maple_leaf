AUTOMAKE_OPTIONS=foreign

# Create dynamic libraries
lib_LTLIBRARIES=libml_dictionary.la
libml_dictionary_la_SOURCES=ml_dictionary.c 
libml_dictionary_la_CFLAGS=-g -I./


# 安装该包到 ($prefix}/include/meap_leaf/ml_dictionary/ 下
ml_dictionaryincludedir=$(includedir)/@PACKAGENAME@/ml_dictionary
ml_dictionaryinclude_HEADERS=ml_dictionary.h

# 安装库文件到 {$prefix}/lib64/meap_leaf/ml_dictionary/ 下
libdir=$(prefix)/lib64/@PACKAGENAME@/ml_dictionary

# 安装文档文件到 {$prefix}/share/meap_leaf/ml_dictionary/ 下
EXTRA_DIST=sample.c

ml_dictionarydatadir=$(datarootdir)/@PACKAGENAME@/ml_dictionary
ml_dictionarydata_DATA=sample.c

