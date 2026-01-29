#ifndef __UNION_SPECIAL_ATTACKS__
#define __UNION_SPECIAL_ATTACKS__

#include <tasks.h>

#include "misc.h"
#include "filters.h"

#ifndef STR
# define STR(x)		(x)->query_stat(SS_STR)
# define DEX(x)		(x)->query_stat(SS_DEX)
#endif

#ifndef Genesis
#define COMBAT_DEBUG
#endif

#ifdef COMBAT_DEBUG
#define CDBB write_file("/d/Avenir/union/special/ofling_damage", "\n")
#define CDB(x) \
    write_file("/d/Avenir/union/special/ofling_damage", \
    "-- "+ me->query_name() +" vs. "+ enemy->query_name() +": "+ x +"\n")
#else
#define CDBB
#define CDB(x)
#endif

/* Prototypes */
private void do_slash(object me, object enemy);
private void do_fling(object me, object enemy, object knife);


private void
rem_prep(object who)
{
    who->remove_prop(PREP);
    who->catch_tell("You feel you can attack again.\n");
}

private mixed
check_prep(object who, int prop)
{
    int myprop = TP->query_prop(PREP);

    if (!myprop)
	return 0;

    if (myprop == P_WAITING)
	return "You are not yet ready to attack.\n";

    if (prop == myprop)
	return "You are already preparing to do that.\n";

    if (myprop)
	return "You are preparing to do something else.\n";

    return 0;
}

#include "fling.h"
#include "slash.h"

#endif /* __UNION_SPECIAL_ATTACKS__ */
