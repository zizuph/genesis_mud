inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* dented silver helm, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("dented");
    add_adj("silver");
    set_short("dented silver helm");
    set_long("This helm, made of silver steel, looks well used and worn. "+
    "There are many dents that mar its once smooth surface. In the center "+
    "of the helm, there is a picture of a golden sun with rays.\n");
    set_ac(30);
    set_at(A_HEAD);
    set_am(({-2,1,-2}));
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_VALUE,50);
}
