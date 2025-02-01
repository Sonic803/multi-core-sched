#!/bin/bash

# Directory containing the simulation results
RESULTS_DIR=$1
# assert it ends with results
if [[ ! $RESULTS_DIR =~ results$ ]]; then
	echo "The directory name must end with 'results'"
	exit 1
fi

NUM_RUNS=864

rm -rf "${RESULTS_DIR}"
mkdir -p "${RESULTS_DIR}"
cd "${RESULTS_DIR}"

seq $NUM_RUNS | parallel -j8 ../run -u Cmdenv -c tredPlot -r '{}' --cpu-time-limit=30s

opp_scavetool x "tredPlot"* -o "3d_new.json"

# rm -f *.json
# rm -f *.vci

# extract_one() {
# 	base_name=$1
# 	output_name=$(echo "$1" | cut -d'-' -f2)
	
# 	# Run opp_scavetool on the file
# 	# if [ ! -f "${output_name}.json" ]; then
# 	opp_scavetool x "${base_name}"* -o "${output_name}.json"
# 	# fi
# }

# export -f extract_one

# base_names=$(ls | cut -d'#' -f1 | uniq)
# echo "$base_names" | parallel -j16 extract_one '{}'
