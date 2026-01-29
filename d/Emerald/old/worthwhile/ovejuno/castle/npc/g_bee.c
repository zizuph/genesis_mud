/* 
 * /d/Gondor/lebennin/sirith/farms/npc/bee.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz.
 *
 * /d/Gondor/common/npc/bee with a weaker poison and a null
 * sting_sequence() (bees don't sting unless attacked)
 */
#pragma strict_types

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

inherit "/d/Gondor/common/npc/bee";

public void
create_mosquito()
{
    ::create_mosquito();
    add_act("emote darts around the flowers.");
    add_name("g_bee");
    set_poison_file(POISON_DIR + "weak_bee_sting");
    set_act_time(5);	/* a little less spammy */
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry something.\n");
}

public void sting_sequence(){}
