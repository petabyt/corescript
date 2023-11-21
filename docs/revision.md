# Corescript Programming Language Revision Document

## April 2017
- Commands: print, message, set=, printf
- Run JS code with ()
- Print variables with parenthesis (`print Hello, (name)`)
- Make and set variables with `set=` (`set=name=Jimmy`)
- Comments start with `##` and end with newline.
- Alert box `message Hello, World`

## November 2017 (first release)
- Commands: print, printf, var, input, cls, msg, set, if, goto, play, not, stop, button
### Added Commands:
- var: `var name=Jim`
- input: `input key=Press a key`
- msg: (changed from `message`)
- set: `set name=John`
- if: `if name=Jim 42` (if name is "Jim", goto line 42)
- not: opposite of `if`
- goto: `goto 47`
- play: `play https://example.com/audio.mp3`
- stop: halts program
- button: `button [Start game]=10` (make a text button, goto 10 when pressed)

## January 2018
- (a new advanced web editor with syntax highlighting was made)
- `if`, `set`, `var`, and `not` can have spaces around the equal signs.  
Ex: `var name = Jim`
- Instead of spaces seperating string and line numbers in `if` and `not` statements,  
use `:`. Ex: `if name = Jim:42`
- Added labels. Define them with `:foo`. They can be used in place of line numbers.
- Comments start with `//` and end with newline
- Added build-in function `rand` (`print (rand 0 10)`)

## November 2019
- Allowed multilingual command support. Ex: `imprimir Buenos`

## April 2020
- Removed all commands except: print, var, if, not, input, goto, set, stop
- Removed jumping to line numbers, only allow labels
- Added `return`. Jumps to the last time a label was called (last line + 1).  

## June 2020
- Removed stop, not
- Standardized math functions: add, sub, div, mult, rem, rand, sin  
See: https://github.com/corescript-lang/editor/blob/master/package.js#L143
- Use # for comments

## August 2020
- Use [] instead of () for "raw" statements.
- Added `>` and `<` for use along with `=` in `if` statements.
