// md.hpp, written by Sayre Christenson, 10 October 2013

#define _USE_MATH_DEFINES

#define X 0
#define Y 1

#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<fstream>

using namespace std;

struct params {
	
	int N;
	double len;
	double kTm;
	double VkT;
	double incr;
	double r0;
};

struct sys_state {

	double *pos[2];
	double *vel[2];
	double *acc[2];
};

struct sys_state *initialize(struct params pars);
void position_iterate(struct sys_state *state, struct params pars);
void compute_accel(struct sys_state *state, struct params pars);
void velocity_iterate(struct sys_state *state, double *current_acc[2], struct params pars);

struct params set_pars(int n_particles);

double mb_dist(double v, double kT_m);

double lj_acc(double r, struct params pars);
