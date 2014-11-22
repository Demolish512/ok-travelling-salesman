// BranchAndBound.h : Algorytm stosujacy prosta zasade branch and bound.
//
// Poddrzewa rozwiazania ktore sa gorsze od aktualnie najlepszego rozwiazania
// sa pomijane.

#pragma once
#include "algorithms.h"

class BranchAndBoundAlgorithm {
private:
	static void BnB(int c[], int c_i, int c_v, int last_used, bool not_used[], int bs[], int * bs_v, AdjacencyMatrix * g) {
		// BOUND
		if ( c_v >= *bs_v ) {
			not_used[last_used] = true;
			return;
		}
		if ( c_i == g->get_size() ) {
			if ( c_v + g->get_weight(last_used, 0) < *bs_v ) {
				*bs_v = c_v + g->get_weight(last_used, 0);
				for (int i = 0; i < g->get_size(); i++)
					bs[i] = c[i];
			}
			return;
		}
		// BRANCH
		for (int i = 0; i < g->get_size(); i++)
			if (not_used[i]) {
				not_used[i] = false;
				c[c_i] = i;
				BnB(c, c_i + 1, c_v + g->get_weight(last_used, i), i, not_used, bs, bs_v, g);
				not_used[i] = true;
			}
		return;
	}
public:
	static Output* perform_calculations(AdjacencyMatrix graph) {
		// gorna granica
		int bs_v = INT_MAX;
		// tablice: robocza i z najlepszym rozwiazaniem
		int * c = new int[graph.get_size()];
		int * bs = new int[graph.get_size()];
		// tablica uzytych wierzcholkow
		bool * not_used = new bool[graph.get_size()];
		for (int i = 1; i < graph.get_size(); i++)
			not_used[i] = true;
		// pierwszy wierzcholek -0
		not_used[0] = false;
		c[0] = 0;
		BnB(c, 1, 0, 0, not_used, bs, &bs_v, &graph);
		// wyjscie
		Output* output = new Output( graph.get_size() );
		for (int i = 0; i < graph.get_size(); i++)
			output->push_cycle(bs[i]);
		output->set_value(bs_v);

		delete [] c;
		delete [] bs;
		delete [] not_used;
		return output;
	}
};
