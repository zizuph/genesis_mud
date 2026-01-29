/* needed defines 
 * Created by Damaris 01/2001
 */

#ifndef OBJ_DEFS
#define OBJ_DEFS
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

#endif OBJ_DEFS

