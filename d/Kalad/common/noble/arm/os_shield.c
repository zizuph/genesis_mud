inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("shield");
    set_adj("ornate");
    add_adj("steel");
    set_short("ornate steel shield");
    set_long("This is a very thick, heavy steel shield. It is ornately "+
    "decorated. Strong, but padded leather straps give you a good grip.\n");
    set_ac(22);     
    set_at(A_SHIELD);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2000);
}

