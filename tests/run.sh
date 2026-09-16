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

# A missing data file is reported and exits 255; anything else means the error
# path has been broken.
"$BIN" "$ROOT/maps/does-not-exist" > /dev/null 2>&1
status=$?
if [ "$status" -eq 255 ]; then
	echo "ok   missing file exits 255"
	pass=$((pass + 1))
else
	echo "FAIL missing file exits 255 (got $status)"
	fail=$((fail + 1))
fi

echo
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
