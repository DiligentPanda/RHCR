#pragma once
#include "BasicGraph.h"


class SimpleGrid :
	public BasicGraph
{
public:
	// vector<int> endpoints;
	// vector<int> agent_home_locations;

    vector<int> starts;
    vector<int> tasks;
    vector<int> empty_locations;

    bool load_map(string fname);
    bool load_starts(string fname);
    bool load_tasks(string fname);
    void preprocessing(bool consider_rotation); // compute heuristics
private:
    bool load_weighted_map(string fname);
    bool load_unweighted_map(string fname);
};
