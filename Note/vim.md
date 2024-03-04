---
title: vim tutorial
date: 2024-1-23 12:18:18
tags: 
- vim
categories: 
- [Tutorial, Program Tool]
excerpt: "Vim is a highly configurable text editor built to make creating and changing any kind of text very efficient."
comment: true
---
> Vim is a highly configurable text editor built to make creating and changing any kind of text very efficient.
## command introduce
### delete
- `d` ：delete
### cut
- `x` ：cut
### change
- `c` : change
### copy
 yank = copy
-  `yy` ：copy this line
-  `3yy` : copy n line
-  `"ayy` : copy this to register a
- `"Ayy` : copy this and append register a
### paste
- `p` ：paste last clipboard to this(`x`,`d`,`y` are included)
### insert
- `i` : insert in the font of this cursor
- `I` ：insert in the font of this line
- `a` ：insert in the back of this cursor
- `A` ：insert in the back of this line
- `o` : insert in the last line of this line
- `O` ：insert in the next line of this line

### undo/redo
- `u` : undo
- `<C-r>` : redo
### move cursor
#### character move
- `hjkl` : left,down,up,right
- `0` ： move to the start character of this line
- `$` ： move to the end character of this line
#### word move
- `w` ： move to the first character of next word
- `e` ： move to the last character of next word
#### line move
- `NG` ：= `:N` commond
- `gg` : move to the first line
- `G` : move to the last line
#### other
- `%` : move in `()，{}, []`
- `*` : move to the next same word
- `#` : move to the last same word
- `f{char}` : search forward for a match in the same line
- `F{char}` : search backward for a match in the same line
- `;` : repeat the last search using the same direction
- `,` : repeat the last search using the opposite direction

### visual mode
- `v`: character visual mode
- `V`: line visual mode
    - `>,<` increase indent, decrease indent
- `C-v` : block visual mode

### motion
- `i{char}` (inner)inner include char
- `a{char}` (around)include char

### `<operator><motion><char>`
- `<operator>` : `y`,`d`,`c`,`v`...
- `<motion>` : `i`,`a`
- `<char>` : `"`,`'`,`{`,`[`,`<`,`w`(word),`t`(tag),`s`(sentence),`p`(paragraph)...
#### example
- `ciw` : (change inner word) delete the word and insert

### function define
- `<C-]>` jump to function defination
- `<C-o>` return last position

### folding
- `zf` : create fold,use method like `<operator><motion><char>`
- `zo` : open fold
- `zc` : close fold

### record
- `q{char}` : 'q'+'char' start record
- `q` : stop record
- `@{char}` : do record something

### mark
- m{char} : make a mark
- ``` `{char}``` : jump to the postion marked
- `'{char}` : jump to the start of the line marked
