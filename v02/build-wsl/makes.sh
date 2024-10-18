clear

MAKE_CMD="$1"
MAKE_ARGS=""
shift

while test $# -gt 0
do
    MAKE_ARGS="$MAKE_ARGS $1"
    shift
done

make -f commands.mak $MAKE_CMD ARGS="$MAKE_ARGS"
