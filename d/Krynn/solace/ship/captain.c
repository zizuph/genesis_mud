inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

int intro = 0;

void
create_monster()
{
    set_name("cartha");
    add_name("captain");
    set_living_name("cartha");
    set_race_name("human");
    add_adj("peg-legged");
    add_adj("muscled");
    set_long("This muscled human has a peg leg. Still, his arms " +
        "are plenty strong to row a boat. He has dark features.\n");
    set_stats(({ 60, 60, 60, 160, 90, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);
    set_chat_time(9);
    add_chat("The Solace Stream is a pleasure to row on.");
    add_chat("That herbalist in Solace, Remington. What a bitter " +
        "fellow. I'm glad he's left for Haven.");
    add_chat("The White-rage River floods in spring, but I can " +
        "still handle it.");
    add_chat("I've heard the Seekers of Haven are soon to start " +
    "taking a census of the people of Solace!");
    add_chat("I wish the Qualinesti Elves would open their borders. " +
        "I would certainly row people there if I could!");
    add_chat("It is said that only ghosts inhabit the ruins of " +
        "Xak Tsaroth!");
/*
    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");
*/

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
        "The human stares you down with glaring eyes, and you " +
        "decide not to attack.\n");

    set_ticket(TICKET);
    set_price(PRICE);
}

string
query_my_title()
{
    return "Delito of Solace";
}

int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
    notify_fail("The captain says: You don't need to buy any " +
        "ticket. Youngsters like yourself travel for free.\n");
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
        "Cartha " + query_my_title() + ", male human.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("cartha");
    set_alarm(1.0,0.0,"reset_introduce");
}

void
reset_introduce()
{
    intro = 0;
}
