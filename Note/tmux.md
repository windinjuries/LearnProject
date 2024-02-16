# TMUX

## introduce
1. server: back server, server usually has one 
2. session: Sessions are the top-level structure in tmux, representing a collection of related terminal windows
3. window: Windows are the sub-level of sessions, representing visible pages within a session.
4. pane: Panes are the sub-level of windows, representing adjustable, resizable areas within a window.

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

### rename current window
`prefix + ,`

### switch window
`prefix + num [0..9]`

## reference
[tmux cheat sheet](https://tmuxcheatsheet.com/)


