
inherit "/std/guild/guild_occ_sh.c";
#include <macros.h>
#include "/d/Calia/mountain/defs.h"
#include "/d/Calia/walkers/fire/specials/firewalker.h"

is_fire(object living)
{
    return living->query_guild_member(GUILD_NAME);
}

int
water_walk()
{
    object tp;
    int hps;
    tp = TP;

    if (!is_fire(tp))
       {
          if (tp->query_hp() < 100)
             {
                write("You feel moving would mean certain death, and "+
                   "decide to remain here.\n");
                return 1;
             }
          write("You get hurt by walking in the river!\n");
          hps = -100;
          tp->heal_hp(hps);
          return 0;
       }
       write("You walk in the river and are immune from its heat.\n");
       return 0;
}
