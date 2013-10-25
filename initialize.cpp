// initialize.cpp, written by Sayre Christenson, 17 October 2013

#include"md.hpp"

using namespace std;

struct sys_state *initialize(struct params pars)
{

	int n;
	srand(time(0));				// seed rand

	// position
	double *pos_x = new double[pars.N];
	double *pos_y = new double[pars.N];

	for (n = 0 ; n < pars.N ; n++) {

		pos_x[n] = pars.len * rand() / (double) RAND_MAX;
		pos_y[n] = pars.len * rand() / (double) RAND_MAX;
	}

	// velocity
	double *vel_x = new double[pars.N];
	double *vel_y = new double[pars.N];

	double v;
	for (n = 0 ; n < pars.N ; n++) {

		v = 2 * (rand() / (double) RAND_MAX);

		// double random
		if (1 - mb_dist(v, pars.kTm) < rand() / (double) RAND_MAX) {

			double angle = 2*M_PI * rand() / (double) RAND_MAX;
			vel_x[n] = v * cos(angle);
			vel_y[n] = v * sin(angle);
		}
		else n--;
	}

	// accel
	double *acc_x = new double[pars.N];
	double *acc_y = new double[pars.N];

	// assign
	struct sys_state *state = new struct sys_state;
	state->pos[X] = pos_x;
	state->pos[Y] = pos_y;

	state->vel[X] = vel_x;
	state->vel[Y] = vel_y;

	state->acc[X] = acc_x;
	state->acc[Y] = acc_y;

	return state;
}

double mb_dist(double v, double kTm)
{
	return (v / kTm) * exp(- v*v / (2 * kTm));
}


struct params set_pars(int n_particles)
{
	struct params pars;
	pars.N = n_particles;
	pars.len = 50;
	pars.kTm = 0.1;
	pars.incr = 0.003;
	pars.VkT = 2;
	pars.r0 = 1;

	return pars;
}
