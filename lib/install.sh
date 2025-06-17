BASE=~/.kaba
DEST=$BASE/modules

if [ ! -d "$DEST" ]
then
	mkdir "$DEST"
fi
cp *.kaba "$DEST/"
