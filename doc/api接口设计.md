[TOC]

#签名及授权

##签名策略

为了保证服务器的安全性，通常情况下`sign`签名验证都是必须的。一般调用`API`时需要对请求参数进行签名验证，签名方式如下：

1. 按照请求参数名称字母先后顺序进行排序，得到`keyvaluekeyvalue...keyvalue`形式字符串。例如，将`arong=1 mrong=2 crong=3`排序为`arong=1 crong=3 mrong=2`，然后将参数名和参数值进行拼接，得到参数字符串`arong1crong3mrong2`。
2. 将`secret`（`secret`仅作加密使用, 为了保证数据安全请不要在请求参数中使用）加在参数字符串的头部进行`MD5`加密，即得到签名`sign`。

##签名示例

下面以获取产品列表举例：

方法名称：`GetProducts`
参数：`pageindex`，`pagesize`
请求方式：`get`

首先，按照规则生成排序后的签名参数，将`secret`加在字符串头部，得到参数字符串`212821ec2035d78f524a86da13a9dceekey076ba2bcb4a0cb38ce721cc00d27426bpageindex1pagesize10timestamp1498197290`。

接着，进行`MD5`加密，得到签名`sign=a63590fef7b467bc10d97f915dd193bd`。

最后，组合得到完整的请求链接如下：
```
http://api.domain.com/GetProducts?key=076ba2bcb4a0cb38ce721cc00d27426b&pageindex=1&pagesize=10&sign=a63590fef7b467bc10d97f915dd193bd&timestamp=1498197290
```

##用户授权

1. 通过账号和密码登陆，授权成功后系统返回授权`token`，`token`有效期为若干天，每次重新登陆都会生成一个新的`token`值。
2. 将`token`加入请求的参数中且参与签名。
3. 不需要用户登陆的公共模块，则无需传入`token`进行用户授权。


#`API`接口

## 通用参数

| 名称          | 类型       | 是否可选       | 说明   | 备注                                 |
| :---------- | :------- | :--------- | :--- | :--------------------------------- |
| `key`       | `string` | `required` | 键    | 由系统授权得到                            |
| `token`     | `string` | `required` | 令牌   | 用户登入时，由系统分配                        |
| `timestamp` | `string` | `required` | 时间戳  | 精确到毫秒                              |
| `sign`      | `string` | `required` | 签名   | 对除`sign`外的`API`调用参数进行`md5/rsa`加密得到 |


#参考链接

[RESTful API 设计指南](http://www.ruanyifeng.com/blog/2014/05/restful_api.html)   
[理解OAuth 2.0](http://www.ruanyifeng.com/blog/2014/05/oauth_2_0.html)  
[RESTful API 设计最佳实践](http://www.cnblogs.com/yuzhongwusan/p/3152526.html)  
[Rest API 开发](http://www.cnblogs.com/springyangwc/archive/2012/01/18/2325784.html)  
[理解RESTful架构](http://kb.cnblogs.com/page/114905/)  
[RESTful HTTP的实践](http://www.infoq.com/cn/articles/designing-restful-http-apps-roth)  
[API请求签名服务器校验猜测](http://www.cnblogs.com/jecob/p/4864130.html)   
[Web API系列(一)设计经验与总结](http://www.cnblogs.com/zhangweizhong/p/5475158.html)  
[Web API系列(二)接口安全和参数校验]()  