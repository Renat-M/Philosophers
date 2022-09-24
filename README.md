# Philosophers
🍽 🍝 The project about threads and forks, mutex and semaphores

Dining philosophers problem is a problem created by Edsger Wybe Dijkstra in 1965 to explain the deadlock state of an operating system, which is traditionally commonly introduced in lectures on operating systems

Subject is presented in the [en.subject.pdf](https://github.com/lavrenovamaria/42-philosophers/files/7378771/en.subject.pdf)

For example, N philosophers are sitting at a round table and eating. A fork is placed between the philosophers, and the philosophers eat through the following process. 

The philosopher repeats three actions: \
`eating ➔ sleeping ➔ thinking`.
When eating, both forks should be used. 
If you lift both forks, eat for a certain amount of time. 
When you're done eating, put down your fork.
Not a single philosopher should die due to lack of food for a certain period of time.
If all the philosophers were hungry and picked up the left forks at the same time, the right forks would have already been picked up by the philosopher sitting to their right, and everyone would be forever unable to hold the right forks. That is, there is no further progress, and the philosophers remain on standby forever. This phenomenon is called deadlock. Once in a `deadlock`, philosophers continue to suffer and die of starvation.
The task is to implement a program that solves this problem using `mutex` or `semaphore`

The philosopher and the fork have the same number of forks, and the philosopher can eat only with two forks.

A philosopher should sleep after eating.
A philosopher begins to think after sleeping.
A philosopher dies if he does not eat for a certain period of time.
The program ends when one philosopher dies.
You have to do it to avoid deadlock.

Arguments when input are as follows:

The first argument number_of_philosophers: the number of philosophers (same as the number of forks).

2nd argument time_to_eat: time to eat [ms]

3rd argument time_to_die: Time to die [ms] (Initialized when eaten)

4th argument time_to_sleep: Sleep time [ms]

Fifth argument number_of_times_each_philosopher_must_eat: the number of times philosophers ate to terminate the program (all philosophers)

In mandatory part we used threads and mutexes, in bonus part - processes and semaphores

- Do not test with more than 200 philosophers
- Do not test with time_to_die or time_to_eat or time_to_sleep under 60 ms - Test with 1 800 200 200, the
philosopher should not eat and should die!
- Test with 5 800 200 200, no one should die!
- Test with 5 800 200 200 7, no one should die and the simulation should stop when all the philosopher has eaten
atleast 7 times each.
- Test with 4 410 200 200, no one should die!
- Test with 4 310 200 100, a philosopher should die!
