inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>

#define ENV(xxx) environment(xxx)

int intro = 0;

/*
* Prototypes
*/
void grimoire_found(mixed ob);

void
create_monster()
{
    set_name("bermort");
    add_name("captain");
    set_race_name("human");
    set_adj("bored");
    add_adj("unshaven");
    set_long("This bored unshaven human is the ferry master " +
      "who takes passengers and cargo up and down the Vingaard " +
      "River.\n");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);

    set_chat_time(8);
    add_chat("I get so bored going up and down the river.");
    add_chat("Draconians never bother my boat for some strange reason.");
    add_chat("I noticed the Brightblade castle is in " +
      "ruins. Times are truly dark at the moment.");
    add_chat("I hear hill dwarf clans are gathering on the plains of Estwilde.");
    add_chat("Nightlund is an evil place now, with Lord Soth and his " +
      "undead minions terrorizing the area.");

    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
      "The ferry master is not worthy of your attention.\n");

    set_ticket(TICKET);
    set_price(PRICE);

    add_notify_meet_interactive("no_grimoire");
}    

string
query_my_title()
{
    return "the Ferry Master";
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
      "Bermort the Ferry Master, male human.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("bermort");
    intro = 0;
}


void
no_grimoire()
{
    object *players;
    object *obs;
    int i;
    int j;
    int gAlarm_time;

    gAlarm_time = 4;
    players = FILTER_LIVE(all_inventory(ENV(TO)));

    for (i = 1; i < sizeof(players); i++)
    {
	obs = deep_inventory(players[i]);

	for (j = 1; j < sizeof(obs); j++)
	{
	    if (obs[j]->id("refnasgrim"))
	    {
		obs[j]->remove_object();
		set_alarm(gAlarm_time, 0.0, &grimoire_found(players[i]));
		gAlarm_time +=2;
	    }
	}
    }

    return;
}


void
grimoire_found(mixed ob)
{
    command("shout I don't want such dangerous things on my ship!");
    command("shout Give me that.");
    ob->catch_msg(" takes your grimoire.\n");
    tell_room(ENV(TO), "The captain takes something from " + QTNAME(ob) +
      ".\n", ob);

    return;
}
