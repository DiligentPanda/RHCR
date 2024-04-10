#!/bin/bash
set -ex

./compile.sh

./build/lifelong -m maps/sorting_map.grid -k 800 --scenario=SORTING --simulation_window=5 --planning_window=10 --solver=PBS --seed=0
