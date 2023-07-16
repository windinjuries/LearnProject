---
title: neovim tutorial
date: 2022-12-23 12:18:18
tags: 
- neovim

---
> Neovim在GitHub上自述为*Vim-fork focused on extensibility and usability*，所以自Neovim诞生以来，它就专注于提高自己的扩展性与易用性，例如内置终端、异步执行这两个比较重要的功能都是Neovim率先支持，而Vim追赶在后的。经过多年在各自赛道上的发展，Neovim与Vim已经产生了不少差异。不过现阶段来看，**Neovim的特性仍然几乎是Vim的超集**，也就是说除了自己独有的功能外，Neovim还支持Vim的绝大部分功能。

<img src="https://picx.zhimg.com/v2-300e97a93f78e336e63861b9b6df9910_r.jpg?source=172ae18b1b9b6df9910_r.jpg" alt="neovim" style="zoom: 50%;" />

# neovim

## 参考链接

[学习 Neovim 全 lua 配置](https://github.com/nshen/learn-neovim-lua/tree/bak)



## 环境安装

### 安装WSL2



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
## 配置方式

### vim

配置文件路径

```bash
~/.config/nvim/init.vim
```



### lua

配置文件路径：

```bash
~/.config/nvim/init.lua
```

.vim可以调用.lua配置文件，实现混合配置 ，或者是纯lua编程，接下来所有配置采用Lua编程方式

## 插件管理

1. 安装 Packer.nvim 插件管理器

之前 `vim` 最常见的插件管理应该是 [vim-plug](https://github.com/junegunn/vim-plug) 我也用过，但 `Neovim` 0.5 以后一般都会推荐使用 `lua` 原生的 [packer.nvim](https://github.com/wbthomason/packer.nvim) 做插件管理 。

```shell
git clone --depth 1 https://github.com/wbthomason/packer.nvim\
 ~/.local/share/nvim/site/pack/packer/start/packer.nvim
```

2. 创建插件配置文件lua/plugins.lua

```lua
return require('packer').startup(function()
  -- Packer can manage itself
  use 'wbthomason/packer.nvim'
end)
```
3. 修改init.lua,加载插件管理配置文件

```lua
" Packer插件管理"
require('plugins')
```
4. 插件安装与更新

```lua
-- Regenerate compiled loader file
:PackerCompile

-- Remove any disabled or unused plugins
:PackerClean

-- Clean, then install missing plugins
:PackerInstall

-- Clean, then update and install plugins
:PackerUpdate

-- Perform `PackerUpdate` and then `PackerCompile`
:PackerSync

-- Loads opt plugin immediately
:PackerLoad completion-nvim ale
```

## 主题管理