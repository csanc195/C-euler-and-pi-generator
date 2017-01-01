C-euler-and-pi-generator

The following program generates the mathematical numbers pi and e up 
to a desired number of significant digits using only the sum of the 
infinite Taylor series as the method of generation. 

A common program output appears as follows:

      Using the infinite taylor series to calculate e:
+------------------------------------------------------------+
| Calculated e with  10  significant digit accuracy:         |
+------------------------------------------------------------+
| Math.h  e:   2.71828182845904509080                        |
| Generated e: 2.71828182844675936281                        |
|                          ^                                 |
| Number of terms calculated:  13                            |
| Time used to compute:   0.0090000000000000010547119 ms     |
+------------------------------------------------------------+

     Using the infinite taylor series to calculate pi:
+------------------------------------------------------------+
| Calculated PI with  6  significant digit accuracy:         |
+------------------------------------------------------------+
| Math.h  PI:   3.14159265358979311600                       |
| Generated PI: 3.14159285358973949798                       |
|                       ^                                    |
| Number of terms calculated:  5000001                       |
| Time used to compute:   164.3559999999999945430317894 ms   |
+------------------------------------------------------------+
