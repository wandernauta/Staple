/* donut.St */
/* A test file for the Staple language and interpreter. */

:star  [ 42 chr ] def
:space [ 32 chr ] def

0 [
  1 +

  0 [
    1 +

    over 10 - float 2.0 *
    over 20 - float
    hypot

    dup ceil 7.0 gt
    swap floor 15.0 lt
    both

    dup [ star print ] fi
    dup negate [ space print ] fi
    pop
  ] 40 times

  pop

  " " println
] 20 times
