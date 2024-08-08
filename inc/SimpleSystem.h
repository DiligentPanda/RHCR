#pragma once
#include "BasicSystem.h"
#include "SimpleGraph.h"

class SimpleSystem :
	public BasicSystem
{
public:
	SimpleSystem(const SimpleGrid& G, MAPFSolver& solver);
	~SimpleSystem();

	void simulate(int simulation_time);

	std::vector<int> task_counter;

	void save_results(float throughput, float mean_step_time);

private:
	const SimpleGrid& G;
	unordered_set<int> held_endpoints;

	void initialize();
	void initialize_start_locations();
	void initialize_goal_locations();
	void update_goal_locations();
};

