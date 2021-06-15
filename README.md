# CSeaHash
C implementation of the seahash **non-cryptographic** general purpose hash function.

# Disclaimer
seahash is not a cryptographically secure hash and neither is CSeaHash, they are tuned for
speed, not security!! __*Use a proper secure hashing algorithm for security
critical applications!*__, some suggestions include: SHA-3 (Keccak), BLAKE2
and if you absolutely can't use the previous two the SHA2 family.

# TODO:
- [x] hashes are repeatable
- [x] passes dumb collision test
- [x] reasonably fast
- [ ] make the code more readable and organized
- [ ] proper testing
- [x] tentatively support 32 bit targets

# Features
* Can be compiled without a libc and standalone
* tiny footprint with good quality hashes and very good collision resistance±

±[Disclaimer](#Disclaimer)

# Portability
The code uses only compiler builtins and stddefs, and tries to
make as few assumptions about platform features and layout 
as possible see comments on [seahash.c](./src/seahash.c) 
for information and what you might need to customize.
I assume you know how to use clang to cross compile or
have a custom gcc toolchain and can make changes to the
cmake file.

# License
BSD 3-Clause License

Copyright (c) 2021, Matheus Xavier
All rights reserved.

Based on the [reference rust implementation](https://github.com/redox-os/tfs/blob/master/seahash/src/reference.rs)
by ticki.