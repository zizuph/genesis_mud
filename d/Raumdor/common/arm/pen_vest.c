inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("vest");
    set_adj("black");
    add_adj("leather");
    set_short("black leather vest");
    set_long("This vest is made of blackened leather. It appears strong "+
    "and well made.\n");
    set_at(A_TORSO);
    set_ac(30);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,350);
}
