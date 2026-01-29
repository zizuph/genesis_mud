#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "../sys/defs.h"

inherit  ("/std/weapon");
inherit  ("/lib/keep");

public nomask void
create_weapon() {
  set_name("mace");
  set_adj("black");
  add_adj("spiked");
  set_long("Forged in the pits beneath Barad-Dur for the Dark Lord's " +
           "armies, this weapon is fashioned of steel, inset with " +
           "short, sharp spikes which are of varying lengths, " +
           "between one and three inches long.  The black, wood handle " +
           "of the mace shows the picture of the Red Eye with rays of " +
           "red light extending from behind its lower hemisphere.\n");
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_IMPALE);
  set_hands(W_BOTH);
  set_hit(30);
  set_pen(22);
  add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(30, 22) + random(250) - 125);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(31, W_CLUB) +
                         random(800) + 400);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
