
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>


#define DAB_HARB    DABAAY_DIR + "harbor/"
#define HUNTING_TREVIN "_i_hunting_trevin"

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

public void
create_monster()
{
    set_name("harlan");
    add_name("captain");
    set_living_name("harlan");
    set_race_name("human");
    add_adj("cold");
    add_adj("hardened");
    set_title("the grumpy one");
    add_ask("tall wiry male human", reply_assassin, 1);

    seteuid(getuid());
    MONEY_MAKE_CC(random(20) + 10)->move(this_object());

    add_prop(OBJ_M_NO_ATTACK,
      "You attempt to attack the human, but realize that it may " +
      "strand a friend, and stop.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK,
      "You attempt to attack the human, but realize that it may " +
      "strand a friend, and stop.\n");
    add_prop(NPC_I_NO_LOOKS, 1);


    add_ask("destination","@@query_destination",1);

    set_ticket(SHIP_DIR + "n_ticket");
    set_price(75);
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

public string
query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == (NPORT_DIR + "pier1"))
    {
        return ("say Our course be for Last, pier 1.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == (DAB_HARB + "npier 2"))
    {
        return ("say We be bound for Dabaay pier 2.");
    }
    else return ("say I ferry passengers between Dabaay and " +
          "Last.");
}

