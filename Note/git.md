---
title: git tutorial
date: 2023-03-05 09:21:23
tags:
- git
categories: 
- [Tutorial, Program Tool]
excerpt: "Git是一个开源的分布式版本控制系统，可以有效、高速地处理从很小到非常大的项目版本管理。也是Linus Torvalds为了帮助管理Linux内核开发而开发的一个开放源码的版本控制软件。"
comment: true
---

## Git Principle

* <img src="https://res.cloudinary.com/fengerzh/image/upload/git-reset_drbfhd.png" alt="git" style="zoom: 25%;" />

上图描述了 git 对象的在不同的生命周期中不同的存储位置，通过不同的 git 命令改变 git 对象的存储生命周期。

1. Workspace：工作区，项目代码存放的地方
2. Index / Stage：暂存区，用于临时存放你的改动，事实上它只是一个文件，保存即将提交到文件列表信息
3. Repository：仓库区（或本地仓库），就是安全存放数据的位置，这里面有你提交到所有版本的数据。其中HEAD指向最新放入仓库的版本
4. Remote：远程仓库，托管代码的服务器，可以简单的认为是你项目组中的一台电脑用于远程数据交换

## File Status

版本控制就是对文件的版本控制，要对文件进行修改、提交等操作

- Untracked: 未跟踪, 此文件在文件夹中, 但并没有加入到git库, 不参与版本控制. 通过git add 状态变为Staged.
- Unmodify: 文件已经入库, 未修改, 即版本库中的文件快照内容与文件夹中完全一致. 这种类型的文件有两种去处, 如果它被修改, 而变为Modified. 如果使用git rm移出版本库, 则成为Untracked文件
- Modified: 文件已修改, 仅仅是修改, 并没有进行其他的操作. 这个文件也有两个去处, 通过git add可进入暂存staged状态, 使用git checkout 则丢弃修改过, 返回到unmodify状态, 这个git checkout即从库中取出文件, 覆盖当前修改 !
- Staged: 暂存状态. 执行git commit则将修改同步到库中, 这时库中的文件和本地文件又变为一致, 文件为Unmodify状态. 执行git reset HEAD filename取消暂存, 文件状态为Modified

## Command Introduce 

### init
```bash
git init 
```

### clone
```bash
git clone https://www.github.git
```

### add
```bash
#添加当前目录的所有文件到暂存区
git add . 
#添加指定目录到暂存区，包括子目录
git add [path] 
#添加指定文件到暂存区
git add [file] 
```
### rm

```bash
# 从暂存区和工作区删除文件
git rm [file] 
#从暂存区删除文件
git rm -cached [file] 
```
### commit

```bash
# 以打开默认编辑器提交
git commit 
#提交暂存区的指定文件到本地仓库
git commit [file] -m [message] 
#使用一次新的commit，替代上一次提交
git commit --amend -m [message] 
```

### status

```bash
#查看当前工作区暂存区变动
git status  
```

### log

```bash
#查看提交历史
git log --oneline --graph
```
### remote

```bash
#列出当前仓库中已配置的远程仓库。
git remote 
#列出当前仓库中已配置的远程仓库，并显示它们的 URL。
git remote -v 
#指定一个远程仓库的名称和URL，将其添加到当前仓库中。
git remote add [remote_name] [remote_url] 
#从当前仓库中删除指定的远程仓库。
git remote remove [remote_name] 
#修改指定远程仓库的URL
git remote set-url [remote_name] [new_url] 
#显示指定远程仓库的详细信息，包括URL和跟踪分支
git remote show [remote_name] 
```

### push

```bash
#将本地分支master更新全部推送到远程仓库origin的main分支
#自动创建远程分支
git push origin master:main 
#删除远程branch_name分支
git push origin -d [branch_name] 
#推送所有标签
git push --tags 
```

### pull && fetch

```bash
#拉取远程仓库所有分支更新并合并到本地分支
git pull  
#将远程master分支合并到当前本地分支
git pull origin master 
#将远程master分支合并到当前本地master分支，冒号后面表示本地分支
git pull origin master:master 
#拉取所有远端的最新代码
git fetch --all  
#拉取远程最新master分支代码
git fetch origin master 
```

### branch
```bash
#新建分支
git branch [branch_name] 
```
```bash
#切换分支
git checkout [branch_name] 
```
```bash
#查看分支
git branch 
#查看远程分支
git branch -a 
```
```bash
#删除分支
git branch -D [branch_name] 
```

### merge
```bash
#合并当前分支到branch_name
git merge [branchname] 
```

### checkout

```bash
# 将暂存区的文件版本恢复到工作区文件上
# 注意：未被添加到暂存区的文件无法恢复

git checkout -- [file]  
#丢弃所有文件
git checkout -- .  
```

### reset
```bash
# reset分为以下三种类型：
# 1. soft: 将HEAD和master分支的指针移动到指定commit
# 2. mixed: 在soft基础上将commit中的文件版本覆盖到stage(可以用于取消git add)
# 3. hard: 将stage中的文件覆盖到workspace，该操作执行后无法恢复workspace修改的文件
# ATTENTION：reset是移动master分支指针，checkout是移动HEAD

git reset –-soft [commit] 
git reset –-mixed [commit]
git reset –-hard [commit]
```

### revert
```bash
#回滚某个版本作为一个新版本
git revert [commit]
```

### stash

```bash
# 保存进度
git stash
# 查看保存的进度
git stash list
# 恢复进度
git stash pop 
## 删除进度
git stash drop
```
## tag

```bash
# 轻量标签
git tag [tagname] [commit]
# 附注标签
git tag -a [tagname] [commit]
# 显示所有标签
git tag 
# 显示某一标签
git show [tagname]
# 推送本地标签
git push origin [tagname]
# 推送所有标签
git push origin --tags
# 删除本地标签
git tag -d [tagname]
# 删除远程标签
git push origin -d [tagname]

```
### diff

```bash
# 查看工作区和暂存区的区别(以摘要形式)
git diff --stat [file/path]

# 查看工作区和commit的区别
git diff commit

# 查看工作区和HEAD的区别
git diff HEAD

# 查看暂存区和commit的区别
git diff --cached commit

# 查看commit1和commit2的区别
git diff commit1 commit2
```

### cherry-pick
``` bash
# 挑选指定提交到应用分支
git cherry-pick [commit1] [commit2]
```

注意：命令的详细介绍在Linux环境下可如 `man git` 或者 `git --help` 查看
## Reference
[Pro Git](https://git-scm.com/book/zh/)  
[GotGit](https://www.worldhello.net/gotgit/)  
[git command introduce](https://blog.csdn.net/weixin_36168780/article/details/112100325)  
[git commit messgae](https://www.cnblogs.com/ltaodream/p/16113677.html)
