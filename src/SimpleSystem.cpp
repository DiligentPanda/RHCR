#include "SimpleSystem.h"
#include "WHCAStar.h"
#include "ECBS.h"
#include "LRAStar.h"
#include "PBS.h"

SimpleSystem::SimpleSystem(const SimpleGrid& G, MAPFSolver& solver): BasicSystem(G, solver), G(G) {}


SimpleSystem::~SimpleSystem()
{
}

void SimpleSystem::initialize()
{
	initialize_solvers();

	starts.resize(num_of_drives);
	goal_locations.resize(num_of_drives);
	paths.resize(num_of_drives);
	finished_tasks.resize(num_of_drives);
	bool succ = load_records(); // continue simulating from the records
	if (!succ)
	{
		timestep = 0;
		succ = load_locations();
		if (!succ)
		{
			cout << "Randomly generating initial locations" << endl;
			initialize_start_locations();
			initialize_goal_locations();
		}
	}
}

void SimpleSystem::initialize_start_locations()
{
	// Choose random start locations
	// Any non-obstacle locations can be start locations
	// Start locations should be unique
	for (int k = 0; k < num_of_drives; k++)
	{
		int orientation = -1;
		if (consider_rotation)
		{
			orientation = rand() % 4;
		}
		starts[k] = State(G.starts[k], 0, orientation);
		paths[k].emplace_back(starts[k]);
		finished_tasks[k].emplace_back(G.starts[k], 0);
	}
}


void SimpleSystem::initialize_goal_locations()
{
	if (hold_endpoints || useDummyPaths)
		return;
	// Choose random goal locations
	// Goal locations are not necessarily unique
	task_counter.resize(num_of_drives);
	for (int k = 0; k < num_of_drives; k++)
	{
		// int goal = G.endpoints[rand() % (int)G.endpoints.size()];
		// goal_locations[k].emplace_back(goal, 0);
		int i = task_counter[k] * num_of_drives + k;
		// std::cout << i <<","<< G.tasks.size() <<","<<G.starts.size()<< std::endl;

		int loc = G.tasks[i% G.tasks.size()];
		goal_locations[k].emplace_back(loc, 0);
		task_counter[k]++;

	}
}



