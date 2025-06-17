for X in *
do
	if [ ! -f $X/install.sh ]
	then
		continue
	fi

	echo $X
	cd $X
	bash install.sh
	cd ..
done

