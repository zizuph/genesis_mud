/*
 *  /d/Emerald/north_shore/outpost/npc/outpost_elite.c
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
    config_guard(80); 

    set_name("elite guard");
    add_name("elite");
    add_adj("outpost"); 
    set_short("elite outpost guard");
    set_long("This young guard looks more able than most. His eyes"
      + " show fierce determination, and yet are unable to mask"
      + " a great sense of apprehension. His face is dirty and his"
      + " armour scored by battle.\n");

    set_act_time(5);
    add_act("emote gnashes his teeth and curses.");
    add_act("emote says: If they return, they will taste my"
      + " wrath!");
    add_act("emote says: The Captain will put a stop to these"
      + " raids, mark my words!");

    set_cact_time(4);
    add_cact("emote shouts: Taste iron you foolish wretch!");
    add_cact("emote shouts: This is it! They have returned! Attack!");
    add_cact("emote yells: Quick! I have them cornered!");

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
    add_equipment(OUTPOST_WEP_DIR + "mace");
    add_equipment(OUTPOST_ARM_DIR + "chainmail");
    add_equipment(OUTPOST_ARM_DIR + "shield");

    if (!random(3))
    {
        add_equipment("/d/Genesis/gems/obj/agate");
    }
} /* arm_me */
