inherit "/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    set_name("boots");
    add_adj("black");
    set_adj("suede");
    set_short("pair of black suede boots");
    set_pshort("pairs of black suede boots");
    set_long("These boots are made of soft suede, black in color. "+
    "They look sturdy, since they have strong leather soles. "+
    "They come up all the way to your calves.\n");
    set_at(A_FEET);
    set_ac(3);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_VALUE,100);
}
