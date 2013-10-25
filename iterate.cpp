// iterate.cpp, written by Sayre Christenson, 20 October 2013

#include "md.hpp"

// verlet algorithm: position
void position_iterate(struct sys_state *state, struct params pars)
{
	double a;
	
	for (int i = 0 ; i < 2 ; i++) {
		for (int n = 0 ; n < pars.N ; n++) {

			state->pos[i][n] = state->pos[i][n] + pars.incr*state->vel[i][n] +
				                    (pars.incr*pars.incr) * state->acc[i][n] / 2;

			// periodic boundary
			state->pos[i][n] = state->pos[i][n] - pars.len * floor(state->pos[i][n] /pars.len);

			// what's up
			if (state->pos[i][n] != state->pos[i][n]) {
				cout << "shit\n";
				cout << state->vel[i][n] << endl;
				cout << state->acc[i][n] << endl;

				exit(EXIT_FAILURE);
			}
		}
	}
}

// verlet algorithm: velocity
void velocity_iterate(struct sys_state *state, double *current_acc[2], struct params pars)
{
	double current_a, new_a;
	
	for (int i = 0 ; i < 2 ; i++) {
		for (int n = 0 ; n < pars.N ; n++) {

			state->vel[i][n] = state->vel[i][n] + 
				pars.incr*(current_acc[i][n] + state->acc[i][n])/2;
		}
	}
}

// compute new accelerations
void compute_accel(struct sys_state *state, struct params pars)
{
	double r;
	double delta_x;
	double delta_y;

	double mag_acc;
	double acc_x;
	double acc_y;
	
	for (int n = 0 ; n < pars.N ; n++) {

		acc_x = 0;
		acc_y = 0;

		for (int m = 0 ; m < pars.N ; m++) {

			if (n == m) continue;

			delta_x = state->pos[X][m] - state->pos[X][n]; // m > n => dx > 0
			delta_y = state->pos[Y][m] - state->pos[Y][n];

			// periodic boundary (think about signs)
			delta_x = delta_x - round(delta_x / pars.len) * pars.len;
			delta_y = delta_y - round(delta_y / pars.len) * pars.len;

			r = sqrt(delta_x*delta_x + delta_y*delta_y);

			mag_acc = lj_acc(r, pars);

			acc_x += mag_acc * (delta_x/r);
			acc_y += mag_acc * (delta_y/r);
		}

		state->acc[X][n] = acc_x;
		state->acc[Y][n] = acc_y;
	}
}


double lj_acc(double r, struct params pars)
{
	return pars.VkT * pars.kTm * (2 * pow(pars.r0/r, 12) - pow(pars.r0/r, 6));
	// other ways of writing this		
}
