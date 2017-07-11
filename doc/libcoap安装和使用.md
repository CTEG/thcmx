`CoAP`是一种面向网络的协议，采用了与`HTTP`类似的特征，核心内容为资源抽象、`REST`交互以及可扩展的头选项等。 为了克服`HTTP`对于受限环境的劣势，`CoAP`既考虑到数据报长度的最优化，又考虑到提供可靠通信。一方面，`CoAP`提供`URI`，`REST`式的方法，如`GET`，`POST`，`PUT`和`DELETE`，以及可以独立定义的头选项以提高可扩展性。另一方面，`CoAP`基于`UDP`协议，为了弥补`UDP`传输的不可靠性，`CoAP`定义了带有重传机制的事务处理机制。

`libcoap`是`CoAP`协议的`C`语言实现，提供了`server`和`client`功能，它是调试`CoAP`的有力工具。


# 下载、编译和安装

通过`git clone`指令从`github`仓库中获得最新版本。
```
$ git clone  https://github.com/authmillenon/libcoap.git
```

由于`libcoap`的源代码包中只有`configure.in`文件，所以比一般的`linux`源代码方式安装多了一步`autoconf`，使用`autoconf`可生成`configure`文件。
```
$ autoconf
$ ./configure
$ make
$ sudo make install
```

安装完成之后，便会新建`/usr/local/include/libcoap`目录，并把`coap.h`、`config.h`、`debug.h`、`pdu.h`等头文件复制到该目录中。另外，编译生成的`libcoap.a`静态链接库被复制到了`/usr/local/lib`中。同时，编译完成之后，在`example`目录中会增加两个重要文件——`coap-client`和`coap-server`。


# `libcoap`使用

进入`example`文件夹，在该文件夹中还有两个可执行文件，`coap-client`和`coap-server`。`coap-client`提供非常丰富的客户端测试指令，而`coap-server`提供一个较为简单的服务器端功能。

在开始服务器端测试之前，必须知晓服务器端的`IP`地址。在`firefox`中安装`copper`插件，浏览器地址栏中输入`coap://xxx.xxx.xxx.xxx`，点击工具栏中的`GET`按钮，那么coap-server便会返回内容。


# 客户端测试

运行`coap-server`
```
$ ./coap-server
```

运行`coap-client`
```
$ ./coap-client -m get -o result.txt coap://localhost
```
`m`：表示`coap`访问方法，默认为`get`方法，此处设置为`get`方法，除了`get`方法之外还包括`put`、`post`和`delete`。
`o`：表示访问获得的内容保存到`result.txt`文件中。

如果访问成功，那么控制台输出：
```
v:1 t:0 tkl:0 c:1 id:45104  
```
`v`：表示`coap`的版本编号，此时的`coap`的版本编号为`1`。
`t`：表示报文类型为`CON`。
`tkl`：表示`token`区域的长度，此时的`token`区域的长度为`0`。
`c`：表示访问方法。
`id`：表示`message id`。

`result.txt`文件内容为： 
```
This is a test server made with libcoap (see http://libcoap.sf.net)
Copyright (C) 2010--2013 Olaf Bergmann bergmann@tzi.org
```


# 总结

`libcoap`中的`coap-client`是一个非常实用的工具，可通过控制台设置不同的参数，该工具可与`firefox copper`插件配合使用。