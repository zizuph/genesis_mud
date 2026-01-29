#include "../defs.h"

inherit CARAVAN + "npc/lknight2";

public void
create_kalad_monster()
{
   ::create_kalad_monster();

   set_stats(({
      120+random(10), 110+random(10), 120+random(10),
      85+random(10), 85+random(10), 120+random(10)
   }));
}