void SimpleSystem::update_goal_locations()
{
    if (!LRA_called)
        new_agents.clear();
	// if (hold_endpoints)
	// {
	// 	unordered_map<int, int> held_locations; // <location, agent id>
	// 	for (int k = 0; k < num_of_drives; k++)
	// 	{
	// 		int curr = paths[k][timestep].location; // current location
	// 		if (goal_locations[k].empty())
	// 		{
	// 			int next = G.endpoints[rand() % (int)G.endpoints.size()];
	// 			while (next == curr || held_endpoints.find(next) != held_endpoints.end())
	// 			{
	// 				next = G.endpoints[rand() % (int)G.endpoints.size()];
	// 			}
	// 			goal_locations[k].emplace_back(next, 0);
	// 			held_endpoints.insert(next);
	// 		}
	// 		if (paths[k].back().location == goal_locations[k].back().first &&  // agent already has paths to its goal location
	// 			paths[k].back().timestep >= goal_locations[k].back().second) // after its release time
	// 		{
	// 			int agent = k;
	// 			int loc = goal_locations[k].back().first;
	// 			auto it = held_locations.find(loc);
	// 			while (it != held_locations.end()) // its start location has been held by another agent
	// 			{
	// 				int removed_agent = it->second;
	// 				if (goal_locations[removed_agent].back().first != loc)
	// 					cout << "BUG" << endl;
	// 				new_agents.remove(removed_agent); // another agent cannot move to its new goal location
	// 				cout << "Agent " << removed_agent << " has to wait for agent " << agent << " because of location " << loc << endl;
	// 				held_locations[loc] = agent; // this agent has to keep holding this location
	// 				agent = removed_agent;
	// 				loc = paths[agent][timestep].location; // another agent's start location
	// 				it = held_locations.find(loc);
	// 			}
	// 			held_locations[loc] = agent;
	// 		}
	// 		else // agent does not have paths to its goal location yet
	// 		{
	// 			if (held_locations.find(goal_locations[k].back().first) == held_locations.end()) // if the goal location has not been held by other agents
	// 			{
	// 				held_locations[goal_locations[k].back().first] = k; // hold this goal location
	// 				new_agents.emplace_back(k); // replan paths for this agent later
	// 				continue;
	// 			}
	// 			// the goal location has already been held by other agents 
	// 			// so this agent has to keep holding its start location instead
	// 			int agent = k;
	// 			int loc = curr;
	// 			cout << "Agent " << agent << " has to wait for agent " << held_locations[goal_locations[k].back().first] << " because of location " <<
	// 				goal_locations[k].back().first << endl;
	// 			auto it = held_locations.find(loc);
	// 			while (it != held_locations.end()) // its start location has been held by another agent
	// 			{
	// 				int removed_agent = it->second;
	// 				if (goal_locations[removed_agent].back().first != loc)
	// 					cout << "BUG" << endl;
	// 				new_agents.remove(removed_agent); // another agent cannot move to its new goal location
	// 				cout << "Agent " << removed_agent << " has to wait for agent " << agent << " because of location " << loc << endl;
	// 				held_locations[loc] = agent; // this agent has to keep holding its start location
	// 				agent = removed_agent;
	// 				loc = paths[agent][timestep].location; // another agent's start location
	// 				it = held_locations.find(loc);
	// 			}
	// 			held_locations[loc] = agent;// this agent has to keep holding its start location
	// 		}
	// 	}
	// }
	// else

	if (hold_endpoints || useDummyPaths) {
		std::cout<<"hold_endpoints and useDummyPaths are not supported in SimpleSystem yet"<<std::endl;
		exit(-1);
	}

	{
		for (int k = 0; k < num_of_drives; k++)
		{
			int curr = paths[k][timestep].location; // current location
			// if (useDummyPaths)
			// {
			// 	if (goal_locations[k].empty())
			// 	{
			// 		goal_locations[k].emplace_back(G.agent_home_locations[k], 0);
			// 	}
			// 	if (goal_locations[k].size() == 1)
			// 	{
			// 		int next;
			// 		do {
			// 			next = G.endpoints[rand() % (int)G.endpoints.size()];
			// 		} while (next == curr);
			// 		goal_locations[k].emplace(goal_locations[k].begin(), next, 0);
			// 		new_agents.emplace_back(k);
			// 	}
			// }
			// else
			{
				pair<int, int> goal; // The last goal location
				if (goal_locations[k].empty())
				{
					goal = make_pair(curr, 0);
				}
				else
				{
					goal = goal_locations[k].back();
				}
				double min_timesteps = G.get_Manhattan_distance(goal.first, curr); // G.heuristics.at(goal)[curr];
				while (min_timesteps <= simulation_window)
					// The agent might finish its tasks during the next planning horizon
				{
					// // assign a new task
					// pair<int, int> next;
					// if (G.types[goal.first] == "Endpoint")
					// {
					// 	do
					// 	{
					// 		next = make_pair(G.endpoints[rand() % (int)G.endpoints.size()], 0);
					// 	} while (next == goal);
					// }
					// else
					// {
					// 	std::cout << "ERROR in update_goal_function()" << std::endl;
					// 	std::cout << "The fiducial type should not be " << G.types[curr] << std::endl;
					// 	exit(-1);
					// }
					// goal_locations[k].emplace_back(next);
					// min_timesteps += G.get_Manhattan_distance(next.first, goal.first); // G.heuristics.at(next)[goal];
					// goal = next;

					int i = task_counter[k] * num_of_drives + k;
					int loc = G.tasks[i% G.tasks.size()];
					goal_locations[k].emplace_back(loc, 0);
					task_counter[k]++;
					
					// goal_locations[k].emplace_back(next);
					min_timesteps += G.get_Manhattan_distance(loc, goal.first); // G.heuristics.at(next)[goal];
					goal = goal_locations[k].back();

				}
			}
		}
	}

}


void SimpleSystem::simulate(int simulation_time)
{
	auto start_clock = std::clock();

	std::cout << "*** Simulating " << seed << " ***" << std::endl;
	this->simulation_time = simulation_time;
	initialize();

	for (; timestep < simulation_time; timestep += simulation_window)
	{
		std::cout << "Timestep " << timestep << std::endl;

		update_start_locations();
		update_goal_locations();
		solve();

		// move drives
		auto new_finished_tasks = move();
		std::cout << new_finished_tasks.size() << " tasks has been finished" << std::endl;

		// update tasks
		for (auto task : new_finished_tasks)
		{
			int id, loc, t;
			std::tie(id, loc, t) = task;
			finished_tasks[id].emplace_back(loc, t);
			num_of_tasks++;
			if (hold_endpoints)
				held_endpoints.erase(loc);
		}

		// if (congested())
		// {
		// 	cout << "***** Too many traffic jams ***" << endl;
		// 	break;
		// }
	}

	update_start_locations();

	float runtime = (std::clock() - start_clock) * 1.0  / CLOCKS_PER_SEC;
	float mean_step_time = (float) runtime/simulation_time;
	float throughput = (float) num_of_tasks/simulation_time;

	std::cout<< "throughput: "<<throughput<<std::endl;
	std::cout << "mean step time: " << mean_step_time << " s" << std::endl;
	std::cout << std::endl << "Done!" << std::endl;

	save_results(throughput, mean_step_time);
}

void SimpleSystem::save_results(float throughput, float mean_step_time)
{
	if (screen)
		std::cout << "*** Saving " << seed << " ***" << std::endl;
    clock_t t = std::clock();
    std::ofstream output;

    // settings
    output.open(outfile+"/res.csv", std::ios::out);
	output<<seed<<","<<throughput<<","<<mean_step_time<<std::endl;
    output.close();
}