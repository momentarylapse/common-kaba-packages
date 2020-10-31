for X in bindiff circuit cli huibui k2k kabama lib sisyphos shadercomp tools xmake
do
	echo $X
	cd $X
	bash install.sh
	cd ..
done

