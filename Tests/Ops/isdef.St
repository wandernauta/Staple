:foo [ true ] def
:bar [ true ] def

[ :foo isdef ] assert
[ :bar isdef negate ] assert