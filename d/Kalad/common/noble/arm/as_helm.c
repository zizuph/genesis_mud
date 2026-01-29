inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("ancient");
    add_adj("steel");
    set_short("ancient steel helm");
    set_long("This is a very old looking helm. It is covered with "+
    "symbols that date many hundreds of years back. It looks well-"+
    "made, however.\n");
    set_ac(28); 
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2200);
}

