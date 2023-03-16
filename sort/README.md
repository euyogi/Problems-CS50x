---
files: [answers.txt]
url: https://cdn.cs50.net/2022/fall/labs/3/sort/README.md
window: [terminal]
---

# Lab 3: Sort

{% alert warning %}

Labs are practice problems which, time permitting, may be started or completed in your section, and are assessed on correctness only. You are encouraged to collaborate with classmates on this lab, though each member in a group collaborating is expected to contribute equally to the lab.

{% endalert %}

Analyze three sorting programs to determine which algorithms they use.

## Background

Recall from lecture that we saw a few algorithms for sorting a sequence of numbers: selection sort, bubble sort, and merge sort.

* Selection sort iterates through the unsorted portions of a list, selecting the smallest element each time and moving it to its correct location.
* Bubble sort compares pairs of adjacent values one at a time and swaps them if they are in the incorrect order. This continues until the list is sorted.
* Merge sort recursively divides the list into two repeatedly and then merges the smaller lists back into a larger one in the correct order.

## Instructions

Provided to you are three already-compiled C programs, `sort1`, `sort2`, and `sort3`. Each of these programs implements a different sorting algorithm: selection sort, bubble sort, or merge sort (though not necessarily in that order!). Your task is to determine which sorting algorithm is used by each file. Why might your choice of inputs influence your determination? What sorts of inputs might lead you to incorrect conclusions?

* `sort1`, `sort2`, and `sort3` are binary files, so you won't be able to view the C source code for each. To assess which sort implements which algorithm, run the sorts on different lists of values.
* Multiple `.txt` files are provided to you. These files contain `n` lines of values, either reversed, shuffled, or sorted.
  * For example, `reversed10000.txt` contains 10000 lines of numbers that are reversed from `10000`, while `random10000.txt` contains 10000 lines of numbers that are in random order.
* To run the sorts on the text files, in the terminal, run `./[program_name] [text_file.txt]`. Make sure you have made use of `cd` to move into the `sort` directory!
  * For example, to sort `reversed10000.txt` with `sort1`, run `./sort1 reversed10000.txt`.
* You may find it helpful to time your sorts. To do so, run `time ./[sort_file] [text_file.txt]`.
  * For example, you could run `time ./sort1 reversed10000.txt` to run `sort1` on 10,000 reversed numbers. At the end of your terminal's output, you can look at the `real` time to see how much time actually elapsed while running the program.
* Record your answers in `answers.txt`, along with an explanation for each program, by filling in the blanks marked `TODO`.

### Walkthrough

{% alert primary %}

This video was recorded when the course was still using CS50 IDE for writing code. Though the interface may look different from your codespace, the behavior of the two environments should be largely similar!

{% endalert %}

{% video https://video.cs50.io/-Bhxxw6JKKY %}

### Hints

* The different types of `.txt` files may help you determine which sort is which. Consider how each algorithm performs with an already sorted list. How about a reversed list? Or shuffled list? It may help to work through a smaller list of each type and walk through each sorting process.

{% spoiler "Not sure how to solve?" %}

{% video https://video.cs50.io/uOYhrBs37j0 %}

{% endspoiler %}

### How to Check Your Answers

Execute the below to evaluate the correctness of your answers using `check50`. But be sure to fill in your explanations as well, which `check50` won't check here!

```
check50 cs50/labs/2022/fall/sort
```

## How to Submit

1. Download your `answers.txt` file by control-clicking or right-clicking on the file in your codespace's file browser and choosing **Download**.
1. Go to CS50's [Gradescope page](https://www.gradescope.com/courses/411020).
1. Click "Lab 3: Sort".
1. Drag and drop your `answers.txt` file to the area that says "Drag & Drop". Be sure it has that **exact** filename! If you upload a file with a different name, the autograder likely will fail when trying to run it, and ensuring you have uploaded files with the correct filename is your responsibility!
1. Click "Upload".

You should see a message that says "Lab 3: Sort submitted successfully!"

{% spoiler "Want to see the staff's solution?" %}
```
sort1 uses: Bubble Sort
How do you know?: On a large random file, sort1 takes much longer than an already-sorted file of the same size. For already-sorted files, sort1 returns results almost instantaneously, regardless of size. This suggests that sort1 has a different upper bound runtime than lower bound runtime. This is consistent with Bubble Sort, which runs in O(n^2) and Ω(n).
sort2 uses: Merge Sort
How do you know?: On larger random files, sort2 is the fastest of the three sorts. Since we know that Merge Sort runs in O(n log n) while Bubble Sort and Selection Sort run in the slower O(n^2), sort2 is likely Merge Sort.
sort3 uses: Selection Sort
How do you know?: On a large random file, sort3 takes just as long as sort1, but performs no better when the list is already sorted. This suggests that the algorithm runs in O(n^2) and Ω(n^2), which is consistent with Selection Sort.
```
{% endspoiler %}

{% alert danger %}

Per Step 4 above, after you submit, be sure to check your autograder results. If you see `SUBMISSION ERROR: missing files (0.0/1.0)`, it means your file was not named exactly as prescribed (or you uploaded it to the wrong problem).

Correctness in submissions entails everything from reading the specification, writing code that is compliant with it, and submitting files with the correct name. If you see this error, you should resubmit right away, making sure your submission is fully compliant with the specification. The staff will not adjust your filenames for you after the fact!

{% endalert %}