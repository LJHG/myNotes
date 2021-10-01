# welcome
> Welcome to my code-server
> It's a hard time to configure the environment
> First i didn't know how to set the server.
> And then i just followed the blogs about how to install the code-server.
> I downloaded the file and installed it.
> But i don't know where to find it in the Ubuntu.

> Finally i fingure out the problem.
> And then i needed set it.

> Anyway it's easy looking back now.
> But it's really a hard time for me.
> It took me a whole day.
> Luckily I learned a lot.


## 参考：
https://blog.csdn.net/liteng607/article/details/106601569/
https://blog.csdn.net/weixin_43988498/article/details/110305091

## 待参考：
https://blog.csdn.net/zju_cf/article/details/102765085
https://blog.csdn.net/Granery/article/details/90415636
https://blog.csdn.net/weixin_45590616/article/details/107573068?utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control
https://cloud.tencent.com/developer/ask/236108?from=information.detail.%E5%A6%82%E4%BD%95%E4%BF%9D%E6%8C%81%E4%B8%80%E7%9B%B4%E8%BF%9E%E6%8E%A5%E4%BA%91%E6%9C%8D%E5%8A%A1%E5%99%A8
https://blog.csdn.net/weixin_45590616/article/details/107573068#comments_16254724

https://zhuanlan.zhihu.com/p/109033328
https://zhuanlan.zhihu.com/p/109033328

## 配置步骤
### 1. 购买云服务器
   在 阿里云/腾讯云/华为云 购买云服务器
   系统为Ubuntu
### 2. 下载code-server
   在服务器中下载code-server
   `wget https://github.com/cdr/code-server/releases/download/3.2.0/code-server-3.2.0-linux-x86_64.tar.gz`
### 3. 解压
   将code-server解压到同名文件夹下：
   `tar -xvzf code-server-3.2.0-linux-x86_64.tar.gz`
### 4. 改名
   将文件夹名code-server-3.2.0-linux-x86_64改为code-server，方便以后访问
   `mv code-server-3.2.0-linux-x86_64 code-server`
### 5. 编写启动文件
   1. 创建启动文件
      `vim ./start.sh`
   2. 编辑文件内容
   ```
   export PASSWORD="xxxx"			# 写你的code-server登录密码
   nohup ./code-server --port 9999 --host 0.0.0.0 --auth password > run.log 2>&1 & 		# 端口可以自己指定，其他不改，后台运行
   echo $! > save_pid.txt	
   ```
### 6. 编写关闭文件
   1. 创建关闭文件
      `vim./shut.sh`
   2. 编辑文件内容
   ```
   
   ```

### 7. 启动服务
   `code-server&`

### 8. 设定服务器端口