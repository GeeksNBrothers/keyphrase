keyphrase
=========

A CLI utility that converts a private key expressed in hexadecimal to a phrase, with each word representing as close to 16 bits in your private key as your key's length allows. Also converts phrases back to their hexadecimal equivalents.

There are a few programs that do what this program does, but none I'd found that used a wordlist as extensive as I wanted. A more extensive wordlist allows larger keys to be encoded with fewer words. I wanted something that would give me a key I could reasonably memorize if I wanted to without compromising on security.

This program uses a 65,536 word list, allowing *any* private key to be encoded using as few English words as possible. For example, a 256 bit private key (such as the ones which underlie Bitcoin addresses) can be encoded using only 16 words without any loss of key strength.


## Compiling

    gcc -o keyphrase keyphrase.c funcs.c -std=c99 -Wall


## Usage
    
Creating a phrase from a private key:

    $ keyphrase 0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3
    zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums
    

Getting a private key back from a phrase:

    $ keyphrase "zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums"
    0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3


## Running Tests (with inotify-tools)
    
    $ ./ua_tests.sh
    $ ./unit_tests.sh


## Running Tests (without inotify-tools, unit tests only)

    $ gcc -o tests tests.c funcs.c -std=c99 -Wall
    $ ./tests


**NOTE:** Converting phrases back to keys does not yet work.

**NOTE:** Be very careful in transcribing your keyphrase if you choose to write it down somewhere. There are a lot of unusual words in this wordlist, and quite a few that are likely *very* similar to words you come across often in your day-to-day life. Make sure to try decoding your keyphrase back into your private key before destroying any copies of the original private key.

**NOTE:** If you have [inotify-tools](https://github.com/rvoicilas/inotify-tools) installed, use the included test scripts! They'll give you the shiny, Grunt-like experience of having your tests compile and run automatically every time you make a change to your source files. If you're running Ubuntu, you can install the package with `sudo apt-get install inotify-tools`.

