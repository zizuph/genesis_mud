/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/captain";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define HUNTING_TREVIN "_i_hunting_trevin"
#define DAB_HARB    DABAAY_DIR + "harbor/"

int power;

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
           command("say Yeah, I took him north to Last lastnight.");
           command("say Stomped on board and demanded I take him to Last");
           command("say He had the gold to make it worth my while though.");
           command("say I haven't seen him since he left the ship.");
           return "";
    }
    return "";
}

public string
query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == (NPORT_DIR + "pier1"))
    {
        return ("say Dabaay harbor be our destination.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == (DAB_HARB + "npier_2"))
    {
        return ("say We be bound for Dabaay harbour in Terel.");
    }
    else return ("say I ferry passengers between Dabaay and " +
          "Sparkle.");
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */

public void
create_monster()
{
    ::create_monster();

    power = 30+random(70);
    set_name("harlan");
    add_name("captain");
    set_living_name("harlan");
    set_race_name("human");
    set_adj("cold");
    add_adj("hardened");
    set_title("the grumpy one");

    default_config_npc(power);
    heal_hp(10000);
    set_skill(SS_AWARENESS, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);

    set_ticket(SHIP_DIR + "n_ticket");
    set_price(75);
    add_ask("tall wiry male human", reply_assassin, 1);
    add_ask("destination","@@query_destination",1);
   
}

public int
buy(string str)
{
    if (this_player()->query_average_stat() < 15 )
    {
        command("say to " + OB_NAME(this_player()) + " I can only " +
          "afford to let the youngest travel for free, and you seem " +
          "to be one of them.");
        notify_fail("");
        return 0;
    }

    return ::buy(str);
}
