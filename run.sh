#!/bin/bash
set -ex

./compile.sh

MAP="data/paper_exp_v3/small/sortation_small.map"
STARTS="data/paper_exp_v3/agents/sortation_small_uniform/sortation_small_uniform_0_600.agents"
TASKS="data/paper_exp_v3/tasks/sortation_small_uniform/sortation_small_uniform_0.tasks"
N_AGENTS=600
STEPS=500
OUTPUT_FD="exps/instance_0"
CUTOFF_TIME=10

./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
