#!/bin/bash

iteration=0;
while [ 1 ]
	do
		echo "Waiting for result iteration No. ${iteration} proccess pid-> $1"
		./client $1 $2
		echo "Done\n"
		let "iteration++"
	done;
