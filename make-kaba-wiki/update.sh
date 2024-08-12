KABA=kaba

if [ -n "$1" ]
then
	KABA="$1"
	echo "using kaba: $KABA"
fi

# clean-up if needed
rm -f *.txt
rm -rf current


# make current version
if $KABA make-kaba-wiki.kaba
then
	mkdir current
	mv *.txt current

	python3 upload.py

	# save version
	rm -rf previous
	mv current previous
else
	rm -f *.txt
fi
