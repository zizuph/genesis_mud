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
    string   rnd_adj = one_of_list( ({ "young", "nervous",
                                       "nimble", "able",
                                       "busy", "slow-moving",
                                       "weary", "troubled",
                                       "quiet", "simple", }) );

    config_guard(45); 

    set_name("woodcutter");
    add_name( ({ "cutter", "_elf_woodcutter" }) );
    add_adj( ({ rnd_adj, "wood", }) );
    set_short(rnd_adj + " woodcutter");
    set_long("This " + rnd_adj + " elf is hard at work chopping wood"
      + " in the forest. He has a fearful look in his eyes, as if he"
      + " has a bad feeling about something in the area.\n");

    set_act_time(5);
    add_act("emote peers around nervously.");
    add_act("emote says: Just a few more cords of wood, and then"
      + " I'm getting back to the outpost.");
    add_act("emote says: Just look at these trees. Something has"
      + " been tearing them to pieces!");
    add_act("emote ties a few bundles together from the wood he"
      + " has chopped, glancing nervously into the woods.");
    add_act("emote hacks away at a nearby tree.");

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
    add_equipment(OUTPOST_WEP_DIR + "woodaxe");
    add_equipment(OUTPOST_ARM_DIR + "leather"); 

    if (!random(3))
    {
        add_equipment("/d/Genesis/gems/obj/quartz");
    }
} /* arm_me */