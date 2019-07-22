def NIM():
	chipCount = int(input("How many chips are in the game? "))
	type(chipCount)
	m = int(input("max takeable amount is ? "))
	while 1:
		print("type how many chips would you like to take (at max", m ,"chips). type '0' to exit")
		taken = int(input())
		if taken > m:
			print("INVALID INPUT")
			continue			
		if taken==0:
			return
		chipCount= chipCount - taken
		print("TAKING SUCCESSFUL")
		if chipCount <= 0:
			print("you have won dear current player")
			return
NIM()