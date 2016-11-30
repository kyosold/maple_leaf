ml_string
=======

Intro
-----
[ml_string]


Usage
------------

```bash
cp /usr/local/maple_leaf/share/maple_leaf/ml_string/sample.c ./sample.c

gcc -g -o sample sample.c -I /usr/local/maple_leaf/include/ -L /usr/local/maple_leaf/lib64/maple_leaf/ml_string/ -lml_string
````

#### 动态库引入

```bash
echo "/usr/local/maple_leaf/lib64/maple_leaf/ml_string/" >> /etc/ld.so.conf.d/maple_leaf.conf
/sbin/ldconfig
````
