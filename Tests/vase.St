/* vase.St */
/* A test file for the Staple language and interpreter. */

:width [ 15 ] def
:star  [ 42 chr ] def
:space [ 32 chr ] def

:vase [
  [ 0 2 4 7 10 12 13 10 5 2 1 1 2 0 ] unpack

  depth [
    dup [ space print ] swap width - times
    dup [ star print ] swap times
    dup [ star print ] swap times
    dup [ space print ] swap width - times

    pop 
    " " println
  ] swap times
] def

" " println
vase
" " println
