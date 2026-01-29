#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "../sys/defs.h"

inherit  ("/std/weapon");
inherit  ("/lib/keep");

public nomask void
create_weapon() {
  set_name("morningstar");
  set_adj("black");
  add_adj("spiked");
  set_long("This weapon consists of a heavy, spiked, iron ball connected " +
           "to a metal handle by an iron chain.  The spikes of the ball " +
           "are of varying lengths, between two and five inches long, " +
           "and exceedingly sharp.  Swinging the ball at the end of the " +
           "chain, an experienced fighter can wreak havoc with this " +
           "club-like weapon.  It was forged in the pits beneath " +
           "Barad-Dur for the Dark Lord's armies.  The handle of the " +
           "morning star shows the picture of the Red Eye with " +
           "rays of red light extending from behind its lower " +
           "hemisphere.\n");
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_IMPALE);
  set_hands(W_BOTH);
  set_hit(31);
  set_pen(38);
  add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(31, 38) + random(350) - 175);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(31, W_CLUB) +
                         random(1000) + 400);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
