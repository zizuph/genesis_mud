  /* /d/Cirath/ships/earthsea/captain.c
  * The captain of the tyr-roke line.
  * Decius, December 1996
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
  set_name("sevet");
  add_name("captain");
  add_name("trainer");
  set_race_name("human");
  add_adj("raven-haired");
  add_adj("green-eyed");
  set_gender(1);

  set_long("This is one of Tyr's famous falconers, an elite "+
    "trainer of birds. She is rather muscular, and walks "+
    "with an attitude of supreme confidence.\n"+
    "She has scars on her left arm, right arm, "+
    "left leg, and nose.\n"+
    "She is wearing green pants, a green silk shirt, and "+
    "a black leather vest.\n"+
    "She has a tattoo of a soaring eagle on her left cheek.\n");

  set_title("the Roc Trainer of Tyr");
  set_stats(({100,100,100,100,100,100}));
  set_skill(SS_AWARENESS,50);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_UNARM_COMBAT, 50);
  heal_hp(10000);

  set_act_time(10);

  add_act("say Rocs are fearsome carnivores, do not stand "+
    "within reach of it's beak.");
  add_act("say We falconers are favored by Kalak.");
  add_act("emote smiles proudly.");
  add_act("say It took many hard months to train this roc"+
    " yet still, one slip and ....");
  add_act("emote pats the roc gently.");
  add_act("emote tightens a leather strap on the roc.");

  add_prop(OBJ_M_NO_ATTACK,"You feel that would be a bad idea.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,"You feel that would be a bad "+
    "idea.\n");

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

