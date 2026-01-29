#pragma save_binary

inherit "/d/Genesis/ship/captain";
#include "ship.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

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
    set_name("cetus");
    add_name("captain");
    add_name("_cetus_");
    set_race_name("human");
    add_adj("massive");
    add_adj("muscular");
    add_adj("sea-faring");
    set_stats(({ 60, 60, 60, 65, 82, 120}));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 70); 
    heal_hp(10000);
    set_chat_time(15);
    add_chat("Hmmm...maybe we're in for a storm later.");
    add_chat("They say the great white whale has been seen nearby.");
    add_chat("Har, matey!");


    set_act_time(15);
    add_act("emote pulls out a spy glass and looks out to sea.",0);
    add_act("emote whistles a little sea ditty.", 0);
    add_act("emote looks at the sky with a weather eye.",0);

    add_prop(OBJ_M_NO_ATTACK, "The Elementals of Calia won't let you " +
                              "attack this captain.\n"); 

    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The Elementals of Calia won't " +
                              "let you attack this captain.\n"); 
    set_ticket(TICKET);
    set_price(PRICE);
}

string
query_my_title()
{
	return "the Old Seadog";
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
    set_alarm(2.0,0.0, &command("introduce me"));
}

