#include <vector>

class Experiment
{
private:
    bool _record_trajectories;
    double _x1, _x2, _v1, _v2, _v_com, _time, _dt;
    unsigned long long int _m1, _m2, _collision_counter;
    std::vector<double> _record_time, _record_x1, _record_x2, _record_v1, _record_v2;

public:
    Experiment(const int mass_ratio, bool record_trajectories);
    ~Experiment();
    void simulate();
    void record_parameters();
    unsigned long long int get_collision_counter() const;
    bool trajectories_available() const;
    std::vector<double> get_time_record() const;
    std::vector<double> get_x1_record() const;
    std::vector<double> get_x2_record() const;
    std::vector<double> get_v1_record() const;
    std::vector<double> get_v2_record() const;
};

bool record_trajectories(unsigned long long int m)