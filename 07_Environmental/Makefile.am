CFLAGS = -g

bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c


TESTS=test

test:
    echo "SHA1 \"checksum" | ./rhasher > provided
    echo -n "checksum" | sha1sum | awk '{print $$1 }' > expected
    cmp expected provided

    echo "MD5 \"checksum" | ./rhasher > provided
    echo -n "checksum" | md5sum | awk '{print $$1 }' > expected
    cmp expected provided
    
gitclean:
  git clean -df
