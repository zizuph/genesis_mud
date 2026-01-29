inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

int intro = 0;

void
create_monster()
{
    set_name("zardago");
    add_name("captain");
    set_living_name("zardago");
    set_race_name("elf");
    add_adj("weather-beaten");
    add_adj("rugged");
    set_stats(({ 60, 60, 60, 160, 90, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);
    set_chat_time(9);
    add_chat("Ah, to see the enchanting Qualinesti again!");
    add_chat("If you visit Solace, to the north of Newports, be " +
        "sure to visit Tarshir!");
    add_chat("The minotaurs of Mithas are excellent rowers!");
    add_chat("Travelling on Newsea is a pleasure, for the most part.");
    add_chat("We better watch out for Ergothian Pirates.");

    add_ask(({"fairview","ship"}),"The captain says: She's a fine " +
        "ship!\n");
    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
        "You feel this man is under strong protection.\n");

    set_ticket(TICKET);
    set_price(PRICE);
}

string
query_my_title()
{
    return "of Qualinesti, Captain of the Fairview";
}

int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
    notify_fail("The captain says: You don't need to buy any ticket. " +
		"Young travel for free.\n");
	return 0;
    }

    return ::buy(str);
}

void
react_introduce(string person,string who)
{
    if (!intro)
      intro = set_alarm(4.0,0.0,"introduce_me");
}

void
introduce_me()
{
    tell_room(E(TO),QCTNAME(TO) + " introduces himself as:\n" +
        "Zardago " + query_my_title() + ", male elf.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("zardago");
    set_alarm(1.0,0.0,"reset_introduce");
}

void
reset_introduce()
{
    intro = 0;
}
