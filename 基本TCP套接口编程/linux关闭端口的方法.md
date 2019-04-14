# Linux查看端口使用状态、关闭端口方法
前提：首先你必须知道，端口不是独立存在的，它是依附于进程的。某个进程开启，那么它对应的端口就开启了，进程关闭，则该端口也就关闭了。下次若某个进程再次开启，则相应的端口也再次开启。而不要纯粹的理解为关闭掉某个端口，不过可以禁用某个端口。

1. 可以通过"netstat -anp" 来查看哪些端口被打开。
（注：加参数'-n'会将应用程序转为端口显示，即数字格式的地址，如：nfs->2049, ftp->21，因此可以开启两个终端，一一对应一下程序所对应的端口号）
2. 然后可以通过"lsof -i:$PORT"查看应用该端口的程序（$PORT指对应的端口号）。或者你也可以查看文件/etc/services，从里面可以找出端口所对应的服务。
（注：有些端口通过netstat查不出来，更可靠的方法是"sudo nmap -sT -O localhost"）
3. 若要关闭某个端口，则可以：
1)通过iptables工具将该端口禁掉，如：
"sudo iptables -A INPUT -p tcp --dport $PORT -j DROP"
"sudo iptables -A OUTPUT -p tcp --dport $PORT -j DROP"    
2)或者关掉对应的应用程序，则端口就自然关闭了，如：
"kill -9 PID" (PID：进程号)
如：    通过"netstat -anp | grep ssh"
有显示：    tcp 0 127.0.0.1:2121 0.0.0.0:* LISTEN 7546/ssh
则：    "kill -9 7546"