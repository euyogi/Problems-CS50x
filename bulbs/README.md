---
files: [bulbs.c]
url: https://cdn.cs50.net/2022/fall/psets/2/bulbs/README.md
window: [terminal]
---

{% if extension %}
# Bulbs

## Not-So-Broken Light Bulbs

In lecture, you may have noticed what seemed like a "bug" at the front of the stage, whereby some of the bulbs always seem to be off:

![screenshot of Week 2 lecture with strip of bulbs](binary_bulbs.jpg)

Each sequence of bulbs, though, encodes a message in *binary*, the language computers "speak." Let's write a program to make secret messages of your own, perhaps that we could even put on stage!

## Implementation Details

To write our program, we'll first need to think about **bases**.

### The Basics

The simplest *base* is base-1, or *unary*; to write a number, *N*, in base-1, we would simply write *N* consecutive `1`s. So the number `4` in base-1 would be written as `1111`, and the number `12` as `111111111111`. Think of it like counting on your fingers or tallying up a score with marks on a board.

You might see why base-1 isn't used much nowadays. (The numbers get rather long!) Instead, a common convention is base-10, or *decimal*. In base-10, each *digit* is multiplied by some power of 10, in order to represent larger numbers. For instance, $$123$$ is short for $$123 = 1 \cdot 10^2 + 2 \cdot 10^1 + 3 \cdot 10^0$$.

Changing base is as simple as changing the $$10$$ above to a different number. For instance, if you wrote `123` in base-4, the number you'd really be writing is $$123 = 1 \cdot 4^2 + 2 \cdot 4^1 + 3 \cdot 4^0$$, which is equal to the decimal number $$27$$.

Computers, though, use base-2, or *binary*. In binary, writing `123` would be a mistake, since binary numbers can only have `0`s and `1`s. But the process of figuring out exactly what decimal number a binary number stands for is exactly the same. For instance, the number `10101` in base-2 represents $$1 \cdot 2^4 + 0 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 1 \cdot 2^0$$, which is equal to the decimal number $$21$$.

### Encoding a Message

Light bulbs can only be on or off. In other words, light bulbs represent two possible states; either the bulb is on, or the bulb is off, just as binary numbers are either 1 or 0. We'll have to find a way to encode text as a sequence of binary numbers.

Let's write a program called `bulbs` that takes a message and converts it to a set of bulbs that we could show to an unsuspecting audience. We'll do it in two steps:

* The first step consists of turning the text into decimal numbers. Let's say we want to encode the message `HI!`. Luckily, we already have a convention in place for how to do this, [ASCII](https://asciichart.com/). Notice that `H` is represented by the decimal number `72`, `I` is represented by `73`, and `!` is represented by `33`.
* The next step involves taking our decimal numbers (like `72`, `73`, and `33`) and converting them into equivalent binary numbers, which only use 0s and 1s. For the sake of having a consistent number of bits in each of our binary numbers, assume that each decimal is represented with 8 bits. `72` is `01001000`, `73` is `01001001`, and `33` is `00100001`.

Lastly, we'll interpret these binary numbers as instructions for the light bulbs on stage; 0 is off, 1 is on. (You'll find that `bulbs.c` includes a `print_bulb` function that's been implemented for you, which takes in a `0` or `1` and outputs emoji representing light bulbs.)

Here's an example of how the completed program might work. Unlike the Sanders stage, we'll print one byte per line for clarity.

```
# ./bulbs
Message: HI!
⚫🟡⚫⚫🟡⚫⚫⚫
⚫🟡⚫⚫🟡⚫⚫🟡
⚫⚫🟡⚫⚫⚫⚫🟡
```

To check our work, we can read a bulb that's on (🟡) as a `1` and bulb that's off (⚫) as a `0`. Then `HI!` became

```
01001000
01001001
00100001
```

which is precisely what we'd expect.

Another example:

