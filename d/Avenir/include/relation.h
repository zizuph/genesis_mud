// file name:        /d/Avenir/include/relation.h
// creator(s):       Denis, Mar'97
// purpose:          Sybarite relationship.
// note:             Don't use the properties _live_i_am_sybarite and
//		     _live_i_am_infidel in your code directly.
/*
 * Revisions:
 * 	Lucius, Mar 2009: Removed FAITHFUL bits, they are redundant
 * 			  and barely utilized, replacing with SYBARITE checks.
 *
 */
#ifndef __AVENIR_RELATIONS__
#define __AVENIR_RELATIONS__
/*
 * Sybarite skill defines.
 */
#define SS_INFIDEL	139011

#define SYB_CRAFT	0x2
#define SYB_RACE	0x4
#define SYB_LAY		0x8
#define SYB_OCC		0x10

/*
 * Sybarite property defines
 */     
#define SYBARITE	"_live_i_am_sybarite"
#define EVILDOER	"_live_i_am_evildoer"
#define DANCER		"_live_i_am_dancer_of_veils"
#define MUMMER		"_live_i_am_mummer"

/*
 * Guild names
 */
#define UNION_GUILD	"Union of the Warriors of Shadow"

/*
 * Relationship checking macros.
 */
#define IS_INFIDEL(ob)	ob->query_skill(SS_INFIDEL)
#define IS_EVILDOER(ob)	ob->query_prop(EVILDOER)
#define IS_SYBARITE(ob)	ob->query_prop(SYBARITE)
#define IS_DANCER(ob)	ob->query_prop(DANCER)
#define IS_MUMMER(ob)	ob->query_prop(MUMMER)
#define IS_UNION(ob)	(ob->query_guild_name_occ() == UNION_GUILD)

/*
 * Relationship setting macros.
 */
#define MAKE_SYBARITE	add_prop(SYBARITE, 1)
#define MAKE_INFIDEL	set_skill(SS_INFIDEL, 1)

/*
 * Wrath of Plalgus defines
 */
#define WRATHOBJ	"/d/Avenir/common/gods/plalgus_hammer"
#define WRATHMARK	"/d/Avenir/common/gods/plalgus_mark"
#define WRATHNAME	"_hammer_of_plalgus_has_fallen"
#define WRATH_LOG	"/d/Avenir/log/misc/plalgus_hammer"
#define ABSOLVE_LOG	"/d/Avenir/log/misc/absolved"

#endif  __AVENIR_RELATIONS__
