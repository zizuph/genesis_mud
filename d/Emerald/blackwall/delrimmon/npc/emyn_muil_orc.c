/*
 *  /d/Emerald/blackwall/delrimmon/npc/emyn_muil_orc.c
 * 
 *  This is the file which gives the orcs of Isengard some area-
 *  specific emotes for their stay in the Blackwall Mountains.
 *
 *  Copyright (c) October 1998, by Cooper Sherry (Gorboth) 
 *
 *  TODO:    add responses to mortal questions
 */
#pragma strict_types

inherit "/d/Gondor/rohan/isengard/npc/isengard_orc.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_emyn_muil_orc();
public void    create_isengard_orc();
public void    add_isengard_emotes();

/*
 * Function name:        create_emyn_muil_orc
 * Description  :        dummy function for inheriting files
 */
public void
create_emyn_muil_orc()
{
} /* create_emyn_muil_orc */

/*
 * Function name:        create_isengard_orc
 * Description  :        set up the npc
 */
nomask void
create_isengard_orc()
{
    create_emyn_muil_orc();
} /* create_isengard_orc */

/*
 * Function name:        add_isengard_emotes
 * Description  :        we want to overwrite the emotes defined
 *                       in the master, giving these orcs ones
 *                       which relate to their situation
 */
public void
add_isengard_emotes()
{
    set_chat_time(15 + random(15));
    add_chat("How long have we been at this stinking lake, and still no"
        + " sign of anything!");
    add_chat("Water, trees, and these nasty cliffs! I hate this place!");
    add_chat("What's eating Ugluk? He's touchier than ever since we saw that"
      + " flying shadow...");
    add_chat("If you ask me, there's no such thing as a halfling!");
    add_chat("If there's one thing I hate, its orders to bring someone back"
      + " alive!");
    add_chat("At least in Isengard we had decent food and drink!");

    set_cchat_time(5 + random(10));
    add_cchat("At last, something to do here!");
    add_cchat("Taste my black blade, pathetic fool!");
    add_cchat("I've been thinking this place needed a few bodies to brighten"
      + " up the atmosphere. How nice of you to donate yours!");
    add_cchat("If there's one thing I can't stand, its you!!");
    add_cchat("I see you'll be a bit more sport than those damn squirrels!");
    add_cchat("Now you've angered me. Soon you'll be dead!");
    add_cchat("My sword needs a scabbard! Your throat will do nicely!");

    set_act_time(15 + random(15));
    add_act("yawn");
    add_act("frown");
    add_act("emote peers idly at his weapon.");
    add_act("scratch");

    set_cact_time(2 + random(2));
    add_cact("emote crouches, swinging wildly at you with his weapon!");
    add_cact("shout Die, you worthless maggot!!");
    add_cact("emote spits on you in disgust!");
    add_cact("scream");
    add_cact("shout Intruders! Intruders at last!");
} /* add_isengard_emotes */
