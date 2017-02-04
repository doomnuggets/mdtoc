# mdtoc

Simple table of contents generator for GitHub flavored markdown files.


## Installation

1. Clone the repository

```bash
git clone https://github.com/doomnuggets/mdtoc.git
```

2. Compile it from source

You can run `make` to build it and test it out afterwards, or you can execute `sudo make
install` to build it and end up with a copy of it in `/usr/bin/mdtoc`.


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
