#ifndef MIBSTD_H
#define MIBSTD_H

#define U_INT_SIZE 1
typedef unsigned char u_int;		// unsigned integer		# 8bit
#define D_U_INT_SIZE 2
typedef unsigned short d_u_int;		// double unsigned integer 	# 16bit
#define Q_U_INT_SIZE 4
typedef unsigned long q_u_int;		// quadruple unsigned integer	# 32bit

#define SIZE_INT_SIZE D_U_INT_SIZE
typedef d_u_int size_int;

#define NULL 0

#endif
