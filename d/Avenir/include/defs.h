// file name:	     /d/Avenir/include/defs.h
// creator(s):       Denis, Mar'97,
//		     based on writings by the original members of Avenir: 1993
// purpose:          To descrease the amount of keypresses you need to make
//		     while coding.
// note:             If you feel this file is missing anything, feel free
//                   to discuss it with Avenir's Liege.
// revision history: 
// * Lucius May 2009: Various cleanups.
//
#ifndef _AVENIR_DEFS
#define _AVENIR_DEFS

#define BLACK		add_prop(ROOM_I_LIGHT,  0);
#define BLACKER		add_prop(ROOM_I_LIGHT, -1);
#define LIGHT		add_prop(ROOM_I_LIGHT,  1);
#define LIGHTER		add_prop(ROOM_I_LIGHT,  2);
#define OUT		add_prop(ROOM_I_INSIDE, 0);
#define IN		add_prop(ROOM_I_INSIDE, 1); \
			add_prop(ROOM_I_ALLOW_STEED, 1);
#define NO_STEED	remove_prop(ROOM_I_ALLOW_STEED);

#define AE		add_exit
#define AI		add_item
#define ACI		add_cmd_item

#define ADD(x,y)	add_action(x, y)
#define ADA(x)		add_action(x, x)

#define HAS_WATER	add_prop(OBJ_I_CONTAIN_WATER, 1);

#ifndef TO
#  define TO		this_object()
#endif
#ifndef TP
#  define TP		this_player()
#endif

#define QRACE(x)	(x)->query_race_name()        /* sub-race */
#define POSSESS(x)	(x)->query_possessive()       /* his/hers */
#define OBJECTIVE(x)	(x)->query_objective()        /* him/her  */
#define PRONOUN(x)	(x)->query_pronoun()          /* he/she   */

#define NEVERKNOWN	add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN	add_prop(LIVE_I_ALWAYSKNOWN, 1)

#define HP(x)		(x)->query_hp()
#define SET_MAX_HP	set_hp(query_max_hp())

#define STR(x)		(x)->query_stat(SS_STR)
#define DEX(x)		(x)->query_stat(SS_DEX)
#define CON(x)		(x)->query_stat(SS_CON)
#define INT(x)		(x)->query_stat(SS_INT)
#define WIS(x)		(x)->query_stat(SS_WIS)
#define DIS(x)		(x)->query_stat(SS_DIS)

#define NF		notify_fail
#define CAP		capitalize
#define QVB		query_verb()
#define NFVB		NF(CAP(QVB) + " what?\n")
#define ONEOF(x)	one_of_list(x)
#define ENV		environment

#endif  /* _AVENIR_DEFS */
