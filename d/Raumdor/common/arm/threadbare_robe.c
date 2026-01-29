/* 2018.03.22 (Shanoga) */

#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_short("threadbare robe");
    set_long("These rags must be centuries old. The shredded robe has " +
      "faded to grey, losing any semblance of its original colour " +
      "or pattern. Time and exposure to the elements have rendered it " +
      "nearly useless.\n");
    set_default_armour(3, A_ROBE, ({-2, -2, 2}), 0);
    add_prop(OBJ_I_WEIGHT, 850);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}
