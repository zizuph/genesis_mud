/* Captain for the black ship from Gelan to Kalad.

   Coded by Maniac & Jaacar, 27/11/95
 */

#pragma save_binary

inherit "/d/Genesis/ship/captain";
#include "ship.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <const.h>

int intro = 0;

object ship;

int
set_ship(object s)
{
	ship = s;
}


void
create_monster()
{
    set_name("hadrashak");
    add_name("_hadrashak_");
    add_name("captain");
    set_race_name("daemon");
    set_gender(G_MALE);
    add_adj("massive");
    add_adj("leathery-winged");
    set_title("the Daemon Sailor");
    set_stats(({ 120, 120, 120, 120, 120, 120}));
    add_prop(NPC_I_NO_LOOKS,1);
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 100);
    heal_hp(10000);


    add_prop(OBJ_M_NO_ATTACK,
        "The captain flaps his large leathery wings as you move "+
        "towards him and you decide not to attack him.\n");

    add_prop(OBJ_M_NO_MAGIC_ATTACK, "You feel the captain is somehow "+
        "resistant to your attempt.\n");
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
add_introduced(string person)
{
    if (!intro)
      intro = set_alarm(2.0,0.0,"introduce_me");
}

void
introduce_me()
{
    command("introduce me");
    intro = 0;
}

