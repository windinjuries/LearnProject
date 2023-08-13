# vim
## copy
 yank = copy
-  `yy` ：copy this line
-  `3yy` : copy n line
-  `"ayy` : copy this to register a
- `"Ayy` : copy this and append register a

## insert
- `i` : insert in the font of this cursor  
- `I` ：insert in the font of this line
- `a` ：insert in the back of this cursor  
- `A` ：insert in the back of this line
- `o` : insert in the last line of this line  
- `O` ：insert in the next line of this line

## undo/redo
- `u` : undo
- `<C-r>` : redo
## move cursor
### character move
- `hjkl` : left,down,up,right
- `0` ： move to the start character of this line  
- `$` ： move to the end character of this line
### word move
- `w` ： move to the first character of next word  
- `e` ： move to the last acharacter of next word--
### line move
- `NG` ：= `:N` commond  
- `gg` : move to the first line  
- `G` : move to the last line
### other
- `%` : move in `()，{}, []` 
- `*` : move to the next same word  
- `#` : move to the last same word
- `f{char}` : search forward for a match in the same line  
- `F{char}` : search backward for a match in the same line
- `;` : repeat the last search using the same direction
- `,` : repeat the last search using the opposite direction

## visual mode
- `v`: character visual mode  
- `V`: line visual mode  
- `C-v` : block visual mode

## motion
- `i{char}` (inner)innot include char--
- `a{char}` (around)include char

## `<operator><motion><char>`
`<operator>` : `y`,`d`,`c`,`v`...  
`<motion>` : `i`,`v`--
`<char>` : `w`(word),`"`,`'`,`{`,`[`....  
### example
- `ciw` : (change innner word) delete the word and insert

## function define
- `<C-]>` jump to function defination--
- `<C-o>` return last position

