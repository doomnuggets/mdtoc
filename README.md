# mdtoc

Simple table of contents generator for GitHub flavored markdown files.


## Installation

**Clone the repository**

```bash
git clone https://github.com/doomnuggets/mdtoc.git
```

**Move your horses**

```
cd mdtoc
```

**Compile from source**

If you'd like to call `mdtoc` from anywhere on your system use:

```bash
make install
```

Or, if you only want to test it out for now:

```bash
make
```


## Generating a table of contents

You can either pass the file to read from like so:

```
mdtoc file.md
```

Or you can pipe to `mdtoc`:

```
cat ~/file.md | mdtoc
```

### Example

```
doom@nuggets:~/code/c/mdtoc: ./mdtoc README.md
+ [mdtoc](#mdtoc)
  + [Installation](#installation)
  + [Generating a table of contents](#generating-a-table-of-contents)
    + [Example](#example)
```
