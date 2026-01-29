 

inherit "/d/Genesis/ship/captain";

#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>

int intro = 0;

void
create_monster()
{
    set_name("Ephrim");
    add_name("captain");
    add_name("ferryman");
    set_race_name("human");
    add_adj("chortling");
    set_adj("old");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    /*
    set_chat_time(9);
    
    add_chat("My minotaurs work hard.");
    add_chat("How nice it is travelling by sea.");
    add_chat("I really like Palanthas. As soon as I have earned enough money I'll retire there.");
    add_chat("The proprietor of the Inn in Palanthas is a good friend of mine. He's always having problems though.");
    */

    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    /*add_prop(OBJ_M_NO_ATTACK,
        "You feel this man is under strong protection.\n");
	*/
    set_ticket(TICKET);
    set_price(PRICE);
}    

string
query_my_title()
{
    return "the Vingaard River ferryman";
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
go_home()
{
    TO->move_living("home",TDIR + "ferryman_hut");
    TO->command("emote enters the hut.");
    set_alarm(0.1,0.0,remove_object);
}
