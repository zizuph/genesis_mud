inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name("tunic");
    set_adj("linen");
    set_short("linen tunic");
    set_long("A white linen tunic belted with a brown sash.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
