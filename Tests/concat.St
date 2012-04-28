/* concat.St */
/* A test file for the Staple language and interpreter. */

:pushfun [
  /* Build a few lists */
  [ 34 chr print 32 chr print ]
  [ " And in case I don't see you again... " println ]
  [ " Good afternoon, " print ]
  [ " good evening, " print ]
  [ " and goodnight! " print ]
  [ 34 chr println ]

  /* Concatenate them */
  [ cat ] 5 times
] def

pushfun do
