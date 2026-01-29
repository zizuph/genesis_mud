/* Sarr */
#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("shield");
    set_adj("steel");
    add_adj("black");
    set_short("black steel shield");
    set_long(
      "This shield is made of strong blackened steel. It looks rather large. " +
      "On the front, you see a painting of a grim looking skull.\n");
    set_ac(15);
    set_at(A_SHIELD);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_VALUE, 250);
}
