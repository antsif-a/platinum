modern c++ is a complex language.
we establish certain design and style conventions and think that they are best for writing modern c++ 

philosphy:
1. performance above all
2. a fool admires complexity, a genius admires simplicity
    - api should be self-explanatory
    - interfaces should be convenient
3. name things as they are
    - array is a dynamic array
    - tuple is a tuple
    - hash_map is a hash map
    - string is a null terminated string

design choices:
1. modules over headers
2. pass-by-reference is a default (implicit) behaviour for non-scalar arguments in functions,
copying complex objects should be explicit
   - use raw pointers for nullable/optional arguments, C‑compatible structures, or when the caller must explicitly take the address
   - use const on member functions for read‑only access; mark parameters const when the function does not modify them
3. members are public for lightweight structs and are private for complex classes
4. forbid exceptions, use structs like result containing value or error 
5. when it's ambiguous what implicit conversion is used, there is always an explicit conversion
    - .buffer() and .str() for string: `string s; read(fd, s.buffer());`

stylistic choices:
1. prefer snake case over camel case
2. prefer lowercase over uppercase
