/* by Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_short("white robe");
    set_long(
      "This is a white robe, or drape, of rough material. There is a "
      +"decoration of a sword-shaped cross on its back.\n");
    set_default_armour(10, A_ROBE, 0, 0);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 200);
}
