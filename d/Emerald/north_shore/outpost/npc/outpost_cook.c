/*
 *  /d/Emerald/north_shore/outpost/npc/outpost_cook.c
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
    config_guard(60); 

    add_adj("outpost");
    set_name("cook"); 
    set_short("outpost cook");
    set_long("Sweaty, and looking a bit at the end of his rope, this poor"
       + " fellow has clearly not been enjoying his post lately. Cooking"
       + " may be a labor of love, but that only goes so far in a fort"
       + " constantly under siege by invaders!\n");

    set_act_time(5);
    add_act("emote says: How much longer must we stay? This outpost is"
      + " no place for the likes of me!");
    add_act("emote grimly goes about his cooking duties.");
    add_act("emote drifts into thought, looking absently at his work.");

    set_cact_time(3);
    add_cact("emote shouts: This cleaver can cut up your meat, too!");
    add_cact("emote shouts: Guards! Help!"); 

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
    add_equipment(OUTPOST_WEP_DIR + "cleaver");
} /* arm_me */
