inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name(({"woodsman's tunic","woodsmans tunic","tunic"}));
    set_adj("green");
     set_adj("woodsmans");
   set_short("green woodsman's tunic");
     set_long("A dark green tunic embroidered with an axe.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
