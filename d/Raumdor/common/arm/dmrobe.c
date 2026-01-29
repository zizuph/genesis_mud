/* by Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_short("black robe");
    set_long(
      "This is a black, torn and tattered robe of rough material. On the " +
      "back, you see the symbol of a grim skull.\n");
    set_default_armour(10, A_ROBE, 0, 0);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 200);
}
