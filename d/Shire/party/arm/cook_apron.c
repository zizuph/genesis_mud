inherit "/std/armour";

#include <wa_types.h>
#include "/d/Shire/common/defs.h"

void
create_armour()
{
    set_name("apron");
    set_short("food-stained white apron");
    set_long("A beautiful white apron, slightly stained "+
      "by some food.\n");
    add_adj(({"white","food-stained"}));

    set_at(A_BODY);
    set_ac(3);

    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE, 100);
}
