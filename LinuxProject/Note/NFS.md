# Network File System
## server
### 安装
```bash
apt install nfs-kernel-server
```
### 配置
- 配置文件 `/etc/exports`
- server共享的文件路径 `/home/book/Project/nfs_mnt`
- 允许的网络地址 `192.168.31.0/24`
- 权限 `rw`
```
/home/book/Project/nfs_mnt 192.168.31.0/24(rw,nohide,insecure,no_subtree_check,async,no_root_squash)
```
## client 
### 安装
```bash
apt install nfs-common
```
### 挂载
```bash
#server ip:dir local_dir
mount -t nfs 192.168.31.52:home/book/Project/nfs_mnt /mnt
```

### 取消挂载
```bash
umount  /mnt
```

## reference
> [NFS挂载教程](https://www.cnblogs.com/lizhuming/p/13946107.html#nfs%E7%8E%AF%E5%A2%83%E6%90%AD%E5%BB%BA)
