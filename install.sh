BASE=/usr/local/share/kaba
if [ ! -d $BASE/lib ]
then
	mkdir $BASE/lib
fi
cp *.kaba $BASE/lib/
