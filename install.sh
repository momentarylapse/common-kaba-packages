for X in bindiff circuit cli huibui k2k kabama lib sisyphos shadercomp xmake
do
	echo $X
	cd $X
	bash install.sh
	cd ..
done

