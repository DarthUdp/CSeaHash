# CAHash
C implementation of the seahash non-cryptographic hash function.

# Disclaimer
<h2>seahash is not a cryptographically secure hash, it's tuned for
speed, not security, use a proper secure hashing algorithm for security
critical applications!</h2>

# TODO:
- [x] hashes are repeatable
- [x] passes dumb collision test
- [x] reasonably fast
- [ ] try to make results match reference
- [ ] make the code more readable and organized
- [ ] proper testing

# License
BSD 3-Clause License

Copyright (c) 2021, Matheus Xavier
All rights reserved.

Based on the [reference rust implementation](https://github.com/redox-os/tfs/blob/master/seahash/src/reference.rs)
by ticki.