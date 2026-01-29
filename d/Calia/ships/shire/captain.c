
/* 
 *  Ship captain for the Shire shipline that runs from Calia. 
 */

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
    set_name("sutec");
    add_name("captain");
    add_name("_sutec_");
    set_race_name("human");
    add_adj("tall");
    add_adj("muscular");
    set_stats(({ 60, 60, 60, 65, 82, 120}));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 75); 
    heal_hp(10000);
    set_chat_time(15);
    add_chat("Hmmm...maybe we're in for a storm later.");
    add_chat("Have you seen the mermaid?");
    add_chat("What a lovely day for a swim!");
    add_chat("I hear there is a great sea serpent off the shores of Calia!");
    add_chat("I think I should lay off the bottle.  I thought I just " +
             "saw a mermaid!");

    set_act_time(15);
    add_act("emote pulls out a spy glass and looks out to sea.",0);
    add_act("emote whistles a little sea ditty.", 0);
    add_act("emote looks at the sky with a weather eye.",0);
    add_act("emote drinks from a large bottle of rum.",0);

    add_prop(OBJ_M_NO_ATTACK,
          "The Elementals of Calia will not allow you to attack "+
          "this captain.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 
          "The Elementals of Calia will not allow you to attack "+
          "this captain.\n");
    set_ticket(TICKET);
    set_price(PRICE);
}

string
query_my_title()
{
        return "the Legendary Sea-serpent Slayer";
}

void
add_introduced(string who)
{
    set_alarm(2.0, 0.0, &command("introduce me"));
}

