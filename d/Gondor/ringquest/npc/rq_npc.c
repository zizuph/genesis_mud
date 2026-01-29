/*
 *	/d/Gondor/ringquest/npc/rq_npc.c
 *
 *	Copyright (C) 1995 by Christian Markus
 *
 *	To be inherited by all Ring Quest npcs.
 *	(The members of the Fellowship, and all potential Ring Bearers.)
 *
 *	It does not inherit /d/Gondor/std/monster.c, as most npcs
 *	using this will not be in the domain Gondor.
 *
 *	Olorin, December 1995
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ringquest/lib/defs.h"

public void
create_rq_npc()
{
}

nomask void
create_monster()
{
    create_rq_npc();
}

