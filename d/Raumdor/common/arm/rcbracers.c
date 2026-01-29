inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* charred silver bracers, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_adj("charred");
    add_adj("silver");
    set_short("charred silver bracers");
    set_long("These arm bracers look filthy. They are charred, dented "+
    "and scratched. However, they still look usable, and are made of "+
    "some fine silver steel. Etched on each piece is a symbol of a golden "+
    "sun with rays.\n");
    set_ac(30);
    set_at(A_ARMS);
    set_am(({-1,2,0}));
    add_prop(OBJ_I_WEIGHT,5500);
    add_prop(OBJ_I_VOLUME,4600);
    add_prop(OBJ_I_VALUE,55);
}
