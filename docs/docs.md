# The Official Corescript Documentation
"*Corescript is a bare-bones minimalist high-level  
programming language designed to be extremely simple   
and easy to hack.*"

Corescript is not a flexible production language. It is a learning and  
prototyping tool. It is not meant for advanced projects. Instead, it is  
designed for simplicity, minimalism, and hackability.

Now that we have that out of the way, welcome to the official  
Corescript programming guide.

[The Online IDLE](https://corescript-lang.github.io/editor/)

## Hello World Example
To start off, let's look at something very simple.  
This is the classic "Hello, World" program.
```
print Hello, World!
```

Pretty straightforward, right? Good, let's move on to the next example.

## Variables
Variables can simply be declared by using:
```
var name = John
```

You *must* use a space between the equal sign, or the code will  
not parse. And besides, it is easier to read that way.

To set a variable, use the `set` command.
```
set name = John Doe
```

## "Raw", and Printing Variables
Now that we have our cool variable, what do we do with it?  
Well, you can't eat it, nor can you use it to visit Mars, so  
let's try to print it to the screen.
```
print Hello, [name]!
```

Using parenthesis around variables isn't only used in `print`, but  
it can also be used in other commands that require strings.
```
var name = John
input question = How are you, [name]?
print Cool, goodbye [name].
```

In Corescript, anything between parenthesis will try to be parsed.  
If the parsing does not succeed, then no nothing will be changed.
```
print [This is not a variable.]
```
Output: (This is not a variable)

Now that we have a few basic commands down, let's use them to make another  
example.
```
input name = What's your name?
print Hello, [name]!
```
This will ask for input, and greet the user once they have done so.

# Labels + Goto
Sometimes you want to do something over and over again, like  
annoying somebody until they give in. We do this in programming too.  
```
:top
print This is repeated forever
goto top
```

In that example, we declare a label by using a `:` and putting  
our label text after it. Then we put in our code, and when finished, tell it  
to `goto` to the place where `:top` was called, and thus the cycle continues.

*In the web editor, type "slow" into the terminal to turn on slowmode. This  
will allow loop to work without crashing your page.*

# Functions
## Math
In programming, you will at one point need to use math.  
Whether it is adding +1, or calculating the chances you will win  
the lottery, programming would be useless without it.
```
var a = 12
set a = [add a 48]
print [a]
```
This should print 60. Pretty basic. There is more than just adding in Corescript  
of course. These are the math functions available:
* add (+)
* sub (-)
* mult (*)
* div (/)
* rem (%)
* rand
*rand should be used as "min, max". Ex: `print [rand 1 10]`*

Their purpose should all be pretty self-explainable.
# Strings
* len: `len string`
* char: `char 1 variable`

# Other Commands
There are some other commands in Corescript I didn't dedicate  
a section to. The first one being `return`.

It is used with labels.  
`return` goes back to the last time the label was used.  
This excludes when the label was defined. An example explains this best.  
```
goto hello
stop

:hello
print Hello!
return hello
```
When `goto hello` is called, it runs `print hello`, and since `return` was  
last used on `goto hello`, it moves back to that line.  

This is not an essential command, but it can be used to avoid this:
```
goto hello
:helloBack
stop

:hello
print Hello!
return helloBack
```

# If
If statements are essential in programming.  
If you want to check if variable `name` is "Jimmy",  
then you can do this:
```
var name = Jimmy
if name = Jimmy:enter
print You are not Jimmy...
stop
:enter
print Welcome, Jimmy.
```
In this example, if `name` is "Jimmy", then `goto` "enter".  
If it is not "Jimmy", then nothing will happen, and it will  
resume to the next line as if nothing happened.

Lets say we want to try and be lucky, and see if our luck  
can get 1 in a million. We will use the `rand` math function for this.
```
var luckyNumber = 32392
var guess = [rand 1 1000000]
if guess = [luckyNumber]:correct
print We did not get the lucky number :(
stop
:correct
print We did it! We got [guess]!
```
