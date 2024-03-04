---
title: neovim tutorial
date: 2023-8-23 12:18:18
tags: 
- neovim
categories: 
- [Tutorial, Program Tool]
comment: true
cover: "https://picx.zhimg.com/v2-300e97a93f78e336e63861b9b6df9910_r.jpg?source=172ae18b1b9b6df9910_r.jpg"
excerpt: "Neovim在GitHub上自述为*Vim-fork focused on extensibility and usability*，所以自Neovim诞生以来，它就专注于提高自己的扩展性与易用性，例如内置终端、异步执行这两个比较重要的功能都是Neovim率先支持，而Vim追赶在后的。经过多年在各自赛道上的发展，Neovim与Vim已经产生了不少差异。不过现阶段来看，**Neovim的特性仍然几乎是Vim的超集**，也就是说除了自己独有的功能外，Neovim还支持Vim的绝大部分功能。"
---
<!-- <img src="https://picx.zhimg.com/v2-300e97a93f78e336e63861b9b6df9910_r.jpg?source=172ae18b1b9b6df9910_r.jpg" alt="neovim" style="zoom: 50%;" /> -->

# neovim

## 参考链接

[学习 Neovim 全 lua 配置](https://github.com/nshen/learn-neovim-lua/tree/bak)
[Get started lazyvim](https://www.lazyvim.org/)



### 安装neovim

```shell
#安装稳定版/不稳定版
sudo add-apt-repository ppa:neovim-ppa/stable
sudo add-apt-repository ppa:neovim-ppa/unstable
sudo apt-get update
sudo apt-get install neovim

#查看有哪些neovim版本
sudo apt install apt-show-versions 
apt-show-versions -a neovim

#选择合适的版本安装
sudo apt-get install neovim=0.4.4-1~ubuntu20.04.1~ppa1
```


