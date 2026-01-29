inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* filthy silver greaves, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("filthy");
    add_adj("silver");
    set_short("filthy silver greaves");
    set_long("These pair of greaves are well-used. They have many dents, "+
    "scratches and tears. However, they are still usable. After clearing "+
    "away some of the dirt, you see on the silver-steel metal, a symbol "+
    "of a golden sun with rays.\n");
    set_ac(30);
    set_at(A_LEGS);
    set_am(({-1,2,0}));
    add_prop(OBJ_I_WEIGHT,6000);
    add_prop(OBJ_I_VOLUME,4200);
    add_prop(OBJ_I_VALUE,75);
}
