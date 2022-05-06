//数理工学実験テーマ7 //課題1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <tuple>
#include <climits>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>

using namespace std;

using AdjList = vector<vector<size_t>>;
using WeightMatrix = vector<vector<int>>;
#define N 128

// Chrono based time measurement
class Timer
{
public:
	Timer()
	{
		reset();
	}
	void reset()
	{
		m_timestamp = std::chrono::high_resolution_clock::now();
	}
	double diff()
	{
		std::chrono::duration<double> fs = std::chrono::high_resolution_clock::now() - m_timestamp;
		return fs.count();
	}

private:
	std::chrono::high_resolution_clock::time_point m_timestamp;
};

/**
 * Read a graph from a file
 * @param filename
 */
tuple<
	AdjList,
	WeightMatrix,
	size_t, size_t>
read_graph(const string &filename)
{

	ifstream instance_infile;

	try
	{
		instance_infile.open(filename);
		// pReadBuf = &instance_infile;
	}
	catch (const exception &e)
	{
		cout << "ERROR: could not open file '" << filename
			 << "' for reading" << endl;
		cout << "Using stdin..." << endl;
		// pReadBuf = &cin;
		// throw(e);
	} // file for reading the instance should be open now

	if (instance_infile.is_open())
	{
		size_t n, m;
		string st;

		instance_infile >> n >> m;

		AdjList adj_list(n, vector<size_t>());
		WeightMatrix weight(n, vector<int>(n, 0));

		for (size_t i = 0; i < m; ++i)
		{
			size_t u, v;
			int w;

			instance_infile >> u >> v >> w;

			adj_list[u].push_back(v);
			weight[u][v] = w;
		}
		instance_infile.close();

		return make_tuple(adj_list, weight, n, m);
	}
	else
	{
		cout << "Could not open file " << filename
			 << " for reading." << endl;
		return make_tuple(AdjList(), WeightMatrix(), 0, 0);
	}
}

int path_recurse(
	const AdjList &adj_list,
	const WeightMatrix &weight,
	bitset<N> &F,
	int running_sol,
	size_t s,
	size_t t,
	int &incumbent,
	int &nodecount)
{
	nodecount++;
	if (s == t)
	{
		if (running_sol < incumbent)
		{
			incumbent = running_sol;
		}
		return incumbent;
	}
	else
	{
		for (const auto &u : adj_list[s])
			if (not F[u])
			{
				F[u] = true;
				int w = weight[s][u];
				running_sol += w;
				path_recurse(
					adj_list,
					weight,
					F, running_sol,
					u, t, incumbent, nodecount);
				F[u] = false;
				running_sol -= w;
			}
		return incumbent;
	}
}

int main(int argc, char **argv)
{

	if (argc < 3)
	{
		cout << "At least supply instance filename..." << endl;
		return -1;
	}

	// Preps
	bitset<128> F;
	AdjList adj_list;
	WeightMatrix weight;
	int incumbent = INT_MAX;
	size_t s, t, n, m;
	bool sd(false), td(false);
	string inFileName;
	int nodecount = 0;

	// Parse input
	for (size_t i(0); i < argc; ++i)
	{
		if (argv[i][0] != '-')
			continue;
		string ff(argv[i]);
		if (ff == "-f")
			inFileName = string(argv[++i]);
		if (ff == "-s")
		{
			s = atoi(argv[++i]);
			sd = true;
		}
		if (ff == "-t")
		{
			t = atoi(argv[++i]);
			td = true;
		}
	}

	tie(adj_list, weight, n, m) = read_graph(inFileName);
	if (!sd)
		s = 0;
	if (!td)
		t = n - 1;

	Timer tt;
	F[s] = true;
	path_recurse(adj_list, weight, F, 0, s, t, incumbent, nodecount);
	double time = tt.diff();

	cout << n << ", "
		 << m << ", "
		 << incumbent << ", " //長さ
		 << nodecount << ", " //ノード数
		 << time << endl;	  //実行時間

	return 0;
}
