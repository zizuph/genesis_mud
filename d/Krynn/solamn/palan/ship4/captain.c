inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

#define ENV(xxx) environment(xxx)

int intro = 0;

void
create_monster()
{
    set_name("justin");
    add_name("captain");
    set_race_name("elf");
    add_adj("tall");
    set_adj("lisping");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);
    set_chat_time(9);

    add_chat("My minotaurth work hard.");
    add_chat("How nithe it ith travelling by thea.");
    add_chat("I really like Palanthath. Ath thoon ath I have earned enough money I'll retire there.");
    add_chat("The proprietor of the Inn in Palanthath ith a good friend of mine. He'th alwayth having problemth though.");
    add_chat("Hmmph. I think we're behind thchedule again.");
    add_chat("How nithe it ith travelling by thea.");
    add_chat("We better watch out for Ergothian Pirateth.");
    add_chat("I wish my ship was ath fine as thothe made by Thirdan the Shipwright.");

    add_ask(({"palanthas","inn","proprietor"}),"say I know Leiden thince we both were kids! Just go and ask him for a job.",1);

    set_cchat_time(11);
    add_cchat("Thtop it, you pethtering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylightth out of you!");
    add_cchat("Right! I'm really gonna thtump you thith time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna thmack you so hard....");

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
        "You feel this man is under strong protection.\n");

    set_ticket(TICKET);
    set_price(PRICE);

}    

string
query_my_title()
{
    return "the Broken Tongue";
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
	      "Captain Justin " + query_my_title() + ", male elf.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("justin");
    intro = 0;
}

