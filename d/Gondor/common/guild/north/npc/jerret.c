#pragma strict_types

inherit "/d/Gondor/common/npc/npc_ranger.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_ranger() 
{
    set_living_name("jerret");
    set_name("jerret");
    add_name(({"shopkeeper","owner","shopowner"}));
    set_race_name("human");
    set_adj("tall");
    add_adj("stern-faced");
    set_title("the shopkeeper");
    set_company("the North");
    set_long(BS("This is Jerret, the shopkeeper. He watches you closely, "+
    "so you do not get the chance to steal anything. "+
    "Besides that, he leaves you on your "+
    "own to check out the stuff that is lying around.\n"));
    default_config_npc(52);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_TRADING, 55);
    set_alignment(600+random(200));
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("My name is Jerret.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy some excellent equipment?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");
}

public void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(EDORAS_DIR + "obj/broadsword")->move(TO);
    command("wield sword");
    clone_object(EDORAS_DIR + "obj/leather")->move(TO);
    command("wear armour");
}

/* solamnian prestige */
int query_knight_prestige() {return (-5);}

varargs string
introduce(object player)
{
  if(!objectp(player) || !interactive(player))
    return "";

  if(!present(player,ENV(TO)))
    return "";

  command("hail " + player->query_real_name());
  command("present me");
  return "";

}
