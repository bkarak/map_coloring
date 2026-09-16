#!/bin/sh
#
# Run the supplied graphs through both searches and compare with the recorded
# output under tests/expected/.
#
# Those files were produced by the 2002 sources as they were submitted, before
# the 2026 pass that cleared the compiler warnings, so this is what shows that
# pass changed nothing. Keep it that way: if a change here is meant to alter the
# output, say so in the commit rather than quietly refreshing the files.
#
# map.109 is deliberately not covered. The first stage is 2^n and there is no
# n=109 answer to wait for.
#
#   ./tests/run.sh [path-to-binary]

set -u

BIN=${1:-./mapColoring}
DIR=$(dirname "$0")
ROOT=$DIR/..
EXPECTED=$DIR/expected

if [ ! -x "$BIN" ]; then
	echo "no binary at $BIN — run make first" >&2
	exit 2
fi

pass=0
fail=0

check() {
	name=$1
	expected=$EXPECTED/$2
	shift 2
	if "$BIN" "$@" 2>&1 | diff -u "$expected" - > /tmp/mapcolor-test.$$ 2>&1; then
		echo "ok   $name"
		pass=$((pass + 1))
	else
		echo "FAIL $name"
		sed 's/^/     /' /tmp/mapcolor-test.$$
		fail=$((fail + 1))
	fi
	rm -f /tmp/mapcolor-test.$$
}

for n in 5 7 12; do
	check "map.$n, greedy" "map.$n.greedy.txt" "$ROOT/maps/map.$n"
	check "map.$n, exhaustive" "map.$n.best.txt" "$ROOT/maps/map.$n" -best
done

check "no arguments prints the help" "help.txt"

exit_status() {
	name=$1
	want=$2
	file=$3
	"$BIN" "$file" > /dev/null 2>&1
	got=$?
	if [ "$got" -eq "$want" ]; then
		echo "ok   $name"
		pass=$((pass + 1))
	else
		echo "FAIL $name (exit $got, wanted $want)"
		fail=$((fail + 1))
	fi
}

# A missing data file is reported and exits 255; anything else means the error
# path has been broken.
exit_status "missing file exits 255" 255 "$ROOT/maps/does-not-exist"

# A file whose first line is not a vertex count is rejected. Before parse_file
# checked what fscanf returned, number_of_nodes was left uninitialised here and
# the program went into a 2^garbage enumeration that never came back.
exit_status "malformed header exits 255" 255 "$DIR/malformed.map"

echo
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
