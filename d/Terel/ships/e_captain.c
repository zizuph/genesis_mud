/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/captain";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

int power;

public string
query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Terel/dabaay/harbor/spier_1"))
    {
        return ("say Our destination be the home of the elves.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Genesis/start/elf/room/cove_3"))
    {
        return ("say We be bound for Dabaay harbour in Terel.");
    }
    else return ("say I ferry passengers between Dabaay and " +
          "the birthplace of the elves.");
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

    set_name("graygo");
    set_title("the newbie captain and hater of elves");
    add_name("captain");
    set_living_name("graygo");
    set_race_name("human");
    set_adj("grumpy");
    add_adj("stout");

    default_config_npc(power);
    heal_hp(10000);
    set_skill(SS_AWARENESS, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);

    set_ticket(SHIP_DIR + "e_ticket");
    set_price(75);

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
