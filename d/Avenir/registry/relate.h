/*
 * /d/Avenir/registry/relate.h
 *
 * Definitions file for relationships.
 * To disable relationships with non-existant players, #define REALPLAYERS 1
 * To add a category, add the necessary information here in the defines and
 * be sure to alter the sign text in relate.c. No other modification is
 * necessary.
 *
 * Modification log:
 */
#ifndef _RELATION_DEFS_
#define _RELATION_DEFS_

#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/smis/sys/statserv.h"

/* All defines go below this line. */

#define DEBUG(x)	find_living("lucius")->catch_msg(x + "\n");
#define REGISTRY	"/d/Avenir/registry/"
#define PROOF		(REGISTRY + "proof")
#define PROOF_ID	"_relation_proof"
#define RELATE		(REGISTRY + "relate")
#define SEAL		(REGISTRY + "seal")
#define CYNREDE_SUBLOC	"_cynrede_subloc_"
#define REG_LOG		"/d/Avenir/log/registry"

#define BOUND       ({ "blood-bound", "dual-bound", "pair-bound", \
			"kindred-spirit", "life-bound", "soul-mate", \
			"soul-twin", "twice-bound", "twin-flame" })
#define ANCESTOR    ({ "ancestor", "ancestress" })
#define DESCENDANT  ({ "descendant", "heir" })
#define GRANDPARENT ({ "grandfather", "grandmother", "grandparent" })
#define GRANDCHILD  ({ "grandson", "grandaughter", "grandchild" })
#define SPOUSE      ({ "husband", "wife", "spouse", "consort", "mate", \
			"partner" })
#define PATRON      ({ "patron", "patroness", "lady", "lord" })
#define CONCUBINE   ({ "concubine", "consort", "odalisque", "paramour", \
			"pleasure slave" })
#define SIBSPOUSE   ({ "brother-husband", "sister-wife", "sibling-spouse" })
#define PARENT      ({ "father", "mother", "parent", "matriarch", \
    			"patriarch" })
#define CHILD       ({ "child", "daughter", "son", "bastard", "issue", \
			"offspring", "scion" })
#define STEPPARENT  ({ "step-father", "step-mother", "step-parent" })
#define STEPCHILD   ({ "step-son", "step-daughter", "step-child" })
#define SIBLING     ({ "sibling", "brother", "sister", "half-brother", \
			"half-sister", "twin-brother", "twin-sister" })
#define COUSIN      ({ "cousin", "second-cousin", "distant-cousin" })
#define TIOS        ({ "uncle", "aunt" })
#define SOBRINOS    ({ "nephew", "niece" })
#define FOSTER      ({ "foster-parent", "foster-mother", "foster-father", \
			"fosterer", "fostered", "foster-child", \
			"foster-son", "foster-daughter", "foster-sister", \
			"foster-brother" })
#define FRIEND      ({ "ally", "companion", "comrade", "friend" })
#define LOVER       ({ "lover", "boyfriend", "girlfriend", \
			"admirer", "beloved", "bewitched", "cherished", \
			"enamoured", "enthralled", "suitor", "sweetheart" })
#define FIANCE      ({ "fiance", "fiancee", "betrothed", "intended", \
    			"promised" })
#define MASTR       ({ "master", "mistress", "owner", "liege-lord", \
    			"liege-lady" })
#define SERVANT     ({ "slave", "captive", "follower", "pet", "retainer", \
			"servant", "vassal" })
#define WARDER      ({ "warder", "caretaker", "champion", "chaperone", \
			"guardian", "nanny", "protector" })
#define WARD        ({ "ward", "charge", "protectee", "responsibility" })
#define ENEMY       ({ "enemy", "foe", "mortal-enemy", "rival", \
    			"sworn-enemy" })
#define RELATIVE    ({ "relative", "kin" })
#define EX          ({ "ex" })

#define CATS        ({ "bound", "ancestor", "descendant", "grandparent",      \
                       "grandchild", "spouse", "concubine", "patron",         \
                       "sibling-spouse", "parent", "child", "step-parent",    \
                       "step-child", "sibling", "cousin", "uncle-aunt",       \
                       "nephew-niece", "foster", "friend", "lover", "fiance", \
                       "fiancee", "master", "servant", "enemy", "relative",   \
                       "ward", "warder", "ex" })

#define MATCHING  ([ \
	"bound" : "bound",			\
	"ancestor" : "descendant",		\
		"descendant" : "ancestor",	\
	"grandparent" : "grandchild",		\
		"grandchild" : "grandparent",	\
	"spouse" : "spouse",			\
	"concubine" : "patron", 		\
		"patron" : "concubine",		\
	"sibling-spouse" : "sibling-spouse",	\
	"parent" : "child",			\
		"child" : "parent",		\
	"step-parent" : "step-child",		\
		"step-child" : "step-parent",	\
	"sibling" : "sibling",			\
	"cousin" : "cousin",			\
	"uncle-aunt" : "nephew-niece",		\
		"nephew-niece" : "uncle-aunt",	\
	"foster" : "foster",			\
	"friend" : "friend",			\
	"lover" : "lover",			\
	"fiance" : "fiancee",			\
		"fiancee" : "fiance",		\
	"master" : "servant",			\
		"servant" : "master",		\
	"enemy" : "enemy",			\
	"ex" : "ex",				\
	"ward" : "warder",			\
		"warder" : "ward",		\
	"relative" : "relative"			\
])

#define RELATES ([ \
	"bound"          : ({ BOUND, BOUND }),            \
	"ancestor"       : ({ ANCESTOR, DESCENDANT }),    \
	"descendant"     : ({ DESCENDANT, ANCESTOR }),    \
	"grandparent"    : ({ GRANDPARENT, GRANDCHILD }), \
	"grandchild"     : ({ GRANDCHILD, GRANDPARENT }), \
	"spouse"         : ({ SPOUSE, SPOUSE }),          \
	"concubine"      : ({ CONCUBINE, PATRON }),       \
	"patron"         : ({ PATRON, CONCUBINE }),       \
	"sibling-spouse" : ({ SIBSPOUSE, SIBSPOUSE }),    \
	"parent"         : ({ PARENT, CHILD }),           \
	"child"          : ({ CHILD, PARENT }),           \
	"step-parent"    : ({ STEPPARENT, STEPCHILD }),   \
	"step-child"     : ({ STEPCHILD, STEPPARENT }),   \
	"sibling"        : ({ SIBLING, SIBLING }),        \
	"cousin"         : ({ COUSIN, COUSIN }),          \
	"nephew-niece"   : ({ SOBRINOS, TIOS }),          \
	"uncle-aunt"     : ({ TIOS, SOBRINOS }),          \
	"foster"         : ({ FOSTER, FOSTER }),          \
	"friend"         : ({ FRIEND, FRIEND }),          \
	"lover"          : ({ LOVER, LOVER }),            \
	"fiance"         : ({ FIANCE, FIANCE }),          \
	"fiancee"        : ({ FIANCE, FIANCE }),          \
	"master"         : ({ MASTR, SERVANT }),          \
	"servant"        : ({ SERVANT, MASTR }),          \
	"warder"         : ({ WARDER, WARD }),            \
	"ward"           : ({ WARD, WARDER }),            \
	"enemy"          : ({ ENEMY, ENEMY }),            \
	"ex"             : ({ EX, EX }),                  \
	"relative"       : ({ RELATIVE, RELATIVE }),      \
])

/* All defines go above this line. */
#endif
