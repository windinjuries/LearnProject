## ssh
```bash
ssh user_name@ip
```
connect to ip by openssh

## ssh-keygen
```bash
ssh-keygen -t rsa
```
generate authentication key

## ssh-copy-id
```bash
ssh-copy-id username@local_dev_board_ip
```
copy password to board linux `~/.ssh/authorized_keys`

## sftp
```bash
sftp user_name@ip

```
## scp

```bash
scp -r dir user@ip:dir
scp file user@ip:file
```
copy file by ssh
## rsync

```bash
rsync -av dir dir
```
sync file by ssh