#!/bin/sh

if [ $# -ne 2 ]; then
    echo "./diff_flame.sh a.folded b.folded"
    exit 0
fi

aname=`basename "$1" .folded`
bname=`basename "$2" .folded`

tooldir=tool

newname="$aname-$bname-diff.svg"
perl $tooldir/difffolded.pl -n "$1" "$2" | perl $tooldir/flamegraph.pl > "$newname"
echo "$newname generated"

