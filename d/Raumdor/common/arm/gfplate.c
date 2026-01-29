/* Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("fullplate");
    set_adj("black");
    add_adj("steel");
    set_short("black steel fullplate");
    set_long(
      "A finely crafted piece of armour of interlocking torso and head " +
      "pieces. It is made of fine blackened steel, with chain links. It is " +
      "quite impressive.\n");
    set_ac(20);
    set_at(A_CHEST | A_HEAD);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 8600);
    add_prop(OBJ_I_VALUE, 520);
}
