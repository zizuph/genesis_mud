#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <std.h>
#include HOBBIT_FILE

inherit HOBBITMAKER;

void
create_hobbit()
{
    set_power(60);
    set_type(CITIZEN);
    disable_all_noise();
/*
    set_chat_time(10 + random(11));
    add_chat("Hmmm can't wait till the next party!");
    add_chat("Would you like to order yourself a party?");
    add_chat("I hope the next party was as good as the last one!");

    set_act_time(7 + random(14));
    add_act("think");
    add_act("hrumble");
    add_act("htummy");
    add_act("hcheer");
*/
    set_default_answer(QCTNAME(TO) + " has no idea what you are "+
      "talking about.\n");
    add_ask(({"party","parties","buy","order"}),
      "say If you want to order a party type 'order party'!", 1);
}

string
hobbit_long()
{
    return "The "+query_nonmet_name() +" is here to arrange a party for someone. "+
    CAP(HE_SHE(TO))+" looks extremely busy and in quite a hurry.\n";
}

void
arm_hobbit()
{
}
