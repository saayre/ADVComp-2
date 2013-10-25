// md.cpp, written by Sayre Christenson, 10 October 2013

#include"md.hpp"

int main(int argc, char *argv[])
{
	// help statement
	if (argc == 0) cout << "usage: ./md 'N' 'exp of step_max'\n";

	// set parameters
	struct params pars = set_pars( atoi(argv[1]) );
	int step;
	int step_max = pow(10, atoi(argv[2]));

	// set up grid
	struct sys_state *state = initialize(pars);

	// output
	ofstream movie;
	movie.open("md.xyz");
	movie << pars.N << endl << endl;

	// first iterate
	compute_accel(state, pars);

	// gen case iterate
	double *current_acc[2];
	for (step = 0 ; step < step_max ; step++) {

		// update position
		position_iterate(state, pars);

		// update accel field
		*current_acc = *(state->acc);
		compute_accel(state, pars);

		// update velocities
		velocity_iterate(state, current_acc, pars);

		// scaling (implement later)

		// calculate MSD and PCF

		// write to file for vdm
		if (step % 10 == 0) {
			for (int n = 0 ; n < pars.N ; n++) {
				movie << " X " << state->pos[X][n] << ' ' << state->pos[Y][n] << " 0" << endl;
			}
		}
	}

	return 0;
}
