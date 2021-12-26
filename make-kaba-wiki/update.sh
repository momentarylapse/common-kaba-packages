KABA=kaba

if [ -n "$1" ]
then
	KABA="$1"
	echo "using kaba: $KABA"
fi

# clean-up if needed
rm -rf *.txt
rm -rf current


# make current version
$KABA make-kaba-wiki.kaba
mkdir current
mv *.txt current

python upload.py

# save version
rm -rf previous
mv current previous
