#!/bin/bash

# Directory containing the simulation results
RESULTS_DIR="simulations/results"
cd "${RESULTS_DIR}"

rm -f *.json
rm -f *.vci

extract_one() {
	# Extract the base name up to the '#' character
	base_name=$(basename "$1" | cut -d'#' -f1)
	output_name=$(basename "$1" | cut -d'-' -f2)
	
	# Run opp_scavetool on the file
	if [ ! -f "${output_name}.json" ]; then
		opp_scavetool x "${base_name}"* -o "${output_name}.json"
	fi
}


export -f extract_one

files=$(ls)
echo $files | parallel -j16 extract_one '{}'
