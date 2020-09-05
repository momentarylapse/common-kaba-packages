BASE=/usr/local/share/kaba
if [ ! -d $BASE/apps ]
then
	mkdir $BASE/apps
fi
if [ ! -d $BASE/apps/cli ]
then
	mkdir $BASE/apps/cli
fi
cp *.kaba $BASE/apps/cli
