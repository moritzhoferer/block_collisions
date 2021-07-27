# Block collisions

This is another pretty inefficient way to determine PI. This implementation is motivated by two Youtube video ([Video 1](https://www.youtube.com/watch?v=HEfHFsfGXjs), [Video 2](https://www.youtube.com/watch?v=jsYwFizhncE)) by the channel 3Blue1Brown. This is a simple implementation that calculates the trajectory and the number of collisions. There is also a paper about this: Galperin, Gregory. ["Playing pool with π (the number π from a billiard point of view)." Regular and chaotic dynamics 8.4 (2003): 375-394.](https://doi.org/10.1070/RD2003v008n04ABEH000252). While I tried to parallelize the velocity updating, I realized that it triples the calculation time.

TODO:

* ~~**ISSUE** For mass ratios above 1:10**8 the program give a wrong results.~~
* ~~Export data in two csv files.~~
* ~~Adapt `trajectory.py` to the csv input.~~
