BASE=/usr/share/kaba
if [ ! -d $BASE/apps ]
then
	mkdir $BASE/apps
fi
if [ ! -d $BASE/apps/sisyphos ]
then
	mkdir $BASE/apps/sisyphos
fi
cp *.kaba $BASE/apps/sisyphos
