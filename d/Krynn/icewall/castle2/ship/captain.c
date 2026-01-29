inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

int intro = 0;

void
create_monster()
{
    set_name("Berge");
    add_name("berge");
    add_name("captain");
    set_living_name("berge");
    set_race_name("human");
    add_adj("coarse");
    add_adj("wise");
    set_stats(({ 120, 120, 120, 120, 90, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);
    set_chat_time(9);
    add_chat("The southern seas can be rough.");
    add_chat("I have heard that the Knights of Solamnia once again defend " +
        "Palanthas.");
    add_chat("The white dragonarmy grows in power.");
    add_chat("The seas are dangerous. I have seen dragons flying high " +
        "in the air.");
    add_chat("The Ergothian pirates no longer trouble my ship... I guess " +
        "they met a gruesome end someplace.");

    add_ask(({"icerunner","ship"}),"The captain says: The ship is fine enough.\n");
    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
        "You feel that fate protects this man.\n");

    set_ticket(TICKET);
    set_price(PRICE);
}

int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
    notify_fail("The captain says: You don't need to buy any ticket. " +
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
    tell_room(E(TO),QCTNAME(TO) + " says: I have never heard of " +
        "you before... And my own name is worth nothing to you. " +
        "Just call me captain.\n");
    set_alarm(1.0,0.0,"reset_introduce");
}

void
reset_introduce()
{
    intro = 0;
}
