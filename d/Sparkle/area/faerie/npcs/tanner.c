/*
 * Tanner of Green Oaks
 * By Finwe, April 2005
 */

inherit "/std/monster";

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

void
create_monster()
{
    set_race_name("elf");

    set_name("ingvane");
    set_adj("studious");
    set_adj("cheerful");
    set_short("studious cheerful elf");
    set_long("This is the tanner of Green Oaks. He specializes in making " +
        "and selling objects made from leather. His objects are well " +
        "received and used by many who come here. His hands are unusually " +
        "stained from the trade, but it doesn't seem to bother him. Even " +
        "though elves rever animals, they do appreciate the strength " +
        "leather provides, and use it carefully for those purposes.\n");
    set_title("Tor'Aldra, Tanner of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-attackable

    set_chat_time(40+random(10));

    set_gender(G_MALE);

    set_chat_time(60+random(60));
    add_chat("Be sure to examine the shelves and mannequins to see " +
        "what is available.");
    add_chat("The sign shows my wares for sale.");
    add_chat("Elves appreciate my skill in tanning hides.");
    add_chat("My leather work is known far and wide.");
    add_chat("You won't find any finer leather products anywhere else.");
    add_chat("What can I get you?");
    
    set_act_time(60+random(60));
    add_act("emote polishes the counter.");
    add_act("emote sweeps the floor.");
    add_act("emote does some tooling on a piece of leather.");
    add_act("emote greets a visitor.");
    add_act("emote does some busy work behind the counter.");
    add_act("emote finishes work on something and displays it..");

}

init_living()
{
    ::init_living();
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet you!");
    command("shake " + TP->query_real_name() );
}
