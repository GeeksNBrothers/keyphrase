keyphrase
=========

A CLI utility that converts a private key expressed in hexadecimal to a phrase, with each word representing as close to 16 bits in your private key as your key's length allows. Also converts phrases back to their hexadecimal equivalents.

There are a few programs that do what this program does, but none I'd found that used a wordlist as extensive as I wanted. A more extensive wordlist allows larger keys to be encoded with fewer words. I wanted something that would give me a key I could reasonably memorize if I wanted to without compromising on security.

This program uses a 65,536 word list, allowing *any* private key to be encoded using as few English words as possible. For example, a 256 bit private key (such as the ones which underlie Bitcoin addresses) can be encoded using only 16 words without any loss of key strength.


## Compiling and Installing

    make
    make install

**NOTE:** On some systems, you may need to run `sudo make install` instead of just `make install`.


## Usage
    
Creating a phrase from a private key:

    $ keyphrase 0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3
    zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums
    

Getting a private key back from a phrase:

    $ keyphrase "zyzzyvas flutings mushers octopuses bizones talkier evokers coagent ringer neutral antipode omnibus havening whistles mistitled vacuums"
    0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3


## Bitcoin Examples

Getting a Bitcoin address and importable private key (WIF) from a 256-bit private key using [pycoin](https://github.com/richardkiss/pycoin) (cross-platform):

    $ python
    >>> from pycoin.key import Key
    >>> k = Key(secret_exponent=0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3)
    >>> print k.address()
    1Cj9a8z4r7yoHcMB87LAd5dMJbeb4dFTYt
    >>> print k.wif()
    L5oLTsjGYwq8Suef1c5jDc6kLbYS6LG1VG7E1kFoN4hg2sVNoW3W
    >>> 

Getting a Bitcoin address and importable private key (WIF) from a 256-bit private key using [bitcoin.sh](https://raw.githubusercontent.com/ryepdx/keyphrase/master/bitcoin.sh) (Linux-only):

    $ source bitcoin.sh
    $ newBitcoinKey 0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3
    ---
    secret exponent:          0xFFFF562F8F9A961E158BDE2D4CCD2A64BB1D923208939714675BFAB28BBAF2A3
    public key:
        X:                    CAFA2E819FFB11C209651801A47E574A330BDEEF805FB2689A1C2ADE3512F9B4
        Y:                    0AF853CFBECD031DBB5CAF3EE77CD35587D9CCA244B8F28910FC426E01C3E716
    compressed:
        WIF:                  L5oLTsjGYwq8Suef1c5jDc6kLbYS6LG1VG7E1kFoN4hg2sVNoW3W
        bitcoin address:      1Cj9a8z4r7yoHcMB87LAd5dMJbeb4dFTYt
    uncompressed:
        WIF:                  5Km2h5F7F312grYBstSzbaKyVTQSApQnsovX8saiKNEHzzX2psz
        bitcoin address:      1Q7anhn5mgRHTivdujHeSVyRkeAtBmw8K7
    $ 

Credit for bitcoin.sh goes to [Lucien Grondilu's bitcoin-bash-tools](https://github.com/grondilu/bitcoin-bash-tools).


## Running Tests (with inotify-tools)
    
    $ ./ua_tests.sh --watch
    $ ./unit_tests.sh --watch


## Running Tests (without inotify-tools)
    
    $ ./ua_tests.sh
    $ ./unit_tests.sh


## Notes

1. Be very careful in transcribing your keyphrase if you choose to write it down somewhere. There are a lot of unusual words in this wordlist, and quite a few that are likely *very* similar to words you come across often in your day-to-day life. Make sure to try decoding your keyphrase back into your private key before destroying any copies of the original private key.
2. If you're hacking on this project and you have [inotify-tools](https://github.com/rvoicilas/inotify-tools) installed, use the included test scripts! They'll give you the shiny, Grunt-like experience of having your tests compile and run automatically every time you make a change to your source files. If you're running Ubuntu, you can install the package with `sudo apt-get install inotify-tools`.
3. Wordlist based on [the English wordlist from SIL International](http://www-01.sil.org/linguistics/wordlists/english/).
