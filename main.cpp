// Moritz Hoferer
// Date: January 15, 2019
// Work motivated by the video "The most unexpected answer to a counting puzzle" by 3Blue1Brown to replicate results of
// G. GALPERIN about "PLAYING POOL WITH π (THE NUMBER π FROM A BILLIARD POINT OF VIEW)
// Link to video: https://www.youtube.com/watch?v=HEfHFsfGXjs
// DOI of paper: https://doi.org/10.1070/RD2003v008n04ABEH000252
//
// For mass ratios larger than 1:1e4, the program calculates the trajectory of the two masses.
// Otherwise the program determins the number of collisons starting of a mass ration 1:1 and increasing the 
// second mass by a factor of 100 in every iteration.

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

    double masses[2];
    double velocities[2];
    double v[2];
    unsigned long long int collision_counter = 0;
    string output_file_name;

    masses[0] = 1; masses[1] = strtod(argv[1], nullptr);

    if (masses[1] <= 10000){

        double place;
        vector<double> places;
        double dt;
        vector<double> times;

        velocities[0] = 0., velocities[1] = -1.;
        output_file_name = "m2_" + string(argv[1]) + ".dat";
        times.push_back(0.);
        places.push_back(1.); places.push_back(1.5);

         do {
            // time until collision
            dt = (places.end()[-1] - places.end()[-2]) / (velocities[0] - velocities[1]);
            place = places.end()[-2] + velocities[0] * dt;
            places.push_back(place); places.push_back(place);
            times.push_back(times.back() + dt);

            // velocities after the collision of the two blocks
            v[0] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[0];
            v[1] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[1];
            collision_counter += 1;

            if (v[0] < 0){
                // time until collision of mass 1 with the wall
                dt = -places.end()[-2]/v[0];
                //collision of mass 1 with the wall
                collision_counter += 1;
                // position of mass 1
                places.push_back(0.);
                // position of mass 2
                places.push_back(places.end()[-2] + v[1] * dt);
                // update time
                times.push_back(times.back() + dt);
                // mass 1 turns direction and keeps velocity
                v[0] *= -1.;
            }

            velocities[0] = v[0];
            velocities[1] = v[1];

        }
        while (velocities[1] < 0. or velocities[1] < abs(velocities[0]));

        cout << "Number of collisions: " << collision_counter << endl;

        ofstream output_file;
        output_file.open(output_file_name);
        output_file << "# t \t x1 \t x2" << endl;
        for (unsigned int i = 0; i < times.size(); ++i) {
            output_file << times[i] << "\t" << places[2*i] << "\t" << places[2*i + 1] << endl;
        }
        output_file.close();

    } else {

        double m2_max = masses[1];
        masses[1] = 1;

        output_file_name = "m2_collisions.dat";
        ofstream output_file;
        output_file.open(output_file_name);
        output_file << "# m2 \t collisions" << endl;

        do{
            collision_counter = 0;
            velocities[0] = 0; velocities[1] = -1;

            do {
                // velocities after the collision of the two blocks
                v[0] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[0];
                v[1] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[1];
                collision_counter += 1;

                if (v[0] < 0){
                    //collision of mass 1 with the wall
                    collision_counter += 1;
                    // mass 1 turns direction and keeps velocity
                    v[0] *= -1.;
                }

                velocities[0] = v[0];
                velocities[1] = v[1];
            }
            while (velocities[1] < 0. or velocities[1] < abs(velocities[0]));

            output_file << masses[1] << "\t" << collision_counter << endl;

            masses[1] *= 100;

        }
        while(masses[1] < m2_max);

        output_file.close();
    }


    return 0;
}
