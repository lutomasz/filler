#!/bin/bash

vm=./tools/filler_vm
my_player=./filler.lupozzi
# my_player=tools/players/./sofchami.filler
window_height=250
nb_match=5

all_players="
tools/players/sofchami.filler
"
# tools/players/carli.filler
# tools/players/abarriel.filler
# tools/players/abanlin.filler
# tools/players/grati.filler
# tools/players/hcao.filler
# tools/players/superjeannot.filler
# tools/players/ntoniolo.filler
# tools/players/carodrig.filler
# tools/players/champely.filler
# tools/players/nboulif.filler
# tools/players/qhonore.filler
# tools/players/lcharvol.filler
# tools/players/hvromman.filler
# tools/players/rpousseu_last.filler

all_maps="
tools/maps/map00
tools/maps/map01
tools/maps/map02
"
#tools/maps/map03

run_games() {
	let index=0
	for player in $all_players; do
		for map in  $all_maps; do
			for ((i=1;i<=nb_match;i++)); do
				$vm -f ./$map -p1 ./$my_player -p2 ./$player | python3 visu/filler_visu.py $window_height $index  &
				let index++
			done
			for ((i=1;i<=nb_match;i++)); do
				$vm -f ./$map -p1 ./$player -p2 ./$my_player | python3 visu/filler_visu.py $window_height $index &
				let index++
			done
		done
	done
	read -p "Press enter to quit all"
	pkill -f filler
}

run_games
