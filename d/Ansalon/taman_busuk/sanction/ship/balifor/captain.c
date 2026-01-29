inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>

#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/admin/admin.h"

#define ENV(xxx) environment(xxx)

int intro = 0;

/*
* Prototypes
*/
void grimoire_found(mixed ob);

void
create_monster()
{
    set_name("ogel");
    add_name("captain");
    set_race_name("hobgoblin");
    add_adj("short");
    set_adj("mean-tempered");
    set_long("This hobgoblin is the unlikely captain of the ship. Dirty " +
      "black hair sprouts beneath a dark cloth hat, and he has a patch " +
      "over one eye.\n");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);

    set_chat_time(9);
    add_chat("People say Sanction smells bad.. I have no idea what " +
      "they mean.");
    add_chat("There are more and more goods being brought inland " +
      "to Neraka. The troops seem to be massing there.");

    set_act_time(6);
    add_act("emote peers into the distance.");
    add_act("scratch chin");

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
    return " the master of the Raven";
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

    if (GUILD_ADMIN->query_priest_has_punishment(this_player()->query_real_name(),
        P_TRAVEL_RESTRICTED) == 1)
    {
        notify_fail("The captain looks at you and gets something wild " +
            "in his eyes as he refuses to have anything to do with you.\n");
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
      "Captain Ogel the master of the Raven, male hobgoblin.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("ogel");
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
