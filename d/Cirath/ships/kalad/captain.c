 /* /d/Cirath/ships/kalad/captain.c
  * The captain of the tyr-kalad line.
  * Decius, November 1996
  */

#pragma save_binary
#pragma strict_types

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
  set_name("kokor");
  add_name("captain");
  set_race_name("human");
  add_adj("tall");
  add_adj("quiet");

  set_long("This tall human has a quiet demeanor, yet "+
    "carries an aura of authority. He seems to be used "+
    "to having his orders acted upon with dispatch.\n"+
    "He has scars on his right arm and forehead.\n"+
    "He is wearing a brown silk vest, black pants, and "+
    "brown leather boots.\n"+
    "His hair is short, black and straight.\n"+
    "He has a tattoo of a nightmare beast on his right "+
    "hand.\n");
  set_title("the independent caravan master");
  set_stats(({100,100,100,100,100,100}));
  set_skill(SS_AWARENESS,50);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_UNARM_COMBAT, 50);
  heal_hp(10000);

  set_act_time(20);

  add_act("emote whispers something to a guard.");
  add_act("emote studies his map.");
  add_act("emote drinks from a waterskin.");
  add_act("emote looks around warily.");
  add_act("emote watches you intently.");

  add_prop(OBJ_M_NO_ATTACK, "You briefly consider attacking the "+
      "caravan master, then you look at the heavily armed guards.\n"+
      "Hmm... maybe that's not a good idea...\n");
  
  add_prop(OBJ_M_NO_MAGIC_ATTACK, "You briefly consider attacking the "+
      "caravan master, then you look at the heavily armed guards.\n"+
      "Hmm... maybe that's not a good idea...\n");

  set_ticket(TICKET);
  set_price(PRICE);
}

int
buy(string str)
{
  if (this_player()->query_average_stat() < 20)
  {
    notify_fail("Little ones travel for free... You don't need a "+
        "ticket.\n");
    return 0;
  }

return ::buy(str);
}

void
add_introduced(string who)
{
  set_alarm(2.0,0.0, &command("introduce me"));
}

