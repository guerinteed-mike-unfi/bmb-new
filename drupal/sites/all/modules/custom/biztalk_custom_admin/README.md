# Biztalk Drupal 7 Module

This module is created to be a part of two separate site repositories:

* https://github.com/metaltoad/unfi_com
* https://github.com/metaltoad/bluemarblebrands

It is created as a Git submodule inside the above repositories. They have diverged a bit, and due to some merge conflict issues with unfi_com, it's probably best to use those repositories to make sure the codebase is specific for the intended site.

To clone these repositories:
```
git submodule init
git submodule update
```

It provides an interface for exporting Webform submissions into a pipe-delimited file.

The files are output using cron, and placed in the *output* directory, which is actually a symlink.

At the time of this writing, the symlink is pointing to the shared directory on the server:

```
/mnt/cifs
```

To change the destination of the output, the symlink needs to be changed to point to the proper place.
