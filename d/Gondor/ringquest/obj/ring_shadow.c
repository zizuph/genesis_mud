/*
 *	/d/Mordor/ringquest/obj/ring_shadow.c
 *
 *	A auto-shadow for the Ringbearer.
 *
 *	Copyright (C) by Christian Markus 1995
 *
 *	Olorin, August 1995
 *
 *	Revision history:
 */
#pragma strict_types

inherit "/std/shadow.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

mixed
query_skill_name(int type)
{
    if (type == SS_AFFECTED_BY_RING)
    {
        if (shadow_who->query_wiz_level())
            return "One Ring Power";
        else
            return "";
    }

    return query_shadow_who()->query_skill_name(type);
}

/*
 * Function name: shadow_me
 * Description:   This function is called when a player gets the One Ring.
 *                It adds the autoshadow in the player.
 * Arguments:	  player - the player
 * Returns:       1 - everything went right
 *                0 - no player or player already shadowed
 */
public int
shadow_me(object player)
{
    NF("Something is seriously wrong with the Ring shadow.\n");
    if (!::shadow_me(player))
	return 0;

    FIX_EUID
    player->add_autoshadow(MASTER + ":");

    return 1;
}

/*
 * Function name: query_ring_shadow
 * Description:   Is the shadow already loaded?
 * Returns:       1
 */
public int
query_ring_shadow()
{
    return 1;
}

public void
remove_ring_shadow()
{
    destruct();
}

