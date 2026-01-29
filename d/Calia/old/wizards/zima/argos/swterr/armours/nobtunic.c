inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name("tunic");
    set_adj("silk");
    set_adj("purple");
    set_short("silk tunic");
    set_long("It is a silk tunic dyed in purple and threaded with gold.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
