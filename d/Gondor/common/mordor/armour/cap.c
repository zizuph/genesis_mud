#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../sys/defs.h"

inherit  ("/std/armour");
inherit  ("/lib/keep");

public nomask void
create_armour() {
  set_name("cap");
  set_adj("black");
  add_adj("ringmail");
  add_adj("leather");
  set_short("black cap of the Red-Eye");
  set_pshort("black caps of the Red-Eye");
  set_long("This black cap was forged in the pits beneath Barad-Dur " +
           "for the armies of the Dark Lord.  It has an iron rim " +
           "and an iron cross-band over iron ringmail overlapping " +
           "black leather.  Upon the forehead piece of the armour " +
           "is emblazoned a large, iron insigia of the Red Eye " +
           "with rays of red light extending from behind its lower " +
           "hemisphere, which can be clearly seen at a good " +
           "distance.\n");
  set_at(A_HEAD);
  set_ac(16);
  set_am(({ -2, 3, -1 }));
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(16) + random(50) - 25);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(16, A_HEAD) +
                         random(200) - 100);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
  add_prop(MORDOR_M_NO_SELL, 1);
}
