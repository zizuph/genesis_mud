/*
 *  /d/Emerald/common/guild/aod/npc/waiter.c
 *
 *  This is the waiter for the Army of Darkness Mess Hall.
 *
 *  Created October 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_NPC_DIR + "aod_ogre";

#include <stdproperties.h>

/* prototypes */
public void        create_aod_ogre();


/*
 * Function name:        create_aod_ogre
 * Description  :        dummy routine for inheriting files
 */
public void
create_aod_ogre()
{
    set_living_name("Gugak");
    set_name("gugak");
    add_name( ({ "waiter", "_army_of_darkness_waiter" }) );
    set_adj( ({ "fat", "apron-fitted" }) );

    set_title("the Fat, Waiter for the Army's Mess Hall");

    set_long("This very fat Ogre looks like he is in a foul mood. He"
      + " is splattered with food, and looks impatiently around. You"
      + " can probably order food from him if he's in the Mess Hall"
      + " with you.\n");

    add_act("emote scrapes some dead cow from his apron and licks"
      + " his fingers.");
    add_act("emote shouts into the kitchen: NEED MORE COW, QUICK!");
    add_act("emote walks around the hall, trailing beer and wine"
      + " with each footprint.");
    add_act("emote jumps up as a cow dashes suddenly out of the"
      + " kitchen. Catching it by the tail, he picks up the terrified"
      + " creature and hurls it back through the hole in the wall.");
    add_act("emote booms: WHAT YOU WANT? WE GOT COW, COW, COW, AND COW.");
    add_act("emote booms: NOT LIKE COW? WHAT, COW TOO GOOD FOR SISSY"
      + " LIKE YOU? EAT COW AND SHUT MOUTH!!!");
    add_act("emote wipes some blood on his apron.");

    config_ogre(140);  /* A powerful npc */

    set_job_response("HUH? ME BRING FOOD! YOU HUNGRY?");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */