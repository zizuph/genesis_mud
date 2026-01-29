/*
 * wizard.c
 *
 * Used in npc/bluedragon.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    set_name("wizard");
    set_adj("evil");
    set_long("This is the evil wizard Kanthrun who was turned into a dragon " +
             "by the other evil wizard in the castle.\n");

    default_config_npc(75);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);

    set_alignment(-300);
}

void
whisper(string s)
{
    command("whisper " + TP->query_real_name() + " " + s);
}

void
reward(object tp)
{
    set_this_player(tp);

    if (QDONE(ROKEGROUP, BLUEDRAGON))
    {
        write("The wizard says: It is really fun to spoil the quest for " +
              "others, right?\n");
        command("kick " + TP->query_real_name());
        command("emote disappears in a puff of smoke.");
        remove_object();
        return;
    }

    QSET(ROKEGROUP, BLUEDRAGON);
    QLOG("Blue dragon quest", BLUEDRAGONXP);

    TP->add_exp_quest(BLUEDRAGONXP);

    whisper("Thank you! I've been a prisoner here since");
    whisper("Refnas threw me out of the castle.");
    whisper("Now I am free to haunt the locals again!");
    whisper("You will be handsomely rewarded!");

    write("You feel more experienced!\n");

    command("emote disappears in a puff of smoke.");
    remove_object();
}
