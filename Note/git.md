> Git（读音为/gɪt/）是一个开源的分布式版本控制系统，可以有效、高速地处理从很小到非常大的项目版本管理。也是Linus Torvalds为了帮助管理Linux内核开发而开发的一个开放源码的版本控制软件。

# git运行机制

* <img src="https://res.cloudinary.com/fengerzh/image/upload/git-reset_drbfhd.png" alt="neovim" style="zoom: 80%;" />

上图描述了 git 对象的在不同的生命周期中不同的存储位置，通过不同的 git 命令改变 git 对象的存储生命周期。

1. Workspace：工作区，项目代码存放的地方
2. Index / Stage：暂存区，用于临时存放你的改动，事实上它只是一个文件，保存即将提交到文件列表信息
3. Repository：仓库区（或本地仓库），就是安全存放数据的位置，这里面有你提交到所有版本的数据。其中HEAD指向最新放入仓库的版本
4. Remote：远程仓库，托管代码的服务器，可以简单的认为是你项目组中的一台电脑用于远程数据交换

# 文件状态

版本控制就是对文件的版本控制，要对文件进行修改、提交等操作

- Untracked: 未跟踪, 此文件在文件夹中, 但并没有加入到git库, 不参与版本控制. 通过git add 状态变为Staged.
- Unmodify: 文件已经入库, 未修改, 即版本库中的文件快照内容与文件夹中完全一致. 这种类型的文件有两种去处, 如果它被修改, 而变为Modified. 如果使用git rm移出版本库, 则成为Untracked文件
- Modified: 文件已修改, 仅仅是修改, 并没有进行其他的操作. 这个文件也有两个去处, 通过git add可进入暂存staged状态, 使用git checkout 则丢弃修改过, 返回到unmodify状态, 这个git checkout即从库中取出文件, 覆盖当前修改 !
- Staged: 暂存状态. 执行git commit则将修改同步到库中, 这时库中的文件和本地文件又变为一致, 文件为Unmodify状态. 执行git reset HEAD filename取消暂存, 文件状态为Modified

# 指令详解

## 创建本地git仓库

```bash
git init #新建仓库
```

## 克隆远程仓库

```bash
git clone https://www.github.git
```

## 新建分支

```bash
git checkout -b dev #创建开发分支dev，并切换到该分支
```

## 保存文件到暂存区
```bash
git add . #添加当前目录的所有文件到暂存区
git add [path] #添加指定目录到暂存区，包括子目录
git add [file] #添加指定文件到暂存区
```
## 删除文件

```bash
git rm [file] # 从暂存区和工作区删除文件
git rm -cached [file] #从暂存区删除文件
```

## 提交暂存区文件到本地仓库

```bash
git commit # 以打开默认编辑器提交
git commit [file] -m [message] #提交暂存区的指定文件到本地仓库
git commit --amend -m [message] #使用一次新的commit，替代上一次提交
```

## 查看状态

```bash
git status  #查看当前工作区暂存区变动
```

## 查看日志

```bash
git log  #查看提交历史
```
## 管理远程仓库

```bash
git remote #列出当前仓库中已配置的远程仓库。
git remote -v #列出当前仓库中已配置的远程仓库，并显示它们的 URL。
git remote add [remote_name] [remote_url] #指定一个远程仓库的名称和URL，将其添加到当前仓库中。
git remote remove [remote_name] #从当前仓库中删除指定的远程仓库。
git remote set-url [remote_name] [new_url] #修改指定远程仓库的URL。
git remote show [remote_name] #显示指定远程仓库的详细信息，包括URL和跟踪分支。
```

## 推送

```bash
git push origin master #将本地分支的更新全部推送到远程仓库master分支
git push origin -d  #删除远程branchname分支
git push --tags #推送所有标签
```

## 拉取

```bash
git pull  #拉取远程仓库所有分支更新并合并到本地分支
git pull origin master #将远程master分支合并到当前本地分支
git pull origin master:master #将远程master分支合并到当前本地master分支，冒号后面表示本地分支
git fetch --all  #拉取所有远端的最新代码
git fetch origin master #拉取远程最新master分支代码
```

## 分支处理

```bash
git branch  #查看分支
—D #删除
-a #本地和远程分支
```

```bash
git branch [branchname] #新建分支branchname
git checkout [branchname] #切换到分支branchname
```

```bash
git merge [branchname] #合并当前分支到barnchname
```

## 撤销

```bash
# 将添加到暂存区的文件版本恢复到工作区文件
# 注意：未被添加到暂存区的文件无法恢复
git checkout -- [file]  #丢弃某个文件file
git checkout -- .  #丢弃所有文件
```

```bash
# reset分为以下三步：
# 1. 将HEAD和master分支指针移动到对应的commit上
# 2. 将commit中的文件版本覆盖到stage
# 3. 将stage覆盖到workspace
# 注意：
# 1. reset是用于移动master分支指针，checkout是移动HEAD
# 2. hard方式使用很危险
git reset –-soft [commit] 
git reset –-mixed [commit]
git reset –-hard [commit]
```

```bash
#用于没添加到暂存区的工作区文件
git revert 版本号  #回滚某个版本作为新版本
```

> 参考文献
> https://blog.csdn.net/weixin_36168780/article/details/112100325
