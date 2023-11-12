FTP就是文件传输协议。用于互联网双向传输，控制文件下载空间在服务器复制文件从本地计算机或本地上传文件复制到服务器上的空间。
### 修改配置文件
```bash
sudo vim /etc/vsftpd.conf
```

### 重新加载配置文件
```bash
sudo /etc/init.d/vsftpd restart
```

### 重启ftp服务
```bash
sudo systemctl restart vsftpd
```
### 查看ftp服务状态
```bash
sudo systemctl status vsftpd
```
[FTP Ubuntu配置](https://blog.csdn.net/qq_42992084/article/details/127717675)