#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDCAPTAIN;

#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/admin/admin.h"

int intro = 0;

void
create_captain()
{
  ::create_captain();
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
      intro = set_alarm(1.0,0.0,"introduce_me");
}

void
introduce_me()
{
    tell_room(ENVX(TO),QCTNAME(TO) + " introduces himself as:\n" +
      "Captain Ogel the master of the Raven, male hobgoblin.\n");
    FILTER_LIVE(all_inventory(ENVX(TO)))->add_introduced("ogel");
    intro = 0;
}

