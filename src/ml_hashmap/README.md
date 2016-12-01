ml_hashmap
=======

Intro
-----
[ml_hashmap] 是一套可以使用内存做的map表，对其使用key->value键值对进行insert, find, delete操作。


Usage
------------

```bash
cp /usr/local/maple_leaf/share/maple_leaf/ml_hashmap/sample.c ./sample.c

gcc -g -o sample sample.c -I /usr/local/maple_leaf/include/ -L /usr/local/maple_leaf/lib64/maple_leaf/ml_hashmap/ -lml_hashmap
````

#### 动态库引入

```bash
echo "/usr/local/maple_leaf/lib64/maple_leaf/ml_hashmap/" >> /etc/ld.so.conf.d/maple_leaf.conf
/sbin/ldconfig
````
