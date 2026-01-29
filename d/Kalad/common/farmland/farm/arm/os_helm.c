inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("ornate");
    add_adj("steel");
    set_short("ornate steel helm");
    set_long("This is a very strong looking helm made of steel. It "+
    "is very finely crafted, and ornatly decorated.\n");
    set_ac(25); 
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2200);
}

