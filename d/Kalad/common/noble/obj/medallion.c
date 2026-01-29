inherit "/std/armour";
#include "/d/Kalad/defs.h"
/* Sarr, */

void
create_armour()
{
    set_name("medallion");
    set_adj("golden");
    set_short("golden medallion");
    set_long("Hanging on a chain of solid gold, a pendant in the "+
    "shape of a cresent moon swings. There are three white pearls imbedded "+
    "in it at the center and each tip. Inscribed on the back is the name "+
    "'Hequebus'.\n");
    set_at(A_NECK);
    set_ac(1);
    add_prop(OBJ_I_WEIGHT,150);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,1000);
}

