#include "../defs.h"

inherit CARAVAN + "npc/lknight";

public void
create_kalad_monster()
{
   ::create_kalad_monster();

   add_name("guard");

   set_stats(({
      105+random(10), 85+random(10), 105+random(10),
      80+random(10), 80+random(10), 105+random(10)
   }));
}
