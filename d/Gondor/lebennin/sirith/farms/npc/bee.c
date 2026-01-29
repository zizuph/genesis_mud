/* 
 * /d/Gondor/lebennin/sirith/farms/npc/bee.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar).
 *
 * /d/Gondor/common/npc/bee with a weaker poison and a null
 * sting_sequence() (bees don't sting unless attacked)
 */

#pragma strict_types

#include <stdproperties.h>	/* for NPC_I_NO_LOOKS, etc */
#include "/d/Gondor/defs.h"
#include "../defs.h"

inherit "/d/Gondor/common/npc/bee";
inherit "/std/combat/unarmed.c";

public void	create_mosquito();
public void	sting_sequence();
public int	query_knight_prestige();

/*
 * Function name:	create_mosquito
 * Description	:	set up the insect (really a bee)
 */
public void
create_mosquito()
{
    ::create_mosquito();
    add_name(SIRITH_LIVESTOCK);
    add_act("emote darts around a basket.");
    set_poison_file(POISON_DIR + "weak_bee_sting");
    set_act_time(5);	/* a little less spammy */
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
} /* create_mosquito */

public void sting_sequence() {}
public int query_knight_prestige() { return 0; }


/*
 * Function name:	cr_attacked_by
 * Description	:	This routine is called when we are attacked.
 * Arguments	:	object ob: The attacker
 *
 * if there's a farmer in the room, notify them.
 */
public void
attacked_by(object ob)
{
    object	*farmers;

    ::attacked_by(ob);

    farmers = filter(all_inventory(ENV()), &->id(SIRITH_FARMER));
    if (sizeof(farmers))
	farmers->queue_defend(TO, ob);
} /* cr_attacked_by */
