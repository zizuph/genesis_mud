#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../sys/defs.h"

inherit  ("/std/armour");
inherit  ("/lib/keep");

public nomask void
create_armour() {
  set_name("shirt");
  set_adj("black");
  add_adj("mail");
  set_long("This armour was forged in the pits beneath " +
           "Barad-Dur for the armies of the Dark Lord.  " +
           "It is made of sewn leather, of what creature " +
           "you dare not say, and is studded with iron studs " +
           "and rings, affording some protection for the " +
           "body.\n");
  set_at(A_TORSO);
  set_ac(24);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(24) + random(250) - 125);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(24, A_TORSO) +
                         random(600) - 300);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
