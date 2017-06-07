#!/bin/bash

if [ "$2" == "" ]
then


######Part 1
if [ "$1" == "-er1" ]
then
	gcc -O0 phods1.c -o phods1
	./phods1
	rm ./phods1

######Part 2
elif [ "$1" == "-er2" ]
then
	gcc -O0 phods2.c -o phods2
	./phods2
	rm ./phods2 

############Part 3

elif [ "$1" == "-er3" ]
then


	N=144
	M=176

	while [ "$M" -ne 0 ]; do
  	remainder=$(( $N % $M ))	#euclid algorithm for gcd
  	N=$M
  	M=$remainder
	done

	GCD=$N

	modulo=0
	divisor=1
	let Nend=GCD+1

	while [  "$divisor" -lt $Nend ]; do
		let modulo=GCD%divisor
		if [ "$modulo" -eq 0 ]
		then echo "Block size $divisor:"
       	     	sed -i "/#define B/c\#define B $divisor" ./phods3.c 	 #!!erotima 3
	     	gcc -O0 phods3.c -o phods3B
		./phods3B
	        rm ./phods3B
		echo ""
		fi
		let divisor=divisor+1
	done

###########Part 4

elif [ "$1" == "-er4" ]
then

	BX=144		
	BY=176

	moduloy=0
	modulox=0
	divisorx=1

	let xend=BX+1
	let yend=BY+1
	while [ "$divisorx" -lt $xend ]; do
		divisory=1
		let modulox=BX%divisorx
		if [ "$modulox" -eq 0 ]	
		then	while [ "$divisory" -lt $yend ] ; do			
				let moduloy=BY%divisory
				if [ "$moduloy" -eq 0 ] 
				then	echo "Bx=$divisorx and By=$divisory"
					sed -i "/#define Bx/c\#define Bx $divisorx" ./phods4.c
					sed -i "/#define By/c\#define By $divisory" ./phods4.c 
					gcc -O0 phods4.c -o phods4
					./phods4
					rm ./phods4
					echo ""	
				fi
				let divisory=divisory+1
			done
		fi
		let divisorx=divisorx+1
	done

#########extra Part: 4b. Implementation of an heuristic method, finding the best Bx,By combination

elif [ "$1" == "-er4b" ]
	then

	BX=144	
	BY=176

	moduloy=0
	modulox=0
	divisorx=1
	divisory=1
	bestx=0
	let xend=BX+1
	let yend=BY+1
	
	sed -i "/#define Bx/c\#define Bx $divisorx" ./phods4b.c
	sed -i "/#define By/c\#define By $divisory" ./phods4b.c 
	gcc -O0 phods4b.c -o phods4b
	best=$(./phods4b)
	let rbest=2*best

	while [ "$divisorx" -lt $xend ] ; do			
		let modulox=BX%divisorx
		if [ "$modulox" -eq 0 ] 
		then	sed -i "/#define Bx/c\#define Bx $divisorx" ./phods4b.c
			sed -i "/#define By/c\#define By $BY" ./phods4b.c 
			gcc -O0 phods4b.c -o phods4b
			value=$(./phods4b)
			echo "Bx is:" $divisorx "By is:" $BY "time :" $value "usec"
			if [ "$value" -lt "$best" ]
			then let best=value
			     let bestx=divisorx
			fi 
			rm ./phods4b	
		fi
		let divisorx=divisorx+1
	done
	let best=rbest
	echo ""	
	echo "Best Bx is :$bestx"
	echo ""
	besty=176	
	while [ "$divisory" -lt $yend ] ; do			
			let moduloy=BY%divisory
			if [ "$moduloy" -eq 0 ] 
			then	sed -i "/#define Bx/c\#define Bx $bestx" ./phods4b.c
				sed -i "/#define By/c\#define By $divisory" ./phods4b.c 
				gcc -O0 phods4b.c -o phods4b
				value=$(./phods4b)
				echo "Bx is:" $bestx "By is:" $divisory "time :" $value "usec"

				if [ "$value" -lt "$best" ]
				then let best=value
				     let besty=divisory
				fi
 				rm ./phods4b	
			fi
			let divisory=divisory+1
	done
	
	echo ""
	echo "Best By is:$besty"
	echo "Best Bx-By is: $bestx" " $besty"

#########help menu

elif [ "$1" == "-h" ]
then
	echo "****************************************************************************"
	echo "              First exercise in Embedded Systems Design!                    "
	echo ""
	echo ""
	echo "This script runs four tests with different configurations in phods algorithm"
	echo "                     Warning!Run with bash instead of sh!"				  	
	echo ""
	echo "****************************************************************************"
	echo "The following files need to be in the same directory with the script to function"
	echo "'akiyo0.y' 'akiyo1.y' 'phods1.c' 'phods2.c' 'phods3.c' 'phods4.c'"
	echo ""
	echo "****************************************************************************"
	echo ""
	echo "To run one of the four tests you need to pass it through the first argument!"
	echo "Available arguments: -er1 -er2 -er3 -er4 -er4b"
	echo "****************************************************************************"

########error menu
else echo "Wrong Argument:Type -h for help"

fi
else echo "Too many arguments!"
fi
