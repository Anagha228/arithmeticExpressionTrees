CC = clang
CFLAGS = -std=c99 -Wall -pedantic

all: bin/preorder bin/inorder bin/postorder bin/calculate bin/heap

bin/preorder: src/preorder.c
	$(CC) $(CFLAGS) src/preorder.c -o bin/preorder

bin/inorder: src/inorder.c
	$(CC) $(CFLAGS) src/inorder.c -o bin/inorder

bin/postorder: src/postorder.c
	$(CC) $(CFLAGS) src/postorder.c -o bin/postorder

bin/calculate: src/calculate.c
	$(CC) $(CFLAGS) src/calculate.c -o bin/calculate -lm

bin/heap: src/heap.c
	$(CC) $(CFLAGS) src/heap.c -o bin/heap

clean:
	rm -f bin/*