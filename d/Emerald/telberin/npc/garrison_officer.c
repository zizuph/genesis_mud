/*
 *  /d/Emerald/telberin/npc/garrison_officer.c
 *
 *  This is a quest npc who gives players a small tour-sized
 *  quest to obtain a report from the captain of the north
 *  shore outpost.
 *
 *  Location: /d/Emerald/telberin/kot_office.c
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>


/* prototypes */
public void    create_telberin_elf();
public void    introduce(object who);
public void    react_intro(object tp);


/*
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf()
{
    set_living_name("jesti");
    set_name("jesti");
    add_name( ({ "jesti mendan", "officer", "soldier" }) );
    add_adj( ({ "severe", "hard-faced" }) );

    set_title("Mendan, Garrison Sergeant of the Protectorate"
      + " of Telberin");

    set_short("severe, hard-faced elf");
    set_long("An intensity radiates from this powerful-looking"
      + " elf. He is clearly cut from the cloth of many"
      + " generations of proud warriors. But no amount of"
      + " battle prowess could wipe away the clear lines"
      + " of concern and fatigue which mark his features.\n");

    config_elf(250);  /* One of the great warriors of Telberin */

    set_act_time(20);
    add_act("emote takes an official document from an elf who has"
      + " just entered the room and reads it. Scowling, he writes"
      + " some quick words on the parchment, reseals it, and hands"
      + " it back to the messenger who quickly hurries out again.");
    add_act("emote clenches his fists.");
    add_act("emote goes to the door, where a number of soldiers"
      + " have just arrived. After a few moments of terse"
      + " conversation, he gives them fresh orders and they"
      + " hurry off.");
    add_act("emote mumbles: No word from Markul ... I will need"
      + " to send another messenger.");
    add_act("emote mutters: I can only hope the North Shore"
      + " outpost has not fallen. I must have news!");

    set_cact_time(10);
    add_cact("emote peers at you with a look of death.");
    add_cact("emote widens his eyes as he moves to kill you.");
    add_cact("shout To arms! Invaders in the city!");
    add_cact("emote shouts: Fly, servant of Darkness! You will"
      + " meet only death in Telberin!");

    set_job_response("I an officer of the Protectorate of"
      + " Telberin.");
} /* create_elf */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */
