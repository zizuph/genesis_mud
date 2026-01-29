/* Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_adj("steel-clad");
    add_adj("silvery");
    set_short("pair of steel-clad silvery boots");
    set_pshort("pairs of steel-clad silvery boots");
    set_long(
      "These boots are made of fine leather, and are rimmed with silvery steel.\n");
    set_ac(25);
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 3200);
    add_prop(OBJ_I_VALUE, 30);
}
