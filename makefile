SRCS_MVOTE = voter.c voterintk.c postal_codes_node.c postal_codes.c \
dataholder.c bucket.c  hash_table.c action.c mvote.c  

OBJS_MVOTE = $(SRCS_MVOTE:.c=.o)

all: mvote

mvote: $(OBJS_MVOTE)
	gcc -g -o mvote $(OBJS_MVOTE) -lm

voter.o: voter.h voter.c
	gcc -g -c voter.c -o voter.o

voterintk.o: voterintk.h voterintk.c voter.h
	gcc -g -c voterintk.c -o voterintk.o

postal_codes_node.o: postal_codes_node.h postal_codes_node.c voterintk.h
	gcc -g -c postal_codes_node.c -o postal_codes_node.o

postal_codes.o: postal_codes.h postal_codes.c voter.h postal_codes_node.h
	gcc -g -c postal_codes.c -o postal_codes.o

dataholder.o: dataholder.h dataholder.c voter.h
	gcc -g -c dataholder.c -o dataholder.o

bucket.o: bucket.h bucket.c voter.h
	gcc -g -c bucket.c -o bucket.o

hash_table.o: hash_table.h hash_table.c bucket.h voter.h dataholder.h
	gcc -g -c hash_table.c -o hash_table.o

action.o: action.h action.c hash_table.h voter.h
	gcc -g -c action.c -o action.o

mvote.o: mvote.c voter.h hash_table.h
	gcc -g -c mvote.c -o mvote.o











.PHONY: clean
clean:
	rm -f mvote $(OBJS_MVOTE)