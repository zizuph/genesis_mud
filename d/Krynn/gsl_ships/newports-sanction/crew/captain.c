/*
 * Revision history:
 * 25 Feb 2000, by Boron added support for the war, if the Knights hold the
 *                  other side, we are staying here! :)
 */
inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>
#include "/d/Krynn/common/warfare/warfare.h"

#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/admin/admin.h"

#define ENV(xxx)        environment(xxx)

int intro = 0;

void
create_monster()
{
    set_name("captain");
    set_race_name("human");
    add_adj("tall");
    set_adj("dark-haired");
    set_long("This man is the captain of the troop ferry between Sanction " +
    "and Newports.\n");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);

    set_chat_time(9);
    add_chat("Get a move on! We don't have all day!");
    add_chat("There will be no trouble on my ship.");
    add_chat("Goblins are the worst things to carry onboard. You never " +
        "get the smell out.");
    add_chat("Knights?! Ha! Corruption sleeps in Solamnia... They are no better than us.");

    set_act_time(16);
    add_act("smirk all");
    add_act("emote studies you appraisingly.");

    add_prop(OBJ_M_NO_ATTACK,
      "You feel this captain is under strong protection.\n");

    set_ticket(TICKET);
}


int
buy(string str)
{
	set_price(PRICE);

    if (GUILD_ADMIN->query_priest_has_punishment(this_player()->query_real_name(),
        P_TRAVEL_RESTRICTED) == 1)
    {
        notify_fail("The captain looks at you and gets something wild " +
            "in his eyes as he refuses to have anything to do with you.\n");
        return 0;
    }

/*
    if (ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == KNIGHT_ARMY)
    {
        if (find_object(PIER) == environment(this_player()) )
        {
            command("shout I'm not risking this transport!");
            command("say As long as the Knights hold Newports, I'm staying here!");
            return 1;
        }
        else
        {
            command("say Hurry we need to get out of this place!");
		}
    }
    else if (! ARMYMASTER->correct_army(WAR_AREA_NEWPORT, ARMYMASTER->army_of_player(TP) ) )
    {
		command("spit " + TP->query_real_name() );
		command("say You think I'll take you?");
		command("grumble");
		command("say Oh well but its gonna cost you! I'm not gonna risk arrest and whatever for free!");

		set_price(PRICE * 100);
	}
*/


    if (this_player()->query_average_stat() < 20)
    {
        notify_fail(query_The_name(TP) + " grumbles: " +
        "You don't need to buy any ticket. " +
        "Young ones like you travel for free.\n");
    return 0;
    }


    return ::buy(str);
}

void
introduce_me(string name)
{
    intro = 0;
    if (P(lower_case(name),E(TO)))
    {
        command("say So you are " + C(name) + "? Who cares?");
    }
}

void
add_introduced(string name)
{
    if (intro)
        return;
    intro = set_alarm(2.0,0.0,&introduce_me(name));
}
