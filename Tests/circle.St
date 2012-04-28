/* circle.St */
/* A test file for the Staple language and interpreter. */

[
  /* Ask the user about their circle's radius, convert the input */
  " " println
  " What's the radius of your circle? " prompt float

  /* If there's a non-zero float on top... */
  if dup 0.0 eq negate [
    /* Multiply that with two pi */
    3.14 2.0 * *
    
    /* Print the result as a string */
    " Your circle's circumference is about " print
    string println
  ] fi
] loop
