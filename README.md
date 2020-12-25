# fake_work
Provide a busy loop issuing `noops`.

Link as a shared library.

Usage: fake_work(n) where n is the number of iterations to spin for. To spin for a set amount of time, multiple the desired time in nanoseconds by the average frequency of your processor.
