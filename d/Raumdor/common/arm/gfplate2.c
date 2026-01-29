/* Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("breastplate");
    set_adj("black");
    add_adj("steel");
    set_short("black steel breastplate");
    set_long(
      "A finely crafted piece of armour mainly protecting the chest. It is " +
      "made of fine blackened steel. It is quite impressive.\n");
    set_ac(25);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 8600);
    add_prop(OBJ_I_VALUE, 520);
}
