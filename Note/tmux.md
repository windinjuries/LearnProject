# TMUX

## session
### start a session
`tmux new -s name`
### session list
`prefix + s`  
`tmux ls`
### attach to session
`tmux a -t mysession`
### detach
`tmux detach`  
`prefix + d`
### kill session
`tmux kill-session -t mysession`
### rename session
`prefix + $`
## windows
### start a window
`prefix + c`
### windows list
`prefix + w`
### close current window
`prefix + ,`
### rename current window
`prefix + &`

## panel


## tmux config
```bash
# tmux set
# source this conf need:
# 1. ctrl+prefix
# 2. :
# 3. source-file ~/.tmux.conf

# 设置加载在配置文件指令为：prefix + r
bind r source-file ~/.tmux.conf
display-message "tmux.conf is reloaded."

# Set the prefix to Ctrl+a
set -g prefix C-a
# unbind the prefix
unbind C-b
# enable mouse
set-option -g mouse on
# default statusbar colors
set -g status-interval 1
set -g status-justify left
setw -g monitor-activity on
set -g status-bg black
setw -g window-status-format '#[fg=brightblue] #I #W '
setw -g window-status-current-format '#[fg=magenta,bold] #I #W:#F'
setw -g window-status-activity-style bg=black
setw -g window-status-bell-style bg=black
```


