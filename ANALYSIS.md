# Joint Analysis

## Question 1

<!-- TODO: answer Question 1 -->

## Question 2

**You wrote the tag check in `dt_value_as_int` by hand. Some languages don't let you. They make the tagged union a language construct, so the compiler writes the check for you, refuses to compile a read that skips it, and refuses to compile a set of cases that misses one. Rust's `enum` and `match` work this way, and so do ML's datatypes and Swift's enumerations with associated values. What does the C version let you do that a compiler enforcing the check wouldn't, and is any of it worth wanting?**

C lets you do several things that a compiler-enforced tagged union would reject. You can read the data inside a union without checking the tag, so a float's bits can be treated as an int. You can build a value whose tag claims one type while the data holds another, or leave the tag unset entirely. You can also skip cases when handling a tag, and you can add a new type later without touching existing code, because the tag is just a number and nothing forces old handlers to account for the new one. A compiler that enforces the check forbids the first three outright and, for the last, makes you update every place that handles the cases.

Most of this isn't worth wanting. Reading the wrong type, mismatching tag and data, and missing a case are all plain mistakes, and in C they surface only as garbage values or bugs at runtime. The one real freedom is skipping a check you have already performed, since testing the same tag twice is redundant and costs a little time in hot code. But that freedom isn't lost in Rust, which allows unchecked access when you explicitly mark the code as `unsafe`. Adding a type without revisiting old handlers can matter in some designs, but it is a minor convenience next to the safety it costs, because the forced update is exactly how the compiler guarantees no case goes unhandled. In the end, C's extra freedom is mostly the freedom to make mistakes, and the compiler-enforced version removes those mistakes while keeping the useful capabilities available on request.

## Question 3

<!-- TODO: answer Question 3 -->

## Question 4

**Compare access after release with an allocation that remains unreleased at the driver's final check. What damage can each cause in a long-running server? How does that answer change for a command-line tool that exits in a second?**

Using memory after it has been freed is the more dangerous mistake, because the program touches memory it no longer owns. By then that spot may already belong to something else, so reading it gives wrong values, and writing to it silently corrupts other data. The damage happens at the moment of the bad access, and it can cause crashes, wrong results, or even security holes if someone can control what ends up in that spot. An allocation that is never released is a different kind of mistake. Nothing breaks at the moment it happens, because the memory is simply reserved and never used or given back. It is wasted space but not wrong behavior.

In a long-running server, both are serious for different reasons. A use after free can crash or corrupt the server on any request that hits it, and since the server handles requests constantly, it will eventually hit it. A leak is a slow problem: each request may waste a small amount, but because the server never stops, the waste keeps adding up until memory runs out and the server slows down, crashes, or gets killed.

For a command-line tool that exits in a second, the answer changes for the leak but not for the use after free. When a program exits, the operating system takes back all of its memory, including anything that was never released, so a leak has no time to build up into a problem. The use after free is just as harmful as before, because it only takes one bad access to corrupt data or crash the program, no matter how short its run is. So running time decides how much a leak matters, but it makes no difference to how dangerous a use after free is.