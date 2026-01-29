/* Misc defs for the Union occ soul.
 *   Cirion, 29 April 1996
 *
 *   Lilith, Oct 2004: Updated TR macro to tell_watcher
 *   Lucius, Aug 2017: Jettison extraneous defines.
 *
 */
#ifndef __UNION_MISC__
#define __UNION_MISC__

/* Definitions for preparations & waiting in special attacks */
#define PREP           "_Union_I_Special_Attack"
#define P_FLING        1
#define P_SLASH        2
#define P_WAITING      3

/* Definitions for specials */
#define SWAY           (OBJ + "sway")
#define SWAY_MANA      6
#define SWAY_FATIGUE   10

/* Definitions to make combat messages easier */
#define ME(x)   me->catch_msg(x+"\n")
#define YOU(x)  enemy->catch_msg(x+"\n");
#define TW(x)   me->tell_watcher(x+"\n", enemy);
#define TWM(x)  me->tell_watcher_miss(x+"\n", enemy);

#define KNIFE(x)    (x)->query_skill(SS_WEP_KNIFE)
#define PARRY(x)    (x)->query_skill(SS_PARRY)
#define DEFENCE(x)  (x)->query_skill(SS_DEFENCE)
#define SWORD(x)    (x)->query_skill(SS_WEP_SWORD)

/* Union Specials. */
#define SLASH(x)    (x)->query_skill(SS_SLASH)
#define FLING(x)    (x)->query_skill(SS_FLING)

#endif /* __UNION_MISC__ */
