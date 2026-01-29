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
    set_name("donnovan");
    add_name("captain");
    set_race_name("human");
    add_adj("swarthy");
    set_adj("grey-bearded");
    set_long("This man has been hired by the Green Dragonarmy to transport "+
      "troops across the Bay of Balifor.  He is middle-aged and looks to "+
      "have been a pirate prior to his current employment.\n");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);

    set_chat_time(36);
    add_chat("The fresh sea air calms my spirit.");
    add_chat("I can't stand the way my ship smells after transporting "+
      "those filthy draconians.");

    set_act_time(30);
    add_act("emote breathes deeply of the salty sea air.");
    add_act("emote orders a deck hand around.");

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
      "You feel this captain is under strong protection.\n");

    set_ticket(TICKET);
    set_price(PRICE);

    add_notify_meet_interactive("no_grimoire");
}    

string
query_my_title()
{
    return " the master of the Deringer";
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
      "Captain Donnovan the master of the Deringer, male human.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("donnovan");
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
