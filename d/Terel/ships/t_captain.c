
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>

int power;

public void
create_monster()
{

    power = 30+random(15);

    set_name("samlon");
    add_name("captain");
    set_living_name("samlon");
    set_race_name("human");
    add_adj("friendly");
    add_adj("robust");
    set_title("the experienced captain, son of Kamlon");

    seteuid(getuid());
    MONEY_MAKE_CC(random(20) + 10)->move(this_object());

    default_config_npc(power);
    heal_hp(10000);
    set_skill(SS_AWARENESS, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);

    add_prop(OBJ_M_NO_ATTACK,
      "You attempt to attack the human, but realize that it may " +
      "strand a friend, and stop.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK,
      "You attempt to attack the human, but realize that it may " +
      "strand a friend, and stop.\n");
    add_prop(NPC_I_NO_LOOKS, 1);

    add_ask("destination","@@query_destination",1);

    set_ticket(SHIP_DIR + "t_ticket");
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
      == ("/d/Terel/dabaay/harbor/spier_3"))
    {
        return ("say Sparkle, pier5 tis our destination.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Genesis/start/human/town/pier5"))
    {
        return ("say We be bound for Dabaay harbour in Terel.");
    }
    else return ("say I ferry passengers between Dabaay and " +
          "Sparkle.");
}

