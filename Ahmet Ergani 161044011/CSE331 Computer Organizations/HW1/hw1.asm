.data
filename: .asciiz "input_hw1.txt"	#filename
zero: .asciiz "0"
one: .asciiz "1"
two: .asciiz "2"
three: .asciiz "3"
four: .asciiz "4"
five: .asciiz "5"
six: .asciiz "6"
seven: .asciiz "7"
eight: .asciiz "8"
nine: .asciiz "9"

dot: .asciiz "."
space: .asciiz " "

wordZero: .asciiz "zero"
wordOne: .asciiz "one"
wordTwo: .asciiz "two"
wordThree: .asciiz "three"
wordFour: .asciiz "four"
wordFive: .asciiz "five"
wordSix: .asciiz "six"
wordSeven: .asciiz "seven"
wordEight: .asciiz "eight"
wordNine: .asciiz "nine"

wordZeroBig: .asciiz "Zero"
wordOneBig: .asciiz "One"
wordTwoBig: .asciiz "Two"
wordThreeBig: .asciiz "Three"
wordFourBig: .asciiz "Four"
wordFiveBig: .asciiz "Five"
wordSixBig: .asciiz "Six"
wordSevenBig: .asciiz "Seven"
wordEightBig: .asciiz "Eight"
wordNineBig: .asciiz "Nine"
buffer: .space 256

.text
main:
#openning file
	li $v0, 13			#syscall for openfile
	la $a0, filename		#filename
	li $a1, 0			#type -> reading
	li $a2, 0			#mode is ignored
	syscall
	move $s0,$v0			# save the file descriptor

#reading file
	li   $v0, 14        		# system call for reading from file
	move $a0, $s0       		# file descriptor 
	la   $a1, buffer    		# address of buffer from which to read
	li   $a2,  256       		# hardcoded buffer length
	syscall             		# read from file

	li $s4, 0		# flag for sentence start	
	la $s0, zero		# will be used for comparison
	la $s1, nine		# will be used for comparison
	la $s6, dot		# will be used to check dot
	la $s7, space		# will be used to check space
	la $t0,buffer		# loading the address of the string to t0
	
	iterate:		#loop
		lb $t1,0($t0)			# storing the digit to t1
		lb $t4,0($s0)
		beqz $t1, exit   		# if $t1 == 0 then go to exit for termination  
		bge $t1,$t4, numCheck
		j printDigit

printDigit:			#prints the byte in $t1 and increments the string address
	lb $t8,0($s6)		#dot
	lb $t9,0($s7)		#space
	beq  $t1,$t9,print	#printing a space so not changing the flag and directly printing
	beq  $t1,$t8,resetFlag	#printing a dot so resetting the flag
	li $s4,1		#set he flag 1
	print:
		li   $v0, 11        		# system call for printing a char
		move $a0,$t1			#moving the char to be printed to $a0
		syscall
		add $t0, $t0, 1      		# next digit
		move $t7,$a0			#we store the last printed digit in $t7
		j iterate
	
resetFlag:
	li $s4,0
	j print
		
	
numCheck:			# digit's ASCII value is bigger than or equal to '0'. Checking if it is also smaller than or equal to'9' to confirm t is a number
	lb $t5,0($s1)
	ble $t1,$t5, numConfirmed
	j printDigit			# not a number. printing as digit

numConfirmed:			# digit is a number. Checking if it's right digit is also a number	
	move $t3,$t1
	add $t0, $t0, 1      		# next digit
	lb $t1,0($t0)			# storing the digit to t1
	bge $t1,$t4, rightCheck		#checks right neighbour
	bge $t7,$t4, leftCheck		#checks left neighbour
	beqz $s4, printNumBig   	# neighbour is not a number. Printing number as a word with uppercase
	j printNum			# neighbour is not a number. Printing number as a word with lowercase


rightCheck:			# right neighbour's ASCII value is bigger than or equal to '0'. Checking if it is also smaller than or equal to'9' to confirm t is a number
	ble $t1,$t5,fail 
	lb $t8,0($s6)		#dot
	beqz $s4, printNumBig   # neighbour is not a number. Printing number as a word with uppercase
	j printNum		# neighbour is not a number. Printing number as a word with lowercase

leftCheck:			# right neighbour's ASCII value is bigger than or equal to '0'. Checking if it is also smaller than or equal to'9' to confirm t is a number
	ble $t7,$t5,fail 
	beqz $s4, printNumBig   # neighbour is not a number. Printing number as a word with uppercase
	j printNum		# neighbour is not a number. Printing number as a word with lowercase


