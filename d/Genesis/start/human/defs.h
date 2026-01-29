/*
 *	/d/Genesis/start/human/defs.h
 * Added website for information purposes - TAPAKAH, 05/2005
 */

// Directories:
#define HUMAN_DIR	"/d/Genesis/start/human/"
#define TOWN_DIR	(HUMAN_DIR + "town/")
#define OBJ_DIR		(HUMAN_DIR + "obj/")


#define TP			this_player()
#define TO			this_object()
#define TI			this_interactive()

#define ENV(x)		environment(x)
#define CAP(x)		capitalize(x)
#define LOW(x)		lower_case(x)
#define NFN(x)		notify_fail((x) + "\n")
#define NF(str)		notify_fail(str)

#define HE(x)		(x)->query_pronoun()
#define HIS(x)		(x)->query_possessive()
#define HIM(x)		(x)->query_objective()

#define WEBSITE		"http://www.genesismud.org"
