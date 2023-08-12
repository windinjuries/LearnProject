# vim
## copy
 yank = copy
1. `yy` ：copy this line
2. `3yy` : copy n lines
3. `"ayy` : copy this to register a
3. `"Ayy` : copy this and append register a

## insert
1. i : insert in the font of this cursor
   I ：insert in the font of this line
2. a ：insert in the back of this cursor
   A ：insert in the back of this line
3. o : insert in the last line of this line
   O ：insert in the next line of this line

## undo/redo
- u : undo
- <C-r> : redo
## move cursor
- hjkl : left,down,up,right
- 0 ： move to the start character of this line
  $ ： move to the end character of this line
- w ： move to the first character of next word
  e ： move to the last acharacter of next word
- NG ：= `:N` commond
  gg : move to the first line
  G : move to the last line
- % : move in `()，{}, []` 
- * : move to the next same word
  # : move to the last same word

