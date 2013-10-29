// md.cpp, written by Sayre Christenson, 10 October 2013

#include"md.hpp"

int main(int argc, char *argv[])
{
	// help statement
	if (argc == 1) {
		cout << "usage: ./md 'N' 'exp of step_max'\n";
		return 0;
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

	ofstream magv;
	magv.open("magv.txt");

	// first iterate
	compute_accel(state, pars);

	// gen case iterate
	double *current_acc[2];
	double Kavg = 0;
	for (step = 0 ; step < step_max ; step++) {

		// update position
		position_iterate(state, pars);

		// update accel field
		cout << "hihi\n";
		array_copy(state->acc[X], current_acc[X], pars.N);
		array_copy(state->acc[Y], current_acc[Y], pars.N);
		cout << "hihi\n";

		double temp;
		for (int u = 0 ; u < pars.N ; u++) {
			temp = current_acc[X][u];
			temp = current_acc[Y][u];
			cout << "hihi " << u << endl;
		}

		compute_accel(state, pars);

		// update velocities
		Kavg = velocity_iterate(state->, current_acc, pars);

		// scaling (implement later)

		// calculate MSD and PCF

		// write to file for vdm
		if (step % 10 == 0) {
			for (int n = 0 ; n < pars.N ; n++) {
				movie << " X " << state->pos[X][n] << ' ' << state->pos[Y][n] << " 0" << endl;
			}

			magv << Kavg << endl;
		}
	}

	movie.close();
	magv.close();

	return 0;
}


void array_copy(double *state_acc, double *current_acc, int N)
{
	for (int u = 0 ; u < N ; u++) *current_acc[u] = state_acc[u];
}
