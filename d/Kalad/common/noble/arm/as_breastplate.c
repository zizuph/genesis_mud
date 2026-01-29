inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("breastplate");
    add_name("plate");
    set_adj("ancient");
    add_adj("steel");
    set_short("ancient steel breastplate");
    set_long("This is a heavy piece of armour made of a solid steel plate. "+
    "It looks very ancient, as if it was passed down through many generations "+
    "of people. Some of the symbols date back many hundreds of years.\n");
    set_ac(40);     
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,9600);
    add_prop(OBJ_I_VOLUME,8000);
}

