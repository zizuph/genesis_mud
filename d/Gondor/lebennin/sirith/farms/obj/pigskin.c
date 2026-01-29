/*
 * /d/Gondor/lebennin/sirith/farms/obj/pigskin.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * XXX don't really want them to eat the pigskin, but not sure
 * how to prevent it.
 */

inherit	"/std/leftover";

#include <macros.h>		/* for IS_CLONE */
#include <stdproperties.h>	/* for HEAP_S_UNIQUE_ID */
#include "/d/Gondor/defs.h"
#include "../defs.h"

public void	create_leftover();
public void	leftover_init(string organ, string race);


/*
 * Function name:	create_leftover
 * Description	:	set up the skin
 */
public void
create_leftover()
{
    if (!IS_CLONE) return;
    FIX_EUID;
    set_name( ({ "pig skin", "skin" }) );
    set_short("pig skin");
    set_pshort("pig skins");
    set_long(BSN("The pig skin has been gouged and slashed, "+
	"and is covered with blood."));
 
    /* pig is 3' tall x 5' long x 2' wide. assume 1' of height is legs,
     * so skin is 5' x (2+2+2)' x 1" thick == 4320 cubic inches
     */ 
    add_prop_obj_i_weight(4536);	/* 10 lb */
    add_prop_obj_i_volume(70796);	/* 4320 cubic inches */
    add_prop_obj_i_value(50);
    set_decay_time(1000);
    set_amount(1);
} /* create_leftover */


/*
 * Function name:	leftover_init
 * Description	:	mask parent to set up props and description
 *			if player poisoned pig.
 * Arguments	:	string organ -- which part
 *			string race -- which race
 */
public void
leftover_init(string organ, string race)
{
    string	killer;
    object	corpse,
		tp = TP;

    if (objectp(corpse = previous_object()) ||
        (objectp(tp) &&
         objectp(corpse = present(PIGCORPSE, ENV(tp)))))
    {
	if (strlen(killer = corpse->query_prop(SIRITH_S_WAS_POIS)))
	{
	    DEBUG_LOG(tp->query_real_name()+" skinned a poisoned pig.\n");
	    add_prop(SIRITH_S_WAS_POIS, killer);
	    set_long(BSN("The pig skin is a little ragged at the edges, "+
		"but otherwise is in excellent condition."));
            remove_prop(HEAP_S_UNIQUE_ID);
            add_prop(HEAP_S_UNIQUE_ID, query_long());
	}
	else
	{
	    DEBUG_LOG(tp->query_real_name()+" skinned a pig "+
		"who did not die of poison.\n");
	}
    }
    else
    {
	ERR_LOG(" leftover_init(): no previous object and no corpse\n");
    }
    ::leftover_init(organ, race);
} /* leftover_init */
