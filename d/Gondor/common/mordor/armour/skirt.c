#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../sys/defs.h"

inherit  ("/std/armour");
inherit  ("/lib/keep");

public nomask void
create_armour() {
  set_name("skirt");
  set_adj("black");
  add_adj("mail");
  set_long("This armour was forged in the pits beneath " +
           "Barad-Dur for the armies of the Dark Lord.  " +
           "Wide, leather thongs hang to just below knee-length " +
           "from a wide belt, and are studded with iron studs " +
           "and rings affording some protection for the legs.\n");
  set_at(A_LEGS);
  set_ac(20);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) + random(250) - 125);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS) +
                         random(400) - 200);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
