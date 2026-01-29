/*
 * healernew.c
 *
 * Used in wild/q6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    int i;

    set_name("jhonlee");
    add_name("healer");
    set_living_name("jhonlee");
    set_long("This is an old man, wearing white robes and some kind of harp or\n" +
             "maybe a zither. His appearance radiates ancient wisdom and magic.\n" +
             "He has obviously returned from his journey to The Other Side.\n");
    set_title("ancient master of magical arts and knowledges");
    set_race_name("human");
    set_gender(0);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_all_attack_unarmed(50, 50);

    set_chat_time(120);
    set_act_time(120);
    add_chat("All changed! It is all changed.");
    add_act("emote stands and looks out over the rift " +
            "into the mist.");
    add_chat("I have been to the Other Side, I have looked across " +
             "and seen the promised land ... ");
    add_act("nod wisely");
    add_chat("In my dream there was a vision of great dragons " +
             "flying through fire!");
    set_default_answer(QCTNAME(this_object()) + " says: I cannot " +
                       "answer your question. In life you must find the answers for " +
                       "yourself.\n");
}
