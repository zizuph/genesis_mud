#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    set_name("ring");
    set_adj(({"wide", "gold"}));
    set_short("wide gold ring");
    set_long(
      "Smooth and beautiful, this gold ring is wide and bears a symbol.\n");
    add_item("symbol",
      "It's an arc, with several lines surrounding it on one side.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_I_VALUE, GOLD_VALUE * 3);
    set_ac(1);
    set_at(A_ANY_FINGER);
}
