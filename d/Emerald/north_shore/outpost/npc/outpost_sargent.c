/*
 *  /d/Emerald/north_shore/outpost/npc/outpost_sargent.c (sp?)
 *
 *  These npcs were originally created by Mhyrkhaan for an outpost
 *  project that was indefinately put on hold. They have been
 *  retooled for the reopening of the domain and for higher
 *  standards of quality.
 *
 *  Update Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/npc/guard"; 

#include "../defs.h"


/*
 * Function name:        create_guard
 * Description  :        set up the npc with presets
 */
public void 
create_guard() 
{
    config_guard(120);

    set_name("sergeant");
    add_adj("sergeant"); 
    add_adj("outpost"); 
    set_short("outpost sergeant"); 
    set_long("This elf is clearly one of the people in charge within"
      + " the outpost. His carriage and bearing suggest long-standing"
      + " leadership, and his face is set with a look of purpose and"
      + " certainty. Were it not for the sorry condition of his"
      + " armour, and the fresh wounds upon his face, one would have"
      + " no reason to imagine that anything was going wrong.\n");

    set_act_time(5);
    add_act("emote checks the condition of his sword.");
    add_act("emote breaths a heavy sigh.");
    add_act("emote says: Fear not, this outpost shall be rebuilt,"
      + " and the North Shore secured once more.");
    add_act("emote says: Yes, but this last raid was far more"
      + " effective than we felt was possible!");

    set_cact_time(4);
    add_cact("emote shouts: For Telberin!");
    add_cact("emote says: If this outpost falls, it will not be"
      + " to the likes of you!");
    add_cact("emote shouts: Attack! Attack! Invaders have come!");

    arm_me();
} /* create_guard */


/*
 * Function name:        arm_me
 * Description  :        give the npc his armaments
 */
public void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "broadsword");
    add_equipment(OUTPOST_ARM_DIR + "chainmail");
    add_equipment(OUTPOST_ARM_DIR + "shield");

    if (!random(3))
    {
        add_equipment("/d/Genesis/gems/obj/coral");
    }
} /* arm_me */
