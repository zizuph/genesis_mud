inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

void
create_monster()
{
   set_name("prisoner");
   set_race_name("dwarf");
   set_adj("skinny");
   set_adj("aggitated");
   set_short("skinny aggitated prisoner");
   set_long("This prisoner looks "+
      "like he's been here a while. He looks concerned.\n");
   set_stats(({60,55,55,43,48,57}));
   set_hp(TO->query_max_hp());
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 35);
   MONEY_MAKE_CC(100 + random(400))->move(TO);
   set_chat_time(9);
   add_chat("Where is that guard with my food!?");
   add_chat("They give me money to keep me quiet.");
   add_chat("I know they don't like me cause im a dwarf, "+
      "but i don't care.");
   add_chat("I know what kind of things go on around here.");
   seteuid(getuid(this_object()));
}
