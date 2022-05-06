/*
 * Generate random undirected weighted graphs
 * that contain at least one negative cycle
 */

#include <random>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define DEBUG false
#define DBG(x) if (DEBUG) cout << #x << ": " << x << endl;
#define DBG1D(x) \
	if (DEBUG) { \
		cout << #x << ":" << endl; \
		for (int i = 0; i < x.size(); ++i) { \
			cout << "  " << "[" << i << "]: " \
				 << x[i] << endl; \
		} \
	}

int main(int argc, char** argv) {

	// Check if we have 2 input arguments
	if (argc != 3) {
		cout <<
			"Usage:\n\t" <<
			"./program n [#vertices] m [#edges]" << endl;
		return 0;
	}

	int n, m;
	n = atoi(argv[1]);
	m = atoi(argv[2]);

	if (n < 4) {
		cout << "Please input at least n>=6 for #vertices" << endl;
		return 0;
	}

	if (m < 2*n || m > n*(n-1)) {
		cout << "Please choose #edges m:" << endl <<
				"2*n <= m <= n*(n-1)" << endl;
		return 0;
	}

	vector < vector <bool> > adjMatrix(n);
	vector <vector <int> > weightMatrix(n);

	for (int i = 0; i < n; ++i) {
		adjMatrix[i] = vector <bool> (n, false);
		 // mark self loops as already added edges
		adjMatrix[i][i] = true;
		weightMatrix[i] = vector <int> (n, 0);
	}

	// set up random number generator
	random_device rd;
	mt19937 mt(rd());
	mt.seed(8); // static seed for reproducibility
	uniform_int_distribution<int> randInt(0.3*n, 0.66*n+0.5);
	uniform_int_distribution<int> randWeight(-50, 99);

	// prepare vertex ids
	vector<int> vertexIds(n);
	for (int i = 0; i < n; ++i) {
		vertexIds[i] = i;
	}
	// randomly shuffle the vertex ids
	shuffle(vertexIds.begin(), vertexIds.end(), mt);
	DBG1D(vertexIds);

	// choose negative cycle length
	int k = randInt(mt);
	// make sure the cycle has length >= 3
	k = (k >= 2)? k:2;
	if (k == n-1) --k;
	DBG(k);

	// add weights for the cycle
	int added_edges = 0;
	int totalWeight = 0;
	for (int i = 0; i < k; ++i) {
		int u = vertexIds[i];
		int v = vertexIds[i+1];
		int weight = randWeight(mt);
		totalWeight += weight;
		adjMatrix[u][v] = adjMatrix[v][u] = true;
		weightMatrix[u][v] = weight;
		weightMatrix[v][u] = -weight;
		added_edges += 2;
	}
	int uu, vv;
	uu = vertexIds[k];
	vv = vertexIds[0];
	adjMatrix[uu][vv] = adjMatrix[vv][uu] = true;
	weightMatrix[uu][vv] = -totalWeight - 1;
	weightMatrix[vv][uu] = totalWeight - 1;
	// finished constructing a negative weight cycle
	added_edges += 2;
	DBG(added_edges);

	// add edges between vertices in and out of the cycle
	int indCycle = 0;
	for (int indOut = k+1; indOut < n; ++indOut) {
		int u = vertexIds[indCycle];
		int v = vertexIds[indOut];
		adjMatrix[u][v] = adjMatrix[v][u] = true;
		int weight = randWeight(mt);
		weightMatrix[u][v] = weight;
		weightMatrix[v][u] = -weight;
		added_edges += 2;
		++indCycle;
		if (indCycle > k) indCycle = 0;
	}
	DBG(added_edges);

	// so far we should have added 2*n
	// edges and made the graph strongly connected

	// next, we will add edges randomly
	// to avoid unnecessary looping for dense graphs,
	// first we initialize a random matrix
	vector < vector <int> > randNeighbors(n);
	for (auto &row : randNeighbors) {
		shuffle(vertexIds.begin(), vertexIds.end(), mt);
		row = vector<int>(vertexIds);
		DBG1D(row);
	}

	int u = k + 1; // id of vertex to start adding edges
	int edgesToAdd = m - 2*n;
	while (edgesToAdd > 0) {
		// loop over remaining number of edges to be added
		if (! randNeighbors[u].empty()) {
			int v = randNeighbors[u].back();
			randNeighbors[u].pop_back();
			if (! adjMatrix[u][v]) {
				// adding one edge
				adjMatrix[u][v] = true;
				int weight = randWeight(mt);
				weightMatrix[u][v] = weight;
				--edgesToAdd;
				added_edges += 1;
			}
		}
		++u;
		if (u >= n) u = 0;
	}
	DBG(added_edges);

	int tot = 0;
	cout << n << " " << m << endl;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i != j && adjMatrix[i][j]) {
				cout << i << " " << j << " " <<
					weightMatrix[i][j] << endl;
				++tot;
			}
	DBG(tot);
	return 0;
}
