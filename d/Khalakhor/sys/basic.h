/*
 * - /sys/basic.h
 *
 *  A file to hold simple, commonly used defines in one place
 *  rather then have them repeatedly spread throughout the mud.
 */
#ifndef __SYS_BASIC__
#define __SYS_BASIC__

#define TP	this_player()
#define TO	this_object()
#define TI	this_interactive()

#define NF	notify_fail
#define ENV	environment
#define CAP	capitalize
#define LC	lower_case

#define PRO(x)	(x)->query_pronoun()
#define POS(x)	(x)->query_possessive()
#define OBJ(x)	(x)->query_objective()
#define HE(x)	PRO(x)
#define HIS(x)	POS(x)
#define HIM(x)	OBJ(x)

#define QTN(who)   query_the_name(who)
#define IS_WIZ(name) ("/secure/master"->query_wiz_level(name) > 0 ? : 1 : 0)

#define TRUE  1
#define FALSE 0

#endif __SYS_BASIC__

