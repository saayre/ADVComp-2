// test2.cpp, written by Sayre Christenson, 24 October 2013

#include"md.hpp"

int main(int argc, char *argv[])
{
	// help statement
	if (argc == 1) {
		cout << "usage: ./test2 'N' 'exp of step_max'\n";
		return 1;
	}

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
	for (int n = 0 ; n < pars.N ; n++) {
		state->acc[X][n] = 0.5;
		state->acc[Y][n] = 0;
	}

	// gen case iterate
	double *current_acc[2];
	for (step = 0 ; step < step_max ; step++) {

		// update position
		position_iterate(state, pars);

		if (state->pos[2][2] != state->pos[2][2]) {
			cout << "position\n";
			cout << state->vel[2][2] << endl;
			cout << state->acc[2][2] << endl;

			exit(EXIT_FAILURE);
		}

		// // update accel field
		*current_acc = *(state->acc);
		// compute_accel(state, pars);

		// if (state->acc[2][2] != state->acc[2][2]) {
		// 	cout << "accel\n";
		// 	cout << state->pos[2][2] << endl;
		// 	cout << state->vel[2][2] << endl;

		// 	exit(EXIT_FAILURE);
		// }

		// update velocities
		velocity_iterate(state, current_acc, pars);

		if (state->vel[2][2] != state->vel[2][2]) {
			cout << "velocity\n";
			cout << state->pos[2][2] << endl;
			cout << state->acc[2][2] << endl;

			exit(EXIT_FAILURE);
		}

		// scaling (implement later)

		// calculate MSD and PCF

		// write to file for vdm
		if (step % 3 == 0) {
			for (int n = 0 ; n < pars.N ; n++) {
				movie << " X " << state->pos[X][n] << ' ' << state->pos[Y][n] << " 0" << endl;
			}
		}
	}

	return 0;
}
