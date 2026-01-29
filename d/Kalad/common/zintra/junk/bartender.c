/* bartender.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"

void
create_monster()
{
    set_name("one-eye");
    add_name("bartender");
    set_adj("mean");
    add_adj("black-haired");
    set_long("He's here to take your money, what else?\n");

    default_config_mobile(75);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 80);

    set_act_time(20);
    add_act("emote wipes down the bar with a filthy cloth.");
    add_act("coughs");

    set_chat_time(20);
    add_chat("If you're not going to order, get out!");
    add_chat("What?  No tip?!?");

}

string
query_title()
{
    return "the Bartender";
}





