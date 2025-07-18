BASE=~/.kaba
if [ ! -d $BASE/packages ]
then
	mkdir $BASE/packages
fi
if [ ! -d $BASE/packages/package ]
then
	mkdir $BASE/packages/package
fi
cp *.kaba $BASE/packages/package
