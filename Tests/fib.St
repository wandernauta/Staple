/* fib.St */
/* A test file for the Staple language and interpreter. */

:fib [
  over over +
] def

" " println
" Here are the first 25 Fibonacci numbers, for your viewing pleasure: " println

0 1
[ fib ] 25 times

pack println

" " println
