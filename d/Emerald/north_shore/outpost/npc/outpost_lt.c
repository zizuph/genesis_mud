/*
 *  /d/Emerald/north_shore/outpost/npc/outpost_lt.c
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
    config_guard(100); 

    add_adj("outpost");
    set_name("lieutenant"); 
    set_short("outpost lieutenant"); 
    set_long("This soldier carries himself as one who has lead"
      + " forces in battle before. His stature is sturdy, and his"
      + " eyes hard. Even so, he looks rather weary, and grimly"
      + " goes about his duty as one long-seeking relief.\n");

    set_act_time(5);
    add_act("emote peers wearily at you.");
    add_act("emote pauses to check his damaged armour.");
    add_act("emote says: We simply cannot continue to hold this"
      + " outpost without reinforcements!");
    add_act("emote says: No, the Captain is right ... we must not"
      + " abandon this post.");

    set_cact_time(4);
    add_cact("emote shouts: For Telberin!");
    add_cact("emote says: If this outpost falls, it will not be"
      + " to the likes of you!");


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
    add_equipment(OUTPOST_WEP_DIR + "mil_longsword");
    add_equipment(OUTPOST_ARM_DIR + "chainmail");
    add_equipment(OUTPOST_ARM_DIR + "shield");

    if (!random(3))
    {
        add_equipment("/d/Genesis/gems/obj/jasper");
    }
} /* arm_me */
