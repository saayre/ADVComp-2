// test.cpp, written by Sayre Christenson, 2013-10-17

#include"md.hpp"

int main(int argc, char *argv[])
{
	struct params pars = set_pars(pow(10, atoi(argv[1])));
	
	int max_step = pow(10, atoi(argv[2]));
	struct sys_state *state = initialize(pars);

	// // histogram

	// ofstream movie;
	// movie.open("vdist.txt");
	
	// double v;
	// int array[20] = {0};
	// for (int n = 0 ; n < pars.N ; n++) {

	// 	v = sqrt(state->vel[X][n]*state->vel[X][n] + state->vel[Y][n]*state->vel[Y][n]);
	// 	array[(int) floor(10*v)]++;
	// }

	// for (int i = 0 ; i < 20 ; i++) {

	// 	movie << i+1 << ' ' << array[i] << endl;
	// }

	// movie.close();

	ofstream movie;
	movie.open("test.xyz");

	movie << pars.N << endl << endl;
	
	for (int step = 0 ; step < max_step ; step++) {
		position_iterate(state, pars);

		if (step % 100 == 0) {
			for (int n = 0 ; n < pars.N ; n++) {
				movie << " X " << state->pos[X][n] << ' ' << state->pos[Y][n] << " 0" << endl;

				cout << state->vel[X][n] << ' ' << state->vel[Y][n] << endl;
			}
		}
	}

	movie.close();

	return 0;
}
