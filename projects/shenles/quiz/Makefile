.DEFAULT_GOAL := testme

testme: testme.c
	gcc -o testme testme.c

runtest: testme
	-./testme

clean:
	rm -rf testme
