ml_dictionary
=======

Intro
-----
[ml_dictionary] 实现了一个字典对象，比如一个字符串列表，这个对象可以以key->value形式进行读写。 


Usage
------------

```bash
cp /usr/local/maple_leaf/share/maple_leaf/ml_dictionary/sample.c ./sample.c

gcc -g -o sample sample.c -I /usr/local/maple_leaf/include/ -L /usr/local/maple_leaf/lib64/maple_leaf/ml_dictionary/ -lml_dictionary
````

#### 动态库引入

```bash
echo "/usr/local/maple_leaf/lib64/maple_leaf/ml_dictionary/" >> /etc/ld.so.conf.d/maple_leaf.conf
/sbin/ldconfig
````
