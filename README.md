# Overview #
BOPC with dockerfile

-- To build, run the following from the project root:
```
docker build -t bopc .
```
-- Once built, to run, run the following:
```
docker run --rm -it bopc 
```


This is a fork of BOPC we created to evaluate BOPC in our paper, *A
Generic Technique for Automatically Finding Defense-Aware Code Reuse
Attacks*.

More details to be announced.

The primary changes are:
* Support for 32-bit executables.  The original version of BOPC had
  many 32-bit features hard-coded in (i.e., `st.rax` vs `st.eax`)
  that prevented it from working on 32-bit executables.
* Addition of the `--no-awp` option.  This option prevents BOPC from
  using Arbitrary Write Primitives (AWP) and the ability to
  arbitrary initialize a register.  This is useful to see if BOPC
  really needs these strong assumptions to be able to find an
  attack.
* Various bug fixes.  Some (but not all) have been merged back to
  the original BOPC repository.

