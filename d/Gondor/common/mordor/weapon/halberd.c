#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "../sys/defs.h"

inherit  ("/std/weapon");
inherit  ("/lib/keep");

public nomask void
create_weapon() {
  set_name("halberd");
  set_adj("large");
  add_adj("steel");
  set_long("This is a large, steel halberd with a pole made out " +
           "of hard, black wood, forged in the pits beneath " +
           "Barad-Dur for the Dark Lord's armies.  The weapon " +
           "has two blades, the larger one formed like an axe " +
           "and the smaller one tapers to a sharp point.  The " +
           "top of the wooden pole is capped with a steel " +
           "spear-head, allowing the weapon the be utilized as " +
           "a spear.  Etched into the steel blade is the figure " +
           "of the Red Eye with rays of red light extending " +
           "from behind its lower hemisphere.\n");
  set_wt(W_POLEARM);
  set_dt(W_IMPALE | W_SLASH | W_BLUDGEON);
  set_hands(W_BOTH);
  set_hit(28);
  set_pen(40);
  add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(28, 40) + random(400) - 200);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(28, W_POLEARM) +
                         random(500) + 1000);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
