#!/bin/bash

cat output.txt \
    | sed '0,/^----/d' | sed '0,/^----/d' \
	| sed 's/   */;/g' | sed 's/ ns;/;/g' \
	| sed 's/FuzzyChainFixture./;/' \
	| sed 's/;.*>./;/' \
	| sed 's/Goedel/&;/' | sed 's/Goguen/&;/' | sed 's/Lukasiewicz/&;/' \
	| awk -F';' '{printf "%s;%s;%s;%s\n", $3, $1, $2, $5}' \
	| sed -E 's/([0-9]+);Bitwise/;Bitwise-\1/' > output.csv

