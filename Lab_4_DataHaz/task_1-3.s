.set noreorder # Avoid reordering instructions
 		.text # Start generating instructions
 		.globl start # The label should be globally known
 		.set noat
 		.ent start # The label marks an entry point
 		
 start: 		addi $1, $0, 0x2 # Load the value 2
 		addi $3, $0, 0x1 # Load the value 1
 		addi $6, $0, 0x3 # Load the value 3
 		addi $5, $0, 0x4 # Load the value 4
 		
 		sub	$2, $1, $3
 		and 	$12, $2, $5
 		or	$13, $6, $2
 		add	$14, $2, $2
 		sw	$15, 100($2)
 		nop
 		nop
 		nop
 		
 		.end start # Marks the end of the program
