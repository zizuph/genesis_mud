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
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("Sparkle is a nice place, not considering all the rats.");
    add_chat("My minotaurs work hard.");
    add_chat("How nice it is travelling by sea.");
    add_chat("We better watch out for Ergothian Pirates.");
    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
        "You feel this man is under strong protection.\n");

    set_ticket(TICKET);
    set_price(PRICE);
}

string
query_my_title()
{
    return "the Sea Wizard";
}

int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
	notify_fail("You don't need to buy any ticket. " +
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
	      "Captain Zardago " + query_my_title() + ", male elf.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("zardago");
    intro = 0;
}
