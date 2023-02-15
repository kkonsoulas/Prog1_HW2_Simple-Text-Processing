compile:
	gcc -Wall -g hw2.c -o hw2 -lhw2 -L.

tests: test1 test2 test3 test4

test1:
	cat hw2tests/hw2_1.h > hw2.h
	gcc -Wall -g hw2.c -o hw2 -lhw2 -L.
	./hw2 -p -h <hw2tests/a_in1 >hw2tests/myout
	diff hw2tests/myout hw2tests/a_out1

test2:
	cat hw2tests/hw2_2.h > hw2.h
	gcc -Wall -g hw2.c -o hw2 -lhw2 -L.
	./hw2 -p -h <hw2tests/a_in2 >hw2tests/myout
	diff hw2tests/myout hw2tests/a_out2

test3:
	cat hw2tests/hw2_3.h > hw2.h
	gcc -Wall -g hw2.c -o hw2 -lhw2 -L.
	./hw2 -p -h -r hw2tests/s_in3 <hw2tests/a_in3 >hw2tests/myout
	diff hw2tests/myout hw2tests/a_out3

test4:
	cat hw2tests/hw2_4.h > hw2.h
	gcc -Wall -g hw2.c -o hw2 -lhw2 -L.
	./hw2 -p -h -r hw2tests/s_in4 <hw2tests/a_in4 >hw2tests/myout
	diff hw2tests/myout hw2tests/a_out4