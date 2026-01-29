#include "../defs.h"

inherit CARAVAN + "npc/lknight1";

public void
create_kalad_monster()
{
   ::create_kalad_monster();

   set_stats(({
      110+random(10), 100+random(10), 110+random(10),
      85+random(10), 85+random(10), 110+random(10)
   }));
}
