	 .set noreorder  			# Avoid reordering instructions
 	 .text 						# Start generating instructions
	 .globl	start 				# The label should be globally known
	 .ent start 				# The label marks an entry point
	 
start:	 addi $8, $0, 0x1 	# Load the value 1
 		 addi $9, $0, 0x1 	# Load the value 1
		 add $10, $8, $9 	# Add the values
		 addi $8, $0, 0xFF 	# into reg X , from addr X , load value
		
		 b start 			# branch back to start (loop)
		 nop				# No Operation
		 .end start			# Marks the end of the program
		 