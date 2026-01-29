/* Captain for the walnut ship from Gelan to Krynn */

#pragma save_binary

inherit "/d/Genesis/ship/captain";
#include "ship.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

object ship;

int
set_ship(object s)
{
	ship = s;
}

void
create_monster()
{
    set_name("wandle");
    add_name("captain");
    set_race_name("human");
    add_adj("tubby");
    add_adj("bearded");
    set_title("the Unseaworthy");
    set_stats(({ 60, 60, 60, 65, 82, 120}));
    set_skill(SS_SWIM, 50);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 75);
    heal_hp(10000);

    set_act_time(6);
    add_act("say It's a tough life at sea on a walnut.");
    add_act("say Yo ho ho and my bottle's empty, damn it.");
    add_act("say At least the weather's holding up.");
    add_act("emote looks decidedly queasy.");
    add_act("emote tries to whistle a little sea ditty to calm his " +
           "stomach.");
    add_act("emote doubles over and pukes. You " +
            "wonder if this guy's in the right profession.");

    add_prop(OBJ_M_NO_ATTACK, "The Elementals of Calia will " +
           "not allow you to attack this captain.\n"); 

    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The Elementals of Calia will " +
           "not allow you to attack this captain.\n"); 

    set_ticket(TICKET);
    set_price(PRICE);
}


int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
	notify_fail("Nahh...little shrimps travel for free! "+
		"You don't need any ticket.\n");
	return 0;
    }

    return ::buy(str);
}


void
add_introduced(string who)
{
      set_alarm(2.0, 0.0, &command("introduce me"));
}

