<h1>Install</h1>

<pre>
$ git clone git@github.com:slitvinov/basilisk
$ cd basilisk/src
$ >Makefile.tests
$ cp config.gcc config
$ BASILISK="`pwd`" make qcc draw_get.h draw_json.h
$ cd gl
$ make
</pre>


Tutorial (needs ImageMagic):

<pre>
$ ~/basilisk/src/qcc bump.c -lm
$ ./a.out > a.ppm
$ animate a.ppm
</pre>

