/*
 * /d/Gondor/lebennin/sirith/farms/npc/livestock.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * inherited by farm livestock so they can get help from any farmers
 * in room when attacked
 *
 * not giving any knight prestige for killing livestock
 */


#pragma strict_types
 
inherit "/std/creature";
inherit "/std/combat/unarmed.c";

#include "../defs.h"

public void	create_sirith_livestock();
nomask void	create_creature();


/*
 * Function name:	create_sirith_livestock
 * Description	:	configure your livestock here
 */
public void
create_sirith_livestock()
{
} /* create_sirith_livestock */


/*
 * Function name:	create_creature
 * Description	:	set up livestock
 */
nomask void
create_creature()
{
    create_sirith_livestock();
    add_name(SIRITH_LIVESTOCK);
} /* create_creature */



/*
 * Function name:  cr_attacked_by
 * Description:    This routine is called when we are attacked.
 * Arguments:	   ob: The attacker
 *
 * if there's a farmer in the room, notify her/him.
 */
public void
attacked_by(object ob)
{
    object	*farmers;

    ::attacked_by(ob);

    farmers = filter(all_inventory(environment()), &->id(SIRITH_FARMER));
    if (sizeof(farmers))
    {
	farmers->queue_defend(this_object(), ob);
    }
} /* cr_attacked_by */