```
# ./bulbs
Message: HI MOM
⚫🟡⚫⚫🟡⚫⚫⚫
⚫🟡⚫⚫🟡⚫⚫🟡
⚫⚫🟡⚫⚫⚫⚫⚫
⚫🟡⚫⚫🟡🟡⚫🟡
⚫🟡⚫⚫🟡🟡🟡🟡
⚫🟡⚫⚫🟡🟡⚫🟡
```

Notice that all characters are included in the lightbulb instructions, including nonalphabetical characters like spaces (`00100000`).

## Specification

Design and implement a program, `bulbs`, that converts text into instructions for the strip of bulbs on CS50's stage as follows:

* Implement your program in a file called `bulbs.c`.
* Your program must first ask the user for a message using `get_string`.
* Your program must then convert the given `string` into a series of 8-bit binary numbers, one for each character of the string.
* You can use the provided `print_bulb` function to print a series of `0`s and `1`s as a series of yellow and black emoji, which represent on and off light bulbs.
* Each "byte" of 8 symbols should be printed on its own line when outputted; there should be a `\n` after the last "byte" of 8 symbols as well.

{% spoiler "Hints for Decimal-to-Binary" %}

Let's walk through an example with the number 4. How would you convert 4 to binary? Start by considering the right-most bit, that which—if on—adds 1 to the number we're representing. Do you need this bit to be on? Divide 4 by 2 to find out:

$$4 / 2 = 2$$

2 divides evenly into 4, which tells us there's no remainder of 1 to worry about. We can safely leave this right-most bit off, then:

```
0
```

What about the preceding bit, now, the one just the left of this bit we discovered? To check, let's follow a similar process, but pick up where we left off. In the previous step, we divided 4 by 2 and got 2. Now, does 2 divide evenly into 2? It does, so there's no remainder of 2 to worry about:

```
00
```

Let's continue further still. After dividing 2 by 2, we're left with 1. Diving 1 by 2 leaves a remainder of 1. That means we'll need to turn this bit on:

```
100
```

And now that we've divided our number down to 0, we need no further bits to represent it. Notice that we discovered the bits to represent 4 in the opposite order in which we need to print them: we'll likely need a structure that lets us store these bits, so we can print them forwards later on. And, of course, in your actual code, you'll be working with `char`s of 8 bits, so you'll want to prepend any needed 0's.

When checking for remainders, the modulo (`%`) operator may come in handy! `4 % 2`, for example, returns 0, meaning that 2 divides into 4 with a remainder of 0.

{% endspoiler %}

## How to Test Your Code

Your program should behave per the examples above. You can check your code using `check50`, a program that CS50 will use to test your code when you submit, by typing in the following at the `$` prompt. But be sure to test it yourself as well!

```
check50 cs50/problems/2022/fall/bulbs
```

To evaluate that the style of your code, type in the following at the `$` prompt. 

```
style50 bulbs.c
```

## How to Submit

1. Download your `bulbs.c` file by control-clicking or right-clicking on the file in your codespace's file browser and choosing **Download**.
1. Go to CS50's [Gradescope page](https://www.gradescope.com/courses/411020).
1. Click "Problem Set 2: Bulbs".
1. Drag and drop your `bulbs.c` file to the area that says "Drag & Drop". Be sure it has that **exact** filename! If you upload a file with a different name, the autograder likely will fail when trying to run it, and ensuring you have uploaded files with the correct filename is your responsibility!
1. Click "Upload".

You should see a message that says "Problem Set 2: Bulbs submitted successfully!"

{% alert danger %}

Per Step 4 above, after you submit, be sure to check your autograder results. If you see `SUBMISSION ERROR: missing files (0.0/1.0)`, it means your file was not named exactly as prescribed (or you uploaded it to the wrong problem).

Correctness in submissions entails everything from reading the specification, writing code that is compliant with it, and submitting files with the correct name. If you see this error, you should resubmit right away, making sure your submission is fully compliant with the specification. The staff will not adjust your filenames for you after the fact!

{% endalert %}

{% endif %}