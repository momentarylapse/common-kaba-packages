KABA=kaba
BASE_DIR="/home/michi/.kaba/make-kaba-wiki" # ...

if [ -n "$1" ]
then
	KABA="$1"
	echo "using kaba: $KABA"
fi

# clean-up if needed
rm -rf $BASE_DIR/current


# make current version
if $KABA make-kaba-wiki
then
	python3 upload.py

	# save version
	rm -rf $BASE_DIR/previous
	mv $BASE_DIR/current $BASE_DIR/previous
else
	rm -rf $BASE_DIR/current
fi
