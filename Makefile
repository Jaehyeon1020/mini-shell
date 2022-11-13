OBJS=minishell.o head.o tail.o cat.o cp.o mv.o rm.o pwd.o cd.o exit.o
#TARGET=pa2 head tail cat cp mv rm pwd
 
#all: $(TARGET)

pa2 : head.o tail.o cat.o cp.o mv.o rm.o pwd.o cd.o exit.o minishell.o
	gcc -o pa2 head.o tail.o cat.o cp.o mv.o rm.o pwd.o cd.o exit.o minishell.o

#head : head.o
#	gcc -o head head.o

#tail : tail.o
#	gcc -o tail tail.o

#cat : cat.o
#	gcc -o cat cat.o

#cp : cp.o
#	gcc -o cp cp.o

#mv : mv.o
#	gcc -o mv mv.o

#rm : rm.o
#	gcc -o rm rm.o

#pwd : pwd.o
#	gcc -o pwd pwd.o

minishell.o : minishell.c executable.h builtin_cmd.h
	gcc -c minishell.c

head.o : head.c executable.h
	gcc -c head.c

tail.o : tail.c executable.h
	gcc -c tail.c

cat.o : cat.c executable.h
	gcc -c cat.c

cp.o : cp.c executable.h
	gcc -c cp.c

mv.o : mv.c executable.h
	gcc -c mv.c

rm.o : rm.c executable.h
	gcc -c rm.c

pwd.o : pwd.c executable.h
	gcc -c pwd.c

cd.o : cd.c builtin_cmd.h
	gcc -c cd.c

exit.o : exit.c builtin_cmd.h
	gcc -c exit.c

clean:
	rm $(OBJS) pa2
