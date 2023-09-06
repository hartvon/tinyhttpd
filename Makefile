CFLAGS := -O0 -g -W -Wall -lpthread -Wno-unused-parameter

all: httpd client test cgi

httpd: httpd.c
	gcc $(CFLAGS) -o $@ $<

client: simpleclient.c
	gcc $(CFLAGS) -o $@ $<

test: test/test.c
	gcc $(CFLAGS) -o $@ $<

cgi: test/cgi.c
	gcc $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm httpd simpleclient client test cgi
