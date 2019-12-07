#include <vector>
#include <cmath>
#include <iomanip>


class Experiment
{
private:
    bool _record_trajectories;
    double _x1, _x2, _v1, _v2, _v_com, _time, _dt;
    unsigned long long int  _m1, _m2, _collision_counter;
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

Experiment::Experiment(const int mass_ratio, bool record_trajectories)
{
    _collision_counter = 0;
    _time = 0.;
    _m1 = 1; _m2 = mass_ratio;
    _x1 = 1., _x2 = 2.;
    _v1 = 0., _v2 = -1.;

    _record_trajectories = record_trajectories;
    if (_record_trajectories) {record_parameters();}
}

Experiment::~Experiment()
{   
    _collision_counter = 0;
    _record_time.clear();
    _record_x1.clear();
    _record_x2.clear();
    _record_v1.clear();
    _record_v2.clear();
}

void Experiment::simulate()
{   
    do{
        // collision of mass 1 with wall
        if (_v1 < 0.)
        {
            // time until collision & time update
            _dt = - _x1 / _v1;
            _time += _dt;
            // places of the masses
            _x1 = 0;
            _x2 += _v2 * _dt;
            // velocities after collison
            _v1 *= -1.;
        }
        // collision of the two masses
        else
        {
            // mommentum of the center of mass
            _v_com = (_m1 * _v1 + _m2 * _v2) / (_m1 + _m2);
            // time until next collision & time update
            _dt = (_x1 - _x2) / (_v2 - _v1);
            _time += _dt;
            // place of next collision
            _x1 += _v1 * _dt;
            _x2 += _v2 * _dt;
            // velocities after collision
            _v1 = 2. *  _v_com - _v1;
            _v2 = 2. * _v_com - _v2;
        }
        _collision_counter ++;
        if (_record_trajectories) {record_parameters();}
    }
    while(std::abs(_v1) > std::abs(_v2) or _v1 < 0.);

    if (_record_trajectories)
    {
        // continue trajectories a bit after last collision
        _dt = 1;
        _x1 += _v1 * _dt;
        _x2 += _v2 * _dt;
        record_parameters();
    }
}

void Experiment::record_parameters()
{
    _record_time.push_back(_time);
    _record_x1.push_back(_x1);
    _record_x2.push_back(_x2);
    _record_v1.push_back(_v1);
    _record_v2.push_back(_v2);
}

unsigned long long int Experiment::get_collision_counter() const
{
    return _collision_counter;
}

bool Experiment::trajectories_available() const
{
    return _record_trajectories;
}

std::vector<double> Experiment::get_time_record() const
{
    return _record_time;
}

std::vector<double> Experiment::get_x1_record() const
{
    return _record_x1;
}

std::vector<double> Experiment::get_x2_record() const
{
    return _record_x2;
}

std::vector<double> Experiment::get_v1_record() const
{
    return _record_v1;
}

std::vector<double> Experiment::get_v2_record() const
{
    return _record_v2;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool record_trajectories(unsigned long long int m)
{
    if (m <= 10e6) {return true;} else {return false;}
}