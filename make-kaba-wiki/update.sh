KABA=kaba

if [ -n "$1" ]
then
	KABA="$1"
	echo "using kaba: $KABA"
fi

rm -rf *.txt
$KABA make-kaba-wiki.kaba
python upload.py
rm -rf *.txt
