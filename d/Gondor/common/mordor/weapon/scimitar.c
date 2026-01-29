#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "../sys/defs.h"

inherit  ("/std/weapon");
inherit  ("/lib/keep");

public nomask void
create_weapon() {
  set_name("scimitar");
  set_adj("wicked");
  add_adj("curved");
  set_long("This is a broad, curved scimitar of steel with a handle " +
           "made out of hard black wood.  It was forged in the pits " +
           "beneath Barad-Dur for the Dark Lord's armies.  Etched " +
           "into the steel blade is the figure of the Red Eye " +
           "with rays of red light extending from behind its " +
           "lower hemisphere.\n");
  set_wt(W_SWORD);
  set_dt(W_SLASH);
  set_hands(W_ANYH);
  set_hit(36);
  set_pen(24);
  add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(36, 24) + random(300) - 150);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(24, W_SWORD) +
                         random(400) + 400);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
