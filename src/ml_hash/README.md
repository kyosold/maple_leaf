ml_hash
=======

Intro
-----
[ml_hash] Generate a hash value (message digest)


Usage
------------

```bash
cp /usr/local/maple_leaf/share/maple_leaf/ml_hash/sample.c ./sample.c

gcc -g -o sample sample.c -I /usr/local/maple_leaf/include/ -L /usr/local/maple_leaf/lib64/maple_leaf/ml_hash/ -lml_hash
````

#### 动态库引入

```bash
echo "/usr/local/maple_leaf/lib64/maple_leaf/ml_hash/" >> /etc/ld.so.conf.d/maple_leaf.conf
/sbin/ldconfig
````
