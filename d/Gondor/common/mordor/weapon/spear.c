#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "../sys/defs.h"

inherit  ("/std/weapon");
inherit  ("/lib/keep");

public nomask void
create_weapon() {
  set_name("spear");
  set_adj("short");
  add_adj("broad-headed");
  set_long("This weapon is a spear of hard, black wood of about " +
           "four feet in length.  It is tipped with a broad-headed " +
           "steel point, forged in the pits beneath Barad-Dur for the " +
           "Dark Lord's armies, which can inflict wide, stabbing " +
           "wounds at greater extension than most swords.  The " +
           "broad blade of the spear shows the picture of the Red Eye " +
           "with rays of red light extending from behind its lower " +
           "hemisphere.\n");
  set_wt(W_POLEARM);
  set_dt(W_IMPALE);
  set_hands(W_ANYH);
  set_hit(34);
  set_pen(20);
  add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(34, 20) + random(250) - 125);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(31, W_CLUB) +
                         random(400) + 300);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
