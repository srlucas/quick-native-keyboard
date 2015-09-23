# quick-native-keyboard
Quick wrapper to Marmalade's s3eKeyboard features.

The basic idea is to be able to quickly use a native keyboard from **Marmalade QUICK** without the need of much coding from the quick side of things.

# Requirements
* This extension has been tested to be compatible with **Marmalade 7.7.x**. It should work with 7.8.x as well but I didn't had the time to test is properly.
* 

# How to install
* Clone this repo somewhere
* Add the following lines to add something like the following to **<sdk root>/s3e/s3e-default.mkf**:
```mkb
options
{
    module_paths="c:/full/path/to/my/root/github/folder"
}
```
This will be super helpfull when building extensions
* Tell tolua++ to include the new code:
  * Edit ***quick/quickuser_tolua.pkg*** and add something like:
  $cfile "s3eKeyboard/quick/QNativeKeyboard.h"
* Rebuild lua bindings:
  * Run ***<quick root>/quick/quickuser_tolua*** (.bat on Windows, bash script on Mac).
*Rebuild Quick Binaries:
  * Add the new files to ***quick/quickuser.mkf***:
  ```mkb
  files
{
    quickuser_tolua.cpp
    quickuser_tolua.pkg
    quickuser.h
  
    # Our new files
    s3eKeyboard/quick/QNativeKeyboard.h
    s3eKeyboard/quick/QNativeKeyboard.cpp
} 
  ```
  * Follow the guide here: http://docs.madewithmarmalade.com/display/MD/Extending+Quick#ExtendingQuick-rebuild
  * 
# Using the extension from LUA
## Hide/Show Keyboard
In order to use the extension you can use any of the two following methods:
```
nativeKeyboard.showKeyboard()
```
or
```
nativeKeyboard.showKeyboard()
```
to show/hide the keyboard.

## Getting the input text form the keyboard
the extension throws a **char_event** event to the lua layer with the following fields


#
KUDOS to [Kidloom](http://kidloom.com/) for leting me share this code with the community.