fail:				#neighbour is also a number. Unable to print as word
	li   $v0, 11        		# system call for printing a char
	move $a0,$t3			#moving our number to $a0
	syscall
	j printDigit			#printing the Neighbour as a digit

printNum:
	la $s3,zero
	lb $t6,0($s3)
	beq $t3,$t6,printZero		#Checking if the number is 0
	la $s3,one
	lb $t6,0($s3)
	beq $t3,$t6,printOne		#Checking if the number is 1
	la $s3,two
	lb $t6,0($s3)
	beq $t3,$t6,printTwo		#Checking if the number is 2
	la $s3,three
	lb $t6,0($s3)
	beq $t3,$t6,printThree		#Checking if the number is 3
	la $s3,four
	lb $t6,0($s3)
	beq $t3,$t6,printFour		#Checking if the number is 4
	la $s3,five
	lb $t6,0($s3)
	beq $t3,$t6,printFive		#Checking if the number is 5
	la $s3,six
	lb $t6,0($s3)
	beq $t3,$t6,printSix		#Checking if the number is 6
	la $s3,seven
	lb $t6,0($s3)
	beq $t3,$t6,printSeven		#Checking if the number is 7
	la $s3,eight
	lb $t6,0($s3)
	beq $t3,$t6,printEight		#Checking if the number is 8
	la $s3,nine
	lb $t6,0($s3)
	beq $t3,$t6,printNine		#Checking if the number is 9
	
printNumBig:
	la $s3,zero
	lb $t6,0($s3)
	beq $t3,$t6,printZeroBig	#Checking if the number is 0
	la $s3,one
	lb $t6,0($s3)
	beq $t3,$t6,printOneBig		#Checking if the number is 1
	la $s3,two
	lb $t6,0($s3)
	beq $t3,$t6,printTwoBig		#Checking if the number is 2
	la $s3,three
	lb $t6,0($s3)
	beq $t3,$t6,printThreeBig	#Checking if the number is 3
	la $s3,four
	lb $t6,0($s3)
	beq $t3,$t6,printFourBig	#Checking if the number is 4
	la $s3,five
	lb $t6,0($s3)
	beq $t3,$t6,printFiveBig	#Checking if the number is 5
	la $s3,six
	lb $t6,0($s3)
	beq $t3,$t6,printSixBig		#Checking if the number is 6
	la $s3,seven
	lb $t6,0($s3)
	beq $t3,$t6,printSevenBig	#Checking if the number is 7
	la $s3,eight
	lb $t6,0($s3)
	beq $t3,$t6,printEightBig	#Checking if the number is 8
	la $s3,nine
	lb $t6,0($s3)
	beq $t3,$t6,printNineBig	#Checking if the number is 9
	
printZero:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordZero     		# storing the address of the necessary string
	syscall    
	j iterate
printOne:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordOne     		# storing the address of the necessary string
	syscall 
	j iterate
printTwo:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordTwo     		# storing the address of the necessary string
	syscall 
	j iterate
printThree:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordThree     		# storing the address of the necessary string
	syscall
	j iterate 
printFour:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordFour     		# storing the address of the necessary string
	syscall
	j iterate
printFive:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordFive     		# storing the address of the necessary string
	syscall 
	j iterate
printSix:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordSix     		# storing the address of the necessary string
	syscall 
	j iterate
printSeven:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordSeven     		# storing the address of the necessary string
	syscall 
	j iterate
printEight:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordEight    		# storing the address of the necessary string
	syscall 
	j iterate
printNine:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordNine     		# storing the address of the necessary string
	syscall 
	j iterate
	
printZeroBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordZeroBig     	# storing the address of the necessary string
	syscall   
	li $s4,1		#set he flag 1 
	j iterate
printOneBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordOneBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printTwoBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordTwoBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printThreeBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordThreeBig     	# storing the address of the necessary string
	syscall
	li $s4,1		#set he flag 1
	j iterate 
printFourBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordFourBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printFiveBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordFiveBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printSixBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordSixBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printSevenBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordSevenBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printEightBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordEightBig   	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate
printNineBig:
	li  $v0, 4          		# system Call for PRINT STRING
	la  $a0, wordNineBig     	# storing the address of the necessary string
	syscall 
	li $s4,1		#set he flag 1
	j iterate

exit:
li $v0, 10      		# Finish the Program
syscall
