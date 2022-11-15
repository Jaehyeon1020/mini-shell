OBJS=minishell.o head.o tail.o cat.o cp.o mv.o rm.o pwd.o cd.o exit.o
TARGET=pa2 head tail cat cp mv rm pwd
 
all: $(TARGET)

pa2 : minishell.o cd.o exit.o
	gcc -o pa2 minishell.o cd.o exit.o

head : head.o
	gcc -o head head.o

tail : tail.o
	gcc -o tail tail.o

cat : cat.o
	gcc -o cat cat.o

cp : cp.o
	gcc -o cp cp.o

mv : mv.o
	gcc -o mv mv.o

rm : rm.o
	gcc -o rm rm.o

pwd : pwd.o
	gcc -o pwd pwd.o

head.o : head.c
	gcc -c head.c

tail.o : tail.c
	gcc -c tail.c

cat.o : cat.c
	gcc -c cat.c

cp.o : cp.c
	gcc -c cp.c

mv.o : mv.c
	gcc -c mv.c

rm.o : rm.c
	gcc -c rm.c

pwd.o : pwd.c
	gcc -c pwd.c

minishell.o : minishell.c
	gcc -c minishell.c
	
cd.o : cd.c
	gcc -c cd.c

exit.o : exit.c
	gcc -c exit.c

clean:
	rm $(OBJS) $(TARGET)