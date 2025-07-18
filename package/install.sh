BASE=~/.kaba
if [ ! -d $BASE/apps ]
then
	mkdir $BASE/apps
fi
if [ ! -d $BASE/apps/package ]
then
	mkdir $BASE/apps/package
fi
cp *.kaba $BASE/apps/package
