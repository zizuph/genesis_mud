/* Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("steel-plated");
    add_adj("black");
    set_short("pair of black steel-plated gloves");
    set_pshort("pairs of black steel-plated gloves");
    set_long(
      "These black leather gloves are plated with blackened steel around the " +
      "tops of the fingers, knuckles and up to the wrist. Although very " +
      "dense, they are quite flexible.\n");
    set_ac(25);
    set_at(A_HANDS);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_VALUE, 30);
}
