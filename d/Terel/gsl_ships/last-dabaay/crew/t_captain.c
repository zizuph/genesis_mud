#pragma save_binary
#pragma strict_types

#include <money.h>
#include <ss_types.h>
#include <macros.h> 
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDCAPTAIN;

public void
create_captain()
{
  int power;
  ::create_captain();

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

}
