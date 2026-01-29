/*
 * Librarian of Green Oaks
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

    set_name("yealean");
    set_adj("quiet");
    set_adj("studius");
    set_short("chatty nimble elf");

    set_long("With piercing blue eyes and grey hair, this elf is in charge " +
        "of all the many books stored here in the library. She keeps " +
        "everything order, and will lend books out to those who ask " +
        "for them\n");
    set_title("Sai-olan, Libraian of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);

    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    default_config_mobile(90+random(10));

    set_gender(G_MALE);
    set_chat_time(40+random(10));
    add_chat("Please keep your talking down, it's disturbing others here.");
    add_chat("You're likely to find something useful here to read.");
    add_chat("Feel free to write a book of what you have learned here.");
    add_chat("What book can I get for you?");
    add_chat("How may I help you?");
    add_chat("This library is one of the great stores of learning.");
    
    set_act_time(60+random(60));
    add_act("emote puts a book on a shelf.");
    add_act("emote hushes a noisy visitor.");
    add_act("emote rearranges some books on a shelf.");
    add_act("emote reviews a new book.");
    add_act("emote looks around.");
    add_act("emote smiles at you.");

}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet you! " +
        "What can I get for you?");
    command("shake " + TP->query_real_name() );
}


void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("introduce me to "+tp->query_real_name());
    command("say Welcome to Green Oaks!");
    return;
}

void
init_living()
{
    ::init_living();

    if (living(TP) && interactive(TP) && CAN_SEE(TO, TP) &&
        !(TP->query_met(query_real_name())))
    {
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(TP));
        return;
    }

}

