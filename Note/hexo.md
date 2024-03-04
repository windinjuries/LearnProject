---
title: hexo tutorial
date: 2023-05-01 09:21:23
tags:
- hexo
- github
- vercel
categories: 
- [Tutorial, Front]
comment: true
excerpt: "`Hexo`是高效的静态网站生成框架，它基于`Node.js`，快速，简单且功能强大，是搭建博客的首选框架。通过`Hexo`，你可以直接使用`Markdown`语法来撰写博客。"
---
## 环境安装

- Node.js
- git
- python3

## hexo安装

```shell
#安装hexo
npm install -g hexo-cli 
#初始化项目
hexo init <folder>     
#进入项目文件夹
cd <folder> 
#安装必备组件
npm install
```

## 主题安装

[主题参考](https://hexo.io/themes/)

1. 选择主题下载

```shell
git clone -b master https://github.com/Longlongyu/hexo-theme-Cxo themes/Cxo
```

2.更改配置文件`_config.yml`，注意将themes文件夹下的主题文件夹改为与配置的名字一致

```yaml
# Extensions
## Plugins: https://hexo.io/plugins/
## Themes: https://hexo.io/themes/
theme: Cxo
```

3.执行命令包括清除、生成、部署

```shell
hexo clean 
hexo g 
hexo d
```

## GitHub配置

1. 创建仓库

新建一个名为`yourusername.github.io`的仓库，如果你的github用户名是test，那么你就新建`test.github.io`的仓库。将来你的网站访问地址就是 https://test.gtihub.io

2. 配置SSH key
   
   1、运行命令： `ssh-keygen -t rsa -c "邮件地址"` 。邮件地址可以登录你的github - `setting` - `emails` 查看
   2、然后连续3次回车，最终会生成一个文件在用户目录下
   3、打开用户目录，找到 `.ssh\id_rsa.pub` 文件，记事本打开并复制里面的内容
   4、打开你的github主页，进入 `个人设置` - `ssh and gpg keys` - `new ssh key`将刚复制的内容粘贴到key那里，title随便填，保存。
   5、测试连接 运行命令： `ssh -t git@github.com` 。**注意这条命令不用修改，直接运行**
   6、全局配置
   
   ```shell
   git config --global user.name "selier"         #你的github用户名，非昵称
   git config --global user.email  "邮箱@qq.com"  # 填写你的github注册邮箱
   ```

## 博客创建

### 配置 `__config.yml`

```yaml
#配置发布方式
deploy:
  type: git
  repo: https://github.com/windinjuries/windinjuries.github.io.git
  branch: main
```

### 创建博客

```shell
hexo clean 
hexo new "postName" #新建文章
hexo new page "pageName" #新建页面
hexo generate #生成静态页面至public目录
hexo server #开启预览访问端口（默认端口4000，'ctrl + c'关闭server）
hexo deploy #部署到GitHub
```

## 常见问题

### 1.hexo d出现

### 2.node 环境变量windows与WSL冲突

```shell
1. D:\Anaconda3\
2. D:\Anaconda3\Scripts\
3. D:\Anaconda3\Library\bin\
4. C:\Program Files\nodejs\
//通过删除windows环境变量避免冲突
```

