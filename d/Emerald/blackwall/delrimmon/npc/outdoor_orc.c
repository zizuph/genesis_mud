/*
 *  /d/Emerald/blackwall/delrimmon/npc/outdoor_orc.c
 *
 *  This is the file which gives the orcs of Isengard some area-
 *  specific emotes for their stay in the Blackwall Mountains. The oudoor
 *  orcs have different things to say at times.
 *
 *  Copyright (c) October 1998, by Cooper Sherry (Gorboth) 
 *
 *  TODO:    add responses to mortal questions
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/npc/del_rimmon_orc.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_outdoor_orc();
nomask void    create_del_rimmon_orc();

/*
 * Function name:        create_outdoor_orc
 * Description  :        dummy function for inheriting files
 */
public void
create_outdoor_orc()
{
} /* create_outdoor_orc */

/*
 * Function name:        create_del_rimmon_orc
 * Description  :        set up the npc with some outdoor specifics
 */
nomask void
create_del_rimmon_orc()
{
    /* we want these emotes in addition to those defined in
     * del_rimmon_orc, so we don't want to redefine add_isengard_emotes
     */
    add_chat("Hey! What's that moving over there?!");
    add_chat("Bah, I'm sure it was just a squirrel...");
    add_chat("If this scouting doesn't get more interesting, I might have to"
      + " start getting creative. Here, squirrel-squirrel!");

    add_act("emote searches a nearby bush, muttering about squirrels.");

    add_cact("shout Intruders! Go and tell the captain!");

    create_outdoor_orc();
} /* create_del_rimmon_orc */
