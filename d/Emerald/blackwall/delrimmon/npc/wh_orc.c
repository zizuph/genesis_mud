/*
 *    /d/Emerald/blackwall/delrimmon/npc/wh_orc.c
 *
 *    This is the file that the orcs of Saruman in the Blackwall Mountains
 *    either are or will inherit.
 *
 *    Gorboth, March 1996
 *
 * TODO:    add responses to mortal questions
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/npc/emyn_muil_orc.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

nomask void
create_emyn_muil_orc()
{
    if (!random(6))
    {
        Uruk = 1;
    }

    set_chat_time(15 + random(15));
    add_chat("How long have we been at this stinking lake, and still no"
        + " sign of anything!");
    add_chat("Water, trees, and these nasty cliffs! I hate this place!");
    add_chat("Hey! What's that moving over there?!");
    add_chat("Bah, I'm sure it was just a squirrel...");
    add_chat("What's eating Ugluk? He's touchier than ever since we saw that"
      + " flying shadow...");
    add_chat("If you ask me, there's no such thing as a halfling!");
    add_chat("If there's one thing I hate, its orders to bring someone back"
      + " alive!");
    add_chat("You'd think that by now we would at least have seen something!");
    add_chat("If this scouting doesn't get more interesting, I might have to"
      + " start getting creative. Here, squirrel-squirrel!");
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
    add_act("emote searches a nearby bush, muttering about squirrels.");
    add_act("frown");
    add_act("emote peers idly at his weapon.");
    add_act("scratch");

    set_cact_time(2 + random(2));
    add_cact("shout Intruders! Go and tell Ugluk!");
    add_cact("emote crouches, swinging wildly at you with his weapon!");
    add_cact("shout Die, you worthless maggot!!");
    add_cact("emote spits on you in disgust!");
    add_cact("scream");
    add_cact("shout Intruders! Intruders at last!");
}

int
query_uruk()
{
    return Uruk;
}
