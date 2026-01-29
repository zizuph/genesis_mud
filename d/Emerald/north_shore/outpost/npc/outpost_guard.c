/*
 *  /d/Emerald/north_shore/outpost/npc/outpost_guard.c
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
    config_guard(70); 

    set_name("guard");
    add_adj("outpost"); 
    set_short("outpost guard");
    set_long("This young elf, though armed, does not look very"
      + " well-versed at his duty. His armour is battered and his"
      + " face shows fear and anxiety. It seems he has seen"
      + " things he wishes had never come to pass.\n");

    set_act_time(5);
    add_act("emote peers around nervously.");
    add_act("emote says: Heh, if they return, we'll send them"
      + " back without their heads!");
    add_act("emote says: I just wish there were more of us.");

    set_cact_time(4);
    add_cact("emote shouts: They have returned! It's an attack!");
    add_cact("emote shouts: Send for the Captain!");
    add_cact("emote screams at you in fear and anger.");

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
    add_equipment(OUTPOST_WEP_DIR + "spear");
    add_equipment(OUTPOST_ARM_DIR + "ringmail");

    if (!random(3))
    {
        add_equipment("/d/Genesis/gems/obj/quartz");
    }
} /* arm_me */
