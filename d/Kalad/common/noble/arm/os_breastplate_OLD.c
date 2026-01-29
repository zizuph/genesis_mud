inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("breastplate");
    add_name("plate");
    set_adj("ornate");
    add_adj("steel");
    set_short("ornate steel breastplate");
    set_long("This is a heavy piece of armour made of a solid steel plate. "+
      "However, your enemies are going to have a tough time getting to your "+
      "skin if you wear this. It is ornately decorated.\n");
    set_ac(40);     
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,9600);
    add_prop(OBJ_I_VOLUME,8000);
}

