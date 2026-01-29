 /* /d/Cirath/ships/drakmere/captain.c
  * The captain of the tyr-drakmere line.
  * Decius, July 1997
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
  set_name("petyr");
  add_name("captain");
  add_name("merchant");
  set_race_name("human");
  add_adj("short");
  add_adj("well-dressed");

  set_long("This rather small man seems almost lost inside his "+
           "oversized clothing.  Dressed colourfly in the finest "+
           "silk fashions and covered head to toe in lavish "+
           "jewelry, he seems to be a man obsessed with displaying "+
           "a lifestyle of opulence. That he dares do so in this "+
           "dangerous land is an impressive show of bravado, or "+
           "insanity.\n"+
           "He is wearing a purple silk shirt, a bright yellow \n"+
	   "silk jacket, blue silk pants, several gold rings, and "+
           "a gold necklace studded with diamonds.\n");

  

  set_title(", Merchant Traveller of Tyr");
  set_stats(({100,100,100,100,100,100}));
  set_skill(SS_AWARENESS,50);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_UNARM_COMBAT, 50);
  heal_hp(10000);

  set_act_time(20);

  add_act("fidget");
  add_act("yawn");
  add_act("emote converses quietly with a well-dressed passenger.");
  add_act("ponder");
  add_act("emote whispers brief instructions to a liveried servant.");
  add_act("emote straightens his jacket.");
  

  add_prop(OBJ_M_NO_ATTACK, "That would be a bad idea.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK, "That would be a bad idea.\n");
  

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

