/* colors.St */
/* A test file for the Staple language and interpreter. */

:red [ " [31m " print ] def
:grn [ " [32m " print ] def
:ylw [ " [33m " print ] def
:blu [ " [34m " print ] def
:mga [ " [35m " print ] def
:cyn [ " [36m " print ] def
:wht [ " [37m " print ] def

:init   [ " [0m " print ] def

/* Push the names of all defined functions to the stack, then pop :init */
defs pop

" " println

depth [
  /* Call init. We want normal text. */
  :init call

  /* Print the name of the function. */
  dup string print

  /* Call the function */
  call

  /* Print a row of #'s */
  " # " [ " # " cat ] 40 times println
] swap times

:init call " " println
