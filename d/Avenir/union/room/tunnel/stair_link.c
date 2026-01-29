#pragma strict_types

#include "defs.h"
inherit SBASE;

public int
check_stair_room(void)		{ return 1; }

public int
prevent_enter(object ob)
{
    object *who;
    string where, vb;

    if (!query_interactive(ob))
	return ::prevent_enter(ob);

    who = filter(all_inventory(), query_interactive);

    if (!sizeof(who))
	return ::prevent_enter(ob);

    /* Is the player teleporting? Is the player recovering
     * from link death? If so, don't prevent the move!
     */
    if (!ENV(ob)->check_stair_room())
	return ::prevent_enter(ob);

    vb = query_verb();

    if (vb == "up")
	where = "above you";
    else if (vb == "down")
	where = "below you";
    else
	where = "there";

    ob->catch_tell("Someone is standing on the narrow stair "+
	where +", blocking your passage.\n");

    return 1;
}

