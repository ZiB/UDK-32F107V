/*
 *	File:	macros.h
 *	Date:	10.12.2013
 *	Denis Zheleznyakov
 */

#ifndef MACROS_H_
#define MACROS_H_

#define assert_param(expr) 			((void)0);

#define BIT(NUMBER)	            		(1UL << (NUMBER))

#define ARRAY_LENGHT(Value)			(sizeof(Value) / sizeof(Value[0]))

enum boolean {FALSE = 0, TRUE = 1};

#endif /* MACROS_H_ */
