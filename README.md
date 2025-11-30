The program does a knights tour in 2 different ways, either via brute force or a random route until it cant move anymore.
starting off, you can pick the size of the board by changing the #define boardSize at the very top of the program.
then you can run the program, where it gives you 3 options to run, by writing 1, 2 or 3
the first option runs the random tour outputting a board with how far it got starting from each sqaure.
the second option rund the brute force outputting a board with how far it got starting from each sqaure, however this option is very slow on boards bigger that 5x5
the third option runs the brute force tour aswell however it only starts from the top left, outputting the sequence it took once it has found a succesfull route.