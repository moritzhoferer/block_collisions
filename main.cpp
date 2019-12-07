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
//
// Pi: 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "timer.h"
#include "core.cpp"

using namespace std;

int main(int argc, char **argv) {

    timer total_time;
    total_time.start();
    
    string output_file_name;
    unsigned long long int mass_ratio = strtod(argv[1], nullptr);
    
    if (record_trajectories(mass_ratio))
    // if (true)
    {
        Experiment collision_experiment(mass_ratio, true); 
        collision_experiment.simulate();
        cout << "Number of collision: " << collision_experiment.get_collision_counter() << endl;

        if (collision_experiment.trajectories_available()){
            // load data
            vector<double> times = collision_experiment.get_time_record();
            vector<double> x1s = collision_experiment.get_x1_record();
            vector<double> x2s = collision_experiment.get_x2_record();
            vector<double> v1s = collision_experiment.get_v1_record();
            vector<double> v2s = collision_experiment.get_v2_record();
            // write data into file
            output_file_name = "data/m2_" + to_string(mass_ratio) + ".csv";
            ofstream output_file;
            output_file.open(output_file_name);
            output_file << "time,x_1,x_2,v_1,v_2" << endl;
            for (unsigned int i = 0; i < times.size(); ++i) {
                output_file << times[i] << "," << x1s[i] << "," << x2s[i] << ",";
                output_file << v1s[i] << "," << v2s[i] << endl;
            }
            output_file.close();
        }
    }
    else
    {   
        unsigned long long int max_ratio = mass_ratio;
        mass_ratio = 1;
        vector<unsigned long long int> mass_ratios, counts;

        do{
            Experiment collision_experiment(mass_ratio, false); 
            collision_experiment.simulate();
            cout << "Number of collision: " << collision_experiment.get_collision_counter() << endl;
            mass_ratios.push_back(mass_ratio);
            counts.push_back(collision_experiment.get_collision_counter());
            mass_ratio *= 100;
            collision_experiment.~Experiment();
        } while (mass_ratio <= max_ratio);
        
        output_file_name = "data/collisions_counts.csv";
        ofstream output_file;
        output_file.open(output_file_name);
        output_file << "mass_ratio,collision_count" << endl;
        for (unsigned int i = 0; i < mass_ratios.size(); ++i) {
            output_file << mass_ratios[i] << "," << counts[i] << endl;
        }
        output_file.close();        
    }

    total_time.stop();
    total_time.check("Total calculation time");   

    // } else {

    //     double m2_max = masses[1];
    //     masses[1] = 1;

    //     vector<int> record_mass_ratio;
    //     vector<int> record_collision_counter;

    //     do {
    //         timer iteration_time;
    //         iteration_time.restart();
    //         cout << "Mass ratio: 1:" << masses[1] << endl;
    //         collision_counter = 0;
    //         velocities[0] = 0; velocities[1] = -1;

    //         do {
    //             // velocities after the collision of the two blocks
    //             v[0] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[0];
    //             v[1] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[1];
    //             // Parallelization triples the calculation time. NOT SO GOOD.
    //             // #pragma omp parallel num_threads(2)
    //             // {
    //             //     int thread_id = omp_get_thread_num();
    //             //     v[thread_id] = 2. * (masses[0] * velocities[0] + masses[1] * velocities[1])/(masses[0] + masses[1]) - velocities[thread_id];

    //             // }
    //             collision_counter += 1;

    //             if (v[0] < 0){
    //                 //collision of mass 1 with the wall
    //                 collision_counter += 1;
    //                 // mass 1 turns direction and keeps velocity
    //                 v[0] *= -1.;
    //             }

    //             velocities[0] = v[0];
    //             velocities[1] = v[1];
    //         }
    //         while (velocities[1] < 0. or velocities[1] < abs(velocities[0]));

    //         record_mass_ratio.push_back(masses[1]);
    //         record_collision_counter.push_back(collision_counter);
    //         masses[1] *= 100;

    //         iteration_time.stop();
    //         // cout << iteration_time.get_time() << endl;
    //         iteration_time.check();        
    //     }
    //     while(masses[1] <= m2_max);
        
    //     
        
    //     output_file_name = "data/collisions.csv";
    //     ofstream output_file;
    //     output_file.open(output_file_name);
    //     output_file << "mass_ratio,collisions" << endl;
    //     for(unsigned int i = 0; i < record_mass_ratio.size(); ++i){
    //         output_file << record_mass_ratio[i] << "," << record_collision_counter[i] << endl;
    //     }
    //     output_file.close();
    // }

    return 0;
}
