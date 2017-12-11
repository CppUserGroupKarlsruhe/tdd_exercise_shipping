Shipping costs TDD kata
=======================

Test-driven development is a software development process that
basically puts writing a failing unit test before modifying your
production code. This repository provides scaffolds for various
programming languages for hassle-free first steps in the world
of TDD by solving a simple task.

# The task

To serve the ever faster growing world population with Christmas
presents, Santa Claus needs to outsource shipping of parcels
to external contractors. To make the most of his budget, he
is looking for the cheapest way to deliver presents to children.

Your task is to find the cheapest means of transporting a parcel
of given dimensions (length x width x height) and weight among
the following carriers:

## Reindeer Express

| Max. dimensions [cm] | Max. weight [kg] | Price [North Pole Dollar] |
|----------------------|------------------|---------------------------|
| 30 x 20 x 20         | 2                | 2.99                      |
| 40 x 30 x 20         | 5                | 4.99                      |
| 60 x 10 x 60         | 4                | 5.99                      |
| 120 x 60 x 60        | 30               | 14.99                     |

## Fair and square

| Max. dimensions [cm] | Max. weight [kg] | Price [North Pole Dollar] |
|----------------------|------------------|---------------------------|
| 15 x 15 x 15         | 1.5              | 2.25                      |
| 25 x 25 x 25         | 2.5              | 3.24                      |
| 35 x 35 x 35         | 5                | 4.00                      |
| 100 x 100 x 100      | 75               | 56.25                     |

## Chimney stuffers

| Max. dimensions [cm] | Max. weight [kg] | Price [North Pole Dollar] |
|----------------------|------------------|---------------------------|
| 15 x 15 x 40         | 10               | 5.00                      |
| 15 x 15 x 60         | 15               | 6.00                      |
| 15 x 15 x 80         | 20               | 7.00                      |
| 15 x 15 x 100        | 25               | 8.00                      |


Quickstart with C++
-------------------

Follow the instructions in the `README.md` file in the `cpp` branch:

```
> git clone https://github.com/blue-yonder/tdd_exercise_shipping.git
> cd tdd_exercise_shipping
> git checkout cpp
> cmake
```

The header file `shipping/shipping/shipping.h` is supposed to hold any public
declarations you require. The source file `shipping/src/shipping.cpp` is supposed
to hold your implementation. Finally, drive your implementation by adding
tests to the `tests/test_shipping.cpp` file.

To compile your code and execute the unit tests, use the following commands:

```
> make && ctest --verbose
```

Running this command for the first time will present you with a _failing_ unit
test. The unit test does not do anything meaningful, it is just there to
illustrate how writing tests with googletest works (see
[here](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md#basic-assertions)
for more information on googletest).
