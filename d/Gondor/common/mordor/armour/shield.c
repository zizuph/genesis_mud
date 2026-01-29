#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../sys/defs.h"

inherit  ("/std/armour");
inherit  ("/lib/keep");

public nomask void
create_armour() {
  set_name("shield");
  set_adj("black");
  add_adj("steel");
  set_short("black steel shield of the Red-Eye");
  set_pshort("black steel shields of the Red-Eye");
  set_long("This black shield was forged in the pits beneath " +
           "Barad-Dur for the armies of the Dark Lord.  " +
           "Circumferenced by a steel rim and crossbars, it is " +
           "backed by a sheet of iron overlaid upon black, hard " +
           "wood with leather straps for the bearer's arm.  " +
           "It is emblazoned with a large, iron insigia of the " +
           "Red Eye with rays of red light extending from " +
           "behind its lower hemisphere, which can be clearly " +
           "seen at a good distance.\n");
  set_at(A_SHIELD);
  set_ac(28);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(28) + random(500) - 250);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(28, A_SHIELD) +
                         random(1000) - 500);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
  add_prop(MORDOR_M_NO_SELL, 1);
}
