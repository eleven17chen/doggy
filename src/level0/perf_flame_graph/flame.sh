#!/bin/sh

user=`whoami`

dt=`date "+%Y%m%d_%H%M%S"`
dir_name="p$dt"
mkdir -p $dir_name
fname="$dir_name/perf_$dt"

tooldir=tool

draw_flame()
{
    echo "Drawing ..."
    perf script -i "$fname".data | perl $tooldir/stackcollapse-perf.pl > "$fname".folded
    perl $tooldir/flamegraph.pl "$fname".folded > "$fname".svg
    echo ""
    echo "$fname.svg generated"
}

# signal for SIGINT(ctrl + c) and SIGTERM(kill)
trap draw_flame 2 15

echo "current user: $user"
if [ "$user"x = 'root'x ]; then	    
    perf record -F 99 -a -g -o "$fname".data -- sleep 10000
else
    echo "You must be root"
fi

