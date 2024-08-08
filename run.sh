#!/bin/bash
# set -ex

./compile.sh

# sortation
for idx in {0..7}
do
    echo run exp $idx
    MAP="data/paper_exp_v3/small/sortation_small.map"
    STARTS="data/paper_exp_v3/agents/sortation_small_uniform/sortation_small_uniform_${idx}_600.agents"
    TASKS="data/paper_exp_v3/tasks/sortation_small_uniform/sortation_small_uniform_${idx}.tasks"
    N_AGENTS=600
    STEPS=500
    OUTPUT_FD="exps/sortation_small/instance_${idx}"
    CUTOFF_TIME=10

    echo $STARTS
    echo $TASKS

    ./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
done

# warehouse
for idx in {0..7}
do
    echo run exp $idx
    MAP="data/paper_exp_v3/small/warehouse_small.map"
    STARTS="data/paper_exp_v3/agents/warehouse_small_uniform/warehouse_small_uniform_${idx}_600.agents"
    TASKS="data/paper_exp_v3/tasks/warehouse_small_uniform/warehouse_small_uniform_${idx}.tasks"
    N_AGENTS=600
    STEPS=500
    OUTPUT_FD="exps/warehouse_small/instance_${idx}"
    CUTOFF_TIME=10

    echo $STARTS
    echo $TASKS

    ./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
done

# paris
for idx in {0..7}
do
    echo run exp $idx
    MAP="data/paper_exp_v3/small/Paris_1_256_small.map"
    STARTS="data/paper_exp_v3/agents/Paris_1_256_small/Paris_1_256_small_${idx}_600.agents"
    TASKS="data/paper_exp_v3/tasks/Paris_1_256_small/Paris_1_256_small_${idx}.tasks"
    N_AGENTS=600
    STEPS=500
    OUTPUT_FD="exps/paris_small/instance_${idx}"
    CUTOFF_TIME=10

    echo $STARTS
    echo $TASKS

    ./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
done

# berlin
for idx in {0..7}
do
    echo run exp $idx
    MAP="data/paper_exp_v3/small/Berlin_1_256_small.map"
    STARTS="data/paper_exp_v3/agents/Berlin_1_256_small/Berlin_1_256_small_${idx}_600.agents"
    TASKS="data/paper_exp_v3/tasks/Berlin_1_256_small/Berlin_1_256_small_${idx}.tasks"
    N_AGENTS=600
    STEPS=500
    OUTPUT_FD="exps/berlin_small/instance_${idx}"
    CUTOFF_TIME=10

    echo $STARTS
    echo $TASKS

    ./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
done

# random01
for idx in {0..7}
do
    echo run exp $idx
    MAP="data/paper_exp_v3/small/random_256_10_small.map"
    STARTS="data/paper_exp_v3/agents/random_256_10_small/random_256_10_small_${idx}_600.agents"
    TASKS="data/paper_exp_v3/tasks/random_256_10_small/random_256_10_small_${idx}.tasks"
    N_AGENTS=600
    STEPS=500
    OUTPUT_FD="exps/random01_small/instance_${idx}"
    CUTOFF_TIME=10

    echo $STARTS
    echo $TASKS

    ./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
done

# random02
for idx in {0..7}
do
    echo run exp $idx
    MAP="data/paper_exp_v3/small/random_256_20_small.map"
    STARTS="data/paper_exp_v3/agents/random_256_20_small/random_256_20_small_${idx}_600.agents"
    TASKS="data/paper_exp_v3/tasks/random_256_20_small/random_256_20_small_${idx}.tasks"
    N_AGENTS=600
    STEPS=500
    OUTPUT_FD="exps/random02_small/instance_${idx}"
    CUTOFF_TIME=10

    echo $STARTS
    echo $TASKS

    ./build/lifelong -m $MAP --starts $STARTS --tasks $TASKS -k $N_AGENTS --scenario=SIMPLE --simulation_window=5 --planning_window=10 --solver=ECBS --suboptimal_bound=1.5 --seed=0  --simulation_time $STEPS -o $OUTPUT_FD --cutoffTime $CUTOFF_TIME
done